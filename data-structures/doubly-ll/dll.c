#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode_t {
	int data;
	struct dnode_t * prev;
	struct 	dnode_t * next;
} dnode_t;

int dll_create (dnode_t ** head, int data[], int dsize);
void print_reverse_dll (dnode_t * head);
void print_dll (dnode_t * head);
void free_dll (dnode_t ** head);
void insert_end_dll (dnode_t ** head, int data);
int remove_dll (dnode_t ** head, int data);
void sort_dll (dnode_t ** head);


int main (void)
{
	int 		dsize = 7,
				data[] = {9, 8, 7, 6, 5, 4, 3};
	dnode_t 	* head = NULL;

	dll_create(&head, data, dsize); print_dll(head);
/*	insert_end_dll(&head, 2); print_dll(head);
	remove_dll(&head, 9); print_dll(head)		*/
	sort_dll(&head); print_dll(head);
	free_dll(&head);
}

/* creates an dobly linked list */
int dll_create (dnode_t ** head, int data[], int dsize)
{
	int i, status = 0;
	dnode_t * bp = 	NULL,	/* ponints previos node */
	 		* np = 	NULL;	/* ponints new node 	*/

	if (head != NULL)
	{
		/* firstly insert first node */
		np = (dnode_t *) malloc(sizeof(dnode_t));

		if (np != NULL)
		{
			np->prev = NULL;	/* there is no node to points 			*/
			np->data = data[0];
			*head = np;
			bp = np;			/* back pointer points the first node 	*/

			for (i = 1; i < dsize; ++i)
			{
				np = (dnode_t *) malloc(sizeof(dnode_t));

				if (np != NULL)
				{
					np->data = data[i];
					np->prev = bp;	/* link back 		*/
					bp->next = np;	/* link forward 	*/
					bp = np;		/* update bp as np 	*/
				}
				else
					break;
			}

			if (i == dsize)
			{
				np->next = NULL;	/* set last node next as NULL */
				status = 1;
			}
		}
	}
	return status;
}

void insert_end_dll (dnode_t ** head, int data)
{
	dnode_t * tmp = NULL, * np = NULL;

	if (head != NULL)
	{
		np = (dnode_t *) malloc(sizeof(dnode_t));

		if (np != NULL)
		{
			np->data = data;

			/* insert as first node */
			if (*head == NULL)
			{
				np->next = NULL;
				np->prev = NULL;
				*head = np;
			}
			else
			{
				tmp = *head;
				/* set tmp as points to last node */
				while (tmp->next != NULL)
					tmp = tmp->next;

				tmp->next = np;	/* link backward 	*/
				np->prev = tmp;	/* link forward 	*/
			}
		}
	}
}

int remove_dll (dnode_t ** head, int data)
{
	int 	status = 0;
	dnode_t * tmp = NULL;

	if (head != NULL)
	{
		tmp = *head;

		while (tmp != NULL && tmp->data != data)
			tmp = tmp->next;

		if (tmp != NULL)
		{
			/* remove node is first node */
			if (tmp->prev == NULL)
				*head = (*head)->next;
			/* remove node is last node */
			else if (tmp->next == NULL)
				tmp->prev->next = NULL;
			else
			{
				tmp->prev->next = tmp->next; /* link backward 	*/
				tmp->next->prev = tmp->prev; /* link forward 	*/
			}
			free(tmp); status = 1;
		}
	}
	return status;
}

void sort_dll (dnode_t ** head)
{
	dnode_t * tmp;
	
	if (head != NULL)
	{
		
	}
}

void print_reverse_dll (dnode_t * head)
{
 	dnode_t * tmp = head;

 	if (head != NULL)
 	{
		/* tmp points the last node */
 		for (tmp = head; tmp->next != NULL; tmp = tmp->next);

 		/* go back from last pointer to first */
 		do {
 			printf("%-3d", tmp->data);
 			tmp = tmp->prev;
 		} while (tmp != NULL);
 	}
 	printf("\n");
}

void print_dll (dnode_t * head)
{
	if (head != NULL)
	{
		printf("%-3d", head->data); print_dll(head->next);
	}
	else
		printf("\n");
}

void free_dll (dnode_t ** head)
{
	dnode_t * tmp = NULL;

	while (*head != NULL)
	{
		tmp = *head;
		(*head) = (*head)->next;
		free(tmp);
	}
}