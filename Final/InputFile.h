#pragma once

#include <string>

class InputFile
{
public:
	bool Read(std::string filename);
	std::string getContents();

private:
	std::string _contents;
};