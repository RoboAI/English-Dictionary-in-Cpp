#include "CEmbeddedDictionary.h"

CEmbeddedDictionary::CEmbeddedDictionary()
{
}

CEmbeddedDictionary::~CEmbeddedDictionary()
{
}

char* CEmbeddedDictionary::getDefinition(SearchReturn& find_result)
{
	m_definitions_file.seek(find_result.def_begin);
	m_definitions_file.read(m_definition, find_result.def_size);
	m_definition[find_result.def_size] = '\0';
	return m_definition;
}
						 
int CEmbeddedDictionary::findWord(char* line, SearchReturn& find_result) {
	if (line == NULL)
		return ERROR_BASIC;

	if (this->verifySearchWord(line) == false)
		return ERROR_BASIC;

	this->convertToUpper(line);

	while (!this->m_wordslist_file.eof()) {
		if (this->m_wordslist_file.getline() != NULL) {//reads line from file and puts it into m_clast_read_line
			extractDefinitionStartEnd(this->m_wordslist_file.m_clast_read_line, find_result);//extract details into find_result
			if (this->compare_string(line, find_result.found_word_char) == STRING_MATCH) {//if found the word, then return success
				m_wordslist_file.seek(0);
				return ERROR_NONE;
			}
		}
	}

	m_wordslist_file.seek(0);

	return ERROR_WORD_NOT_FOUND;
}

bool CEmbeddedDictionary::open(dictionary_filename& dict_filename, dictionary_filename& words_filename)
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

void CEmbeddedDictionary::close()
{
	m_definitions_file.close();
	m_wordslist_file.close();
}

bool CEmbeddedDictionary::isLetter(int c)
{
	if (((c >= 'A') && (c <= 'Z')) ||
		((c >= 'a') && (c <= 'z'))) {
		return true;
	}
	else
		return false;
}

void CEmbeddedDictionary::clearStruct(SearchReturn& data) {
	this->memset(data.found_word_char, 0, sizeof(data.found_word_char));
	data.def_begin = 0;
	data.def_end = 0;
	data.def_size = 0;
}


char * CEmbeddedDictionary::convertToUpper(char* line) {
	if (line == NULL)
		return NULL;

	char* p = line;

	while (*p != NULL) {
		if ((*p >= (int)'a') && (*p <= (int)'z'))
			*p -= 32;
		p++;
	}

	return line;
}

bool CEmbeddedDictionary::verifySearchWord(const char* line) {
	if (line == NULL)
		return false;

	while (*line != NULL) {
		if (!isLetter(*line++))
			return false;
	}

	return true;
}

bool CEmbeddedDictionary::extractDefinitionStartEnd(const char * pline, SearchReturn & search) {
	if (pline == NULL)
		return false;

	int pos = 0;
	int pos2 = 0;
	int len = this->strlen(pline);
	char s_word_location[20];
	char s_address_location[20];

	this->memset(s_word_location, 0, sizeof(s_word_location));
	this->memset(s_address_location, 0, sizeof(s_address_location));
	this->clearStruct(search);

	if (findChar(WORD_SEPARATOR, pline, &pos) == true) {
		if (findChar(ADDRESS_SEPARATOR, pline, &pos2) == true) {
			this->memcpy(search.found_word_char, sizeof(search.found_word_char), pline, 0, pos);
			this->memcpy(s_word_location, sizeof(s_word_location), pline, pos + 1, pos2 - (pos + 1));
			this->memcpy(s_address_location, sizeof(s_address_location), pline, pos2 + 1, len - (pos2 + 1));

			if (this->stoi(s_word_location, &search.def_begin) != ERROR_NONE)
				return false;

			if (this->stoi(s_address_location, &search.def_end) != ERROR_NONE)
				return false;

			search.def_size = search.def_end - search.def_begin;

			return true;
		}
	}

	return false;
}

bool CEmbeddedDictionary::findChar(char c, const char * pline, int* out_pos)
{
	if ((pline == NULL) || (out_pos == NULL))
		return false;

	while (*pline != NULL) {
		if (*pline == c) {
			return true;
		}
		pline++;
		(*out_pos)++;
	}

	return false;
}

int CEmbeddedDictionary::strlen(const char* str) {
	if (str == NULL)
		return 0;

	int len = 0;
	while (str[len] != NULL) {
		len++;
	}

	return len;
}

void CEmbeddedDictionary::memset(char* _Dest, char val, int size) {
	if (_Dest == NULL || size <= 0)
		return;

	while (size--) {
		*_Dest++ = val;
	}
}

char* CEmbeddedDictionary::memcpy(char* dest, int dest_size, const char* src) {
	if (dest == NULL || src == NULL || dest_size <= 0)
		return NULL;

	while ((*src != NULL) && (dest_size-- > 0)) {
		*dest++ = *src++;
	}

	return dest;
}

char* CEmbeddedDictionary::memcpy(char* dest, int dest_size, const char* src, int src_from, int count) {
	return this->memcpy(dest, (dest_size < count) ? dest_size : count, &src[src_from]);
}

int CEmbeddedDictionary::compare_string(const char* str1, const char* str2) {
	if (str1 == NULL || str2 == NULL)
		return STRING_NO_MATCH;

	while (*str1 == *str2) {
		if (*str1 == '\0')//we should also check *str2 but since they match at this point, its not necessary
			return STRING_MATCH;
		str1++; str2++;
	}

	return STRING_NO_MATCH;//return false as they dont match
}

int CEmbeddedDictionary::stoi(char * line, long* out_value)
{
	if ((line == NULL) || (out_value == NULL))
		return ERROR_BASIC;

	if (*line == '\0')
		return ERROR_BASIC;

	bool isNegative = false;

	//if negative, then skip sign and set negative-flag
	if (*line == '-') {
		line++;//skip the negative sign
		isNegative = true;
	}

	//do the conversion
	*out_value = this->stoi_nocheck(line, out_value);

	//make negative if needed
	if (isNegative == true)
		*out_value *= -1;

	return ERROR_NONE;
}

inline int CEmbeddedDictionary::stoi_nocheck(char * line, long * out_value)
{
	//do the conversion (from StackOverflow)
	while (*line != '\0') {
		*out_value = (*out_value * 10) + (*line - '0');
		++line;
	}

	return *out_value;
}