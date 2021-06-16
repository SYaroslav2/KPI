#include "String.h"



int main() {

	String s1(7, 'g');
	String s(s1, 3, 3);
	String s3;
	printf(" \n Constructor test: \n");
	s1.print();
	s.print();
	String s2(s);
	String s4("Ferrari");
	String s8;
	printf(" \n Operator= test: \n First:\n");
	s8=("Lamborgini");
	s8.print();
	printf(" Second:\n");
	s8 = ('f');
	s8.print();
	printf(" Third:\n");
	s8 = (s4);
	s8.print();
	printf(" \n Operator+= test: \n First:\n");
	s8+=("Audi");
	s8.print();
	printf(" Second:\n");
	s8+=(s4);
	s8.print();

	printf(" \n Resize test: \n First:\n");
	s4.resize(12, 'h');
	s4.print();
	printf(" Second:\n");
	s4.resize(15);
	s4.print();

	printf(" Operator== test:\n");
	bool res = s==s1;
	if (res)
		printf(" True\n");
	else 
		printf(" False\n");
	String s5("This is string");
	String s6("is");
	
	printf(" Find test:\n");
	size_t r = s5.find(s6, 1);
	printf(" The first substring starts at string[%d] element\n", r);
	
	printf(" Find_first_of test:\n");
	r = s5.find_first_of("is", 1, 2);
	printf(" The first character that is equal to any of the first count characters in the substring is string[%d] element\n", r);
	
	printf(" Find_first_not_of test:\n");
	r = s5.find_first_not_of("is", 4, 1);
	printf(" The first character that is not equal to any of the first count characters in the substring is string[%d] element\n", r);

	printf(" Find_last_not_of test:\n");
	r = s5.find_last_not_of("is", 0, 2);
	printf(" The last character not equal to any of the first count characters of the substring is string[%d] element\n", r);
	
	printf(" Rfind test:\n");
	r = s5.rfind(s6, 1);
	printf(" The last substring starts at string[%d] element\n", r);
	
	printf(" Size test:\n");
	r = s1.size();
	printf(" %d\n", r);
	
	printf(" Append test:\n");
	s5.append(s6, 0, 10);
	s5.print();
	
	printf(" Swap test:\n");
	printf(" First string before test:\n");
	s4.print();
	printf(" Second string before test:\n");
	s.print();
	s4.swap(s);
	printf(" First string before test:\n");
	s4.print();
	printf(" Second string before test:\n");
	s.print();

	return 0;
}