#include "StringList.h"


StringList::StringList() {

	Head = Tail = p = NULL;
	count = 0;
	
}



StringList::~StringList() {
	RemoveAll();
}



ListNode* StringList::GetHead() {
	return Head;
}



ListNode* StringList::GetTail() {
	return Tail;
}



void StringList::AddHead(const char* str) {
	ListNode* tmp = new ListNode;
	tmp->prev = NULL;
	tmp->str = new char[strlen(str)];
	strcpy(tmp->str,str);
	tmp->next = Head;
	if (Head != NULL)
		Head->prev = tmp;
	if (count == 0)
		Head = Tail = tmp;
	else Head = tmp;
	count++;
	p = Head;
}



void StringList::AddHead(const StringList *sl) {
	int count_1 = 0;
	ListNode* tmp_1;
	tmp_1 = sl->Head;
	while (tmp_1 != NULL) {
		count_1++;
		tmp_1 = tmp_1->next;
	}
	count = count + count_1;
	if (Head == Tail) {
		p = Head = sl->Head;
		Tail = sl->Tail;
		return;
	}
	(sl->Tail)->next = Head;
	Head->prev = sl->Tail;
	Head = sl->Head;
	p = Head;
}



void StringList::AddTail(const char* str) {
	ListNode* tmp = new ListNode;
	tmp->next = NULL;
	tmp->str = new char[strlen(str)];
	strcpy(tmp->str, str);
	tmp->prev = Tail;
	if (Tail != NULL)
		Tail->next = tmp;
	if (count == 0)
		Head = Tail = p = tmp;
	else Tail = tmp;
	count++;
}



void StringList::AddTail(const StringList *sl) {
	int count_1 = 0;
	ListNode* tmp_1;
	tmp_1 = sl->Head;
	while (tmp_1 != NULL) {
		count_1++;
		tmp_1 = tmp_1->next;
	}
	count = count + count_1;
	if (Head == Tail) {
		p = Head = sl->Head;
		Tail = sl->Tail;
		return;
	}
	(sl->Head)->prev = Tail;
	Tail->next = sl->Head;
	Tail = sl->Tail;
}



void StringList::RemoveAll() {
	while (count > 0) {
		RemoveHead();
	}
}



void StringList::RemoveHead() {
	if (Head == Tail) {
		delete Head;
		count--;
		return;
	}
	ListNode* Deleted = Head;
	ListNode* After_Del = Deleted->next;
	Head = After_Del;
	Head->prev = NULL;
	delete Deleted;
	count--;
}



void StringList::RemoveTail() {
	ListNode* Deleted = Tail;
	ListNode* Prev_Del = Deleted->prev;
	Tail = Prev_Del;
	Tail->next = NULL;
	delete Deleted;
	count--;
}



void StringList::AppendExclusively(const StringList* sl) {

	int count_1 = 0;
	ListNode* tmp_1;
	
	tmp_1 = sl->Head;
	while (tmp_1 != NULL) { 
		count_1 = 0;
		char* str = tmp_1->str;
		ListNode* tmp = Head;
		while (tmp != NULL) {
			if (strcmp(str, tmp->str) != 0) {
				tmp = tmp->next;
				count_1++;
			}
			else break;
		}
		if (count_1 == count) {
			
			if (tmp_1->next == NULL) {
				Tail->next = tmp_1;
				tmp_1->prev = Tail;
				Tail = tmp_1;
				tmp_1 = tmp_1->next;
				count++;
				continue;
			}

			Tail->next = tmp_1;
			tmp_1->prev = Tail;
			tmp_1 = tmp_1->next;
			Tail = tmp_1->prev;
			Tail->next = NULL;
			count++;
			continue;
		}
		tmp_1 = tmp_1->next;
	}

}



