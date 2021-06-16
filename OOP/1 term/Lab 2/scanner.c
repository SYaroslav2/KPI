#include "scanner.h"



int data_capture(const char* str, SCAN_INFO* sc, int id) {

	char *string, *str_ptr;
	int i, count, lenght, counter;
	float money;
	lenght = strlen(str);
	sc->id = id;
	string = (char*)malloc(lenght + 1);
	str_ptr = string;
	counter = 0;
	for (i = 0; i < lenght; i++) {
		if (str[i] == ';') {
			string[i] = '\0';
			counter++;
		}
		else
			string[i] = str[i];
	}
	string[i] = '\0';

	if (counter != 5) {
		return -1;
	}

	strcpy(sc->manufacturer, str_ptr);
	str_ptr += strlen(str_ptr) + 1;
	strcpy(sc->model, str_ptr);
	str_ptr += strlen(str_ptr) + 1;
	count = atoi(str_ptr);
	sc->year = count;
	str_ptr += strlen(str_ptr) + 1;
	money = atof(str_ptr);
	sc->price = money;
	str_ptr += strlen(str_ptr) + 1;
	count = atoi(str_ptr);
	sc->x_size = count;
	str_ptr += strlen(str_ptr) + 1;
	count = atoi(str_ptr);
	sc->y_size = count;
	free(string);
	
	return 0;
}



int create_db(const char* csv, const char* db) {
	
	char str[256], str_1[256];
	int i, counter, flag = 0, count = 0;
	SCAN_INFO sc;
	csv = fopen(csv, "r");
	db = fopen(db, "wb");
	if (csv == NULL) return -1;
	if (db == NULL) return -1;
	i = 0; 
	while (fgets(str, 255, csv)) {
		
		i++;
	}
	fwrite(&i, sizeof(int), 1, db);
	fseek(csv, 0, SEEK_SET);
	i = 0;
	while (fgets(str, 255, csv)) {
		fseek(csv, 0, SEEK_SET);
		counter = 0;
		while (fgets(str_1, 255, csv) && counter < i) {
			counter++;
			flag = 0;
			if (strcmp(str, str_1) == 0)
				flag = 1;
		}

		if (flag == 1)
		{
			i++;
			count++;
			continue;
		}
		if (data_capture(str, &sc, i) == 0)
		{ 
			fwrite(&sc, sizeof(sc), 1, db);
		}
		i++;
	}
	fseek(db, 0, SEEK_SET);
	i = i - count;
	fwrite(&i, sizeof(int), 1, db);
	fclose(csv);
	fclose(db);
	return 0;
}



void sorting_int (int* A, int* B, int N)
{
	int imin, tmp, tmp_1, imin_1;
	for (int s = 0; s < N - 1; s++) {
		imin = s;
		imin_1 = s;
		for (int i = s + 1; i < N; i++)
			if (A[i] < A[imin]) imin = i;
		if (imin != s) {
			imin_1 = imin;
			tmp = A[imin];
			tmp_1 = B[imin_1];
			A[imin] = A[s];
			B[imin_1] = B[s];
			A[s] = tmp;
			B[s] = tmp_1;
		}
	}
}



void sorting_float(float* A, int* B, int N)
{
	float tmp;
	int imin, tmp_1, imin_1;
	for (int s = 0; s < N - 1; s++) {
		imin = s;
		imin_1 = s;
		for (int i = s + 1; i < N; i++)
			if (A[i] < A[imin]) imin = i;
		if (imin != s) {
			imin_1 = imin;
			tmp = A[imin];
			tmp_1 = B[imin_1];
			A[imin] = A[s];
			B[imin_1] = B[s];
			A[s] = tmp;
			B[s] = tmp_1;
		}
	}
}


