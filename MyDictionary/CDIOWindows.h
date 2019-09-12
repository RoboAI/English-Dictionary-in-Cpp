#ifndef _CDIO_WIN_H__
#define _CDIO_WIN_H__

#include <fstream>

#include "CDictionaryIOBase.h"
#include "defines.h"


typedef std::ifstream		dictionary_handle;
typedef std::string			dictionary_filename;

//this class will only implement these functions. make a new class and have two member variables of type
//CDictionaryIOWindows, one for the dictionary, and one for the words list.
class CDIOWindows 
	: public CDictionaryIOBase<dictionary_handle, dictionary_filename>
{
public:
	CDIOWindows();
	~CDIOWindows();

	void	init();
	void	deinit();

	void	open(dictionary_filename& filename);
	void	close();
	bool	good();
	bool	is_open();
	bool	eof();
	void	getline(char* pbuffer, sys_int nsize);
	void	read(char* pbuffer, sys_int ncount);

	char*	getline();
	char*	read(sys_int ncount);
	void	clearBuffer();

public:
	char	m_clast_read_line[LONGEST_LINE];
};

#endif

