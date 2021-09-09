#include <stdio.h>
#include <stdlib.h>

typedef struct stack_t {
	double data;
	struct stack_t * next;
} stack_t;

stack_t * create_stack ();
void push (stack_t ** s, double data);
int  pop (stack_t ** s, double * data);
int  peek (const stack_t * s, double * data);
void print_stack (const stack_t * s);
void free_stack (stack_t ** s);

int main (void)
{
	double sdata;		/* stack data */
	stack_t * s = create_stack();

	push(&s, 17); push(&s, 12); push(&s, 15);
	print_stack(s);

	if (pop(&s, &sdata) == 1)
		printf("pop : %.1f\n", sdata);
	
	if (peek(s, &sdata) == 1)
		printf("peek: %.1f\n", sdata);

	print_stack(s);
	free_stack(&s);
}

/* to be sure stack initialize with NULL */
stack_t * create_stack ()
{
	return NULL;
}

void push (stack_t ** s, double data)
{
	stack_t * np = NULL;

	if (s != NULL)
	{
		/* create new node */
		np = (stack_t *) malloc(sizeof(stack_t));

		if (np != NULL)
		{
			np->data = data;
			np->next = *s;
			*s = np;
		}
	}
}

int pop (stack_t ** s, double * data)
{
	int status = 0;
	stack_t * tmp = NULL;

	if (s != NULL && *s != NULL)
	{
		*data = (*s)->data;
		tmp = *s; 			/* keep the address of popped node to free 	*/
		*s = tmp->next;		/* update the head of the stack				*/
		free(tmp); 
		status = 1;
	}
	return status;
}

int peek (const stack_t * s, double * data)
{
	int status = 0;

	/* if stack is not empty */
	if (s != NULL)
	{
		*data = s->data;
		status = 1;
	}

	return status;
}

void print_stack (const stack_t * s)
{
	printf("Stack:");

	while (s != NULL)
	{
		printf(" %.1f", s->data);
		s = s->next;
	}
	printf("\n");
}

void free_stack (stack_t ** s)
{
	stack_t * tmp;

	if (s != NULL)
	{
		while (*s != NULL)
		{
			tmp = *s;
			*s = (*s)->next;
			free(tmp);
		}
	}
}