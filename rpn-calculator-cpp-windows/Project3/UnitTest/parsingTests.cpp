#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace VS_CALC;

namespace UnitTest
{		
	/* Test if the parseCurrentString method returns the appropiate token 
		in trivial scenarios. The tests use the following syntax:

		Assert::Istrue(EXPECTED_TOKEN == CRPNCalc::parseCurrentSTring
				CRPNCalc::parseCurrentString(INPUT_STRING,&dbl));
	*/
	TEST_CLASS(ParsingTests)
	{
	public:

		TEST_METHOD(NonNumericParsingTest)
		{
			double dbl;
			
			//Expecting tokEmpty
			Assert::IsTrue(tokEmpty == 
				CRPNCalc::parseCurrentString("",&dbl));
			//Expecting tokEmpty
			Assert::IsTrue(tokEmpty == 
				CRPNCalc::parseCurrentString("  ",&dbl));
			//Expecting tokAddition
			Assert::IsTrue(tokAddition == 
				CRPNCalc::parseCurrentString("+",&dbl));
			//Expecting tokSubstraction
			Assert::IsTrue(tokSubstraction == 
				CRPNCalc::parseCurrentString("-",&dbl));
			//Expecting tokMultiplication
			Assert::IsTrue(tokMultiplication == 
				CRPNCalc::parseCurrentString("*",&dbl));
			//Expecting tokDivision
			Assert::IsTrue(tokDivision == 
				CRPNCalc::parseCurrentString("/",&dbl));

			//Expecting tokExponentiation
			Assert::IsTrue(tokExponentiation == 
				CRPNCalc::parseCurrentString("^",&dbl));
			//Expecting tokModulus
			Assert::IsTrue(tokModulus == 
				CRPNCalc::parseCurrentString("%",&dbl));

			//Expecting tokClear
			Assert::IsTrue(tokClear == 
				CRPNCalc::parseCurrentString("C",&dbl));
			//Expecting tokClearEntry
			Assert::IsTrue(tokClearEntry == 
				CRPNCalc::parseCurrentString("CE",&dbl));

			//Expecting tokRotateStackDown
			Assert::IsTrue(tokRotateStackDown == 
				CRPNCalc::parseCurrentString("D",&dbl));

			//Expecting tokSaveToFile
			Assert::IsTrue(tokSaveToFile == 
				CRPNCalc::parseCurrentString("F",&dbl));

			//Expecting tokGetRegister0
			Assert::IsTrue(tokGetRegister0 == 
				CRPNCalc::parseCurrentString("G0",&dbl));
			//Expecting tokGetRegister1
			Assert::IsTrue(tokGetRegister1 == 
				CRPNCalc::parseCurrentString("G1",&dbl));
			//Expecting tokGetRegister2
			Assert::IsTrue(tokGetRegister2 == 
				CRPNCalc::parseCurrentString("G2",&dbl));
			//Expecting tokGetRegister3
			Assert::IsTrue(tokGetRegister3 == 
				CRPNCalc::parseCurrentString("G3",&dbl));
			//Expecting tokGetRegister4
			Assert::IsTrue(tokGetRegister4 == 
				CRPNCalc::parseCurrentString("G4",&dbl));
			//Expecting tokGetRegister5
			Assert::IsTrue(tokGetRegister5 == 
				CRPNCalc::parseCurrentString("G5",&dbl));
			//Expecting tokGetRegister6
			Assert::IsTrue(tokGetRegister6 == 
				CRPNCalc::parseCurrentString("G6",&dbl));
			//Expecting tokGetRegister7
			Assert::IsTrue(tokGetRegister7 == 
				CRPNCalc::parseCurrentString("G7",&dbl));
			//Expecting tokGetRegister8
			Assert::IsTrue(tokGetRegister8 == 
				CRPNCalc::parseCurrentString("G8",&dbl));
			//Expecting tokGetRegister9
			Assert::IsTrue(tokGetRegister9 == 
				CRPNCalc::parseCurrentString("G9",&dbl));

			//Expecting tokTooggleHelp
			Assert::IsTrue(tokToggleHelp == 
				CRPNCalc::parseCurrentString("H",&dbl));
			//Expecting tokLoadFromFile
			Assert::IsTrue(tokLoadFromFile == 
				CRPNCalc::parseCurrentString("L",&dbl));
			//Expecting tokAdditiveInverse
			Assert::IsTrue(tokAdditiveInverse == 
				CRPNCalc::parseCurrentString("M",&dbl));
			//Expecting tokStartRecording
			Assert::IsTrue(tokStartRecording == 
				CRPNCalc::parseCurrentString("P",&dbl));
			//Expecting tokRunStoredProgram
			Assert::IsTrue(tokRunStoredProgram == 
				CRPNCalc::parseCurrentString("R",&dbl));

			//Expecting tokSetRegister0
			Assert::IsTrue(tokSetRegister0 == 
				CRPNCalc::parseCurrentString("S0",&dbl));
			//Expecting tokSetRegister1
			Assert::IsTrue(tokSetRegister1 == 
				CRPNCalc::parseCurrentString("S1",&dbl));
			//Expecting tokSetRegister2
			Assert::IsTrue(tokSetRegister2 == 
				CRPNCalc::parseCurrentString("S2",&dbl));
			//Expecting tokSetRegister3
			Assert::IsTrue(tokSetRegister3 == 
				CRPNCalc::parseCurrentString("S3",&dbl));
			//Expecting tokSetRegister4
			Assert::IsTrue(tokSetRegister4 == 
				CRPNCalc::parseCurrentString("S4",&dbl));
			//Expecting tokSetRegister5
			Assert::IsTrue(tokSetRegister5 == 
				CRPNCalc::parseCurrentString("S5",&dbl));
			//Expecting tokSetRegister6
			Assert::IsTrue(tokSetRegister6 == 
				CRPNCalc::parseCurrentString("S6",&dbl));
			//Expecting tokSetRegister7
			Assert::IsTrue(tokSetRegister7 == 
				CRPNCalc::parseCurrentString("S7",&dbl));
			//Expecting tokSetRegister8
			Assert::IsTrue(tokSetRegister8 == 
				CRPNCalc::parseCurrentString("S8",&dbl));
			//Expecting tokSetRegister9
			Assert::IsTrue(tokSetRegister9 == 
				CRPNCalc::parseCurrentString("S9",&dbl));

			//Expecting tokSetRotateStackUp
			Assert::IsTrue(tokRotateStackUp == 
				CRPNCalc::parseCurrentString("U",&dbl));
			//Expecting tokExit
			Assert::IsTrue(tokExit == 
				CRPNCalc::parseCurrentString("X",&dbl));
		}

		/* Test if the parseCurrentString method returns the appropiate token 
			in case insensitive scenarios. The tests use the following syntax:

			Assert::Istrue(EXPECTED_TOKEN == CRPNCalc::parseCurrentSTring
					CRPNCalc::parseCurrentString(INPUT_STRING,&dbl));
		*/
		TEST_METHOD(NonNumericCaseInsensitiveParsingTest)
		{
			double dbl;
			//Expecting tokClearEntry
			Assert::IsTrue(tokClearEntry == 
				CRPNCalc::parseCurrentString("ce",&dbl));
			//Expecting tokClearEntry
			Assert::IsTrue(tokClearEntry == 
				CRPNCalc::parseCurrentString("cE",&dbl));

			//Expecting tokRotateStackDown
			Assert::IsTrue(tokRotateStackDown == 
				CRPNCalc::parseCurrentString("d",&dbl));

			//Expecting tokGetRegister0
			Assert::IsTrue(tokGetRegister0 == 
				CRPNCalc::parseCurrentString("g0",&dbl));
		}

		/* Test if the parseCurrentString method returns the appropiate token 
			in numeric scenarios. The tests use the following syntax:

			CRPNCalc::parseCurrentString(INPUT_STRING,&dbl);
			Assert::IsTrue(EXPECTED_VALUE == dbl);
		*/
		TEST_METHOD(NumericParsingTest)
		{
			double dbl;
			CRPNCalc::parseCurrentString("2",&dbl);
			//Expecting a parsed 2
			Assert::IsTrue(2 == dbl);

			CRPNCalc::parseCurrentString("3.1416",&dbl);
			//Expecting a parsed 3.1416
			Assert::IsTrue(3.1416 == dbl);

			CRPNCalc::parseCurrentString("-3.1416",&dbl);
			//Expecting a parsed -3.1416
			Assert::IsTrue(-3.1416 == dbl);
		}

		/* Test invalid parsing

			Assert::Istrue(EXPECTED_TOKEN == CRPNCalc::parseCurrentSTring
					CRPNCalc::parseCurrentString(INPUT_STRING,&dbl));
		*/
		TEST_METHOD(InvalidParsingTests)
		{
			double dbl;
			//Expected tokInvalidToken
			Assert::IsTrue(tokInvalidToken == 
				CRPNCalc::parseCurrentString("cep",&dbl));

			//Expected tokInvalidToken
			Assert::IsTrue(tokInvalidToken == 
				CRPNCalc::parseCurrentString("3.14.3",&dbl));

			//Expected tokInvalidToken
			Assert::IsTrue(tokInvalidToken == 
				CRPNCalc::parseCurrentString("3o.14.3",&dbl));

			//Expected tokInvalidToken
			Assert::IsTrue(tokInvalidToken == 
				CRPNCalc::parseCurrentString("u4",&dbl));
		}
	};
}