/*Чтоб было легче убедиться в правильности работы функции, для каждого поля есть вывод файла .idx, который закоментирован */
int make_index(const char* db, const char* field_name) {
	FILE * idx;
	SCAN_INFO* sc;
	int *A;
	int i, count;
	char str[20];
	char idxname[30];

	strcpy(idxname, field_name);
	strcat(idxname, ".idx");
	idx = fopen(idxname, "wb");
	if (idx == NULL) return 0;
	db = fopen(db, "rb");
	if (db == NULL) return 0;
	fread(&i, sizeof(int), 1, db);
	count = i;
	A = malloc(i * sizeof(int));
	sc = malloc(i * sizeof(SCAN_INFO));
	for (int j = 0; j < i; j++)
		A[j] = j;
	i = 0;
	while (fread(&(sc[i++]), sizeof(SCAN_INFO), 1, db) != 0);
	if (field_name == "manufacturer"){
		int imin, tmp_1, imin_1;
		for (int s = 0; s < count; s++) {
			imin = s;
			imin_1 = s;
			for (int i = s + 1; i < count; i++)
				if (strcmp(sc[i].manufacturer, sc[imin].manufacturer) < 0) imin = i;
			if (imin != s) {
				imin_1 = imin;
				tmp_1 = A[imin_1];
				A[imin_1] = A[s];
				A[s] = tmp_1;
				strcpy(str, sc[imin].manufacturer);
				strcpy(sc[imin].manufacturer, sc[s].manufacturer);
				strcpy(sc[s].manufacturer, str);
			}
		}
		/*for (int j = 0; j < count; j++) {
			printf(" %d", A[j]);
		}
		printf("\n");*/

	}
	else if (field_name == "model") {
		int imin, tmp_1, imin_1;
		for (int s = 0; s < count; s++) {
			imin = s;
			imin_1 = s;
			for (int i = s + 1; i < count; i++)
				if (strcmp(sc[i].model, sc[imin].model) < 0) imin = i;
			if (imin != s) {
				imin_1 = imin;
				tmp_1 = A[imin_1];
				A[imin_1] = A[s];
				A[s] = tmp_1;
				strcpy(str, sc[imin].model);
				strcpy(sc[imin].model, sc[s].model);
				strcpy(sc[s].model, str);
			}
		}
		/*for (int j = 0; j < count; j++) {
			printf(" %d", A[j]);
		}
		printf("\n");*/
	}
	else if(field_name == "year") {
		int *B;
		B = malloc(count * sizeof(int));
		for (int j = 0; j < count; j++) {
			B[j] = sc[j].year;
		}
		sorting_int(B, A, count);
		/*for (int j = 0; j < count; j++) {
			printf(" %d", A[j]);
		}
		printf("\n");*/
		free(B);
	}
	else if (field_name == "price") {
		float* B;
		B = malloc(count * sizeof(float));
		for (int j = 0; j < count; j++) {
			B[j] = sc[j].price;
		}
		sorting_float(B, A, count);
		/*for (int j = 0; j < count; j++) {
			printf(" %d", A[j]);
		}
		printf("\n");*/
		free(B);

	}
	else if (field_name == "x_size") {
		int* B;
		B = malloc(count * sizeof(int));
		for (int j = 0; j < count; j++) {
			B[j] = sc[j].x_size;
		}
		sorting_int(B, A, count);
		/*for (int j = 0; j < count; j++) {
			printf(" %d", A[j]);
		}
		printf("\n");*/
		free(B);
	}
	else if (field_name == "y_size") {
		int* B;
		B = malloc(count * sizeof(int));
		for (int j = 0; j < count; j++){
			B[j] = sc[j].y_size;
		}
		sorting_int(B, A, count);
		/*for (int j = 0; j < count; j++){
			printf(" %d", A[j]);
		}
		printf("\n");*/
		free(B);
	}
	else if (field_name == "id") {
		int* B;
		B = malloc(count * sizeof(int));
		for (int j = 0; j < count; j++) {
			B[j] = sc[j].id;
		}
		sorting_int(B, A, count);
		/*for (int j = 0; j < count; j++) {
			printf(" %d", A[j]);
		}
		printf("\n");*/
		free(B);
	}
	
	fwrite(A, sizeof(int), count , idx);
	free(A);
	free(sc);
	fclose(db);
	fclose(idx);
	return 1;

}




void reindex(const char* db) {

	make_index(db, "id");
	make_index(db, "manufacturer");
	make_index(db, "year");
	make_index(db, "model");
	make_index(db, "price");
	make_index(db, "x_size");
	make_index(db, "y_size");

}



