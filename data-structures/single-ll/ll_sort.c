#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 30

typedef struct node_t {
	char 	data[STRLEN];
	struct node_t * next; 
} node_t;

void ll_create (node_t ** head, char w[][STRLEN], int wsize);
void ll_sort (node_t ** head);
void ll_print (node_t * head);
void ll_free (node_t ** head);


int main (void)
{
	node_t * head = NULL;
	int wsize = 14;
	char w[][STRLEN] = {"Bruce", "Maria", "David", "Mary", "Alice", "Tom", "Bunny",
						"Gilbert", "Einstein", "Tesla", "Elon", "Jeff", "Rocky", "Edison"};

	/* create a list and sort them */
	ll_create(&head, w, wsize);
	ll_print(head);

	ll_sort(&head);
	ll_print(head);
	ll_free(&head);
}

void ll_create (node_t ** head, char w[][STRLEN], int wsize)
{
	int 	i;
	node_t 	* tmp = NULL, 
			* last_node = NULL;

	if (head != NULL && w != NULL)
	{		
		for (i = 0; i < wsize; ++i)
		{
			/* create a new node */
			tmp = (node_t *) malloc(sizeof(node_t));

			if (tmp != NULL)
			{
				strcpy(tmp->data, w[i]);

				/* insert new node as first node */
				if (i == 0)
				{
					*head = tmp;
					last_node = tmp;
				}
				else
				{
					/* insert new node as last node */
					last_node->next = tmp;
					
					if (i == wsize - 1)
						tmp->next = NULL;
					/* update next node for next iteration */
					else
						last_node = tmp;
				}
			}
			/* free all the list and return status as 0 */
			else
			{
				ll_free(head); break;
			}
		}
	}
}

void ll_sort (node_t ** head)
{
	node_t 	* ip 	= NULL, * jp 	= NULL,
			* fillp = NULL,	* tmp;

	/* insert an empty node to have a back pointer for first node */
	tmp = (node_t *) malloc(sizeof(node_t));

	if (head != NULL && tmp != NULL)
	{
		tmp->next = *head;
		*head = tmp;

		/* every iteration check if current node is last node or not, if so no need to sort */
		for (ip = *head; ip->next != NULL; ip = ip->next)
		{
			/* ip and jp points the one back node of current node */
			fillp = ip;

			for (jp = ip->next; jp->next != NULL; jp = jp->next)
				if (strcmp(jp->next->data, fillp->next->data) < 0)
					fillp = jp;

			if (fillp != ip)
			{
				/* remove the node have min value from it's place 		 */
				tmp = fillp->next;			/* keep address of removing node */
				fillp->next = tmp->next;	/* link nodes where we remove node */

				tmp->next = ip->next;
				ip->next = tmp;		
			}
		}
		/* head points empty node that we insert, so remove that node */
		tmp = (*head)->next;
		free(*head);	
		*head = tmp;	
	}
}

void ll_sort2 (node_t ** head)
{
	node_t * ip, * jp, * fillp, * bp_cur, * bp_fill;

	if (head != NULL)
	{
		bp_cur = 	
		
		for (ip = (*head)->next; ip != NULL; ip = ip->next)
		{
			fillp = ip;

			for (jp = ip->next; jp != NULL; jp = jp->next)
		}
	}
}

void ll_print (node_t * head)
{
	if (head == NULL)
		printf("\n");
	else
	{
		printf("%s\n", head->data);
		ll_print(head->next);
	}
}

void ll_free (node_t ** head)
{
	if (*head != NULL)
	{
		/* first free rest then free the current node */
		ll_free(&(*head)->next);
		free(*head);
		*head = NULL;
	}
}