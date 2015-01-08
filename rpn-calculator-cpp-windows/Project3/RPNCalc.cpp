#include "RPNCalc.h"

#include <cstdlib>
#include <algorithm>
#include <cmath>

//Include Used for Unit Testing Remove the coment to perform unit tests
//#include "stdafx.h"

using namespace VS_CALC;
using namespace std;

//-----------------------------------------------------------------------------
// Description: Default Constructor
//-----------------------------------------------------------------------------
CRPNCalc::CRPNCalc(bool on) :
	m_on(on),
	m_buffer(""),
	m_error(false),
	m_helpOn(true),
	m_recording(false)
{
	m_on = on;
	m_buffer = "";

	for(int i = 0; i < NUMREGS ; i++)
		m_registers[i] = 0;

	if(on)
		run();
}

//-----------------------------------------------------------------------------
// Description: Pops two numbers form the stack
//-----------------------------------------------------------------------------
bool CRPNCalc::binary_prep(double& d1, double& d2)
{
	if(m_stack.size() < 2)
		return false;
	 d2 = *(m_stack.begin());
	m_stack.pop_front();

	 d1 = *(m_stack.begin());
	m_stack.pop_front();

	return true;
}
//-----------------------------------------------------------------------------
// Description: Pops one numbers form the stack
//-----------------------------------------------------------------------------
bool CRPNCalc::unary_prep(double& d)
{
	if(m_stack.size() < 1)
		return false;
	d = *(m_stack.begin());
	m_stack.pop_front();

	return true;
}

