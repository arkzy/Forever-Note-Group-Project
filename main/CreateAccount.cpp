#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include "Encryption.h"


#include <direct.h>	//for mkdir

#define TEST_FILE "TestDatabase.txt"
#define ACCOUNT_FILE "AccountDatabase.txt"


using namespace std;


bool TestingDirectoryWasCreated(string folderName) {
	//check if a folder created during testing was made and erase it if it was
	//so the test leaves no trace

	
	const char* charFolderName = folderName.c_str();
	int check = _mkdir(charFolderName);
	if (check == -1) {
		//the folder already exists, was created
		//we should delete the folder and return true
		experimental::filesystem::remove(folderName);
		return true;

	}
	else {
		//the folder did not already exist and was only just now created
		//erase the folder and return false
		experimental::filesystem::remove(folderName);
		return false;

	}
	

	
}

void ClearFileForTesting() {
	//if you open a file for writing you clear it's contents
	ofstream MyFile(TEST_FILE);

	
	


	// Close the file
	MyFile.close();

}

bool FileIsEmpty(string fileName) {
	ifstream MyReadFile(fileName);
	string myText;
	bool fileEmpty = true;

	while (getline(MyReadFile, myText)) {

		fileEmpty = false;
		break;
	}

	MyReadFile.close();

	return fileEmpty;
}

void PutInfoOnTestingFile() {
	vector<string> infoForFile = {"testaccount", "1234", "othertest", "password"};
	bool fileEmpty = true;

	//if there is no existing information
	

	if (FileIsEmpty(TEST_FILE)) {
		//fill file with encrypted testing info
		infoForFile = Encrypt(infoForFile);

		// Create and open a text file
		ofstream MyFile(TEST_FILE);

		// Write to the file
		for (int i = 0; i < infoForFile.size(); i++) {
			MyFile << infoForFile.at(i) << endl;
		}
		

		MyFile.close();

	}
	else {
		//do nothing, it already has stuff on it
	}

}


//test version of func that uses the test file
bool TestCreateAccount(string userName, string password) {
	bool userNameIsDuplicate = false;

	if (FileIsEmpty(TEST_FILE)) {
		//it can't be a duplicate, encrypt it and put it on file and make 
		//new directory for the new account
		vector<string> fileData;
		fileData.push_back(userName);
		fileData.push_back(password);

		fileData = Encrypt(fileData);

		ofstream MyFile(TEST_FILE);

		// Write to the file
		for (int i = 0; i < fileData.size(); i++) {
			MyFile << fileData.at(i) << endl;
		}


		// Close the file
		MyFile.close();

		//create new folder for the user
		//https://www.geeksforgeeks.org/create-directoryfolder-cc-program/
		const char* charUserName = userName.c_str();
		int check = _mkdir(charUserName);
		

	}
	else {
		//if there is data on file, check it to see if the incoming information has a duplicate
		vector<string> fileData;
		string myText;

		ifstream MyReadFile(TEST_FILE);

		// Use a while loop together with the getline() function to read the file line by line
		while (getline(MyReadFile, myText)) {
			// Output the text from the file
			fileData.push_back(myText);
		}

		// Close the file
		MyReadFile.close();

		fileData = Decrypt(fileData);

		//check for duplicate usernames only, user names are every other element
		for (int i = 0; i < fileData.size(); i += 2) {
			if (userName == fileData.at(i)) {
				userNameIsDuplicate = true;
				return false;	//this is the signal that it failed
				break;
			}
		}

		//if there is no duplicate, add it to the info and put it on the file
		//and create a new folder for the account
		fileData.push_back(userName);
		fileData.push_back(password);

		fileData = Encrypt(fileData);


		ofstream MyFile(TEST_FILE);

		// Write to the file
		for (int i = 0; i < fileData.size(); i++) {
			MyFile << fileData.at(i) << endl;
		}
		

		// Close the file
		MyFile.close();

		//create new folder for the user
		//https://www.geeksforgeeks.org/create-directoryfolder-cc-program/
		const char* charUserName = userName.c_str();
		int check = _mkdir(charUserName);
		
		


	}

	
	return true;

}



bool CreateAccount(string userName, string password) {
	bool userNameIsDuplicate = false;

	if (FileIsEmpty(ACCOUNT_FILE)) {
		//it can't be a duplicate, encrypt it and put it on file and make 
		//new directory for the new account
		vector<string> fileData;
		fileData.push_back(userName);
		fileData.push_back(password);

		fileData = Encrypt(fileData);

		ofstream MyFile(ACCOUNT_FILE);

		// Write to the file
		for (int i = 0; i < fileData.size(); i++) {
			MyFile << fileData.at(i) << endl;
		}


		// Close the file
		MyFile.close();

		//create new folder for the user
		//https://www.geeksforgeeks.org/create-directoryfolder-cc-program/
		const char* charUserName = userName.c_str();
		int check = _mkdir(charUserName);


	}
	else {
		//if there is data on file, check it to see if the incoming information has a duplicate
		vector<string> fileData;
		string myText;

		ifstream MyReadFile(ACCOUNT_FILE);

		// Use a while loop together with the getline() function to read the file line by line
		while (getline(MyReadFile, myText)) {
			// Output the text from the file
			fileData.push_back(myText);
		}

		// Close the file
		MyReadFile.close();

		fileData = Decrypt(fileData);

		//check for duplicate usernames only, user names are every other element
		for (int i = 0; i < fileData.size(); i += 2) {
			if (userName == fileData.at(i)) {
				userNameIsDuplicate = true;
				return false;	//this is the signal that it failed
				break;
			}
		}

		//if there is no duplicate, add it to the info and put it on the file
		//and create a new folder for the account
		fileData.push_back(userName);
		fileData.push_back(password);

		fileData = Encrypt(fileData);


		ofstream MyFile(ACCOUNT_FILE);

		// Write to the file
		for (int i = 0; i < fileData.size(); i++) {
			MyFile << fileData.at(i) << endl;
		}


		// Close the file
		MyFile.close();

		//create new folder for the user
		//https://www.geeksforgeeks.org/create-directoryfolder-cc-program/
		const char* charUserName = userName.c_str();
		int check = _mkdir(charUserName);




	}


	return true;

}
