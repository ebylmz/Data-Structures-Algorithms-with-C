#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
	int data;
	struct node_t * next;
} node_t;

int remove_dublicate (node_t * ll);
node_t * create_list (int data[], int dsize);
void ll_free (node_t ** head);
void print_list (const node_t * head);
 

int main (void)
{
	int data[] = {1, 2, 3, 2, 3, 4}, dsize = 5;
	node_t * ll = create_list(data, dsize);

	if (ll != NULL)
	{
		print_list(ll);
		if (remove_dublicate(ll) == 1)
		{
			printf("dublicate removed: ");	print_list(ll);
		}
		ll_free(&ll);
	}
}
 
/* removes the ascending order linked list dublicate */
int remove_dublicate (node_t * ll)
{
	int status = 0;		/* indicates dublicate exist */
	node_t * rp;		/* remove pointer, actually no need to use but for clean code */
	
	/* at least two node left to compare */
	while (ll != NULL && ll->next != NULL)
	{
		/* 	in case of dublicate remove the second node, to do not change the value of head node,
			do not change the ll, if removed node is 2, we should compare 1. and 3. node next iteration	*/
		if (ll->data == ll->next->data)
		{
			rp = ll->next;
			ll->next = rp->next;
			free(rp);
			status = 1;
		}
		else
			ll = ll->next;
	}
	return status;
}

node_t * create_list (int data[], int dsize)
{
	int i;
	node_t 	* llist = NULL,
			* tmp, * np;

	if (dsize > 0)
	{
		np = (node_t *) malloc(sizeof(node_t));

		if (np != NULL)
		{
			np->data = data[0]; 
			np->next = NULL;
			tmp = llist = np;

			for (i = 1; i < dsize; ++i)
			{
				np = (node_t *) malloc(sizeof(node_t));

				if (np != NULL)
				{
					np->data = data[i];
					tmp->next = np;		/* link new node with list 			  */
					tmp = tmp->next;	/* update tmp as points the last node */
				}
				else
				{
					ll_free(&llist); break;
				}
			}
			/* after node creation , set last node next as NULL */
			np->next = NULL;
		}
	}
	return llist;
}

void print_list (const node_t * head)
{
	if (head != NULL)
	{
		printf("%d ", head->data);
		print_list(head->next);
	}
	else
		printf("\n");
}

void ll_free (node_t ** head)
{
	node_t * tmp = NULL;

	if (head != NULL)
	{
		tmp = *head;

		while (*head != NULL)
		{
			tmp = *head;
			*head = (*head)->next;
			free(tmp);
		}
	} 
}