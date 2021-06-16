#pragma once
#include <iostream>
#include "List.h"
using namespace std;
class References {
public:
	References();
	References(const char* _word, int* _pages, int size);
	bool operator!=(const References& Reference);
	bool IsMore(int a);
	const char* Get_Word();
	void Correct(const char* s);
	bool Data_Processing(char* s, int counter);
	friend ostream& operator<<(ostream& stream, References& obj);
private:
	char* word;
	int* pages;//pages numbers
	int _size;//number of pages
	int max_size = 300;
};
