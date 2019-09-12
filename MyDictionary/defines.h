#ifndef _DEFINES_H_
#define _DEFINES_H_

#define ERROR_BASIC					-1
#define ERROR_DICTIONARY_END		-2
#define ERROR_NONE					-3
#define ERROR_WORD_NOT_FOUND		-4

#define STRING_MATCH				0
#define STRING_NO_MATCH				-1

#define LARGEST_DEFINITION			13435//enough space to hold largest definition (bytes)
#define LONGEST_WORD				100//enough space to hold longest word
#define LONGEST_LINE				100//enough space to hold longest line
#define WORD_SEPARATOR				':'
#define ADDRESS_SEPARATOR			';'

#define START_OF_DICTIONARY			"[START]"//start tag in dictionary
#define END_OF_DICTIONARY			"[END]"//end tag in dictionary

#define FILE_EXT					".txt"
#define DIR_DICTIONARY				"dictionary/"//dictionary folder
#define DIR_WORDS					"words/"//words-list folder for alphabet files
#define DIR_DEFINITIONS				"defs/"//definitions folder for alphabet definitions
#define WORDS_PREFIX				"words"//prefix for alphabet files. e.g. wordsA.txt
#define FULL_DICTIONARY_FILENAME	"29765-8.txt"//actual dictionary with words and definitions
#define FULL_WORDS_LIST_FILENAME	"FullWordList.txt"



#endif