#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Note.h"

//Constructors
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
	string title;
	string contents;

	fstream fileStream;
	fileStream.open(filePath, ios::in);
	if (fileStream.is_open())
	{
		getline(fileStream, title);
		getline(fileStream, contents);

		fileStream.close();
	}
	Note newNote = Note(title, contents);
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
		fileStream << this->title << endl;
		fileStream << this->contents << endl;

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