#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>


#include "Encryption.h"
#include "Password.h"
#include "CreateAccount.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

/*
string EncryptLine(string fun, vector<char> printablesList, int shift);
vector<string> EncryptList(vector<string> lineList, vector<char> pList, int shift);
vector<char> MakePrintableCharactersList();
string DecryptLine(string fun, vector<char> printablesList, int shift);
vector<string> DecryptList(vector<string> lineList, vector<char> pList, int shift);
*/


namespace UserModuleTests
{
	TEST_CLASS(EncryptionTests)
	{
		//all encrypt list and decrypt list do are call their line counter parts
		//if something isn't wrong here, it's in one of only a few other places
		//which the overall check should catch
	public:
		
		TEST_METHOD(T001_EncryptLine_hello_1_______ifmmp)
		{
			//arrange, act, assert
			string inputMessage = "hello";
			string expected = "ifmmp";
			string actual = "";
			int inputShift = 1;	//this will shift the letters one down on the list of all printable characters

			//make printable characters list simply gets all printable characters
			actual = EncryptLine(inputMessage, MakePrintableCharactersList(), inputShift);

			Assert::AreEqual(expected, actual);

		}


		TEST_METHOD(T002_EncryptLine_tenExclamationMarks_10_______tenPlusSigns)
		{
			//arrange, act, assert
			string inputMessage = "!!!!!!!!!!";
			string expected = "++++++++++";
			string actual = "";
			int inputShift = 10;	//this will shift the letters one down on the list of all printable characters

			//make printable characters list simply gets all printable characters
			actual = EncryptLine(inputMessage, MakePrintableCharactersList(), inputShift);

			Assert::AreEqual(expected, actual);

		}


		TEST_METHOD(T003_EncryptLine_hashMoneyPercentAmpersandQuoteBracketsMultiplicationPlus_20_______sevenToNineColonSemiColonGreaterEqualLessthanQuestion)
		{
			//arrange, act, assert
			string inputMessage = "#$%&'()*+";
			string expected = "789:;<=>?";
			string actual = "";
			int inputShift = 20;	//this will shift the letters one down on the list of all printable characters

			//make printable characters list simply gets all printable characters
			actual = EncryptLine(inputMessage, MakePrintableCharactersList(), inputShift);

			Assert::AreEqual(expected, actual);

		}


		TEST_METHOD(T004_decryptLine_sevenToNineColonSemiColonGreaterEqualLessthanQuestion_20_______hashMoneyPercentAmpersandQuoteBracketsMultiplicationPlus)
		{
			//arrange, act, assert
			string inputMessage = "789:;<=>?";
			string expected = "#$%&'()*+";
			string actual = "";
			int inputShift = 20;	//this will shift the letters one down on the list of all printable characters

			//make printable characters list simply gets all printable characters
			actual = DecryptLine(inputMessage, MakePrintableCharactersList(), inputShift);

			Assert::AreEqual(expected, actual);

		}

		TEST_METHOD(T005_decryptLine_tenPlusSigns_10_______tenExclamationMarks)
		{
			//arrange, act, assert
			string inputMessage = "++++++++++";
			string expected = "!!!!!!!!!!";
			string actual = "";
			int inputShift = 10;	//this will shift the letters one down on the list of all printable characters

			//make printable characters list simply gets all printable characters
			actual = DecryptLine(inputMessage, MakePrintableCharactersList(), inputShift);

			Assert::AreEqual(expected, actual);

		}


		TEST_METHOD(T006_DecryptLine_ifmmp_1_______hello)
		{
			//arrange, act, assert
			string inputMessage = "ifmmp";
			string expected = "hello";
			string actual = "";
			int inputShift = 1;	//this will shift the letters one down on the list of all printable characters

			//make printable characters list simply gets all printable characters
			actual = DecryptLine(inputMessage, MakePrintableCharactersList(), inputShift);

			Assert::AreEqual(expected, actual);

		}


		TEST_METHOD(T007_EncryptAndDecrypt_h_e_l_l_o________h_e_l_l_o)
		{
			//arrange, act, assert
			vector<string> inputMessage = { "h", "e", "l", "l", "o" };
			vector<string> expected = { "h", "e", "l", "l", "o" };
			vector<string> actual;
			vector<string> temp;
			
			//encryp automatically generates a random shift

			temp = Encrypt(inputMessage);
			actual = Decrypt(temp);
			
			//there is no comparison for vectors, so compare two elements
			Assert::AreEqual(expected.at(2),actual.at(2));

		}


		TEST_METHOD(T008_EncryptAndDecrypt_Q_R_S_T_U_V_W_X_Y_Z________Q_R_S_T_U_V_W_X_Y_Z)
		{
			//arrange, act, assert
			vector<string> inputMessage = { "Q", "R", "S", "T", "U", "V" , "W", "X", "Y", "Z"};
			vector<string> expected = { "Q", "R", "S", "T", "U", "V" , "W", "X", "Y", "Z"};
			vector<string> actual;
			vector<string> temp;

		  //these characters are on the end of the printable characters list so this 
			// is a test of how well the wrap-around handling code works

			//encryp automatically generates a random shift

			temp = Encrypt(inputMessage);
			actual = Decrypt(temp);

			//there is no comparison for vectors, so compare two elements
			Assert::AreEqual(expected.at(5), actual.at(5));

		}


		TEST_METHOD(T009_EncryptAndDecrypt_everyPrintableCharacter________everyPrintableCharacter)
		{
			//arrange, act, assert
			vector<char> printableChars = MakePrintableCharactersList();
			vector<string> inputMessage = {"", "stand in"};
			vector<string> expected;

			for (int i = 0; i < printableChars.size(); i++) {
				inputMessage.at(0) += printableChars.at(i);
			}
		
			expected = inputMessage;
			vector<string> actual;
			vector<string> temp;

			//test every printable character so that any message can be handled

			  //encryp automatically generates a random shift

			temp = Encrypt(inputMessage);
			actual = Decrypt(temp);

			//there is no comparison for vectors, so compare two elements
			Assert::AreEqual(expected.at(0), actual.at(0));

		}


	};


