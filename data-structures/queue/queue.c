#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	double data;
	struct node_t * next;
} node_t;

node_t * create_queue ();
void push (node_t ** q, double data);
int  pop (node_t ** q, double * data);
int  peek (const node_t * q, double * data);
void free_queue (node_t ** q);


int main (void)
{
	double pdata;	/* popped data */
	node_t * q = create_queue();

	push(&q, 1);
	push(&q, 2);
	push(&q, 3);
	push(&q, 4);
	if (pop(&q, &pdata) == 1)
		printf("popped %.1f\n", pdata);
	
	free_queue(&q);
}

node_t * create_queue ()
{
	return NULL;
}

void push (node_t ** q, double data)
{
	node_t * np = NULL, * tmp = NULL;

	if (q != NULL)
	{
		/* insert at the end of the list */
		np = (node_t *) malloc(sizeof(node_t));
		
		if (np != NULL)
		{
			np->data = data;
			np->next = NULL;

			if (*q == NULL)
				*q = np;
			else
			{
				tmp = *q;

				/* continue till tmp points the last node */
				while (tmp->next != NULL)
					tmp = tmp->next;  
				tmp->next = np;			
			}
		}
	}
}

int pop (node_t ** q, double * data)
{
	int status = 0;
	node_t * tmp;

	/* for popping at least one node exist */
	if (q != NULL && *q != NULL)
	{
		*data = (*q)->data;
		tmp = *q;		/* tmp holds the first node (popped node) */
		*q = tmp->next;
		free(tmp);
		status = 1;
	}

	return status;
}

int peek (const node_t * q, double * data)
{
	int status = 1;

	if (q != NULL)
		*data = q->data;
	else 
		status = 0;
	return status;
}
 
void free_queue (node_t ** q)
{
	node_t * tmp;

	if (q != NULL)
	{
		while (*q != NULL)
		{
			tmp = *q;
			*q = (*q)->next;
			free(tmp); 
		}
	} 
}