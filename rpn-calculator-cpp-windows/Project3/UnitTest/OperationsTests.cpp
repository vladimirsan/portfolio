#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace VS_CALC;

namespace UnitTest
{		
	TEST_CLASS(OperationsTests)
	{
	public:

		TEST_METHOD(OperandTests)
		{
			CRPNCalc calc(false);
			//Inserting 3.1416 on the calculator
			stringstream sstream("3.1416");
			calc.input(sstream);

			//Expecting 3.1416 to be on the top of the stack
			Assert::IsTrue(3.1416 == *(calc.m_stack.begin()));
		}

		TEST_METHOD(BasicBinaryOperationsTests)
		{
			CRPNCalc calc(false);
			//Inserting 3 into the calculator stack
			stringstream sstream("3");
			calc.input(sstream);

			//Inserting 5 into the calculator stack
			sstream.str("5");
			sstream.clear();
			calc.input(sstream);

			//Inserting + into the calculator stack
			sstream.str("+");
			sstream.clear();
			calc.input(sstream);

			//Expecting 8 at the top of the stack
			Assert::IsTrue(8 == *(calc.m_stack.begin()));

			//Inserting 3 into the calculator stack
			sstream.str("3");
			sstream.clear();
			calc.input(sstream);

			//Inserting - into the calculator stack
			sstream.str("-");
			sstream.clear();
			calc.input(sstream);

			//Expecting 5 at the top of the stack
			Assert::IsTrue(5 == *(calc.m_stack.begin()));

			//Inserting 3 into the calculator stack
			sstream.str("3");
			sstream.clear();
			calc.input(sstream);

			//Inserting * into the calculator stack
			sstream.str("*");
			sstream.clear();
			calc.input(sstream);

			//Expecting 15 at the top of the stack
			Assert::IsTrue(15 == *(calc.m_stack.begin()));

			//Inserting 5 into the calculator stack
			sstream.str("5");
			sstream.clear();
			calc.input(sstream);

			//Inserting / into the calculator stack
			sstream.str("/");
			sstream.clear();
			calc.input(sstream);

			//Expecting 3 at the top of the stack
			Assert::IsTrue(3 == *(calc.m_stack.begin()));

			//Expecting M at the top of the stack
			sstream.str("M");
			sstream.clear();
			calc.input(sstream);

			//Expecting -3 at the top of the stack
			Assert::IsTrue(-3 == *(calc.m_stack.begin()));

			//Inserting 3 into the calculator stack
			sstream.str("3");
			sstream.clear();
			calc.input(sstream);

			//Inserting ^ into the calculator stack
			sstream.str("^");
			sstream.clear();
			calc.input(sstream);

			//Expecting -27 at the top of the stack
			Assert::IsTrue(-27 == *(calc.m_stack.begin()));

			//Inserting 5 into the calculator stack
			sstream.str("5");
			sstream.clear();
			calc.input(sstream);

			//Inserting % into the calculator stack
			sstream.str("%");
			sstream.clear();
			calc.input(sstream);

			//Expecting -27 % 5 at the top of the stack
			Assert::IsTrue(-27 % 5 == *(calc.m_stack.begin()));

			//Inserting C into the calculator stack
			sstream.str("C");
			sstream.clear();
			calc.input(sstream);

			//Expecting the stack to have zero elements after the C token
			Assert::IsTrue(0 == calc.m_stack.size());

			//Inserting 2 into the calculator stack
			sstream.str("2");
			sstream.clear();
			calc.input(sstream);

			//Inserting 2 into the calculator stack
			sstream.str("2");
			sstream.clear();
			calc.input(sstream);

			//Inserting CE into the calculator stack
			sstream.str("CE");
			sstream.clear();
			calc.input(sstream);

			//Expecting the stack to have one element after the CE token
			Assert::IsTrue(1 == calc.m_stack.size());
		}

		TEST_METHOD(RotationTests)
		{
			CRPNCalc calc(false);
			//Inserting 3 into the calculator stack
			stringstream sstream("3");
			calc.input(sstream);

			//Inserting 2 into the calculator stack
			sstream.str("2");
			sstream.clear();
			calc.input(sstream);

			//Inserting 1 into the calculator stack
			sstream.str("1");
			sstream.clear();
			calc.input(sstream);

			//Inserting D into the calculator stack
			sstream.str("D");
			sstream.clear();
			calc.input(sstream);
			
			//Expecting 2 at the top of the stack
			Assert::IsTrue(2 == *(calc.m_stack.begin()));
			//Expecting 1 at the bottom of the stack
			Assert::IsTrue(1 == *(calc.m_stack.end() - 1));

			//Inserting U into the calculator stack
			sstream.str("U");
			sstream.clear();
			calc.input(sstream);

			//Expecting 1 at the top of the stack
			Assert::IsTrue(1 == *(calc.m_stack.begin()));
			//Expecting 3 at the bottom of the stack
			Assert::IsTrue(3 == *(calc.m_stack.end() - 1));
		}

		TEST_METHOD(RegisterTests)
		{
			CRPNCalc calc(false);
			//Inserting 9 into the calculator stack
			stringstream sstream("9");
			calc.input(sstream);

			//Inserting 8 into the calculator stack
			sstream.str("8");
			sstream.clear();
			calc.input(sstream);

			//Inserting 7 into the calculator stack
			sstream.str("7");
			sstream.clear();
			calc.input(sstream);

			//Inserting 6 into the calculator stack
			sstream.str("6");
			sstream.clear();
			calc.input(sstream);

			//Inserting 5 into the calculator stack
			sstream.str("5");
			sstream.clear();
			calc.input(sstream);

			//Inserting 4 into the calculator stack
			sstream.str("4");
			sstream.clear();
			calc.input(sstream);

			//Inserting 3 into the calculator stack
			sstream.str("3");
			sstream.clear();
			calc.input(sstream);

			//Inserting 2 into the calculator stack
			sstream.str("2");
			sstream.clear();
			calc.input(sstream);


			//Inserting 1 into the calculator stack
			sstream.str("1");
			sstream.clear();
			calc.input(sstream);

			//Inserting 0 into the calculator stack
			sstream.str("0");
			sstream.clear();
			calc.input(sstream);

			//Loading S0 with the top of the stack
			sstream.str("S0");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S1 with the top of the stack
			sstream.str("S1");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S2 with the top of the stack
			sstream.str("S2");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S3 with the top of the stack
			sstream.str("S3");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S4 with the top of the stack
			sstream.str("S4");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S5 with the top of the stack
			sstream.str("S5");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S6 with the top of the stack
			sstream.str("S6");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S7 with the top of the stack
			sstream.str("S7");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S8 with the top of the stack
			sstream.str("S8");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Loading S9 with the top of the stack
			sstream.str("S9");
			sstream.clear();
			calc.input(sstream);

			//Rotating Down
			sstream.str("d");
			sstream.clear();
			calc.input(sstream);

			//Retrieving Register 0
			sstream.str("G0");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 0 to be 0
			Assert::IsTrue(0 == *(calc.m_stack.begin()));

			//Retrieving Register 1
			sstream.str("G1");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 1 to be 1
			Assert::IsTrue(1 == *(calc.m_stack.begin()));

			//Retrieving Register 2
			sstream.str("G2");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 2 to be 2
			Assert::IsTrue(2 == *(calc.m_stack.begin()));

			//Retrieving Register 3
			sstream.str("G3");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 3 to be 3
			Assert::IsTrue(3 == *(calc.m_stack.begin()));

			//Retrieving Register 4
			sstream.str("G4");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 4 to be 4
			Assert::IsTrue(4 == *(calc.m_stack.begin()));

			//Retrieving Register 5
			sstream.str("G5");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 5 to be 5
			Assert::IsTrue(5 == *(calc.m_stack.begin()));

			//Retrieving Register 6
			sstream.str("G6");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 6 to be 6
			Assert::IsTrue(6 == *(calc.m_stack.begin()));

			//Retrieving Register 7
			sstream.str("G7");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 7 to be 7
			Assert::IsTrue(7 == *(calc.m_stack.begin()));

			//Retrieving Register 8
			sstream.str("G8");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 8 to be 8
			Assert::IsTrue(8 == *(calc.m_stack.begin()));

			//Retrieving Register 9
			sstream.str("G9");
			sstream.clear();
			calc.input(sstream);

			//Expecting Register 9 to be 9
			Assert::IsTrue(9 == *(calc.m_stack.begin()));
		}

		TEST_METHOD(RecordProgramTests)
		{
			CRPNCalc calc(false);
			//Expecting the m_program list to be empty
			Assert::IsTrue(calc.m_program.size() == 0);

			//Inserting 3 into the calculator stack
			stringstream sstream("3");
			calc.input(sstream);

			//Inserting P into the calculator stack
			sstream.str("P");
			sstream.clear();
			calc.input(sstream);

			//Inserting 4 into m_program
			sstream.str("4");
			sstream.clear();
			calc.input(sstream);

			//Expecting m_program to have one element
			Assert::IsTrue(calc.m_program.size() == 1);

			//Inserting M into m_program
			sstream.str("M");
			sstream.clear();
			calc.input(sstream);

			//Expecting m_program to have two elements
			Assert::IsTrue(calc.m_program.size() == 2);

			//Inserting P into the calculator stack
			sstream.str("P");
			sstream.clear();
			calc.input(sstream);

			//Inserting 5 into the calculator stack
			sstream.str("5");
			sstream.clear();
			calc.input(sstream);

			//Inserting + into the calculator stack
			sstream.str("+");
			sstream.clear();
			calc.input(sstream);

			//Expecting 8 to be at the top of the stack
			//3 + 5
			Assert::IsTrue(8 == *(calc.m_stack.begin()));

			//Inserting R into the calculator stack
			sstream.str("R");
			sstream.clear();
			calc.input(sstream);

			//Expecting -4 to be at the top of the stack
			Assert::IsTrue(-4 == *(calc.m_stack.begin()));
		}


		TEST_METHOD(ErrorConditionsTests)
		{
			CRPNCalc calc(false);
			//Inserting R into the calculator stack
			stringstream sstream("2");
			calc.input(sstream);

			sstream.str("+");
			sstream.clear();
			calc.input(sstream);
			
			//Expecting error to be true after trying to add
			Assert::IsTrue(true == calc.m_error);

			CRPNCalc calc1(false);
			//Inserting R into the calculator stack
			sstream.str("M");
			sstream.clear();
			calc1.input(sstream);
			
			//Expecting error to be true after trying to use M
			Assert::IsTrue(true == calc1.m_error);

			CRPNCalc calc2(false);
			//Inserting R into the calculator stack
			sstream.str("(");
			sstream.clear();
			calc2.input(sstream);
			
			//Expecting error to be true after invalid token
			Assert::IsTrue(true == calc2.m_error);
		}
	};
}