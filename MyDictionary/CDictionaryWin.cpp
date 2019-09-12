#ifndef _CDICTIONARY_WIN_h__
#define _CDICTIONARY_WIN_h__

#include "CDictionaryWin.h"


CDictionaryWin::CDictionaryWin()
{
	init();
}

CDictionaryWin::~CDictionaryWin()
{
	deinit();
}

void CDictionaryWin::init()
{
}

void CDictionaryWin::deinit()
{
	close();
}

bool CDictionaryWin::open(dictionary_filename& dict_filename, dictionary_filename& words_filename)
{
	if (m_definitions_file.is_open() || m_wordslist_file.is_open())
		return false;

	m_definitions_file.open(dict_filename);
	m_wordslist_file.open(words_filename);
	
	if (m_definitions_file.good() && m_wordslist_file.good())
		return true;
	else
		return false;
}

void CDictionaryWin::close()
{
	m_definitions_file.close();
	m_wordslist_file.close();
}

char* CDictionaryWin::find_definition(char* search_word)
{
	return nullptr;
}

char* CDictionaryWin::find_word(char* search_word)
{
	return nullptr;
}

char* CDictionaryWin::getline_wordslist()
{
	return nullptr;
}


#endif