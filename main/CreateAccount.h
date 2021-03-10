#pragma once
#include <string>


using namespace std;


//this is for other modules to call, a false return value means the userName 
//was a duplicate of one that already exists


//below are for testing
void PutInfoOnTestingFile();

void ClearFileForTesting();

bool TestCreateAccount(string, string);

bool TestingDirectoryWasCreated(string);

bool CreateAccount(string, string);

bool FileIsEmpty(string);