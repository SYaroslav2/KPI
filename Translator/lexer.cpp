#define _CRT_SECURE_NO_WARNINGS
#include "lexer.h"
#include "Header.h"
#include "parser.h"


int in_const_table(char str[]) {
	for (int i = 0; i < constants.size(); i++) {
		if (strcmp(str, constants[i].name) == 0)
			return constants[i].key;
	}
	return NULL;
}


int in_ident_table(char str[]) {
	for (int i = 0; i < identificators.size(); i++) {
		if (strcmp(str, identificators[i].name) == 0)
			return identificators[i].key;
	}
	return NULL;
}


int in_key_words_table(char str[]) {
	for (int i = 0; i < key_words.size(); i++) {
		if (strcmp(str, key_words[i].name) == 0)
			return key_words[i].key;
	}
	return NULL;
}


bool is_letter(char ch) {
	int tmp = ch;
	if (tmp > 64 && tmp < 91)
		return true;
	return false;
}


bool is_digit(char ch) {
	int tmp = ch;
	if (tmp > 47 && tmp < 58)
		return true;
	return false;
}


bool is_delimiter(char ch) {
	int tmp = ch;
	for (int i = 0; i < delimitors.size(); i++) {
		if (ch == delimitors[i].key)
			return delimitors[i].key;
	}
	return NULL;
}


int in_delimiter(char ch) {
	int tmp = ch;
	for (int i = 0; i < delimitors.size(); i++) {
		if (ch == delimitors[i].key)
			return delimitors[i].key;
	}
	return NULL;
}


bool is_whitespace(char ch) {

	for (int i = 0; i < 6; i++) {
		if (ch == white_space[i])
			return true;
	}
	return false;
}


