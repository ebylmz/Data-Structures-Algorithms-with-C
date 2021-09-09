#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int * arr,
		count;
} stack_t;

void create_stack (stack_t * stack)
{
	stack->arr = NULL;
	stack->count = 0;
}

void push (stack_t * stack, int val)
{
	int i,
		* new_arr;	/* pointer to keep new allocated memory */

	/* create a new sized array */
	new_arr = (int *)calloc(stack->count + 1, sizeof(int));

	if (new_arr != NULL)
	{
		/* copy previous entries to the new stack */
		for (i = 0; i < stack->count; ++i)
			new_arr[i] = stack->arr[i];

		/* push the new value to stack and increase the counter */
		new_arr[stack->count] = val;
		++(stack->count);

		if (stack->arr != NULL)
			free(stack->arr);
		
		stack->arr = new_arr;
		printf("push %4d\n", val);
	}
}

int pop (stack_t * stack)
{
	int 	i, n,
			err = 0,
			pop_val;
	
	int * new_arr;


	if (stack->count > 1)
	{
		/* create the new stack */
		new_arr = (int *)calloc(stack->count - 1, sizeof(int));

		if (new_arr != NULL)
		{
			for (i = 0, n = stack->count - 1; i < n; ++i)
				new_arr[i] = stack->arr[i];

			pop_val = stack->arr[stack->count - 1];
			--(stack->count);
			
			printf("pop  %4d\n", pop_val);

		/* ! do not forget to free previosly memory and assign new allocated memory */
			free(stack->arr);
			stack->arr = new_arr;
		}
		else
			err = 1;
	}
	else if (stack->count == 1)
	{
		pop_val = stack->arr[0];
		printf("pop  %4d\n", pop_val);
		
		free(stack->arr);
		stack->arr = NULL;
		stack->count = 0;
	}	
	else
		err = 1;

	if (err == 1)
	{
		pop_val = 0;
		printf("cannot popped\n");
	}

	return pop_val;
}

void print_stack (const stack_t * stack)
{
	int i;

	if (stack->count > 0)
	{
		printf("Stack: ");

		for (i = 0; i < stack->count; ++i)
			printf("%d ", stack->arr[i]);
		printf("\n");
	}
	else
		printf("Stack: empty\n");
}

int main(void)
{
	stack_t stack;	/* ! I defined "a stack_t * stack" and occured lots of problem, be careful */

	create_stack(&stack);
	push(&stack, 1);
	push(&stack, 2);
	push(&stack, 3);
	push(&stack, 17);

	print_stack(&stack);

	pop(&stack);
	
	print_stack(&stack);

	pop(&stack);
	pop(&stack);
	pop(&stack);
	pop(&stack);
	
	print_stack(&stack);

	if (stack.arr != NULL)
		free(stack.arr);
}