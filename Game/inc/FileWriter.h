/* Copyright 2021 Carson Stabell */
/* FileWriter (in header file) */

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <fstream>
#include <vector>


class FileWriter {
private:
	const std::string optionsFilePath = "../options/options.txt";
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
	optionFile.open(optionsFilePath);
	if (!optionFile.is_open()) {
		std::cout << "Options File failed to open!";
		return;
	}

}


#endif //FILEWRITER_H