bool lexer(const char* str) {
	char inp_buf[128], outp_buf[128];
	char inp[25] = "/input.sig";
	char outp[25] = "/generated_lex.txt";
	int buf_count = 0;
	strcpy(inp_buf, str);
	int count = strlen(str);

	for (int i = count; i < count + strlen(inp); i++) {
		inp_buf[i] = inp[buf_count];
		buf_count++;
	}
	inp_buf[count + strlen(inp)] = '\0';
	buf_count = 0;
	strcpy(outp_buf, str);
	count = strlen(str);
	for (int i = count; i < count + strlen(outp); i++) {
		outp_buf[i] = outp[buf_count];
		buf_count++;
	}
	outp_buf[count + strlen(outp)] = '\0';
	
	vector<tokens> lexems;
	int row = 1, column = 1, counter = 0;
	char ch;
	bool scanning_result = true;
	
	tokens tmp;
	FILE *file1, *file2;
	if ((file1 = fopen(inp_buf, "r")) == NULL) {
		cout << "File for reading can not be opened!\n";
		return false;
	}
	if ((file2 = fopen(outp_buf, "w")) == NULL) {
		cout << "File for writing can not be opened!\n";
		return false;
	}
	
	ch = fgetc(file1);
	while (ch != EOF) {

		char buf[35];
		if (is_whitespace(ch)) {
			while (true) {
				if (ch == char(10)) {
					row += 1;
					column = 0;
				}
				ch = fgetc(file1);
				column++;
				if (ch == EOF || !is_whitespace(ch))
					break;
			}
		}
		else if (is_digit(ch)) {
			tmp.col_id = column;
			tmp.row_id = row;

			while (true) {
				buf[counter] = ch;
				ch = fgetc(file1);
				column++;
				if (!(ch == EOF || is_digit(ch))) {
					buf[counter + 1] = '\0';
					counter = 0;
					break;
				}
				counter++;
				buf[counter] = ch;

			}
			if (!in_const_table(buf)) {
				data_key constatn;
				constatn.key = const_code++;
				strcpy(constatn.name, buf);
				constants.push_back(constatn);
			}
			strcpy(tmp.name, buf);
			tmp.lex_code = in_const_table(buf);
			lexems.push_back(tmp);
		}
		else if (is_letter(ch)) {
			tmp.col_id = column;
			tmp.row_id = row;

			while (true) {
				buf[counter] = ch;
				ch = fgetc(file1);
				column++;
				if ((ch == EOF) || !(is_letter(ch) || is_digit(ch))) {
					buf[counter + 1] = '\0';
					counter = 0;
					break;
				}
				counter++;
				buf[counter] = ch;

			}
			if (in_key_words_table(buf)) {
				strcpy(tmp.name, buf);
				tmp.lex_code = in_key_words_table(buf);

			}
			else {
				if (!in_ident_table(buf)) {
					data_key identificator;
					identificator.key = ident_code++;
					strcpy(identificator.name, buf);
					identificators.push_back(identificator);
				}

				strcpy(tmp.name, buf);
				tmp.lex_code = in_ident_table(buf);
			}
			lexems.push_back(tmp);
		}
		else if (is_delimiter(ch)) {
			tmp.col_id = column;
			tmp.row_id = row;
			if (ch == ':') {
				char last_char = ch;
				buf[counter] = ch;
				ch = fgetc(file1);
				column++;
				if (ch == '=') {
					counter++;
					buf[counter] = ch;
					buf[counter + 1] = '\0';
					strcpy(tmp.name, buf);
					tmp.lex_code = delimitors_comp[0].key;
					ch = fgetc(file1);
					column++;
					counter = 0;
				}
				else {
					buf[counter + 1] = '\0';
					counter = 0;
					strcpy(tmp.name, buf);
					tmp.lex_code = in_delimiter(last_char);
				}
			} else if (ch == '.') {
				char last_char = ch;
				buf[counter] = ch;
				ch = fgetc(file1);
				column++;
				if (ch == '.') {
					counter++;
					buf[counter] = ch;
					buf[counter + 1] = '\0';
					strcpy(tmp.name, buf);
					tmp.lex_code = delimitors_comp[1].key;
					ch = fgetc(file1);
					column++;
					counter = 0;
				}
				else {
					buf[counter + 1] = '\0';
					counter = 0;
					strcpy(tmp.name, buf);
					tmp.lex_code = in_delimiter(last_char);
				}
			}
			else {
				buf[counter] = ch;
				buf[counter + 1] = '\0';
				strcpy(tmp.name, buf);
				tmp.lex_code = in_delimiter(ch);
				ch = fgetc(file1);
				column += 1;
				counter = 0;
			}
			lexems.push_back(tmp);

		}
		else if (ch == '(') {
			tmp.col_id = column;
			tmp.row_id = row;
			ch = fgetc(file1);
			column++;
			if (ch == EOF || ch != '*')
				fprintf(file2, "Lexer: Error (line %d, column %d): * expected but end of the file found, Illegal character '%c' detected )\n", row, column, '(');
			else if (ch == '*') {
				while (true) {
					ch = fgetc(file1);
					column++;
					if (ch == EOF) {
						fprintf(file2, "Lexer: Error (line %d, column %d): opened comment, *) expected but end of the file found\n", tmp.row_id, tmp.col_id);
						scanning_result = false;
						break;
					}
					if (ch == char(10)) {
						row += 1;
						column = 0;
						ch = fgetc(file1);
						column++;
					}
					if (ch == '*') {
						ch = fgetc(file1);
						column++;
						if (ch != EOF && ch == ')') {
							ch = fgetc(file1);
							column++;
							break;
						}
						else if (ch == EOF) {
							fprintf(file2, "row %d, column %d ) expected but end of the file found(unclosed comment)\n", row, column);
							scanning_result = false;
						}

					}
				}
			}

		}
		else {
			fprintf(file2, "Lexer: Error (line %d, column %d): Illegal character '%c' detected\n", row, column, ch);
			scanning_result = false;
			ch = fgetc(file1);
			column++;
		}
	}
	fprintf(file2, "ROW | COLUMN | LEX_CODE | TOKEN_NAME\n");
	for (int i = 0; i < lexems.size(); i++) {
		fprintf(file2, " %-6d %-8d %-9d %s \n", lexems[i].row_id, lexems[i].col_id, lexems[i].lex_code, lexems[i].name);
	}

	fclose(file1);
	fclose(file2);

	parser(str, key_words, identificators, constants, delimitors_comp, delimitors, lexems);

	return scanning_result;
}