RECORD_SET* get_recs_by_index(const char* dba, char* indx_field) {
	RECORD_SET* rs;
	FILE *idx, *db;
	int counter = 0;
	if (strcmp("manufacturer", indx_field) == 0) counter++;
	if (strcmp("id", indx_field) == 0) counter++; 
	if (strcmp("model", indx_field) == 0) counter++;
	if (strcmp("year", indx_field) == 0) counter++;
	if (strcmp("price", indx_field) == 0) counter++;
	if (strcmp("x_size", indx_field) == 0) counter++;
	if (strcmp("y_size", indx_field) == 0) counter++;
	if (counter == 0) {
		return NULL;
	}
	int  N;
	int* Vec;
	char idxname[30];
	strcpy(idxname, indx_field);
	strcat(idxname, ".idx");
	idx = fopen(idxname, "rb");
	if (idx == NULL) return 0;
	db = fopen(dba, "rb");
	if (db == NULL) return 0;
	fread(&N, sizeof(int), 1, db);
	Vec = malloc(sizeof(int) * N);
	fread(Vec, sizeof(int), N, idx);
	rs = malloc(sizeof(RECORD_SET));
	rs->rec_nmb = N;
	rs->recs = malloc(sizeof(SCAN_INFO) * N);
	for  (int i = 0; i < N; i++) {
		fseek(db, sizeof(int) + sizeof(SCAN_INFO) * Vec[i], SEEK_SET);
		fread(&(rs->recs[i]), sizeof(SCAN_INFO), 1, db);
	}

	free(Vec);
	fclose(db);
	fclose(idx);
	return rs;

}



void del_scanner(const char* db, int id) {
	SCAN_INFO sc;
	int i, position;
	db = fopen(db, "rb+");
	if (db == NULL) return;
	position = 0;
	fread(&i, sizeof(int), 1, db);
	if (i < id ) {
		return;
	}
	while (fread(&sc, sizeof(sc), 1, db) != 0) {
		if (sc.id == id) {
			break;
		}
		position++;
	}
	fseek(db, 0, SEEK_SET);
	fread(&i, sizeof(int), 1, db);
	while (fread(&sc, sizeof(sc), 1, db) != 0);
	fseek(db, 0, SEEK_SET);
	i--;
	fwrite(&i, sizeof(int), 1, db);
	
	fseek(db, (sizeof(int) + sizeof(SCAN_INFO) * position), SEEK_SET);
	fwrite(&sc, sizeof(sc), 1, db);
	
	int res = _chsize(_fileno(db), (sizeof(int) + i * sizeof(SCAN_INFO)));
	
	fclose(db);
	
	reindex("Scanners.db");
		
}




void add_scanner(const char* db, const char* scanner_str) {

	SCAN_INFO sc, st;
	int i, new_id, counter;
	db = fopen(db, "rb+");
	if (db == NULL) return;
	new_id = 0;
	counter = 0;
	fread(&i, sizeof(int), 1, db);

	while (fread(&sc, sizeof(sc), 1, db) != 0) {
		if (sc.id > new_id) new_id = sc.id + 1;
	}
	fseek(db, sizeof(int), SEEK_SET);
	if (data_capture(scanner_str, &st, new_id) == 0) {
		while (fread(&sc, sizeof(sc), 1, db) != 0) {
			counter = 0;
			if (strcmp(sc.manufacturer, st.manufacturer) == 0) counter++;
			if (strcmp(sc.model, st.model) == 0) counter++;
			if (sc.year == st.year) counter++;
			if (sc.price == st.price) counter++;
			if (sc.x_size == st.x_size) counter++;
			if (sc.y_size == st.y_size) counter++;
			if (counter == 6)
				return;
		}
	}
	
	
	int res = _chsize(_fileno(db), (sizeof(int) + (i + 1) * sizeof(SCAN_INFO)));
	fwrite(&st, sizeof(SCAN_INFO), 1, db);
	fseek(db, 0, SEEK_SET);
	i++;
	fwrite(&i, sizeof(int), 1, db);

	
	fclose(db);

	reindex("Scanners.db");

}



