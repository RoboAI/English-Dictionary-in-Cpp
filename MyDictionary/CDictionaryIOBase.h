#ifndef _CDICTIONARY_IO_BASE_H__
#define _CDICTIONARY_IO_BASE_H__

#include <iostream>
#include "dict_typedefs.h"
#include "defines.h"

typedef int		sys_int;
typedef int		error_code;

struct SearchReturn
{
	char		found_word_char[LONGEST_WORD];
//	std::string	found_word;
	long		def_begin;
	long		def_end;
	long		def_size;
};

template<typename T, typename FileLoc>
class CDictionaryIOBase
{
public:
	CDictionaryIOBase() {}
	~CDictionaryIOBase() {}

	virtual void init() = 0;
	virtual void deinit() = 0;
	virtual void open(FileLoc& file) = 0;
	virtual void close() = 0;
	virtual bool good() = 0;
	virtual bool is_open() = 0;
	virtual bool eof() = 0;
	virtual void getline(char* pbuffer, sys_int nsize) = 0;
	virtual void read(char* pbuffer, sys_int nsize) = 0;

//	virtual void findWord(char* word_to_find, SearchReturn& search_found) = 0;

public:
	T		m_dictionary_handle;
	FileLoc	m_file_location;
	bool	m_bGood;
	bool	m_isOpen;
};

#endif

