#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include "Note.h"

//private constants
const string Note::openingBrackets = "{{";
const string Note::closingBrackets = "}}";
const char Note::encryptionChar = '#';

//Constructors
Note::Note() : Note("", "", false, "") { }

Note::Note(string title, string contents) : Note(title, contents, false, "") { }

Note::Note(string title, string contents, bool isEncrypted, string password)
{
	this->title = title;
	this->contents = contents;
	this->isEncrypted = isEncrypted;

	this->SetPassword(password);
}

//private functions
void Note::SetPath(string path)
{
	this->path = path;
}

void Note::ReadNoteField(string temp, string& field, fstream& fileStream)
{
	if (temp.substr(0, 2) == openingBrackets)
	{
		if (temp.substr(temp.length() - 2) == closingBrackets)
		{
			field = temp.substr(2, temp.length() - 4);
		}
		else
		{
			field = temp.substr(2);
			while (getline(fileStream, temp))
			{
				if (temp.substr(temp.length() - 2) == closingBrackets)
				{
					field += temp.substr(0, temp.length() - 2);
					break;
				}
				field += temp;
			}
		}
	}
}

//public functions
PasswordState Note::GetTitle(string& title)
{
	if (passwordState == PasswordState::Locked)
	{
		return passwordState;
	}
	title = this->title;
	return passwordState;
}

PasswordState Note::GetContents(string& contents)
{
	if (passwordState == PasswordState::Locked)
	{
		return passwordState;
	}
	contents = this->contents;
	return passwordState;
}

void Note::SetIsEncrypted(bool isEncrypted)
{
	this->isEncrypted = isEncrypted;
}

void Note::SetPassword(string password)
{
	this->password = password;
	if (password != "")
	{
		this->SetIsEncrypted(true);
		this->isPasswordProtected = true;
		this->passwordState = PasswordState::Unlocked;
	}
	else
	{
		this->isPasswordProtected = false;
		this->passwordState = PasswordState::None;
	}
}

Note Note::Open(string filePath)
{
	string temp;
	string title;
	string contents;
	string encryptionKey;
	string password;

	vector<string> readStrings;

	fstream fileStream;
	fileStream.open(filePath, ios::in);
	if (fileStream.is_open())
	{
		if (!getline(fileStream, temp))
		{
			return Note(); //empty
		}

		//get encryption key, if exists
		if (temp[0] == encryptionChar) //encrypted
		{
			encryptionKey = temp.substr(1);
			if (!getline(fileStream, temp))
			{
				return Note(); //no title/contents
			}
		}

		//get title, required
		Note::ReadNoteField(temp, title, fileStream);
		readStrings.push_back(title);

		//get content, required
		if (!getline(fileStream, temp))
		{
			return Note(); //no contents
		}
		Note::ReadNoteField(temp, contents, fileStream);
		readStrings.push_back(contents);

		//get password
		if (getline(fileStream, temp))
		{
			Note::ReadNoteField(temp, password, fileStream);
			readStrings.push_back(password);
		}

		fileStream.close();
	}

	Note newNote = Note(); //define a Note variable
	//call decryption
	if (encryptionKey != "")
	{
		readStrings.push_back(encryptionKey);
		vector<string> decryptedStrings = readStrings;
		//vector<string> decryptedStrings = Decrypt(readStrings);
		if (decryptedStrings.size() > 2)
		{
			newNote = Note(decryptedStrings[0], decryptedStrings[1], true, decryptedStrings[2]);
		}
		else
		{
			newNote = Note(decryptedStrings[0], decryptedStrings[1], true, "");
		}
	}
	else
	{
		newNote = Note(title, contents);
	}

	newNote.SetPath(filePath);
	return newNote;
}

void Note::WritetoFile(string directoryPath)
{
	fstream fileStream;
	time_t now = time(0);
	tm* timeStruct = new tm;
	localtime_s(timeStruct, &now);

	stringstream stream;
	//create file name based on current date and time
	stream << directoryPath << "\\" << (1900 + timeStruct->tm_year) << setw(2) << setfill('0') << (1 + timeStruct->tm_mon)
		<< setw(2) << setfill('0') << timeStruct->tm_mday << "-" << setw(2) << setfill('0') << timeStruct->tm_hour
		<< setw(2) << setfill('0') << timeStruct->tm_min << setw(2) << setfill('0') << timeStruct->tm_sec << ".note";
	this->path = stream.str();

	fileStream.open(this->path, ios::out);
	if (fileStream.is_open())
	{
		if (this->isEncrypted)
		{
			//call encryption
			vector<string> noteStrings;
			noteStrings.push_back(this->title);
			noteStrings.push_back(this->contents);
			if (this->isPasswordProtected)
			{
				noteStrings.push_back(this->password);
			}

			vector<string> encryptedStrings = noteStrings;
			encryptedStrings.push_back("!@#"); //remove this
			//vector<string> encryptedStrings = Encrypt(noteStrings);
			string encrytionKey = encryptedStrings.back();
			fileStream << "#" << encrytionKey << endl;
			for (vector<string>::iterator i = encryptedStrings.begin(); i != encryptedStrings.end() - 1; i++)
			{
				fileStream << openingBrackets << *i << closingBrackets << endl;
			}
		}
		else
		{
			fileStream << openingBrackets << this->title << closingBrackets << endl;
			fileStream << openingBrackets << this->contents << closingBrackets << endl;
			if (this->isPasswordProtected)
			{
				fileStream << openingBrackets << this->password << closingBrackets << endl;
			}
		}

		fileStream.close();
	}
}

void Note::Delete()
{
	remove(this->path.c_str());
}

PasswordState Note::CheckPassword(string passwordEntry)
{
	if (this->passwordState == PasswordState::Locked && this->password == passwordEntry)
	{
		this->passwordState = PasswordState::Unlocked;
	}
	return this->passwordState;
}

bool Note::IsEmptyNote()
{
	if (this->title == "" || this->contents == "")
	{
		return true;
	}
	return false;
}

Note::~Note()
{
	//delete any manually allocated memory
}