/* Для удобства проверки корректности работы, в коде этой функции есть вывод на консоль, который закоментирован */
void print_db(const char* db) {
	
	int i;
	FILE* txt;
	SCAN_INFO sc;
	txt = fopen("Scanners.txt", "a+");
	if (txt == NULL) {
		return;
	}
	db = fopen(db, "rb");
	if (db == NULL) {
		return;
	}
	fread(&i, sizeof(int), 1, db);
	fprintf(txt, "\n\t\t\tSCAN_INFO\n\n");
	fprintf(txt, "         Manufacturer |   Year   |                Model |    Size |    Price |\n");
	fprintf(txt, "\n");
	while (fread(&sc, sizeof(sc), 1, db) != 0) {
		fprintf(txt,"ID: %4d | %10s |   %4d   | %20s | %dx%d | %8.2f |\n", sc.id, sc.manufacturer,sc.year, sc.model, sc.x_size, sc.y_size, sc.price);
	}
	fprintf(txt, "\n");
	/*fseek(db, 0, SEEK_SET);
	fread(&i, sizeof(int), 1, db);
	printf("\n\t\t\tSCAN_INFO\n\n");
	printf("         Manufacturer |   Year   |                Model |    Size |    Price |\n");
	printf("\n");
	while (fread(&sc, sizeof(sc), 1, db) != 0) {
		printf("ID: %4d | %10s |   %4d   | %20s | %dx%d | %8.2f |\n", sc.id, sc.manufacturer, sc.year, sc.model, sc.x_size, sc.y_size, sc.price);
	}
	printf("\n");*/
	fclose(db);
	fclose(txt);

}



RECORD_SET* select(const char* db, const char* field, const char* value) {
	RECORD_SET* rs;
	int N = 0;
	SCAN_INFO sc;
	int counter = 0;
	if (strcmp("manufacturer", field) == 0) counter++;
	if (strcmp("id", field) == 0) counter++;
	if (strcmp("model", field) == 0) counter++;
	if (strcmp("year", field) == 0) counter++;
	if (strcmp("price", field) == 0) counter++;
	if (strcmp("x_size", field) == 0) counter++;
	if (strcmp("y_size", field) == 0) counter++;
	if (counter == 0) {
		return NULL;
	}
	rs = malloc(sizeof(RECORD_SET));
	rs->recs = NULL;
	db = fopen(db, "rb");
	if (db == NULL) {
		return NULL;
	}
	fseek(db, sizeof(int), SEEK_SET);
	counter = N;
	while (fread(&sc, sizeof(SCAN_INFO), 1, db)) {
		if (strcmp(field, "id") == 0) {
			if (sc.id == atoi(value)) {
				counter++;
			}
		}
		else if (strcmp(field, "manufacturer") == 0) {
			if (sc.manufacturer == value) {
				counter++;
			}
		}
		else if (strcmp(field, "model") == 0) {
			if (sc.model == value) {
				counter++;
			}
		}
		else if (strcmp(field, "year") == 0) {
			if (sc.year == atoi(value)) {
				counter++;
			}
		}
		else if (strcmp(field, "price") == 0) {
			if (sc.price == atof(value)){
				counter++;
			}
		}
		else if (strcmp(field, "x_size") == 0) {
			if (sc.x_size == atoi(value)) {
				counter++;
			}
		}
		else if (strcmp(field, "y_size") == 0) {
			if (sc.y_size == atoi(value)) {
				counter++;
			}
		}
		if (counter > N){

			rs->rec_nmb = counter;
			rs->recs = realloc(rs->recs, sizeof(SCAN_INFO) * counter);
			rs->recs[N] = sc;
			N = counter;
		}
	}
	fclose(db);
	return rs;

}




void print_rec_set(RECORD_SET* rs) {

	if (rs == NULL)
		return;


	printf("\n\t\t\tRECORD_SET\n\n");
	printf("         Manufacturer |   Year   |                Model |    Size |    Price |\n");
	printf("\n");
	for (int i = 0; i < rs->rec_nmb; i++) {
		printf("ID: %4d | %10s |   %4d   | %20s | %dx%d | %8.2f |\n", rs->recs[i].id, rs->recs[i].manufacturer, rs->recs[i].year , rs->recs[i].model, rs->recs[i].x_size, rs->recs[i].y_size, rs->recs[i].price);
	}
	printf("\n");

}