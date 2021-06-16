#define _CRT_SECURE_NO_WARNINGS

#pragma warning (disable : 28182)
#pragma warning (disable : 6386)

#pragma once


#include <string.h>
#include <stdio.h>
#include <cstdlib>

struct ListNode {
	char* str;
	ListNode* next;
	ListNode* prev;
};

typedef const ListNode* POSITION;

class StringList {
public:
	//Constructs an empty list for ListNode objects.
	StringList(void);
	~StringList(void);

	//Head/Tail Access 
	ListNode* GetHead();//Returns the head element of the list 
	ListNode* GetTail();//Returns the tail element of the list 

		//Operations 
	//Adds an element to the head of the list (makes a new head).
	void AddHead(const char* str);
	//Adds all the elements in another list to the head of the list (makes a new head).
	void AddHead(const StringList* sl);
	//Adds an element to the tail of the list (makes a new tail).
	void AddTail(const char* str);
	//Adds all the elements in another list to the tail of the list (makes a new tail).
	void AddTail(const StringList* sl);
	//Removes all the elements from this list.
	void RemoveAll();
	//Removes the element from the head of the list.
	void RemoveHead();
	//Removes the element from the tail of the list.
	void RemoveTail();
	void AppendExclusively(const StringList* sl);
	void Splice(POSITION where, StringList* sl, POSITION first, POSITION last);
	//removes all duplicate elements
	void Unique();


	//Iteration 
	//Gets the next element for iterating.
	ListNode* GetNext();
	//Gets the previous element for iterating.
	ListNode* GetPrev();


	//Retrieval/Modification
	ListNode* GetHeadPosition();


	//Gets the element at a given position.
	POSITION GetAt(int indx)const;
	//Removes an element from this list as specified by position.
	void RemoveAt(int indx);
	//Sets the element at a given position.
	void SetAt(char* s, int indx);

	//Insertion 
//Inserts a new element after a given position.
	void InsertAfter(char* s, int indx);
	//Inserts a new element before a given position.
	void InsertBefore(char* s, int indx);

	//Searching 
	//Gets the position of an element specified by string value.
	POSITION Find(char* s);
	//Gets the position of an element specified by a zero-based index.
	int FindIndex(char* s)const;

	//Status 
//Returns the number of elements in this list.
	int Getsize()const;
	//Tests for the empty list condition (no elements).
	bool IsEmpty()const;

	void Printnode(POSITION p);

private:
	//put your own data members here
	ListNode *Head, *Tail, *p;
	int count;
};

