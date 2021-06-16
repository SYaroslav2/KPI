#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include "lexer.h"
#include <string>
#include <fstream>
using namespace std;

void compare(const char* str, int test_num) {
	FILE *file1, * file2;
	char exp_buf[128];
	char gen_buf[128];
	int flag = 1;
	strcpy(exp_buf, str);
	strcat(exp_buf, "/expected.txt");
	strcpy(gen_buf, str);
	strcat(gen_buf, "/generated.txt");
	printf("test %d\n", test_num);
	if ((file1 = fopen(exp_buf, "r")) == NULL) {
		printf("File can not be opened!\n");
		return;
	}
	if ((file2 = fopen(gen_buf, "r")) == NULL) {
		printf("File can not be opened!\n");
		return;
	}
	if (sizeof(file1) != sizeof(file2))
		flag = 0;
	while (!feof(file1) && !feof(file2)) {
		if (fgets(exp_buf, 128, file1)) {
			if (fgets(gen_buf, 128, file2)) {
				if (strcmp(exp_buf, gen_buf) != 0) {
					flag = 0;
					break;
				}
			}
		}
	}
	if (flag) {
		printf("Generated and expected file are the same \n");
	}
	else
		printf("Generated and expected file are not the same \n");
		
}

int main(int argc, char *argv[]) {
	
	for (int i = 1; i < argc; i++) {
		lexer(argv[i]);
		compare(argv[i], i);
	}
	
	return 0;
}
