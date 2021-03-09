#include <iostream>
#include "Note.h"

int main() {
	Note note = Note("New title", "contents");
	string someString;

	note.GetTitle(someString);
	std::cout << someString << std::endl;
	note.GetContents(someString);
	std::cout << someString << std::endl;

	note.WritetoFile("C:\\Users\\Kevin\\Documents\\Schooling\\College 2\\Classes\\Semester 2\\CSCN71030-Proj2-Team Based Software");
	note.Delete();

	string path = "C:\\Users\\Kevin\\Documents\\Schooling\\College 2\\Classes\\Semester 2\\CSCN71030-Proj2-Team Based Software\\test.note";
	note = Note::Open(path);

	note.GetTitle(someString);
	std::cout << someString << std::endl;
	note.GetContents(someString);
	std::cout << someString << std::endl;
	
	return 0;
}