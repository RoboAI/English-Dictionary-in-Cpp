#include "stdafx.h"
#include "CDIOWindows.h"
#include <string>


CDIOWindows::CDIOWindows()
{
	init();
}

CDIOWindows::~CDIOWindows()
{
	deinit();
}

void CDIOWindows::deinit()
{
	close();
}

void CDIOWindows::init()
{
	m_isOpen = false;
	m_bGood = false;
	clearBuffer();
}

void CDIOWindows::open(dictionary_filename& filename)
{
	close();
	m_file_location.assign(filename);
	m_dictionary_handle.open(filename, std::ifstream::in);
	m_bGood = m_dictionary_handle.good();
}

void CDIOWindows::close()
{
	m_dictionary_handle.close();
}

bool CDIOWindows::good()
{
	return m_bGood = m_dictionary_handle.good();
}

bool CDIOWindows::is_open()
{
	return m_dictionary_handle.is_open();
}

bool CDIOWindows::eof()
{
	return m_dictionary_handle.eof();
}

void CDIOWindows::getline(char* pbuffer, sys_int nsize)
{
	m_dictionary_handle.getline(pbuffer, nsize);
}

void CDIOWindows::read(char* pbuffer, sys_int ncount)
{
	m_dictionary_handle.read(pbuffer, ncount);
}

char * CDIOWindows::getline()
{
	getline(m_clast_read_line, sizeof(m_clast_read_line));
	return m_clast_read_line;
}

char * CDIOWindows::read(sys_int ncount)
{
	read(m_clast_read_line, ncount);
	return m_clast_read_line;
}

void CDIOWindows::clearBuffer()
{
	memset(m_clast_read_line, 0, sizeof(m_clast_read_line));
}

/*
std::string& CDictionaryIOWindows::getline()
{
	std::getline(m_dictionary_handle, m_last_read_line);
	return m_last_read_line;
}*/
/*
char * CDictionaryIOWindows::getReadLine()
{
	return m_clast_read_line;
}*/