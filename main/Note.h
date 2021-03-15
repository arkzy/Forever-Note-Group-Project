#pragma once
#include <iostream>

using namespace std;

enum class PasswordState { None, Locked, Unlocked };

class Note
{
private:
	string title;
	string contents;
	string password;
	string path;
	bool isEncrypted;
	bool isPasswordProtected;
	PasswordState passwordState;

	static const string openingBrackets;
	static const string closingBrackets;
	static const char encryptionChar;

	void SetPath(string);
	static void ReadNoteField(string, string&, fstream&);

public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	Note();
	/// <summary>
	/// Parameterized Note Constructor
	/// </summary>
	/// <param name="title"></param>
	/// <param name="contents"></param>
	Note(string, string);
	/// <summary>
	/// Parameterized Note Constructor
	/// </summary>
	/// <param name="title"></param>
	/// <param name="contents"></param>
	/// <param name="isEncrypted"></param>
	/// <param name="password"></param>
	Note(string, string, bool, string);
	/// <summary>
	/// Destructor
	/// </summary>
	~Note();

	/// <summary>
	/// Get the Note's title, returns the PasswordState.
	/// Given string is not altered if PasswordState is Locked
	/// </summary>
	/// <param name="">becomes title of Note if unlocked</param>
	/// <returns>State of the Password</returns>
	PasswordState GetTitle(string&);
	/// <summary>
	/// Get the Note's contents, returns the PasswordState.
	/// Given string is not altered if PasswordState is Locked
	/// </summary>
	/// <param name="">becomes contents of Note if unlocked</param>
	/// <returns>State of the Password</returns>
	PasswordState GetContents(string&);

	/// <summary>
	/// Set isEnctypted flag
	/// </summary>
	/// <param name="isEncrypted"></param>
	void SetIsEncrypted(bool);
	/// <summary>
	/// Set the password
	/// </summary>
	/// <param name="password"></param>
	void SetPassword(string);
	
	/// <summary>
	/// Opens the given file and returns the Note read from file
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns>read Note</returns>
	static Note Open(string);

	/// <summary>
	/// Writes the Note to a file
	/// </summary>
	/// <param name="directoryPath"></param>
	void WritetoFile(string);
	//void Edit();
	void Delete();
	PasswordState CheckPassword(string);

	bool IsEmptyNote();
};

