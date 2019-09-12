#pragma once

#include "CDIOWindows.h"
#include "defines.h"


class CDictionaryWords : public CDIOWindows
{
public:
	CDictionaryWords();
	~CDictionaryWords();

	int				findWord(std::string& searchWord);
public:

	void			clearStruct(SearchReturn& search);
	bool			isLetter(int c);
	std::string&	convertToUpper(std::string& searchWord);
	bool			verifySearchWord(std::string& searchWord);
	bool			extractDefinitionStartEnd(std::string& line, SearchReturn& search);

public:
	SearchReturn	m_search;
	std::string		m_last_read_line;
};

