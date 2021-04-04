/* Copyright 2021 Carson Stabell */
/* FileWriter (in header file) */

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class FileWriter {
private:
	const std::string optionsFilePath = "../options/options.dat";
	std::vector<option> optionList; //Will store all the options in a list


public:
	FileWriter();
	//Functions for the options file
	void initOption();
	option getOption(int opNum);
	option getOption(std::string opName);

};

//Small option class to better hold data for file IO
class option {
public:
	std::string name = "";
	std::string value = "";
};

FileWriter::FileWriter() {
	initOption();
}

//Will init the Option file and read in all data
void FileWriter::initOption() {
	std::fstream optionFile;
	optionFile.open(optionsFilePath, std::ios::in);
	if (!optionFile.is_open()) {
		std::cout << "Options File failed to open!";
		return;
	}
	std::string line;
	while (!optionFile.eofbit) {
		line = optionFile.;
	}


}


#endif //FILEWRITER_H