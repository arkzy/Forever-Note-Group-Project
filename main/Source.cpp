

#include <iostream>
#include <string>
#include "CreateAccount.h"
#include <direct.h>



using namespace std;

int main() {

	std::cout << "Hello World!" << std::endl;
	//PutInfoOnTestingFile();
	
	//TestCreateAccount("hello", "bye");
	//TestCreateAccount("hello", "bye");

	/*string userName = "hello";
	const char* charUserName = userName.c_str();
	int check = _mkdir(charUserName);
	cout << check << endl;*/
	//check is -1 if the diectory already exists!


	//#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
	//#include <experimental/filesystem>
	//it said there was a way to do it with just filesystem but I couldn't get it to work
	//this works!
	//std::experimental::filesystem::remove("hello");
	
	//this only works for empty directories which is fine because that's all they'll be for testing
	
	
	return 0;
}