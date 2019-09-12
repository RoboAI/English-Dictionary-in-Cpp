//#include "stdafx.h"
#include "CDIOEmbedded.h"
#include <string>
#include <cstring>


CDIOEmbedded::CDIOEmbedded()
{
	init();
}

CDIOEmbedded::~CDIOEmbedded()
{
	deinit();
}

void CDIOEmbedded::deinit()
{
	close();
}

void CDIOEmbedded::init()
{
	m_isOpen = false;
	m_bGood = false;
	clearBuffer();
}

void CDIOEmbedded::open(dictionary_filename& filename)
{
	close();
	m_file_location.assign(filename);
	m_dictionary_handle.open(filename, std::ifstream::in);
	m_bGood = m_dictionary_handle.good();
}

void CDIOEmbedded::close()
{
	m_dictionary_handle.close();
}

bool CDIOEmbedded::good()
{
	return m_bGood = m_dictionary_handle.good();
}

bool CDIOEmbedded::is_open()
{
	return m_dictionary_handle.is_open();
}

bool CDIOEmbedded::eof()
{
	return m_dictionary_handle.eof();
}

void CDIOEmbedded::seek(int pos) 
{
	m_dictionary_handle.seekg(pos);
}

void CDIOEmbedded::getline(char* pbuffer, sys_int nsize)
{
	m_dictionary_handle.getline(pbuffer, nsize);
}

void CDIOEmbedded::read(char* pbuffer, sys_int ncount)
{
	m_dictionary_handle.read(pbuffer, ncount);
}

char * CDIOEmbedded::getline()
{
	getline(m_clast_read_line, sizeof(m_clast_read_line));
	return m_clast_read_line;
}

char * CDIOEmbedded::read(sys_int ncount)
{
	read(m_clast_read_line, ncount);
	return m_clast_read_line;
}

void CDIOEmbedded::clearBuffer()
{
	for (int i = 0; i < sizeof(m_clast_read_line); i++)
		m_clast_read_line[i] = 0;
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
