#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <time.h>

using namespace std;
//https://stackoverflow.com/questions/27054414/printing-all-the-ascii-values-in-c-c/27054451
string EncryptLine(string fun, vector<char> printablesList, int shift);
vector<string> EncryptList(vector<string> lineList, vector<char> pList, int shift);
vector<char> MakePrintableCharactersList();
string DecryptLine(string fun, vector<char> printablesList, int shift);
vector<string> DecryptList(vector<string> lineList, vector<char> pList, int shift);
vector<string> Encrypt(vector<string> message);
vector<string> Decrypt(vector<string> message);

//old testing main
//int main() {
//	vector<string> example = { "hello there sire", "bye ma'am", "all around the world" };
//	example = Encrypt(example);
//	example = Decrypt(example);
//
//	for (int i = 0; i < example.size(); i++) {
//		cout << example.at(i) << endl;
//	}
//
//}

vector<string> Encrypt(vector<string> message) {
	//this will return the encrypted message with the bit flipped key as the last item 
	vector<char> printables = MakePrintableCharactersList();
	srand(time(NULL));
	int shift = rand() % printables.size() + 1;
	vector<string> toReturn = EncryptList(message, printables, shift);

	unsigned char binary = shift;
	binary = ~binary; //flup the bits 

	string stringVersionOfBinary = to_string(binary);
	toReturn.push_back(stringVersionOfBinary);
	//test to make sure that the last value added is right 

	return toReturn;

}

vector<string> Decrypt(vector<string> message) {
	vector<char> printables = MakePrintableCharactersList();
	//last line in the list is the bit flipped key 
	string stringKey = message.at(message.size() - 1);
	int intKey = stoi(stringKey);
	unsigned char binary = intKey;
	binary = ~binary;
	int shift = binary;

	//the last item is the decrypt key, remove it from message 
	message.erase(message.begin() + (message.size() - 1));

	message = DecryptList(message, printables, shift);
	return message;

}



string EncryptLine(string fun, vector<char> printablesList, int shift) {
	//maybe keep this func mostly in tact and call this for each string in the string list 
	string toReturn = "";
	int charIndex = 0;
	for (int k = 0; k < fun.size(); k++) {
		for (int i = 0; i < printablesList.size(); i++) {
			if (fun.at(k) == printablesList.at(i)) {
				charIndex = i;
				charIndex += shift;

				if (charIndex >= 95) {
					//if the list index + shift is outside of list range, 
					//put it in range 
					charIndex -= 95;
					//could something become more than 95 over? I don't think so but I'm not sure
				}
				toReturn += printablesList.at(charIndex);
				break;
			}
		}
	}
	return toReturn;

}

vector<string> EncryptList(vector<string> lineList, vector<char> pList, int shift) {
	//this but return the list of encrypted lines and add a line that is the seed/shift value on the end. Make sure to encrypt it with the binary rubbish!
	vector<string> toReturn;
	for (int i = 0; i < lineList.size(); i++) {
		toReturn.push_back(EncryptLine(lineList.at(i), pList, shift));
	}

	return toReturn;
}

vector<char> MakePrintableCharactersList() {
	vector<char> toReturn;
	//the list of printable chars is 95 long
	for (int a = 0; a < 256; ++a) {
		if (std::isprint(a)) {
			// check if printable
			toReturn.push_back(char(a));
		}
	}
	return toReturn;
}

string DecryptLine(string fun, vector<char> printablesList, int shift) {
	string toReturn = "";
	//cout << fun.size() << ", " << shift << ", " << printablesList.size() << endl;
	int charIndex = 0;
	for (int k = 0; k < fun.size(); k++) {
		for (int i = 0; i < printablesList.size(); i++) {
			if (fun.at(k) == printablesList.at(i)) {
				charIndex = i;
				charIndex -= shift;

				if (charIndex < 0) {
					//if the list index + shift is outside of list range, 
					//put it in range 
					charIndex += 95; //if it's a wrap around case, -= shift will make it negative
					//could something become more than 95 over? I don't think so but I'm not sure
				}

				//cout << charIndex << endl;
				//toReturn += printablesList.at(charIndex);
				//do it here!
				toReturn += printablesList.at(charIndex);
				break;
			}
		}
	}
	return toReturn;
}

vector<string> DecryptList(vector<string> lineList, vector<char> pList, int shift) {
	vector<string> toReturn;
	for (int i = 0; i < lineList.size(); i++) {
		toReturn.push_back(DecryptLine(lineList.at(i), pList, shift));
	}
	return toReturn;
}