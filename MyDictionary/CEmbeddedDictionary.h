#ifndef _CEMBEDDED_DICTIONARY_H__
#define _CEMBEDDED_DICTIONARY_H__

#include "dict_typedefs.h"
#include "CDictionaryIOBase.h"
#include "CDIOEmbedded.h"

//typedef unsigned long		dictionary_handle;
typedef dictionary_handle	file_dictionary;

class CEmbeddedDictionary{
public:
	CEmbeddedDictionary();
	~CEmbeddedDictionary();

	char*			getDefinition(SearchReturn& find_result);
	int				findWord(char* line, SearchReturn& find_result);
	void			clearStruct(SearchReturn& data);

	bool			open(dictionary_filename& dict_filename, dictionary_filename& words_filename);
	void			close();

protected:
	bool			isLetter(int c);
	char*			convertToUpper(char* line);
	bool			verifySearchWord(const char* line);
	bool			extractDefinitionStartEnd(const char* pLine, SearchReturn& search);
	bool			findChar(char c, const char* pline, int* out_pos);
	int				strlen(const char* str);
	void			memset(char* _Dest, char val, int size);
	char*			memcpy(char* dest, int size, const char* src);
	char*			memcpy(char* dest, int dest_size, const char* src, int src_from, int src_to);
	int				compare_string(const char* str1, const char* str2);
	int				stoi(char* line, long* out_value);
	int				stoi_nocheck(char* line, long* out_value);

public:
	CDIOEmbedded	m_definitions_file;
	CDIOEmbedded	m_wordslist_file;
	char			m_definition[LARGEST_DEFINITION];

};

#endif
