#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CreateAccount.h"
#include "Encryption.h"

using namespace std;

#define TEST_FILE "TestDatabase.txt"
#define ACCOUNT_FILE "AccountDatabase.txt"


bool TestingLogIntoAccount(string userName, string password) {
	//get info from file if there, otherwise there are no accounts created
	if (FileIsEmpty(TEST_FILE)) {
		//there are no accounts created
		return false;
	}
	else {

		vector<string> fileData;

		string myText;
		ifstream MyReadFile(TEST_FILE);

		
		while (getline(MyReadFile, myText)) {
			// Output the text from the file
			fileData.push_back(myText);
		}

		// Close the file
		MyReadFile.close();

		//decrypt it
		fileData = Decrypt(fileData);

		//format is: username, password, username, password etc
		//check for both username and password match
		bool itemAtIIsAUserName = true;
		bool userNameFound = false;
		bool passwordFound = false;

		for (int i = 0; i < fileData.size(); i++) {

			if (itemAtIIsAUserName) {
				if (fileData.at(i) == userName) {
					userNameFound = true;
				}
				itemAtIIsAUserName = false;
			}
			else {
				if (fileData.at(i) == password) {
					passwordFound = true;
				}
				itemAtIIsAUserName = true;
			}

		}

		if (passwordFound == true && userNameFound == true) {
			return true;
		}
		else {
			return false;	//this indicates that either the username or password were wrong
		}

	}


	
}

bool LogIntoAccount(string userName, string password) {
	//get info from file if there, otherwise there are no accounts created
	if (FileIsEmpty(ACCOUNT_FILE)) {
		//there are no accounts created
		return false;
	}
	else {

		vector<string> fileData;

		string myText;
		ifstream MyReadFile(ACCOUNT_FILE);


		while (getline(MyReadFile, myText)) {
			// Output the text from the file
			fileData.push_back(myText);
		}

		// Close the file
		MyReadFile.close();

		//decrypt it
		fileData = Decrypt(fileData);

		//format is: username, password, username, password etc
		//check for both username and password match
		bool itemAtIIsAUserName = true;
		bool userNameFound = false;
		bool passwordFound = false;

		for (int i = 0; i < fileData.size(); i++) {

			if (itemAtIIsAUserName) {
				if (fileData.at(i) == userName) {
					userNameFound = true;
				}
				itemAtIIsAUserName = false;
			}
			else {
				if (fileData.at(i) == password) {
					passwordFound = true;
				}
				itemAtIIsAUserName = true;
			}

		}

		if (passwordFound == true && userNameFound == true) {
			return true;
		}
		else {
			return false;	//this indicates that either the username or password were wrong
		}

	}
}