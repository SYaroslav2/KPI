#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include "String.h"
#include <stdexcept>



using namespace std;



String::String() {
	str = NULL;
	len = 0;
}



String::~String() {
	delete[] this->str;
	this->len = 0;
}



String::String(size_t count, char ch) {
	if (count == 0)
		throw out_of_range{ "Bad size" };
	
	str = new char[count +1];
	for (size_t i = 0; i < count; i++) 
		str[i] = ch;

	str[count] = '\0'; 
	len = count;
}



String::String(const String& other, size_t pos, size_t  count) {

	if(other.len == 0)
		throw out_of_range{ "Bad size" };

	if (pos >= other.len) 
		throw out_of_range{ "Bad position" };
	// Данный конструктор в качестве параметра получает поизицию элементав массиве, то есть получая позицию 3, 
	// подразумивается 4-тый элемента, по-этому в следующей проверке стоит именно '>='
	
	if (((pos + count) >= other.size()) || (count == other.npos)) {
		
		str = new char[other.len - pos + 1];
		size_t i;
		for(i = pos; i < other.len; i++) {
			str[i - pos] = other.str[i];
		}
		str[i - pos] = '\0';
		len = other.len - pos;
		return;
	
	}

	str = new char[count + 1];
	size_t i;
	for (i = pos; i < pos + count; i++)
		str[i - pos] = other.str[i];
	
	str[i - pos] = '\0';
	len = count;
}



String::String(const char* s) {
	if (s == NULL)
		throw out_of_range{ "Bad string" };

	str = new char[strlen(s) + 1];
	strcpy(str, s);
	len = strlen(s);
}



String::String(const String& s) {
	if (s.str == NULL)
		throw out_of_range{ "Bad string" };
	
	len = s.len;
	str = new char[len + 1];
	strcpy(str, s.str);
}



size_t String::size()const {
	return this->len;
}



String& String::operator=(const String& str) {
	if (str.len == 0)
		throw out_of_range{ "Bad size" };
	
	if(this->str != NULL) 
		delete[] this->str;
	
	this->str = new char[str.len +1];
	strcpy(this->str, str.str);
	this->len = str.len;

	return *this;
}



String& String::operator=(const char* s) {
	if (strlen(s) == 0)
		throw out_of_range{ "Bad size" };

	if (this->str != NULL)
		delete[] this->str;

	this->str = new char[strlen(s) + 1];
	strcpy(this->str, s);
	this->len = strlen(s);

	return *this;
}



String& String::operator=(char ch) {
	for (size_t i = 0; i < this->len; i++) 
		this->str[i] = ch;
	
	return *this;
}



String& String::operator+=(const String& str) {
	if (str.len == 0)
		throw out_of_range{ "Bad size" };

	char* str1 = new char[this->len + str.len + 1], * s = this->str;
	strcpy(str1, this->str);
	strcat(str1, str.str);
	this->str = str1;
	this->len += str.len;
	delete[] s;

	return *this;
}



String& String::operator+=(char* s) {
	if (strlen(s) == 0)
		throw out_of_range{ "Bad size" };
	
	char* str1 = new char[this->len + strlen(s) + 1], * s1 = this->str;
	strcpy(str1, this->str);
	strcat(str1, s);
	this->str = str1;
	this->len += strlen(s);
	delete[] s1;

	return *this;
}



void String::resize(size_t count) {
	if (this->len == 0)
		throw out_of_range{ "Bad size" };

	if (count == 0)
		throw out_of_range{ "Bad size" };

	if (count == this->len) return;

	srand((unsigned)time(NULL));

	char *s;

	if (count > this->len)	{
		char* new_str = new char[count + 1];
		for (size_t i = 0; i < count; i++) {
			if (i < this->len) 
				new_str[i] = this->str[i];
			else {
				char ch{ rand() % 55 + 60 };
				new_str[i] = ch;
			}

		}
		new_str[count] = '\0';
		s = this->str;
		this->str = new_str;
		this->len = count;
		delete[] s;
	}

	if (count < this->len)	{
		char* new_str = new char[count + 1];
		for (size_t i = 0; i < count; i++) 
			new_str[i] = this->str[i];
		
		new_str[count] = '\0';
		s = this->str;
		this->str = new_str;
		this->len = count;
		delete[] s;
	}
}



void String::resize(size_t count, char ch) {
	if (this->len == 0)
		throw out_of_range{ "Bad size" };

	if (count == 0)
		throw out_of_range{ "Bad size" };

	if (count == this->len) return;

	char* s;

	if (count > this->len) {
		char* new_str = new char[count + 1];
		for (size_t i = 0; i < count; i++) {
			if (i < this->len) 
				new_str[i] = this->str[i];
			else
				new_str[i] = ch;
			
		}
		new_str[count] = '\0';
		
		s = this->str;
		this->str = new_str;
		this->len = count;
		delete[] s;
	}

	if (count < this->len) {
		char* new_str = new char[count + 1];
		for (size_t i = 0; i < count; i++) 
			new_str[i] = this->str[i];
		
		new_str[count] = '\0';
		s = this->str;
		this->str = new_str;
		this->len = count;
		delete[] s;
	}
}



