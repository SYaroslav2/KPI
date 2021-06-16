#include "scanner.h"

int main() {
	/*FILE* csv, * db, *txt;
	create_db("Scanners.csv", "Scanners.db");*/
	/* Это открытие файла используется для того, чтобы очистить текстовый файл от результата прошлой проверки работы программы */
	/*txt = fopen("Scanners.txt", "wt");
	if (txt == NULL) {
		return;
	}
	fclose(txt);
	print_db("Scanners.db");
	reindex("Scanners.db");
	//add_scanner("Scanners.db", "ASUS;AS1055;2009;99.99;210;297");*/
	/* Сдедующий закоментированный вызов функции нужен для проверки корректонсти работы функции */
	/*add_scanner("Scanners.db", "ASUS1;AsScan9;2009;299.99;217;297");
	print_db("Scanners.db");
	del_scanner("Scanners.db", 4);
	print_db("Scanners.db");
	RECORD_SET* rs = select("Scanners.db", "year", "2004");
	print_rec_set(rs);
	rs = get_recs_by_index("Scanners.db", "manufacturer");
	print_rec_set(rs);
	*/
	int sum = 0;
	for (int i = 29; i < 60; i++)
		sum += i;
	printf(" %i", sum);
	return 0;
}
