#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int data;
	struct node_t * next;
} node_t;

void create_list (node_t ** headp); 
void print_list (node_t * head);
void freelist (node_t ** headp);


int main (void)
{
	node_t * head = NULL;
	
	create_list(&head);	print_list(head);
	freelist(&head);

	if (head == NULL)
		printf("list succesfully freed\n");
	else
		printf("list cannot freed\n");
}

void create_list (node_t ** headp) 
{
	int i = 1,	
		data;
	char go;
	
	node_t * newnode = NULL,
		   * prenode = NULL;
	
	/* be sure head pointer points NULL */
	if (*headp != NULL)
		*headp = NULL;

	do {
		newnode = (node_t *) malloc(sizeof(node_t));

		if (newnode != NULL)
		{
			/* take data from user and insert it created list */
			printf("%2d. node data: ", i);
			scanf("%d", &data);
			++i;

			newnode->data = data;
			newnode->next = NULL;

			/* 	if there is previos node link previos node with the new node,
				 o.w. set newnode as the first node pointed by head pointer		*/
			if (prenode == NULL)
			{
				*headp = newnode;
				prenode = newnode;
			}
			else
			{
				prenode->next = newnode;

				/* for next itereation change pre node as new node */
				prenode = newnode;
			}
			
			while (getchar() != '\n');
			printf("Do you want to continue? (y/n): ");
			scanf("%c", &go);
		}
		else
		{
			printf("%d. node cannot created, there is not enough memory\n", i);	
			go = 0;
		}
	} while (go == 'Y' || go == 'y');
}

/* 	this is more efficient comparing to recursive version, we do not need
	to assign to head pointer NULL because last node->next already NULL */
void freelist (node_t ** headp)
{
	node_t * tmp;

	while (*headp != NULL)
	{
		/* keep the address of the next node, and free the current node */
		tmp = *headp;
		*headp = (*headp)->next;
		free(tmp);
	}
}

void print_list (node_t * head)
{
	node_t * tmp;

	/* print all the nodes */
	for (tmp = head; tmp != NULL; tmp = tmp->next) 
		printf("%-2d ", tmp->data);

	printf("\n");
}