//-----------------------------------------------------------------------------
// Description: Parses the tokens in the current input stream
//-----------------------------------------------------------------------------
void CRPNCalc::parse()
{
	string commandBuffer;
	double dbl1,dbl2;
	Token tok;
	
	while(m_instrStream >> commandBuffer)
	{
		tok = parseCurrentString(commandBuffer,&dbl1);
		if(m_recording == true) 
		{
			if(tok == tokStartRecording)
			{
				m_recording = false;
				continue;
			}
			else
			{
				m_program.push_back(commandBuffer);
				continue;
			}
		}

		switch (tok)
		{
		case VS_CALC::tokAddition:
			if(binary_prep(dbl1,dbl2))
				m_stack.push_front(dbl1 + dbl2);
			else
				m_error = true;
		break;
		case VS_CALC::tokSubstraction:
			if(binary_prep(dbl1,dbl2))
				m_stack.push_front(dbl1 - dbl2);
			else
				m_error = true;
		break;
		case VS_CALC::tokMultiplication:
			if(binary_prep(dbl1,dbl2))
				m_stack.push_front(dbl1 * dbl2);
			else
				m_error = true;
		break;
		case VS_CALC::tokDivision:
			if(binary_prep(dbl1,dbl2))
			{
				if(dbl2 != 0)
					m_stack.push_front(dbl1 / dbl2);
				else
					m_error = true;
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokAdditiveInverse:
			if(unary_prep(dbl1))
					m_stack.push_front(-dbl1);
			else
				m_error = true;
		break;
		case VS_CALC::tokExponentiation:
			if(binary_prep(dbl1,dbl2))
				m_stack.push_front(pow(dbl1, dbl2));
			else
				m_error = true;
		break;
		case VS_CALC::tokModulus:
			if(binary_prep(dbl1,dbl2))
				m_stack.push_front(fmod(dbl1,dbl2));
			else
				m_error = true;
		break;
		case VS_CALC::tokClear:
			while(m_stack.size() > 0)
				m_stack.pop_back();
		break;
		case VS_CALC::tokClearEntry:
				m_stack.pop_back();
		break;
		case VS_CALC::tokRotateStackDown:
			if(m_stack.size() > 1)
			{
				double d = *m_stack.begin();
				m_stack.pop_front();
				m_stack.push_back(d);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokRotateStackUp:
			if(m_stack.size() > 1)
			{
				double d = *(m_stack.end() - 1);
				m_stack.pop_back();
				m_stack.push_front(d);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSaveToFile:
		{
			if(m_program.size() > 0)
			{
				std::cout << "Enter filename for the saved program: ";
				string filename;
				std::getline(std::cin,filename);
				ofstream file (filename);

				if(file.is_open())
				{
					for(std::list<string>::iterator i = m_program.begin(); 
						i != m_program.end(); i++)
						file << *i << endl;
					file.close();
				}
				else
					m_error = true;
			}
			else
				m_error = true;
		}
		break;
		case VS_CALC::tokLoadFromFile:
		{
			std::cout << "Enter filename: ";
			string filename;
			std::getline(std::cin,filename);

			ifstream file (filename);
			if(file.is_open())
			{
				m_program.clear();
				string line;
				while(getline(file,line))
					m_program.push_back(line);
				file.close();
			}
			else
				m_error = true;
		}
		break;
		case VS_CALC::tokGetRegister0:
			m_stack.push_front(m_registers[0]);
		break;
		case VS_CALC::tokGetRegister1:
			m_stack.push_front(m_registers[1]);
		break;
		case VS_CALC::tokGetRegister2:
			m_stack.push_front(m_registers[2]);
		break;
		case VS_CALC::tokGetRegister3:
			m_stack.push_front(m_registers[3]);
		break;
		case VS_CALC::tokGetRegister4:
			m_stack.push_front(m_registers[4]);
		break;
		case VS_CALC::tokGetRegister5:
			m_stack.push_front(m_registers[5]);
		break;
		case VS_CALC::tokGetRegister6:
			m_stack.push_front(m_registers[6]);
		break;
		case VS_CALC::tokGetRegister7:
			m_stack.push_front(m_registers[7]);
		break;
		case VS_CALC::tokGetRegister8:
			m_stack.push_front(m_registers[8]);
		break;
		case VS_CALC::tokGetRegister9:
			m_stack.push_front(m_registers[9]);
		break;
		case VS_CALC::tokToggleHelp:
			m_helpOn = !m_helpOn;
		break;
		case VS_CALC::tokStartRecording:
			if(m_recording == false)
			{
				m_program.clear();
				m_recording = true;
			}
		break;
		case VS_CALC::tokRunStoredProgram:
			while(m_program.size() > 0)
			{
				m_buffer = *m_program.begin();
				m_program.pop_front();
				m_instrStream.str(m_buffer);
				m_instrStream.clear();
				parse();
			}
		break;
		case VS_CALC::tokSetRegister0:
			if(unary_prep(dbl1))
			{
				m_registers[0] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSetRegister1:
			if(unary_prep(dbl1))
			{
				m_registers[1] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSetRegister2:
			if(unary_prep(dbl1))
			{
				m_registers[2] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
			break;
		case VS_CALC::tokSetRegister3:
			if(unary_prep(dbl1))
			{
				m_registers[3] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSetRegister4:
			if(unary_prep(dbl1))
			{
				m_registers[4] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSetRegister5:
			if(unary_prep(dbl1))
			{
				m_registers[5] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSetRegister6:
			if(unary_prep(dbl1))
			{
				m_registers[6] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSetRegister7:
			if(unary_prep(dbl1))
			{
				m_registers[7] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSetRegister8:
			if(unary_prep(dbl1))
			{
				m_registers[8] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokSetRegister9:
			if(unary_prep(dbl1))
			{
				m_registers[9] = dbl1;
				m_stack.push_front(dbl1);
			}
			else
				m_error = true;
		break;
		case VS_CALC::tokOperand:
			m_stack.push_front(dbl1);
		break;
		case VS_CALC::tokInvalidToken:
			m_error = true;
		break;
		case VS_CALC::tokExit:
			m_on = false;
		break;
		default:
		break;
		}
	}
}

//-----------------------------------------------------------------------------
// Description: Gets a line from an imput stream and parses it
//-----------------------------------------------------------------------------
void CRPNCalc::input(istream& istr)
{
	std::getline(istr,m_buffer);
	m_instrStream.str(m_buffer);
	m_instrStream.clear();
	parse();
}

//-----------------------------------------------------------------------------
// Description: Calls print and input if calc is on
//-----------------------------------------------------------------------------
void CRPNCalc::run()
{
	while(m_on)
	{
		print(std::cout);
		input(std::cin);
	}
}

//-----------------------------------------------------------------------------
// Description: Prints the calculator, the stack, and error messages (if any)
//-----------------------------------------------------------------------------
void CRPNCalc::print(ostream& ostr)
{
	system("cls");

	ostr << "RPN Programable Calculator by Vladimir Sanchez" << endl << endl;
	if(m_helpOn == true)
		ostr << helpMenu;
	ostr << line;

	if(m_error)
	{
		ostr << "<<ERROR>>";
		ostr << endl << endl << endl;
		m_error = false;
	}
	else 
	{
		if(m_stack.size() > 0)
		ostr << *(m_stack.begin());

		ostr << endl << endl << endl;

		if(m_recording)
			ostr << "Program Line " << m_program.size() << ":";
	}
}

//-----------------------------------------------------------------------------
// Description: Parses a string into a Token
//-----------------------------------------------------------------------------
Token CRPNCalc::parseCurrentString(string command,double* operand)
{
	std::transform(command.begin(),command.end(),
		command.begin(), ::toupper);

	std::string::iterator end_pos = 
		std::remove(command.begin(), command.end(), ' ');
	command.erase(end_pos, command.end());

	if(command == "")
		return tokEmpty;

	if(command == "+")
		return tokAddition;
	if(command == "-")
		return tokSubstraction;
	if(command == "*")
		return tokMultiplication;
	if(command == "/")
		return tokDivision;

	if(command == "^")
		return tokExponentiation;
	if(command == "%")
		return tokModulus;

	if(command == "C")
		return tokClear;
	if(command == "CE")
		return tokClearEntry;

	if(command == "D")
		return tokRotateStackDown;;

	if(command == "F")
		return tokSaveToFile;

	if(command == "G0")
		return tokGetRegister0;
	if(command == "G1")
		return tokGetRegister1;
	if(command == "G2")
		return tokGetRegister2;
	if(command == "G3")
		return tokGetRegister3;
	if(command == "G4")
		return tokGetRegister4;
	if(command == "G5")
		return tokGetRegister5;
	if(command == "G6")
		return tokGetRegister6;
	if(command == "G7")
		return tokGetRegister7;
	if(command == "G8")
		return tokGetRegister8;
	if(command == "G9")
		return tokGetRegister9;

	if(command == "H")
		return tokToggleHelp;

	if(command == "L")
		return tokLoadFromFile;
	if(command == "M")
		return tokAdditiveInverse;
	if(command == "P")
		return tokStartRecording;

	if(command == "R")
		return tokRunStoredProgram;

	if(command == "S0")
		return tokSetRegister0;
	if(command == "S1")
		return tokSetRegister1;
	if(command == "S2")
		return tokSetRegister2;
	if(command == "S3")
		return tokSetRegister3;
	if(command == "S4")
		return tokSetRegister4;
	if(command == "S5")
		return tokSetRegister5;
	if(command == "S6")
		return tokSetRegister6;
	if(command == "S7")
		return tokSetRegister7;
	if(command == "S8")
		return tokSetRegister8;
	if(command == "S9")
		return tokSetRegister9;

	if(command == "U")
		return tokRotateStackUp;

	if(command == "X")
		return tokExit;

	double dbl = 0;
	std::stringstream sstream(command);

	sstream >> dbl;
	if(!sstream.fail() && sstream.eof())
	{
		*operand = dbl;
		return tokOperand;
	}

	return tokInvalidToken;
}

//-----------------------------------------------------------------------------
// Description: Prints The Calculator Status
//-----------------------------------------------------------------------------
ostream &operator <<(ostream &ostr, CRPNCalc &calc)
{
	calc.print(ostr);
	return ostr;
}

//-----------------------------------------------------------------------------
// Description: Gets input for the calculator
//-----------------------------------------------------------------------------
istream &operator >>(istream &istr, CRPNCalc &calc)
{
	calc.input(istr);
	return istr;
}