void String::swap(String& other) {
	if ((other.len == 0) || (this->len == 0))
		throw out_of_range{ "Bad size" };

	char* ptr1, *ptr2;
	size_t i = this->len;
	ptr1 = other.str;
	ptr2 = this->str;
	this->str = ptr1;
	other.str = ptr2;
	this->len = other.len;
	other.len = i;
}



bool operator==(String& lhs, String& rhs) {
	if ((lhs.len == 0) || (rhs.len == 0))
		throw out_of_range{ "Bad size" };

	if (strcmp(lhs.str, rhs.str) == 0) 
		return true;
	else 
		return false;
}



size_t String::find(const String& s, size_t pos) const {
	if(pos >= this->len)
		throw out_of_range{ "Bad size" };

	if ((this->len - pos) < s.len) 
		throw out_of_range{ "Bad second string lenght" };

	if ((s.len == 0) || (this->len == 0))
		throw out_of_range{ "Bad size" };

	size_t count = 0, counter = 0, position, j = 0;
	
	for (size_t i = pos; i <= this->len - s.len; i++) {
		position = i;
		count = i;
		
		while ((this->str[count] == s.str[j]) && (this->str[count] != '\0' && s.str[j] != '\0')) {
			counter++;
			j++;
			count++;
		}
		if (counter == s.len) 
			return position;
		counter = j = 0;
	}

	return npos;
}



size_t String::find_first_of(const char* s, size_t pos, size_t count) const {
	if (pos >= this->len)
		throw out_of_range{ "Bad position" };

	if (count == 0 || count >  strlen(s))
		throw out_of_range{ "Bad count" };

	if ((s == NULL) || (this->len == 0))
		throw out_of_range{ "Bad size" };

	size_t position, j = 0;

	for (size_t i = pos; i < this->len; i++) {
		
		position = i;
		
		while ((this->str[i] != '\0' && s[j] != '\0') && (j < count)) {
			
			if (this->str[i] == s[j]) 
				return position;
			j++;
		}
		j = 0;
	}
	return npos;
}



size_t String::find_first_not_of(const char* s, size_t pos, size_t count) const {
	if (pos >= this->len)
		throw out_of_range{ "Bad position" };

	if (count == 0 || count > strlen(s))
		throw out_of_range{ "Bad count" };

	if ((s == NULL) || (this->len == 0))
		throw out_of_range{ "Bad size" };

	size_t position, j = 0;

	for (size_t i = pos; i < this->len; i++) {
	
		position = i;

		while ((this->str[i] != '\0' && s[j] != '\0') && (j < count)) {

			if (this->str[i] == s[j]) break;

			j++;
		}

		if (j == count) 
			return position;
		j = 0;
	}

	return npos;
}



size_t String::find_last_not_of(const char* s, size_t pos, size_t count) const {
	if (pos >= this->len)
		throw out_of_range{ "Bad position" };

	if (count == 0 || count > strlen(s))
		throw out_of_range{ "Bad count" };

	if ((s == NULL) || (this->len == 0))
		throw out_of_range{ "Bad size" };

	size_t position = 0, j = 0;

	for (size_t i = pos; i < this->len; i++) {

		while ((this->str[i] != '\0' && s[j] != '\0') && (j < count)) {

			if (this->str[i] == s[j]) break;

			j++;
		}

		if (j == count) position = i;
		j = 0;
	}

	if (position == 0) 
		return npos;
		
	return position;
}



size_t String::rfind(const String& s, size_t pos) const {
	if (pos == npos) pos = 0;

	if ((this->len - pos) < s.len) 
		throw out_of_range{ "Bad second string lenght" };

	if (pos >= this->len)
		throw out_of_range{ "Bad position" };

	if ((s.str == NULL) || (this->len == 0))
		throw out_of_range{ "Bad size" };

	size_t position = 0, count, counter = 0, j = 0, i;

	for (i = pos; i <= this->len - s.len; i++) {

		count = i;
		
		while ((this->str[count] == s.str[j]) && (this->str[count] != '\0' && s.str[j] != '\0')) {
			counter++;
			j++;
			count++;
		}

		if (counter == s.len) position = i;
		counter = j = 0;

	}

	if (position == 0) 
		return npos;

	return position;
}



String& String::append(const String& str, size_t pos, size_t count) {
	if (pos >= str.len)
		throw out_of_range{ "Bad position" };

	if ((str.str == NULL) || (this->len == 0))
		throw out_of_range{ "Bad size" };

	size_t counter = pos + count;
	
	if (count == npos || counter > str.len) counter = str.len;
	
	char* s = new char[counter - pos + 1];
	for (size_t i = pos; i < counter; i++) 
		s[i - pos] = str.str[i];
	
	s[counter - pos] = '\0';
	char* str1 = new char[this->len + strlen(s) + 1], *s2 = this->str;
	strcpy(str1, this->str);
	strcat(str1, s);
	this->str = str1;
	this->len += strlen(s);
	delete[] s2;
	delete[] s;
	return *this;
}



void String::print()const {
	if (this->str == NULL)
		throw out_of_range{ "Bad string" };

	for (size_t i = 0; i < this->len; i++)
		printf(" %c", this->str[i]);
	
	printf("\n");
}