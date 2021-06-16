#include"List.h"
#include "Reference.h"
List<References> ExistingWords;
List<References> DeletedWords;

void Delete_if_more(int a);
void CorrectWord(const char* oldWord, const char* newWord);
void Restore(const char* word);
void AddReference(const char* word, int* pages, int size);
void DeleteReference(const char* word);


int main() {

	if (!ExistingWords.load("Reference.csv")) {
		abort();
	}
	printf("\n\t\tList of existing references after loading data form csv\n");
	ExistingWords.Print();
	
	int* arr = new  int[5];
	int array[5] = { 1, 2, 3, 4, 5 };
	arr = array;
	const char* str = "Lovely";
	int size = 5;
	
	AddReference(str, arr, size);
	printf("\n\t\tList of existing references after adding an element\n");
	ExistingWords.Print();
	
	CorrectWord(str, "Lovelyy");
	printf("\n\t\tList of existing references after correction reference word\n");
	ExistingWords.Print();
	
	DeleteReference("Honey");
	printf("\n\t\tList of existing references after removal an element\n");
	ExistingWords.Print();
	
	Delete_if_more(4);
	printf("\n\t\tList of existing references after removal if size > then entered size\n");
	ExistingWords.Print();
	printf("\n\t\tList of deleted references after Delete_if_more\n");
	DeletedWords.Print();
	
	Restore("Swetty");
	printf("\n\t\tList of existing references after restore\n");
	ExistingWords.Print();
	printf("\n\t\tList of deleted references after restore\n");
	DeletedWords.Print();

	return 0;
}



void Delete_if_more(int a) {
	List<References>::iterator it = ExistingWords.begin();
	List<References>::iterator it_next;

	while (it != ExistingWords.end()) {
		if ((*it).data.IsMore(a)) {
			it_next = (*it).next;
			ExistingWords.splice(it, DeletedWords);
			it = it_next;
		}
		else {
			it++;
		}
	}
}



void CorrectWord(const char* oldWord, const char* newWord) {
	for (List<References>::iterator it = ExistingWords.begin(); it != ExistingWords.end(); it++) {
		if (!strcmp((*it).data.Get_Word(), oldWord)) {
			(*it).data.Correct(newWord);
		}
	}
}



void Restore(const char* word) {

	List<References>::iterator it = DeletedWords.begin();
	List<References>::iterator itNext;

	while (it != DeletedWords.end()) {
		if (!strcmp((*it).data.Get_Word(), word)) {
			itNext = (*it).next;
			DeletedWords.splice(it, ExistingWords);
			it = itNext;
		}
		else {
			it++;
		}
	}
}


void AddReference(const char* word, int* pages, int size) {
	References NewWord(word, pages, size);
	ExistingWords.push_front(NewWord);
}


void DeleteReference(const char* word) {
	List<References>::iterator it = ExistingWords.begin();
	List<References>::iterator it_next;

	while (it != ExistingWords.end()) {
		if (!strcmp((*it).data.Get_Word(), word)) {
			it_next = (*it).next;
			ExistingWords.splice(it, DeletedWords);
			it = it_next;
		}
		else {
			it++;
		}
	}
}