// MyDictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

#include "CDIOWindows.h"
#include "CDictionaryWords.h"
#include "CEmbeddedDictionary.h"

void printMenu() {
	std::cout << "Dictionary!!!" << "\n" << std::endl;
	std::cout << "Enter word: ";
}

void printExit() {
	std::cout << "BYE!!!!" << std::endl;
}

char* getChoice(char* temp) {
	std::cin >> temp;
	return temp;
}

std::string& getSearchWord(std::string& searchWord) 
{
	std::cout << "enter search word: ";
	std::cin >> searchWord;
	return searchWord;
}

void extractWord(std::string& line, std::string& out_string)
{
	size_t pos = line.find_first_of(':');
	if (pos != std::string::npos)//we have found it
		out_string = line.substr(0, pos);
}

bool extractDefinitionStartEnd(std::string& line, std::string& out_string, long* pStart, long* pEnd)
{
	long loc = 0;

	size_t pos = line.find_first_of(':');
	if (pos != std::string::npos) {//we have found it
		out_string = line.substr(0, pos);
		size_t pos2 = line.find_first_of(';', pos + 1);
		if (pos2 != std::string::npos){
			std::stringstream ss(line.substr(pos + 1, pos2 - pos));
			ss >> loc;
			*pStart = loc;

			std::stringstream ss2(line.substr(pos2 + 1));
			ss2 >> loc;
			*pEnd = loc;
			return true;
		}
	}

	return false;
}

void doDictionaryFullFile()
{
	std::string line = "";
	std::string found_def = "";
	char def[LARGEST_DEFINITION + 10];

	while (true) {
		memset(def, 0, sizeof(def));

		std::cout << "Enter word to search: ";
		std::cin >> line;
		std::cout << "searching for " << line << "..." << std::endl;

		CDictionaryWords file;
		std::ifstream file_dictionary;
		file.open(std::string("dictionary/FullWordList.txt"));
		file_dictionary.open("dictionary/29765-8.txt", std::ifstream::in);
		//11,679,728

		if (file.findWord(line) == ERROR_NONE)
		{//file.findWord() fills its member function m_search, so use it here
			found_def.reserve(file.m_search.def_size);
			file_dictionary.seekg(file.m_search.def_begin);
			file_dictionary.read(def, file.m_search.def_size);
			std::cout << "found text:\n" << std::endl;
			std::cout << def << std::endl;
		}
		else
			std::cout << "'" << line << "' " << "not found" << std::endl;

		file.close();
		file_dictionary.close();

		std::cout << "\n\n";
	}

	std::cin >> line;

}

void doEmbedded() {
	CEmbeddedDictionary em;
	em.open(std::string("dictionary/29765-8.txt"), std::string("dictionary/FullWordList.txt"));
	char find_text[20] = "";
	char* pdef = NULL;
	SearchReturn r;

	while (true) {
		em.clearStruct(r);
		std::cout << "Enter word to find: ";
		std::cin >> find_text;
		std::cout << std::endl;
		std::cout << "searching for " << find_text << "\n" << std::endl;

		if (em.findWord(find_text, r) == ERROR_NONE) {
			pdef = em.getDefinition(r);
			std::cout << "text found.." << "\n" << std::endl;
			std::cout << pdef << "\n" << std::endl;
			std::cout << "length is: " << strlen(pdef) << "\n" << std::endl;
		}
	}
}

int main()
{
	doDictionaryFullFile();
}