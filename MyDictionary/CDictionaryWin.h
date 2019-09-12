#ifndef _CDICTIONARY_WIN_H_
#define _CDICTIONARY_WIN_H_


#include "CDIOWindows.h"
#include "defines.h"

class CDictionaryWin
{
public:
	CDictionaryWin();
	~CDictionaryWin();

	void init();
	void deinit();

	bool open(dictionary_filename& dict_filename, dictionary_filename& words_filename);
	void close();
	
	char* find_definition(char* search_word);
	char* find_word(char* search_word);
	char* getline_wordslist();

public:
	CDIOWindows	m_definitions_file;
	CDIOWindows	m_wordslist_file;
};
/*
std::string& convertToUpper(std::string& searchWord);
bool isLetter(int c);
bool verifySearchWord(std::string& searchWord);
std::string& getReadFileName(std::string& fileName, char c);
std::string& getWriteFileName(std::string& fileName, char c);
std::string& getFullDictionaryDirRead(std::string& fileName);
std::string& getFullDictionaryDirWrite(std::string& fileName);
template<class T> bool verifyFileOpen(T& file);
int findTextInStream(std::ifstream& file, std::string& textToFind);
bool isValidWord(std::string& line);
int findNextValidWord(std::ifstream& file, std::string& stringFound, long* pStringLoc);

bool generateWordsSingleFile(char wordLetter);
int generateWordsSingleFile(std::string& sFileNameRead, std::string& sFileNameWrite);
int generateWordsSingleFile(std::ifstream& in_file, std::ofstream& out_file);
void generateAllWordFiles();
int generateFullListFile(std::string& sFileNameRead, std::string& sFileNameWrite);
bool generateFullListFile();
*/

#endif
