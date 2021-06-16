#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

typedef struct list
{
	float inf;
	struct list *link;
};


struct list * init(float a)
{
	struct list *lst;
	lst = (struct list*)malloc(sizeof(struct list));
	lst->inf = a;
	lst->link = NULL;
	return (lst);
}

struct list * addelem(list * lst, float number)
{
	struct list *temp, *p;
	temp = (struct list*)malloc(sizeof(list));
	p = lst->link;
	lst->link = temp;
	temp->inf = number;
	temp->link = p;
	return (temp);
}

void listprint(list *lst)
{
	struct list *p;
	p = lst;
	do 
	{
		printf(" %2.0f", p->inf);
		p = p->link;
	} while (p != NULL);
}

struct list *swap(struct list *lst_1, struct list *lst_2, struct list *head)
{
	struct list *prev_1, *prev_2, *next_1, *next_2;
	prev_1 = head;
	prev_2 = head;
	if (prev_1 == lst_1)
		prev_1 = NULL;
	else
	{
		while (prev_1->link != lst_1)
		{
			prev_1 = prev_1->link;
		}
	}
	if (prev_2 == lst_2)
		prev_2 = NULL;
	else
	{
		while (prev_2->link != lst_2)
		{
			prev_2 = prev_2->link;
		}
	}
	next_1 = lst_1->link;
	next_2 = lst_2->link;
	if (lst_2 == next_1)
	{
		lst_2->link = lst_1;
		lst_1->link = next_2;
		if (lst_1 != head)
			prev_1->link = lst_2;
	}
	else 
		if (lst_1 == next_2)
		{
			lst_1->link = lst_2;
			lst_2->link = next_1;
			if (lst_2 != head)
				prev_2->link = lst_2;
		}
		else
		{
			if (lst_1 != head)
				prev_1->link = lst_2;
			lst_2->link = next_1;
			if (lst_2 != head)
				prev_2->link = lst_1;
			lst_1->link = next_2;
		}
	if (lst_1 == head)
		return(lst_2);
	if (lst_2 == head)
		return(lst_1);
	return(head);
	
}

struct list *deletehead(list *root)
{
	struct list *temp;
	temp = root->link;
	free(root);
	return(temp);
}

int main()
{
	float N = 40;
	struct list  *lst, *root, *lst_1, *lst_2, *p_k;
	lst = init(-1);
	root = lst;
	int count_1 = 0, counter = 0;
	for (int i = 2; i <= N; i++)
	{
		if ((i > (5 + count_1)) && (i <= (10 + count_1)))
		{
			counter++;
			if (counter >= 5)
			{
				count_1 = count_1 + 10;
				counter = 0;
				
			}
			lst = addelem(lst, i);
		}
		else lst = addelem(lst, -i);
	}
	printf("\n The old list:\n");
	listprint(root);
	 
	lst_1 = root;
	lst_2 = root;
	count_1 = 0;
	counter = 0;
	int i_1 = 5, i_2 = 10, integer_1 = 10, integer_2 = 15 ;

	while (1)
	{
		lst_1 = root;
		for (int i = 0; i < i_1; i++)
		{
			lst_1 = lst_1->link;
			
		}
		i_1 = i_1 + 1;
		if (i_1 > 25) 
		{
			if (i_1 == integer_1 + 1)
			{
				i_1 = i_1 + 14;
				integer_1 = 20 + integer_1;
				if (i_1 >= N)
					break;
			}
		}
		else
		{
			if (N == 20) 
			{
				if (i_1 == integer_1 + 1)
				{
					i_1 = i_1 + 15;
					integer_1 = 20 + integer_1;
					if (i_1 >= N)
						break;
				}
			}
			else if (N > 20)
			{
				if (i_1 == integer_1)
				{
					i_1 = i_1 + 15;
					integer_1 = 20 + integer_1;
					if (i_1 >= N)
						break;
				}
			}
		}
		lst_2 = root;
		for (int i = 0; i < i_2; i++)
		{
			lst_2 = lst_2->link;
			
		}
		i_2 = i_2 + 1;
		if (i_2 > 30) 
		{
			if (i_2 == integer_2+1)
			{
				i_2 = i_2 + 14;
				integer_2 = 20 + integer_2;
				if (i_2 >= N)
				{
					break;
				}
			}
		}
		else
		{
			if (N == 20) {
				if (i_2 == integer_2 + 1)
				{
					i_2 = i_2 + 15;
					integer_2 = 20 + integer_2;
					if (i_2 >= N)
					{
						break;
					}
				}
			}
			else if (N > 20)
			{
				if (i_2 == integer_2)
				{
					i_2 = i_2 + 15;
					integer_2 = 20 + integer_2;
					if (i_2 >= N)
					{
						break;
					}
				}
			}
		}
		root = swap(lst_1, lst_2, root);
	}
	printf("\n");
	printf(" The new list:\n");
	listprint(root);
	lst = root;
	while (lst != NULL)
		lst = deletehead(lst);
	free(lst);
	_getch();
	return 0;
}