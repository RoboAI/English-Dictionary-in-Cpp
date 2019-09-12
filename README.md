# English-Dictionary-in-Cpp
An English Dictionary using definitions from The Project Gutenberg EBook of Webster's Unabridged Dictionary

https://www.gutenberg.org/ebooks/673

## Embedded and Windows

The project is currently a Console app for windows.

I have written a function to convert the dictionary definitions into an 'indexing file'.

FullWordList.txt has these indexes:
[the first number is the starting pointer for the defintions file, and the second number the ending pointer]

DEFUSE:6582911;6583013
DEFY:6583013;6583950
DEFY:6583950;6584007
DEGAGE:6584007;6584196
DEGARNISH:6584196;6584636
DEGARNISHMENT:6584636;6584755

This code was designed to also run on an embedded environment with minimal code. Some well-known functions have been re-written (or pasted) to have minimal compile/code for the embedded enviroment.

CDictionaryIOBase has the base functions. CDIOWindows and CDIOEmbedded derive from this class, modifying the functionality to suit the embedded chips. The CDIOEmbedded class has most of the 're-written' functions. The CDIOWindows uses traditional windows libraries.

A quick peek into the CDictionaryBase class

```cpp
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

public:
	T m_dictionary_handle;
	FileLoc	m_file_location;
	bool	m_bGood;
	bool	m_isOpen;
};
```

MyDictionary.cpp is the starting point..
