#include <stdio.h>
#include <stdlib.h>

#define SENT -1

typedef struct node_t {
	int data;
	struct node_t * next;
} node_t;

void insert_end (node_t ** headp, int data);
node_t * create_list ();
void print_reverse (node_t * head);
void freelist (node_t ** headp);

int main (void)
{
	node_t * head = NULL;
	 
	head = create_list();	print_reverse(head);
	freelist(&head); print_reverse(head);

	if (head == NULL)
		printf("All list succesfully freed\n");
	else
		printf("Head still points somewhere\n");
}

void insert_end (node_t ** headp, int data)
{
	node_t * tmp,
			* node;

	/* if there isn't any node, just create a new one and assign to headp,
		o.w. find the end node (NULL pointer) insert end 					*/
	if (*headp != NULL)
		for (tmp = *headp; tmp->next != NULL; tmp = tmp->next);

	node = (node_t *) malloc(sizeof(node_t));
	if (node != NULL)
	{
		node->data = data;
		node->next = NULL;

		if (*headp == NULL)
			*headp = node;
		else
			tmp->next = node;
	}
}

node_t * create_list ()
{
	int data,
		i = 1;
	
	node_t * head = NULL;
	
	printf("%2d. node: ", i);
	scanf("%d", &data);
	
	while (data != SENT)
	{
		insert_end (&head, data);	++i;

		printf("%2d. node: ", i);
		scanf("%d", &data);
	}

	return head; 
}

void print_reverse (node_t * head)
{
	/* we haven't reach the end node yet */
	if (head != NULL)
	{
		print_reverse(head->next);
		printf("%-2d ", head->data);
	}
}

/* ı think iterative solution better than recursive solution */

/* reach the the one last node to free the last node */
void freelist (node_t ** headp)
{
	/* if there is list */
	if (*headp != NULL)
	{
		/* if we have only one node */
		if ((*headp)->next == NULL)
		{
			printf("free %d\n", (*headp)->data);
			free(*headp);
			*headp = NULL;
		}
		else
		{
			/* free remainder nodes then free the current node */
			freelist(&(*headp)->next);
			
			printf("free %d\n", (*headp)->data);
			free(*headp);	
			*headp = NULL;
		}
	}
}