	TEST_CLASS(PasswordTests)
	{
		
	public:

		TEST_METHOD(T010_PasswordLock_secret________openBracketYWApostropheYCloseBracket)
		{
			//arrange, act, assert
			string inputPassword = "secret";
			string expected = "(yw'y)";
			vector<string> actual;
			vector<string> inputMessage = { "hello", "there" };
			//password shift is automatically 20

			actual = PasswordLock(inputPassword, inputMessage);

			//password should be the second item in the returned list
			//since the first is the hash line
			Assert::AreEqual(expected, actual.at(1));

		}


		TEST_METHOD(T011_PasswordLock_password1234OtherChars________bunchOfChars)
		{
																		
			//arrange, act, assert
			string inputPassword = "password1234!?*&";
			string expected = "%u((,$'xEFGH5S>:";
			vector<string> actual;
			vector<string> inputMessage = { "hello", "there" };
			//password shift is automatically 20

			actual = PasswordLock(inputPassword, inputMessage);

			//password should be the second item in the returned list
			//since the first is the hash line
			Assert::AreEqual(expected, actual.at(1));

		}



		TEST_METHOD(T012_PasswordUnlock_bunchOfChars________password1234OtherChars)
		{
			//example passwordLocked message:
			//##########
			//%u((,$'xEFGH5S>:
			//gdkkn~sgdqd~rhqd
			//axd~l`&`l
				//`kk~`qntmc~sgd~vnqkc
				//161

			//arrange, act, assert
			
			string expected = "password1234!?*&";
			vector<string> actual;
			vector<string> inputMessage = { "##########", "%u((,$'xEFGH5S>:", "gdkkn~sgdqd~rhqd", "axd~l`&`l", "`kk~`qntmc~sgd~vnqkc", "161" };
			//password shift is automatically 20

			actual = PasswordUnlock(inputMessage);

			//password is first line of returned vector
			Assert::AreEqual(expected, actual.at(0));

		}



		TEST_METHOD(T013_PasswordUnlock_openBracketYWApostropheYCloseBracket________secret)
		{
		
			//example passwordLocked message:
			//##########
			//(yw'y)
			//gdkkn~sgdqd~rhqd
			//axd~l`&`l
				//`kk~`qntmc~sgd~vnqkc
				//161

			//arrange, act, assert

			string expected = "secret";
			vector<string> actual;
			vector<string> inputMessage = { "##########", "(yw'y)", "gdkkn~sgdqd~rhqd", "axd~l`&`l", "`kk~`qntmc~sgd~vnqkc", "161" };
			//password shift is automatically 20

			actual = PasswordUnlock(inputMessage);

			//password is first line of returned vector
			Assert::AreEqual(expected, actual.at(0));

		}



		TEST_METHOD(T014_PasswordUnlock_and_PasswordUnlock_I_LOVE_CODING________I_LOVE_CODING)
		{

		

			//arrange, act, assert
			string inputPassword = "I LOVE CODING";
			string expected = inputPassword;
			vector<string> inputMessage = {"this", "is", "tedious"};
			vector<string> actual;
			vector<string> temp;
		
			//password shift is automatically 20
			temp = PasswordLock(inputPassword, inputMessage);
			actual = PasswordUnlock(temp);

			//password is first line of returned vector
			Assert::AreEqual(expected, actual.at(0));

		}



		TEST_METHOD(T015_PasswordUnlock_and_PasswordUnlock_variouseSymbals________variouseSymbals)
		{



			//arrange, act, assert
			string inputPassword = "!@#$%^&*()~{}[];:'.>,</|";
			string expected = inputPassword;
			vector<string> inputMessage = { "this", "is", "tedious" };
			vector<string> actual;
			vector<string> temp;

			//password shift is automatically 20
			temp = PasswordLock(inputPassword, inputMessage);
			actual = PasswordUnlock(temp);

			//password is first line of returned vector
			Assert::AreEqual(expected, actual.at(0));

		}


		


	};



