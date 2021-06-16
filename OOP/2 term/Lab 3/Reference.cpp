#define _CRT_SECURE_NO_WARNINGS

#include "Reference.h"
#include "List.h"
#include <iomanip>



References::References() {
	_size = 0;
	word = NULL;
	pages = NULL;
}



References::References(const char* _word, int* _pages, int size) {

	if (_word == NULL || size > 300 || size < 0) {
		abort();
	}

	int WordSize = strlen(_word);
	_size = size;
	pages = _pages;
	word = new char[WordSize + 1];
	strcpy(word, _word);
	word[WordSize] = '\0';
	
}



bool References::operator!=(const References& Reference)
{
	if (this == NULL) return true;
	if (strcmp(this->word, Reference.word) != 0) {
		return true;
	}
	return false;
}


bool References::Data_Processing(char* s, int counter) {
	if (counter == 0 || counter > 302) return false;
	char* str_ptr;
	str_ptr = s;
	word = new char[strlen(str_ptr) + 1];
	strcpy(word, str_ptr);
	word[strlen(str_ptr)] = '\0';
	str_ptr += strlen(str_ptr) + 1;
	int* arr = new int[counter - 2];
	int i;
	for (i = 0; i < counter - 2; i++) {
		arr[i] = atoi(str_ptr);
		str_ptr += strlen(str_ptr) + 1;
	}
	pages = arr;
	_size = atoi(str_ptr);
	if (_size > max_size || _size < 0 || _size != counter - 2) return false;
	
	return true;
}



bool References::IsMore(int a) {
	if (a < 0 || a > 300) 
		return false;
	
	if (a <_size) return true;
	return false;
}



const char* References::Get_Word() {

	return word;
}



void References::Correct(const char* newWord) {
	delete[] word;
	word = NULL;

	if (newWord == NULL) {
		abort();
	}

	int newWordSize = strlen(newWord);
	word = new char[newWordSize + 1];

	for (int i = 0; i < newWordSize; i++) {
		word[i] = newWord[i];
	}

	word[newWordSize] = '\0';
}



ostream& operator<<(ostream& stream, References& obj) {
	cout << endl;
	stream << " Word:" << ' ';
	stream << obj.word << endl;
	stream << " Number of pages:" << ' ';
	for (int i = 0; i < obj._size; i++) {
		stream << obj.pages[i] << ' ';
	} 
	cout << endl;
	return stream;
}