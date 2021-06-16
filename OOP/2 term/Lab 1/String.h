#pragma once



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>


class String
{
	char* str;
	size_t len; //� ������� ������������ ������ �� �������, ����� ������ ���� ���������� �����, ��-�����
	//� ��������� � ��� �������� ���������� �������� ������ �� ������� '\0'
	static const size_t npos = 1024;
public:
	explicit String();
	~String();
	String (size_t count, char ch);
	String(const String& other, size_t pos, size_t  count = npos);
	String(const char* s);
	String(const String& s);
	size_t size()const;
	String& operator=(const String& str);
	String& operator=(const char* s);
	String& operator=(char ch);
	String& operator+=(const String& str);
	String& operator+=(char* s);
	void resize(size_t count);
	void resize(size_t count, char ch);
	void swap(String& other);
	friend bool operator==(String & lhs, String & rhs);

	/*� ������������ ������ �� ��������, ��� ������ ������ ���������� ��� �������, ���������� ����� ��� ������ � �������
	������� � ���� ������������ ������ ��� ������� ���� size_t ���������� �������� ���������� ������� ��������
	��� �� ����� ��������, ��� �� ���� ����������� �������� pos - ������ � �������, � count - ���������� ���������
	� ��������� �� �������� ��� ������ ������ ���������� ����� ��������� pos, ������� � ��������� � ��� ������� 
	�� ������� ���������� ����� � ������� ������*/

	size_t find(const String& s, size_t pos = 0) const;
	size_t find_first_of(const char* s, size_t pos, size_t count) const;
	size_t find_first_not_of(const char* s, size_t pos, size_t count) const;
	size_t find_last_not_of(const char* s, size_t pos, size_t count) const;
	size_t rfind(const String& str, size_t pos = npos) const;

	String& append(const String& str, size_t pos, size_t count);
	void print()const;
	
};

