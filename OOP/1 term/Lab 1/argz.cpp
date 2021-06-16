#include "argz.h"



error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len) {

	size_t i;

	if (*argz == NULL)
		return ERROR;


	*argz_len = strlen(string) + 1;
	*argz = (char*)malloc((strlen(string) + 1)* sizeof(char));

	for (i = 0; i < *argz_len - 1; i++) {
		if (string[i] == sep)
		{
			(*argz)[i] = '\0';
		}
		else (*argz)[i] = string[i];
	}
	(*argz)[i] = '\0';
	return OK;
}



size_t argz_count(const char *argz, size_t argz_len) {

	size_t i = 0;
	int counter = 0;
	while (i < argz_len + 1) {
		if (argz[i] == '\0')
		{
			counter++;
		}
		i++;
	}
	return counter;

}



error_t argz_add(char **argz, size_t *argz_len, const char *str) {
	
	char *tmp = *argz, *new_argz, *copy_pos;
	int count, i;
	if (str == NULL)
		return ERROR;
	count = argz_count(*argz, *argz_len);
	*argz_len += strlen(str) + 1;
	new_argz = (char *)malloc(*argz_len);
	copy_pos = new_argz;
	tmp = *argz;
	for (i = 0; i < count + 1; i++) {
		if (i == count) {
			strcpy(copy_pos, str);
		}
		else
		{
			strcpy(copy_pos, tmp);
			copy_pos += strlen(tmp) + 1 ;
			tmp += strlen(tmp) + 1;

		}

	}

	free(*argz);
	*argz = new_argz;
	
	return OK;
}



char *argz_find(char *argz, size_t len, char *entry) {
	size_t count = argz_count(argz, len);
	for (size_t i = 0; i < count; i++) {

		if (strcmp(argz, entry) != 0)
		{
			argz += strlen(argz) + 1;
			if (i == count - 1)
				return NULL;
		}
		else return argz;
		
	}

}



void argz_delete(char **argz, size_t *argz_len, char *entry) {
	
	char *tmp = *argz, *new_argz, *copy_pos;
	int i, count;
	if (!(!entry || argz_find(*argz, *argz_len, entry)))
		return;
	count = argz_count(*argz, *argz_len);
	*argz_len = *argz_len - strlen(entry) - 1;
	new_argz = (char *)malloc(*argz_len);;
	copy_pos = new_argz;
	tmp = *argz; 
	for (i = 0; i < count; i++) {
		if (strcmp(tmp, entry)) {
			strcpy(copy_pos, tmp);
			copy_pos += strlen(tmp) + 1;
		}
		tmp += strlen(tmp) + 1;
	}

	free(*argz);
	*argz = new_argz;
	
}



error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry) {

	char *tmp = *argz, *new_argz, *copy_pos;
	int i, count;
	if (before == NULL)
		return ERROR;
	if (entry == NULL)
		return ERROR;
	if (!before || !argz_find(*argz, *argz_len, before))
		return ERROR;

	if (!(!before || argz_find(*argz, *argz_len, before)))
		return ERROR;
	count = argz_count(*argz, *argz_len);
	*argz_len += strlen(entry) + 1;
	new_argz = (char *)malloc(*argz_len);;
	copy_pos = new_argz;
	tmp = *argz;
	for (i = 0; i < count + 1; i++) {
		if (strcmp(tmp, before)) {
			strcpy(copy_pos, tmp);
			copy_pos += strlen(tmp) + 1;
			tmp += strlen(tmp) + 1;
		}
		else
		{
			strcpy(copy_pos, entry);
			copy_pos += strlen(entry) + 1;
			strcpy(copy_pos, tmp);
			copy_pos += strlen(tmp) + 1;
			tmp += strlen(tmp) + 1;
			i = i + 1;
		}
		
	}
	
	free(*argz);
	*argz = new_argz;
	
	return OK;
}



char * argz_next(char *argz, size_t argz_len, const char *entry) {
	size_t entry_len;
	char *tmp = argz;
	if (!entry)
		return argz;
	
	size_t count = argz_count(argz, argz_len);
	for (size_t i = 0; i < count; i++) {

		if ((strcmp(tmp, entry) == 0) && (i != count - 1)) {
			tmp += strlen(tmp) + 1;
			return tmp;
		}
		else if(i == count - 1)
		{
			tmp = NULL;
			return tmp;
		}
		tmp += strlen(tmp) + 1;
	}
}



error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with) {

	
	char *tmp = *argz, *new_argz, *copy_pos;
	int i, count;
	if (str == NULL)
		return ERROR;
	if (with == NULL)
		return ERROR;

	count = argz_count(*argz, *argz_len);
	*argz_len = *argz_len + strlen(with) - strlen(str);
	new_argz = (char *)malloc(*argz_len);
	copy_pos = new_argz;
	tmp = *argz;
	for (i = 0; i < count; i++) {
		if (strcmp(tmp, str)) {
			strcpy(copy_pos, tmp);
			copy_pos += strlen(tmp) + 1;
			tmp += strlen(tmp) + 1;
		}
		else
		{
			strcpy(copy_pos, with);
			copy_pos += strlen(with) + 1;
			tmp += strlen(tmp) + 1;
		}

	}

	free(*argz);
	*argz = new_argz;


	return OK;
}




void argz_print(const char *argz, size_t argz_len) {

	size_t i;
	i = 0;
	/*Поскольку вывод массива поэлементно делает программу более читабельной, я испозую именно его, но при этом есть и вывод построчно*/
	/*size_t count = argz_count(argz, argz_len);
	for (size_t i = 0; i < count; i++) {
		printf(" ");
		puts(argz);
		argz += strlen(argz) + 1;
	}*/
	printf(" ");
	while (i < argz_len) {
		if (argz[i] != '\0')
			printf("%c", argz[i]);
		else printf(" ");
		i++;
	}
	printf("\n");
}