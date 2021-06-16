#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include "argz.h"



int main() {
	const char * string = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	char *argz;
	size_t argz_len;

	printf(" argz_create_sep work\n");
	
	argz_create_sep(string, 58, &argz, &argz_len);
	argz_print(argz, argz_len);
	int counter = argz_count(argz, argz_len);
	
	printf(" argz_count work\n");
	printf(" %d\n", counter);

	printf(" argz_add work\n");

	const char *str = "first";	
	argz_add(&argz, &argz_len, str);
	argz_print(argz, argz_len);
	
	printf(" argz_delete work\n");
	
	char copy_entry[17] = "LANG=en_US.UTF-8";
	char *entry = copy_entry;
	argz_delete(&argz, &argz_len, entry);
	argz_print(argz, argz_len);

	printf(" argz_insert work\n");

	char copy_before[15] = "PWD=/bin/monty";
	char *before = copy_before;
	const char *entry_2 = "second";
	argz_insert(&argz, &argz_len, before, entry_2);
	argz_print(argz, argz_len);

	printf(" argz_next work\n");

	char copy_entry_2[7] = "second";
	char *entry_3 = copy_entry_2;
	entry_3 = argz_next(argz, argz_len, entry_3);
	if (entry == NULL)
		printf(" It's the last element or it is no exist there");
	else printf(" %s\n", entry_3);
	
	printf(" argz_replace work\n");
	const char *with = "third";
	const char *str_2 = "usr=monty";
	argz_replace(&argz, &argz_len, str_2, with);
	argz_print(argz, argz_len);
	
	_getch();
	return 0;
}
