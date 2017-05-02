#include "InputFile.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool InputFile::Read(string filename) {
		string line;
		ifstream myfile(filename);
		_contents = "";
		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				_contents += line + '\n';
			}
			myfile.close();
			return true;
		}
		return false;
}


std::string InputFile::getContents() {
		return _contents;
}