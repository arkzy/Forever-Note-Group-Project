#pragma once
#include <vector>
#include <string>

using namespace std;


vector<string> PasswordLock(string password, vector<string> unencryptedNote);

vector<string> PasswordUnlock(vector<string> encryptedNote);