void StringList::Splice(POSITION where, StringList* sl, POSITION first, POSITION last) {

	ListNode* tmp;
	if (where == NULL && this->Head != NULL) {
		abort();
	}
	
	if (sl->Head == NULL)
		abort();
	
	
	if (first == NULL && last == NULL) {
	
	}
	else if (first == NULL && last != NULL) {
		tmp = sl->Head;
		while (tmp != last)
		{
			tmp = tmp->next;
			sl->RemoveHead();
			if (tmp == last)
				sl->RemoveHead();

		}
	}
	else if (first != NULL && last == NULL ) { 
		tmp = sl->Tail;
		while (tmp != first)
		{
			tmp = tmp->prev;
			sl->RemoveTail();
			if (tmp == first) 
				sl->RemoveTail();
			
		}
		
	}
	else if (first != NULL && last != NULL)
	{	
		POSITION pos, pos_1;
		pos = first;
		while (pos != last) {
			if (pos == sl->Head) {
				sl->RemoveHead();
				pos = pos->next;
			}
			else if (pos == sl->Tail) {
				sl->RemoveTail();
				pos = pos->next;
			}
			else {
				pos_1 = pos;
				(pos->prev)->next = pos->next;
				(pos->next)->prev = pos->prev;	
				pos = pos->next;
				if (pos == last) {
					pos_1 = pos;
					(pos->prev)->next = pos->next;
					(pos->next)->prev = pos->prev;
					pos = pos->next;
					delete pos_1;
					break;
				}
			}
			

		}
	
	}
	tmp = sl->Head;
	int counter = 0;
	while (tmp != NULL)
	{
		counter++;
		tmp = tmp->next;
	}
	count = count + counter;
	if (where == NULL && this->Head == NULL) {
		this->Head = sl->Head;
		this->Tail = sl->Tail;
	}
	else if (where == this->Tail) {
		this->AddTail(sl);
		count = count - counter;;
	}
	else {
		tmp = this->Head;
		while (tmp != where)
		{
			tmp = tmp->next;
			if (tmp == NULL){
				abort();
			}
		}
		tmp->next->prev = sl->Tail;
		sl->Tail->next = tmp->next;
		tmp->next = sl->Head;
		sl->Head->prev = tmp;
	}
	
}



void StringList::Unique() {
	ListNode* tmp;
	tmp = Head;
	while (tmp != NULL) {
		char* str = tmp->str;
		ListNode* tmp_1 = tmp->next;
		while (tmp_1 != NULL) {
			if (strcmp(str, tmp_1->str) == 0) {
				if (tmp_1->next == NULL) {
					RemoveTail();
					count--;
					break;
				}
				else {
					(tmp_1->prev)->next = tmp_1->next;
					(tmp_1->next)->prev = tmp->prev;
					ListNode* del_tmp = tmp_1;
					tmp_1 = tmp_1->next;
					delete(del_tmp);
					count--;
				}
			}
			else break;
		}
		tmp = tmp->next;
	}
}


ListNode* StringList::GetNext() {
	if (this->p == NULL)
		abort();
	this->p = this->p->next;
	return this->p;

}



ListNode* StringList::GetPrev() {

	if (this->p == NULL)
		abort();
	this->p = this->p->prev;
	return this->p;
}



ListNode* StringList::GetHeadPosition() {

	p = this->Head;
	return p;

}



POSITION StringList::GetAt(int indx)const {
	if (indx > count || indx < 1)
		abort();
	ListNode* tmp = Head;
	for (int i = 1; i < indx; i++) 
		tmp = tmp->next;
	return tmp;
}



void StringList::RemoveAt(int indx) {
	if (indx > count || indx < 1)
		abort();
	if (indx == 1) {
		RemoveHead();
		return;
	}

	if (indx == count) {
		RemoveTail();
		return;
	}

	ListNode* tmp;
	tmp = Head;
	for (int i = 1; i < indx; i++)
		tmp = tmp->next;
	ListNode* Deleted = tmp;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	delete Deleted;
	count--;
}



void StringList::SetAt(char* s, int indx) {
	if (indx > count || indx < 1)
		abort();
	ListNode* tmp;
	tmp = Head;
	for (int i = 1; i < indx; i++)
		tmp = tmp->next;
	strcpy(tmp->str, s);
}



void StringList::InsertAfter(char* s, int indx) {
	if (indx > count || indx < 1)
		abort();
	ListNode* tmp;
	tmp = Head;
	for (int i = 1; i < indx; i++)
		tmp = tmp->next;
	strcpy(tmp->next->str, s);
}



void StringList::InsertBefore(char* s, int indx) {
	if (indx > count || indx < 1)
		abort();
	ListNode* tmp;
	tmp = Head;
	for (int i = 1; i < indx; i++)
		tmp = tmp->next;
	strcpy(tmp->prev->str, s);

}



POSITION StringList::Find(char* s) {
	if (Head == NULL)
		return NULL;
	ListNode* tmp;
	tmp = Head;
	for (int i = 1; i <= count; i++) {
		if (strcmp(tmp->str, s) == 0)
			return tmp;

		else
			tmp = tmp->next;
		if (tmp == NULL) {
			abort();
			//return NULL;
		}
	}
	
}



int StringList::FindIndex(char* s)const {
	if (Head == NULL)
		return 0;

	
	ListNode* tmp;
	tmp = Head;
	for (int i = 1; i <= count; i++) {
		if (strcmp(tmp->str, s) == 0)
			return i;

		else
			tmp = tmp->next;
	}
	if (tmp == NULL)
		abort();
}



int StringList::Getsize()const {
	return count;
}


bool StringList::IsEmpty()const {
	return(!Head);
}



void StringList::Printnode(POSITION p) {
	/*if (p == NULL)
		printf(" Error");*/
	printf(" %s ", p->str);
}