#include "Encryption.h"
#include <string>
#include <vector>

#define PASSWORD_ENCRYPT_SHIFT 20

using namespace std;


vector<string> PasswordLock(string password, vector<string> unencryptedNote) {
	//encrypt note
	vector<string> encryptedNote = Encrypt(unencryptedNote);

	//encrypt password
	string encryptedPassword = EncryptLine(password, MakePrintableCharactersList(), PASSWORD_ENCRYPT_SHIFT);

	//add password onto front of note
	
	encryptedNote.insert(encryptedNote.begin(), encryptedPassword);

	//add 10 hashes as new first line of note
	string passwordedFileKeyLine = "##########";
	encryptedNote.insert(encryptedNote.begin(), passwordedFileKeyLine);

	return encryptedNote;

}

vector<string> PasswordUnlock(vector<string> encryptedNote) {

	//remove first line, the line of hashes of hashes
	
	encryptedNote.erase(encryptedNote.begin());
	//seperate password from note and decrypt it
	string encryptedPassword = encryptedNote.at(0);
	string decryptedPassword = DecryptLine(encryptedPassword, MakePrintableCharactersList(), PASSWORD_ENCRYPT_SHIFT);
	encryptedNote.erase(encryptedNote.begin());
	//decrypt note
	vector<string> decryptedNote = Decrypt(encryptedNote);
	//add password as new first line of note to pass it back
	decryptedNote.insert(decryptedNote.begin(), decryptedPassword);
	return decryptedNote;

}