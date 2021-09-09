#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENT	-1
#define STRLEN 	40

typedef struct node_t {
	char s[STRLEN];
	struct node_t * next;
} node_t;

int insert_end (node_t ** head, char str[]);
void free_list (node_t ** head);
void print_list (node_t * head);
void create_list (node_t ** head);
void clear_stdin ();
int remove_node (node_t ** head, char data[], int delete_all);
int insert_anywhere (node_t ** head, char data[], int n);


int main (void)
{
	node_t * head = NULL;

	create_list(&head);
	print_list(head);
	remove_node(&head, "burak", 1);
	insert_anywhere(&head, "semra", 0);
	print_list(head);
	free_list(&head);
}

void create_list (node_t ** head)
{
	int	i = 1;
	char data[STRLEN];
	
	printf("%d. node: ", i);
	scanf("%[^\n]", data);  clear_stdin();
	
	while (strcmp(data, "quit") != 0 && strcmp(data, "QUIT") != 0)
	{
		if (insert_anywhere (head, data, i) == 1)
			++i;
		else
		{
			printf("New node cannot added\n"); break;
		}

		printf("%2d. node: ", i);
		scanf("%[^\n]", data);  clear_stdin();
	}
}

/* 	if it is possible (there are 2 node and user wants to insert as 5),
 	insert a new node as will be nth node of list 						*/
int insert_anywhere (node_t ** head, char data[], int n)
{
	int 	i,
			status = 0;
	node_t 	* tmp = NULL,
			* new_node = NULL;

	if (head != NULL && n > 0)
	{
		new_node = (node_t *) malloc(sizeof(node_t));

		if (new_node != NULL)
		{
			strcpy(new_node->s, data);
			new_node->next = NULL;

			/* in case of first place head pointers value must be change */
			if (n == 1)
			{
				new_node->next = *head;
				(*head) = new_node;
				status = 1;
			}
			else
			{
				/* tmp shows first node and counter starts as 1 to indicate first node */
				tmp = *head, i = 1;

				/* to insert new node as n. node tmp should points (n - 1). node */
				while (tmp != NULL && i < n - 1)
				{
					tmp = tmp->next, ++i;
				}

				if (tmp != NULL)
				{
					new_node->next = tmp->next;
					tmp->next = new_node;
					status = 1;
				}
				else
					free(new_node);
			}
		}
	}
	print_list(*head);
	return status;
}

int insert_end (node_t ** head, char data[])
{
	int 	status = 0;
	node_t * tmp = NULL, * new_node = NULL;

	if (head != NULL)
	{
		/* create a new node */
		new_node = (node_t *) malloc(sizeof(node_t));

		if (new_node != NULL)
		{
			strcpy(new_node->s, data);
			new_node->next = NULL;
			
			/* there is an empty list, so return the head as points the first node */
			if (* head == NULL)
				*head = new_node;
			else
			{
				/* find the last node and change its next value as address of new node */
				for (tmp = *head; tmp->next != NULL; tmp = tmp->next);

				tmp->next = new_node;
			}
			status = 1;
		}
	}
	return status;
}

/* 	removes the nodes or node in case of delete_all parameter, by comparing giving data */
int remove_node (node_t ** head, char data[], int delete_all)
{
	int 	status = 0;
	node_t 	* cur_node = NULL, 
			* pre_node = NULL;


	if (head != NULL && *head != NULL)
	{
		for (cur_node = *head; cur_node != NULL; cur_node = cur_node->next)
		{
			/* if current node is remove node free it, o.w. keep the 
				address of current node to insert remove_node->next 	*/
			if (strcmp(cur_node->s, data) == 0)
			{
				/* 	there is no previos node, current node is the first
					node, so head pointer needs to be update 			*/
				if (pre_node == NULL)
					*head = cur_node->next; 
				else
					pre_node->next = cur_node->next;
				
				free(cur_node);
				status = 1;
				
				if (delete_all == 0)
					break;
			}
			else	
				pre_node = cur_node;
		}
	}
	return status;
}

void free_list (node_t ** head)
{
	int i;
	node_t * tmp;

	if (head != NULL)
	{
		/* if there is a list */
		while (*head != NULL)
		{
			/* 	free current node and move the next node 
				tmp keeps the address of current node 		 */
			tmp = *head;
			*head = (*head)->next;
			free(tmp);
		}
	}
}

void print_list (node_t * head)
{
	node_t * tmp;

	printf("list: \n");
	for (tmp = head; tmp != NULL; tmp = tmp->next)
		printf("%s\n", tmp->s);
	printf("\n");
}

void clear_stdin ()
{
	char c;

	do {
		c = getchar();
	} while (c != '\n' && c != '\r');
}