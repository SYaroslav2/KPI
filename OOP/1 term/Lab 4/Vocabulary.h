#define _CRT_SECURE_NO_WARNINGS


#pragma once



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>



#pragma warning (disable : 6011)
#pragma warning (disable : 6386) 
#pragma warning (disable : 6387) 
#pragma warning (disable : 4715)
#pragma warning (disable : 26495)



class Vocabulary
{
	friend class CBinTree;
	char m_EngWord[128];
	int m_Page;
	char m_ItaWord[128];

public:

	void operator=(Vocabulary from) {
		strcpy(m_EngWord, from.m_EngWord);
		m_Page = from.m_Page;
		strcpy(m_ItaWord, from.m_ItaWord);
	}

	void print();

};