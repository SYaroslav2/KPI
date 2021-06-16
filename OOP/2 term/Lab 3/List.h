#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdexcept>
#include "Iterator.h"
#include "Reference.h"
using namespace std;
template <class T>
class List {
	struct ListNode {
		T data;
		ListNode* next;
		ListNode() {
			next = NULL;
		}
		ListNode(T dat) {
			data = dat;
		}
		void Print() {
			cout << data;
		}
	};

public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List();
	~List();

	//methods
	iterator begin();//Returns an iterator addressing the first element 
	iterator end();//Returns an iterator that addresses the location 
   //succeeding the last element


	void clear();//Erases all the elements of a list.
	bool empty();//Tests if a list is empty.

	iterator find(const node_type& val);//Returns an iterator to the 
// first element in a list that 
//match a specified value.

	void pop_front();//Deletes the element at the beginning of a list.

	void push_front(const node_type val);//Adds an element to the beginning 
  //of a list.
	void remove(const node_type val);//Erases first element in a list that 
   //match a specified value.
	bool load(const char* filename);

	int size();//Returns the number of elements in a list.

	void splice(iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
// position of the argument list.
	void Print();//Dumps list into the screen
	iterator findBefore(const node_type& val);
	node_type GetElem(char* str, int counter);
	//Данные функции требуются для контроля данных, что мы добавляем, для исключения повторов
	int check(char* str, int counter);
	int checkin(const node_type val);
private:
	node_type* head;
	iterator* first, * last;
};



template <class T>
List<T>::List() {
	head = NULL;
	first = NULL;
	last = NULL;
}



template <class T>
List<T>::~List() {
	delete head;
	delete first;
	delete last;
}



template <class T>
typename List<T>::iterator List<T>::begin() {
	if (first == NULL) return NULL;
	return *first;
}



template <class T>
typename List<T>::iterator List<T>::end() {
	return *last;
}



template <class T>
void List<T>::clear() {
	while (head != NULL) {
		pop_front();
	}
}



template <class T>
bool List<T>::empty() {
	if (!this->head) return true;
	else return false;
}



template <class T>
typename List<T>::iterator List<T>::find(const node_type& val) {
	node_type* ptr = head;
	
	while (ptr->data != val.data && ptr != NULL) {
		ptr = ptr->next;
	}
	List<T>::iterator it;
	it = ptr;
	return it;
}



template <typename T>
typename List<T>::iterator List<T>::findBefore(const node_type& val) {
	node_type* ptr = head;
	node_type* before = ptr;

	while (ptr != NULL && ptr->data != val.data) {
		before = ptr;
		ptr = ptr->next;
	}
	List<T>::iterator it;
	it = before;
	return it;
	return before;
}



template <class T>
void List<T>::pop_front() {
	if (head != NULL) {
		remove(head->data);
	}
}



template <class T>
void List<T>::push_front(const node_type val) {
	if (checkin(val) == 0)
		return;
	node_type* tmp = new node_type(val.data);

	if (head == NULL) {
		head = tmp;
	
		head->next = NULL;
	}
	else {
		node_type* buffer = head;
		head = tmp;
		head->next = buffer;
		
	}

	delete first;
	delete last;

	first = new iterator(head);

	node_type* ptr = head;

	while (ptr != NULL) {
		ptr = ptr->next;
	}

	last = new iterator(ptr);
}



template <class T>
void List<T>::remove(const node_type val) {
	iterator it = find(val);
	iterator it_before = findBefore(val);
	node_type* ptr_1 = head;
	
	node_type* tmp = &(*it);
	node_type* tmp_before = &(*it_before);

	if (it == NULL) return;

	if (it == it_before) {
		head = tmp->next;
		delete first;
		delete last;
		first = new iterator(head);

		while (ptr_1 != NULL) {
			ptr_1 = ptr_1->next;
		}

		last = new iterator(ptr_1);
		delete tmp;
		tmp = NULL;

		return;
	}

	tmp_before->next = tmp->next;
	delete first;
	delete last;
	first = new iterator(head);

	while (ptr_1 != NULL) {
		ptr_1 = ptr_1->next;
	}

	last = new iterator(ptr_1);
	delete tmp;
	tmp = NULL;
	return;
}



template <class T>
typename List<T>::node_type List<T>::GetElem(char* str, int counter) {
	T elem;
	elem.Data_Processing(str, counter);
	return elem;
}



template <class T>
int List<T>::check(char* str, int counter) {
	T elem;
	bool res;
	res = elem.Data_Processing(str, counter);
	if (res == true) {
		if (find(elem) == NULL) 
				return 1;
		return 0;
	}
	return 0;
}



template <class T>
int List<T>::checkin(const node_type val) {
		
	if (find(val) == NULL)
		return 1;
	return 0;

}



template <class T>
bool List<T>::load(const char* filename) {

	char* string;
	int  lenght, j;

	char str[256];
	T elem;
	FILE* csv_File;
	csv_File = fopen(filename, "r");
	if (!csv_File) return false;


	while (fgets(str, 255, csv_File)) {
		
		lenght = strlen(str);
		string = (char*)malloc(lenght + 1);
		int counter = 0;
		for (j = 0; j < lenght; j++) {
			if (str[j] == ';') {
				string[j] = '\0';
				counter++;
			}
			else {
				string[j] = str[j];

			}
		}
		string[j] = '\0';
		counter++;
		if (check(string, counter) == 1) {
			push_front(GetElem(string, counter));
		}
		else continue;
	}
	return true;
}



template <class T>
int List<T>::size() {
	int counter = 0;
	List<T>::iterator it;
	for (it = this->first; it != this->last; it++)
		counter++;
	return counter;

}



template <class T>
void List<T>::splice(iterator _Where, List<T>& _Right) {
	if (_Where == NULL) 
		abort();
		
	node_type value = (*_Where).data;
	this->remove((*_Where).data);
	_Right.push_front(value);
}



template <class T>
void List<T>::Print() {

	List<T>::node_type* ptr = head;

	while (ptr != NULL) {
		ptr->Print();
		ptr = ptr->next;
	}

}