	TEST_CLASS(CreateAccountTests)
	{
		//there needs to be a seperate file for testing so that running the tests won't 
		//delete data that the program actually needs/is using for manual tests
	public:
		//{"testaccount", "1234", "othertest", "password"};
		TEST_METHOD(T016_TestCreateAccount_testaccount_x________false)
		{
			//it should recognize this account as a duplicate
			//arrange, act, assert
			ClearFileForTesting();
			PutInfoOnTestingFile();	//puts {"testaccount", "1234", "othertest", "password"} on the file;

			string inputUserName = "testaccount";
			string inputPassword = "x";	//password doesn't matter in duplicate search, only username
			bool expected = false;
			
			bool actual = TestCreateAccount(inputUserName, inputPassword);

			//cleanup after the test, clean the file and delete the created directory
			TestingDirectoryWasCreated(inputUserName);
			ClearFileForTesting();

			Assert::AreEqual(expected, actual);

		}



		TEST_METHOD(T017_TestCreateAccount_othertest_x________false)
		{
			//it should recognize this account as a duplicate
			//arrange, act, assert
			ClearFileForTesting();
			PutInfoOnTestingFile();	//puts {"testaccount", "1234", "othertest", "password"} on the file;

			string inputUserName = "othertest";
			string inputPassword = "x";	//password doesn't matter in duplicate search, only username
			bool expected = false;

			bool actual = TestCreateAccount(inputUserName, inputPassword);

			//cleanup after the test, clean the file and delete the created directory
			TestingDirectoryWasCreated(inputUserName);
			ClearFileForTesting();

			Assert::AreEqual(expected, actual);

		}



		TEST_METHOD(T018_TestCreateAccount_original_x________true)
		{
			//it should recognize this account as a duplicate
			//arrange, act, assert
			ClearFileForTesting();
			PutInfoOnTestingFile();	//puts {"testaccount", "1234", "othertest", "password"} on the file;

			string inputUserName = "original";
			string inputPassword = "x";	//password doesn't matter in duplicate search, only username
			bool expected = true;

			bool actual = TestCreateAccount(inputUserName, inputPassword);

			//cleanup after the test, clean the file and delete the created directory
			TestingDirectoryWasCreated(inputUserName);
			ClearFileForTesting();

			Assert::AreEqual(expected, actual);

		}


		TEST_METHOD(T019_TestCreateAccount_newaccount_x________true)
		{
			//it should recognize this account as a duplicate
			//arrange, act, assert
			ClearFileForTesting();
			PutInfoOnTestingFile();	//puts {"testaccount", "1234", "othertest", "password"} on the file;

			string inputUserName = "newaccount";
			string inputPassword = "x";	//password doesn't matter in duplicate search, only username
			bool expected = true;

			bool actual = TestCreateAccount(inputUserName, inputPassword);

			//cleanup after the test, clean the file and delete the created directory
			TestingDirectoryWasCreated(inputUserName);
			ClearFileForTesting();

			Assert::AreEqual(expected, actual);

		}


		





	};


}
