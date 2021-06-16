#include <stdlib.h>
#include <time.h>
#include "CommonVector.h"//розм≥ри масиву, вектора





clock_t Select4ExchangeArr3D(int ***A)
{
	int   k, j_1, L, R, min, max, counter_1, counter_2;//оголошенн€ зм≥нних

	clock_t time_start, time_stop;
	time_start = clock();//початок вим≥ру часу
	for (k = 0; k < P; k++)
	{
		j_1 = 0; //≥н≥ц≥ал≥зац≥€ зм≥нних, що повинн≥ мати саме так≥ значенн€ при сортуванн≥ нового перер≥зу
		L = 0;
		R = M - 1;
		counter_1 = 0;
		counter_2 = N - 1;
		while (L < R || counter_1 < counter_2)//сортуванн€ в≥дбуваЇтьс€ доки в≥дсортован≥ частини не перетнутьс€ 
		{
			j_1 = counter_1;
			if (j_1 > counter_2) break;
			for (int i = L; i < R + 1 || j_1 < counter_2; i++)//цикл, що проводить саме сортуванн€
			{
				if (i == M)
				{
					i = 0;
					j_1++;
				}

				if (A[k][i][j_1] < A[k][L][counter_1])
				{
					min = A[k][i][j_1];
					A[k][i][j_1] = A[k][L][counter_1];
					A[k][L][counter_1] = min;
				}
				else
					if (A[k][i][j_1] > A[k][R][counter_2])
					{
						max = A[k][i][j_1];
						A[k][i][j_1] = A[k][R][counter_2];
						A[k][R][counter_2] = max;
					}
			}

			L = L + 1;
			R = R - 1;
			if (L == M)//€кщо л≥ва границ€ виходить за меж≥ масива, присвоюЇмо њй значенн€ 0 ≥ переходимо на новий стовпець
			{
				L = 0;
				counter_1++;
			}
			if (R == -1)//€кщо права границ€ виходить за меж≥ масива, присвоюЇмо њй значенн€ останнього елемента стопц€ ≥ переходимо на новий стовпець
			{
				R = M - 1;
				counter_2--;
			}
		}
	}
	time_stop = clock();//к≥нець вим≥ру
	return time_stop - time_start;
}

clock_t Select4Exchange(int *V)
{
	int Min, Max;
	int L, R;
	clock_t time_start, time_stop;
	time_start = clock();
	L = 0; R = M *N - 1;
	while (L < R) {
		for (int i = L; i < R + 1; i++) {
			if (V[i] < V[L]) {
				Min = V[i];
				V[i] = V[L];
				V[L] = Min;
			}
			else
				if (V[i] > V[R]) {
					Max = V[i];
					V[i] = V[R];
					V[R] = Max;
				}
		}
		L = L + 1; R = R - 1;
	}
	time_stop = clock();
	return P * (time_stop - time_start);
}

clock_t Insert1Arr3D(int ***A)
{
	int i, j, k, p, v, d, elem, g;//≥н≥ц≥ал≥зац≥€ зм≥нних

	clock_t time_start, time_stop;
	time_start = clock();//початок вим≥ру
	for (g = 0; g < P; g++)
	{
		for (j = 0; j <= N - 1; j++)
		{
			for (i = 0; i <= M - 1; i++)
			{

				if (j == 0 && i == 0)//пропускаЇмо нульовий елемент за умовою сортуванн€
				{
					continue;
				}

				elem = A[g][i][j];
				k = 0;
				p = 0;

				while (elem > A[g][k][p])// нарощуЇмо л≥чильник, €кий вкаже потр≥бну позиц≥ю дл€ елемента
				{
					k++;
					if (k == M)//€кщо л≥чильник б≥льший довжини стовпц€, зб≥льшуЇмо значенн€ л≥чильника стовпц≥в, а л≥чильнику р€дк≥в присвоюЇмо 0 
					{
						p = p + 1;
						k = 0;
					}
				}

				v = i - 1;
				d = j;


				for (v = i - 1; v >= k || d != p; v--)
				{

					if (v != -1) 
					{
						A[g][v + 1][d] = A[g][v][d];
					}

					if (v == -1)
					{
						A[g][0][d] = A[g][M - 1][d - 1];//€кщо елмент у 0 р€дку, потр≥бно пом≥н€ти його м≥сц€ми з останн≥м елементом попереднього стовпц€
						v = M - 1;
						d--;
					}


				}
				A[g][k][p] = elem;

			}
		}
	}
	time_stop = clock();//к≥нець вим≥ру
	return time_stop - time_start;
}


clock_t Insert1(int *V)
{
	int Elem, j;
	clock_t time_start, time_stop;
	time_start = clock();
	for (int i = 1; i < M * N; i++) {
		Elem = V[i];
		j = 0;
		while (Elem > V[j]) j = j + 1;
		for (int k = i - 1; k >= j; k--)
			V[k + 1] = V[k];
		V[j] = Elem;
	}
	time_stop = clock();
	return P * (time_stop - time_start);
}//повертаЇмо час пропорц≥йно перер≥зам у масив≥



clock_t InsertExchangeArr3D(int ***A)
{
	int p, g, tmp, i, j, k;//≥н≥ц≥ал≥зац≥€ зм≥нних

	clock_t time_start, time_stop;
	time_start = clock();//початок вим≥ру
	for (k = 0; k < P; k++) 
	{
		for (j = 0; j < N; j++) 
		{
			for (i = 0; i < M; i++) 
			{
				if (i == 0 && j == 0)//попускаЇмо нульовий елмент за умовою задач≥
				{
					continue;
				}

				p = i;
				g = j;
				while (!(p == 0 && g == 0))//виконуЇмо сортуванн€ доки не д≥йдемо до 0 елемента масива
				{
					if (p == 0) {
						if (A[k][p][g] < A[k][M - 1][g - 1]) {
							tmp = A[k][p][g];
							A[k][p][g] = A[k][M - 1][g - 1];
							A[k][M - 1][g - 1] = tmp;
						}
						g--;//зменшуЇмо значенн€ л≥чильник≥в, щоб цикл був ск≥нченним
						p = M - 1;//при переход≥ на новий стовпец втановлюЇмо л≥чильник на останн≥й елемент стовпц€
					}
					else {
						if (A[k][p][g] < A[k][p - 1][g]) {
							tmp = A[k][p][g];
							A[k][p][g] = A[k][p - 1][g];
							A[k][p - 1][g] = tmp;
						}
						p--;//зменшуЇмо значенн€ л≥чильник≥в, щоб цикл був ск≥нченним
					}
				}
			}
		}
		
	}
	time_stop = clock();//к≥нець вим≥ру
	return time_stop - time_start;
}

clock_t InsertExchange(int *V)
{
	int j, tmp;
	clock_t time_start, time_stop;
	time_start = clock();
	for (int i = 1; i < M * N; i++) {
		j = i;
		while (j > 0 && V[j] < V[j - 1]) {
			tmp = V[j];
			V[j] = V[j - 1];
			V[j - 1] = tmp;
			j = j - 1;
		}
	}
	time_stop = clock();
	return P * (time_stop - time_start);
}


