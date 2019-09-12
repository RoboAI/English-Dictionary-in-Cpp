#include "stdafx.h"
#include "CDictionaryWords.h"
#include <algorithm>
#include <sstream>


CDictionaryWords::CDictionaryWords()
{
}

CDictionaryWords::~CDictionaryWords()
{
}

void CDictionaryWords::clearStruct(SearchReturn & search)
{
//	search.found_word.clear();
	
	memset(search.found_word_char, 0, sizeof(search.found_word_char));
	search.def_begin = 0;
	search.def_end = 0;
	search.def_size = 0;
}

bool CDictionaryWords::isLetter(int c)
{
	if (((c >= 'A') && (c <= 'Z')) ||
		((c >= 'a') && (c <= 'z'))) {
		return true;
	}
	else
		return false;
}

std::string & CDictionaryWords::convertToUpper(std::string & searchWord)
{
	std::transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::toupper);
	return searchWord;
}


bool CDictionaryWords::verifySearchWord(std::string & searchWord)
{
	if (searchWord.empty())
		return false;

	int length = searchWord.length();

	for (int i = 0; i < length; i++)
	{
		int c = static_cast<int>(searchWord[i]);

		if (!isLetter(c)) {
			return false;
		}
	}

	return true;
}

bool CDictionaryWords::extractDefinitionStartEnd(std::string& line, SearchReturn& search)
{
	clearStruct(search);

	size_t pos = 0;
	size_t pos2 = 0;
	std::string s;
	
	if ( (pos = line.find_first_of(WORD_SEPARATOR)) != std::string::npos) {//we have found it
		if ( (pos2 = line.find_first_of(ADDRESS_SEPARATOR, pos + 1)) != std::string::npos) {
			s = line.substr(0, pos);
			std::memcpy(search.found_word_char, s.data(), s.length());

			std::stringstream ss1(line.substr(pos + 1, pos2 - pos));//+ 1 is to skip ':'
			ss1 >> search.def_begin;

			std::stringstream ss2(line.substr(pos2 + 1));// +1 is to skip ';'
			ss2 >> search.def_end;

			search.def_size = search.def_end - search.def_begin;
			return true;
		}
	}

	return false;
}

int CDictionaryWords::findWord(std::string& searchWord)
{
	if (!verifySearchWord(searchWord))
		return ERROR_BASIC;

	convertToUpper(searchWord);
	
	while (!eof()) {
		clearBuffer();//clears m_clast_read_line
		if (getline() != NULL) {//reads line from file and puts it into m_clast_read_line
			m_last_read_line = m_clast_read_line;
			extractDefinitionStartEnd(m_last_read_line, m_search);//extract details from line
			if (searchWord.compare(m_search.found_word_char) == 0) {//if found the word, then return success
				return ERROR_NONE;

				//LAST EDIT
				//change the function back to using the std::string versions of other functions
			}
		}
	}

	return ERROR_WORD_NOT_FOUND;
}
