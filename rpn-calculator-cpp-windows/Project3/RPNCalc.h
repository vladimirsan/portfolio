/*
CS 133 -- Third Project
Reverse Polish Notation Calculator.

----Description----
This console calculator uses post-fix notation instead of in-fix notation--that is, 
operations are written after the numbers operated on. For example, in in-fix notation, 
adding two numbers, then subtracting a third number might be written as "4 + 5 - 6". 
In post-fix notation, the same expression could be written as " 4 5 + 6 -" or " 4 5 6 - +".

----Comments----
Unit Test wasn’t a requirement for these series of C++ classes, however, I decided to learn 
and use Microsoft’s C++ Unit Testing Framework. 

In addition, I decided to use a token system in order to parse the commands. One function is 
dedicated to parsing the input and returning a tokenized representation of it, and another 
function process the token and handles the arithmetic and logic operations.
*/
#ifndef RPNCALC_H
#define RPNCALC_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <new>
#include <sstream>
#include <stack>

using namespace std;

namespace VS_CALC
{

const char helpMenu[] = 
"C clear stack   | CE clear entry  | D rotate down  | F save program to file\n"
"G0-G9 get reg n | H help on/off   | L load program | M +/- | P program on/off"
"\nR run program   | S0-S9 set reg n | U rotate up    | X exit\n";

const char line[] =	
"__________________________________________________________________________\n";

const unsigned short NUMREGS = 10;

typedef enum Token
{
	tokAddition, tokSubstraction, tokMultiplication, tokDivision,

	tokAdditiveInverse, tokExponentiation, tokModulus,

	tokClear, tokClearEntry,

	tokRotateStackDown, tokRotateStackUp,

	tokSaveToFile, tokLoadFromFile,

	tokGetRegister0, tokGetRegister1, tokGetRegister2,
	tokGetRegister3, tokGetRegister4, tokGetRegister5,
	tokGetRegister6, tokGetRegister7, tokGetRegister8,
	tokGetRegister9,

	tokToggleHelp,

	tokStartRecording, tokRunStoredProgram,

	tokSetRegister0, tokSetRegister1, tokSetRegister2,
	tokSetRegister3, tokSetRegister4, tokSetRegister5,
	tokSetRegister6, tokSetRegister7, tokSetRegister8,
	tokSetRegister9,

	tokOperand,tokInvalidToken,tokEmpty,

	tokExit
}Token;

//----------------------------------------------------------------------------
//    Title:		RPNCalc Class
//    Description:	This file contains the class definition for CRPNCalc
//    Programmer:	Vladimir Sanchez
// ----------------------------------------------------------------------------

	class CRPNCalc
	{
	public:
		CRPNCalc(bool on = true);
		void run();                                        
		void print(ostream& ostr);  
		void input(istream& istr);

		static Token parseCurrentString(string command,double* operand);
		//The Following variables should be private after testing
		//They are currently public to allow unit testing
	public:
		deque<double> m_stack;
		list<string> m_program;
		bool m_error;

	private:
		double m_registers[NUMREGS];
		string m_buffer;
		istringstream m_instrStream;
		bool m_helpOn;
		bool m_on;
		bool m_recording;

		void parse();
		bool binary_prep(double& d1, double& d2);
		bool unary_prep(double& d);
	};

	ostream &operator <<(ostream &ostr, CRPNCalc &calc);
	istream &operator >>(istream &istr, CRPNCalc &calc);

} // end namespace VS_CALC

#endif