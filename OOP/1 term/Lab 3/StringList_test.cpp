#include "StringList.h"

// В данной работе я множественно использую функцию abort(), работа программы заканчивается при любой попытке найти что-то или записать 
// за границы списка. 

int main() {


	
	ListNode* tmp;
	POSITION tmp_1;
	POSITION pos;
	int index;



	StringList* sl = new StringList();
	StringList* sl_1 = new StringList();
	StringList* sl_2 = new StringList();
	StringList* sl_3 = new StringList();
	StringList* sl_4 = new StringList();
	StringList* sl_5 = new StringList();


	printf(" IsEmpty test:\n");
	if (sl->IsEmpty())
		printf(" True\n");
	else
		printf(" False\n");


	printf("\n AddHead(1 & 2), AddTail(1 & 2), GetHead, GetTail, print and size test:\n");
	sl->AddHead("4");
	sl->AddTail("3");
	sl_1->AddHead("6");
	sl_1->AddTail("5");
	sl_2->AddHead("2");
	sl_2->AddTail("1");
	sl->AddTail(sl_2);
	sl->AddHead(sl_1);
	tmp = sl->GetHead();
	for (int i = 0; i < sl->Getsize(); i++) {
		sl->Printnode(tmp);
		tmp = tmp->next;
	}
	printf("\n Size of list now is: %d\n", sl->Getsize());


	printf("\n GetAt test:\n");
	pos = sl->GetAt(5);
	sl->Printnode(pos);
	printf("\n");

	// В данной функции есть много вариантов работы, для каждого из них есть своя проверка, которая закоментированная
	printf("\n Splice test:\n");
	printf(" Before:\n");
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf("\n After:\n");
	sl_4->AddHead("15");
	sl_4->AddTail("14");
	sl_4->AddTail("13");
	sl_4->AddTail("12");
	sl_4->AddTail("11");
	sl_4->AddTail("10");
	POSITION pos_1, pos_2, pos_main;
	pos = sl_4->GetHeadPosition();
	pos = sl_4->GetNext();
	//pos_1 = NULL;
	pos_1 = pos;
	pos = sl_4->GetNext();
	pos = sl_4->GetNext();
	//pos_2 = NULL;
	pos_2 = pos;
	pos = sl->GetHeadPosition();
	pos = sl->GetNext();
	//pos_main = NULL;
	//for (pos = sl->GetHeadPosition(); pos->next != NULL; pos = sl->GetNext());
	pos = sl->GetHeadPosition();
	for (int i = 0; i < 3; i++){ // Данный цикл для удобства выбора элемента списка
		pos = sl->GetNext();
	}
	pos_main = pos;
	//sl->Splice(pos_main, sl_5, pos_1, pos_2);
	sl->Splice(pos_main, sl_4, pos_1, pos_2);
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf("\n Size of list now is: %d\n", sl->Getsize());


	printf(" \n");
	// Каждая функция выполняет свои обязательства как надо, для удобства они закомментированы, кроме одной
	printf("\n Delete(1 & 2 & 3 & 4) test:\n");
	printf(" Before:\n");
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf("\n After:\n");
	//sl->RemoveHead();
	//sl->RemoveTail();
	sl->RemoveAt(6);
	//sl->RemoveAll();
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf("\n Size of list now is: %d\n", sl->Getsize());


	printf("\n IsEmpty test:\n");
	if (sl->IsEmpty())
		printf(" True\n");
	else
		printf(" False\n");


	printf("\n AppendExclusivel test:\n");
	printf(" Before:\n");
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf(" After:\n");
	sl_3->AddHead("2");
	sl_3->AddTail("7");
	sl_3->AddTail("6");
	sl_3->AddTail("8");
	sl->AppendExclusively(sl_3);
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf("\n Size of list now is: %d\n", sl->Getsize());
	

	printf("\n Unique test:\n");
	sl->AddHead("6");
	sl->AddHead("6");
	sl->AddHead("6");
	printf(" Before:\n");
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf("\n After:\n");
	sl->Unique();
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf("\n Size of list now is: %d\n", sl->Getsize());


	printf("\n Find test:\n");

	const char* s = "10";
	char* str = new char[strlen(s)];
	strcpy(str, s);
	tmp_1 = sl->Find(str);
	sl->Printnode(tmp_1);
	

	printf(" \n");
	printf("\n FindIndex test:\n");
	s = "10";
	str = new char[strlen(s)];
	strcpy(str, s);
	index = sl->FindIndex(str);
	printf(" %d\n", index);
	
	
	printf("\n GetHeadPosition, GetNext test:\n");
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	

	printf(" \n");
	printf("\n GetPrev test:\n");
	pos = sl->GetHeadPosition();
	pos = sl->GetNext();
	pos = sl->GetNext();
	pos = sl->GetPrev();
	sl->Printnode(pos);


	printf(" \n");
	printf("\n SetAt, InsertAfter, InsertBefore test:\n");
	printf(" Before:\n");
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	printf("\n After:\n");
	s = "9";
	str = new char[strlen(s)];
	strcpy(str, s);
	sl->SetAt(str, 3);
	
	
	s = "8";
	str = new char[strlen(s)];
	strcpy(str, s);
	sl->InsertAfter(str, 3);
	

	s = "15";
	str = new char[strlen(s)];
	strcpy(str, s);
	sl->InsertBefore(str, 3);
	
	for (pos = sl->GetHeadPosition(); pos != NULL; pos = sl->GetNext())
		sl->Printnode(pos);
	
	sl->~StringList();
	return 0;
}