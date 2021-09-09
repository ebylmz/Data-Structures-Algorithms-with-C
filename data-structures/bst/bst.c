#include <stdio.h>
#include <stdlib.h>

typedef struct queue_t {
	int data;
	struct queue_t * next;
} queue_t;

typedef struct tree_t {
	int data;
	struct tree_t * left, * right;
} tree_t;


void bst_insert (tree_t ** t, int data)
{
	if (*t == NULL)
	{
		*t = (tree_t *) malloc(sizeof(tree_t));

		if (*t != NULL)
		{
			(*t)->data = data;
			(*t)->left = (*t)->right = NULL;
		}
	}
	else if (data < (*t)->data)
		bst_insert(&(*t)->left, data);
	else if (data > (*t)->data)
		bst_insert(&(*t)->right, data);
}


void swap (int * i, int * j)
{
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

tree_t * bst_min (tree_t * t) {return (t != NULL && t->left != NULL) ? bst_min(t->left): t;}

tree_t * bst_max (tree_t * t) {return (t != NULL && t->right != NULL) ? bst_max(t->right) : t;}

/*	binary tree deletion:

	1. Swap the last node with delete node
	2. free the delete node (since it's inserted last, it has no child. I mean no loss) 
	-----------------------------------------------------------------------------------
	binary search tree deletion:

	1. find the delete node 
	2. find the inorder successor (the min value that bigger than delete node)	
	3. set delete node data as successor data,
	4. since becomes a dublicated data delete it and return NULL
	
	we always delete the leaf node or node that has one child, 
	thats because we choose inorder successor/predecessor
	since we know they are leaf nodes or they have only one child
*/

tree_t * bst_delete (tree_t * t, int data)
{
	tree_t * tmp;

	if (t != NULL)
	{
		if (data < t->data)
			t->left = bst_delete(t->left, data);
		else if (data > t->data)
			t->right = bst_delete(t->right, data);
		else
		{
			/* first check if there is only one leaf node or none */
			if (t->right == NULL || t->left == NULL)
			{
				tmp = t;
				t = (t->right == NULL) ? t->left : t->right;
				free(tmp);
			}
			else 
			{
				/*
					1. Select right or left subtree. bst_max() for left, bst_min() for right, ı choose right 
					2. Set bst_min as root value (we delete data by changing it's value)
					3. But now there is a dubliceted value (bst_min), next step is deleting that value.
					   Since we select bst_min at right subtree we know it's there so delete at right subtree 
				*/
				tmp = bst_min(t->right);
				t->data = tmp->data;	
				t->right = bst_delete(t->right, t->data);	
			}
		}
	}
	return t;
}

/* to validate given tree is bst, I implement queue by using q_push() function */
void q_push (queue_t ** q, int data)
{
	queue_t * n = (queue_t *) malloc(sizeof(queue_t));

	if (n != NULL)
	{
		n->data = data;
		n->next = *q;
		*q = n;
	}
}

void q_in_order (tree_t * t, queue_t ** q)
{
	if (t != NULL)
	{
		q_in_order(t->right, q);
		q_push(q, t->data);
		q_in_order(t->left, q);
	}
}

void q_destroy (queue_t * q)
{
	if (q != NULL)
	{
		q_destroy(q->next);
		free(q);
	}
}

/* 	1.convert given tree to queue by inorder traversal
	2. check if queue is ordered as increasing, if so return 1 o.w. return 0 
*/
int is_bst (tree_t * t)
{
	int r = 1;
	queue_t * q = NULL, * tmp;

	q_in_order(t, &q);	/* given tree is  */
	tmp = q;

	while (tmp != NULL && r)
	{
		if (tmp->next != NULL && tmp->data > tmp->next->data)
			r = 0;

		tmp = tmp->next;
	}

	q_destroy(q);

	return r; 
}

void bst_destroy (tree_t ** t)
{
	if (*t != NULL)
	{
		bst_destroy(&(*t)->left);
		bst_destroy(&(*t)->right);
		free(*t);
	}
}

void in_order (const tree_t * t) 
{
	if (t != NULL)
	{
		in_order(t->left);
		printf("%d ", t->data);
		in_order(t->right);
	}
}

void t_print2D (const tree_t * t, int n)
{
	int i;

	if (t != NULL)
	{
		t_print2D(t->right, n + 1);

		for (i = 0; i < n; ++i) 
			printf("----- ");
		printf("%d\n", t->data);
		
		t_print2D(t->left, n + 1);
	}
}

int main (void)
{
	tree_t * t = NULL;
	int n;

	bst_insert(&t, 50);
	bst_insert(&t, 30);
	bst_insert(&t, 20);
	bst_insert(&t, 10);
	bst_insert(&t, 60);
	bst_insert(&t, 55);
	bst_insert(&t, 35);
	bst_insert(&t, 40);
	bst_insert(&t, 70);
	bst_insert(&t, 65);
	bst_insert(&t, 80);
	bst_insert(&t, 5);

	printf("inOrder traversal: "); in_order(t); putchar('\n');

	printf("\n2D tree visualation:\n\n");
	t_print2D(t, 0);

	printf("\nDelete value: ");
	scanf("%d", &n);

 	t = bst_delete(t, n); 

	printf("\n2D tree visualation:\n\n");
	t_print2D(t, 0);

	printf(is_bst(t) ? "This is bst\n" : "This is not bst\n");

	bst_destroy(&t);
}