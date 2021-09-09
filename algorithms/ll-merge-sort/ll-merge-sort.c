#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int data;
	struct node_t * next;
} node_t;

/* splits given list at middle and, returns head of the second list */
node_t * split (node_t * l)
{
	node_t 	* f = l,	/* fast pointer, eventually points at end of the list 				*/
	 		* s = l; 	/* slow pointer, eventually points head of the splitted second list	*/

	while (f != NULL)
	{
		f = f->next;

		if (f != NULL && f->next != NULL)
		{
			f = f->next;
			s = s->next;
		}
		/* in that point s points the last node of the first list 	*/
		else
		{
			l = s->next;	/* now l is head of the second list   	*/
			s->next = NULL;	/* put NULL end of the first list 		*/
			break;
		}
	}

	return l;
}

node_t * sorted_merge (node_t * l1, node_t * l2)
{
	node_t * l;	/* the return values as points either l1 or l2 according to their data */

	/* one of the list is empty, other list is already sorted just return it */
	if (l1 == NULL)
		l = l2;
	else if (l2 == NULL)
		l = l1;
	else
	{
		if (l1->data < l2->data)
		{
			l = l1;
			l->next = sorted_merge(l1->next, l2);
		}
		else
		{
			l = l2;
			l->next = sorted_merge(l1, l2->next); 
		}
	}

	return l;
}

node_t * merge_sort (node_t * l)
{
	node_t * l1, * l2;
	
	/* if there is only one entry, list is already sorted, o.w. first split them */
	if (l != NULL && l->next != NULL)
	{
		l1 = l;
		l2 = split(l);

		/* since there are two list, sort them seperatly and then merge */
		l1 = merge_sort(l1);
		l2 = merge_sort(l2);
		
		l = sorted_merge(l1, l2);
	}

	return l;
}

void insert_end (node_t ** l, int data)
{
	if (*l == NULL)
	{
		*l = (node_t *) malloc(sizeof(node_t));

		if (*l != NULL)
		{
			(*l)->data = data;
			(*l)->next = NULL;
		}	
	}
	else
		insert_end(&(*l)->next, data);
}

void print_list (const node_t * l)
{
	if (l != NULL)
	{
		printf("%d  ", l->data);
		print_list(l->next);
	}
	else
		putchar('\n');
}

int main (void)
{
	node_t * l = NULL;  
	insert_end(&l, 6);
	insert_end(&l, 5);
	insert_end(&l, 8);
	insert_end(&l, 4);
	insert_end(&l, 1);
	insert_end(&l, 7);
	insert_end(&l, 9);
	insert_end(&l, 2);
	insert_end(&l, 3);
	
	print_list(l);
	l = merge_sort(l);
	print_list(l);
}

