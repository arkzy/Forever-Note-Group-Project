#pragma once
#include <vector>
#include <string>
using namespace std;

//these are all outside modules will need to call
vector<string> Encrypt(vector<string> message);
vector<string> Decrypt(vector<string> message);



//these are here so I can make tests for them
string EncryptLine(string fun, vector<char> printablesList, int shift);
vector<string> EncryptList(vector<string> lineList, vector<char> pList, int shift);
vector<char> MakePrintableCharactersList();
string DecryptLine(string fun, vector<char> printablesList, int shift);
vector<string> DecryptList(vector<string> lineList, vector<char> pList, int shift);