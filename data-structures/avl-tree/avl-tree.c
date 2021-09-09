#include <stdio.h>
#include <stdlib.h>

typedef struct tree_t {
	int data;
	int height;
	struct tree_t * left, * right;
} tree_t;


int max (int a, int b) {return a > b ? a : b;}

int height (tree_t * t) {return t != NULL ? t->height : 0;}

int avl_get_balance_factor (tree_t * t) {return t != NULL ? height(t->left) - height(t->right) : 0;}

void set_height (tree_t * t) {if (t != NULL) t->height = 1 + max(height(t->left), height(t->right));}

tree_t * bst_min (tree_t * t) {return (t != NULL && t->left != NULL) ? bst_min(t->left) : t;}

tree_t * bst_max (tree_t * t) {return (t != NULL && t->right != NULL) ? bst_max(t->right) : t;}

/*  Left Rotation:

	1. Get the new-root. In left rotation right ones move left, so new-root will be right of child of the pre-root
	2. Keep the left side of the new-root as traveler since pre-root comes there
	3. put pre-root left of new-root and put traveler right of the pre-root since traveler bigger than it
	4. update the hight of the pre and new roots
	5. return the new-root 	 
*/
tree_t * left_rotate (tree_t * t)
{
	tree_t * newroot, * traveler;

	newroot = t->right; 
	traveler = newroot->left;
	
	newroot->left = t;		
	t->right = traveler;	

	/* be careful since height of the new-root depends pre-root first update pre-root height */
	set_height(t);
	set_height(newroot);

	return newroot;
}

tree_t * right_rotate (tree_t * t)
{
	tree_t * newroot, * traveler;

	newroot = t->left;
	traveler = newroot->right;

	newroot->right = t;
	t->left = traveler;

	set_height(t);
	set_height(newroot);

	return newroot;
}

/*  Getting Balanced of the tree

	1. define the rotation type (LL LR RR RL).(LR : Left insertion & R insertion caused unbalance)
	2. 	if rotation type is LR, firstly convert it LL simalarly convert RL to RR than apply rotation
		RR: means insertion at right side so to get balance apply left rotation
	3. apply right rotation for LL and left rotation for RR
	4. update the height of the rearranged root						
*/

tree_t * avl_set_balance (tree_t * t, int data)
{
	int b = avl_get_balance_factor(t);

	if (b > 1)	/* tree unbalanced because of insertions at left side of the root */
	{
		if (avl_get_balance_factor(t->left) < 0) /* LR case */
			t->left = left_rotate(t->left); /* convert LR to LL */
		
		t = right_rotate(t); /* LL case */	
	}
	else if (b < -1)
	{
		if (avl_get_balance_factor(t->right) > 0) /* RL case */
			t->right = right_rotate(t->right); /* convert RL to RR */
		
		t = left_rotate(t); /* RR case */		
	}

	return t;
}

/*
	1. Insert by appliying binary search
	2. Set the new height of the tree
	3. Be sure tree is still balanced
*/
tree_t * avl_insert (tree_t * t, int data)
{
	if (t == NULL)
	{
		t = (tree_t *) malloc(sizeof(tree_t));

		if (t != NULL)
		{
			t->data = data;
			t->height = 1;		/* we set height zero as height of the NULL node */
			t->left = t->right = NULL;
		}
		/* if there was no root, no need to do anyting, but there was it will handle recursivly */
	}
	else if (t->data != data)
	{
		if (data < t->data)
			t->left = avl_insert(t->left, data);
		else
			t->right = avl_insert(t->right, data);

		/* update the height of tree and be sure it's still balanced */
		set_height(t);
		
		t = avl_set_balance(t, data);
	}

	return t;
}
 
/* apply BST delete and be sure tree is still balanced */
tree_t * avl_delete (tree_t * t, int data)
{
	tree_t * tmp;

	if (t != NULL)
	{
		if (data > t->data)
			t->right = avl_delete(t->right, data);
		else if (data < t->data)
			t->left = avl_delete(t->left, data);
		else
		{
			/* first check if delete node has only one child or none */
			if (t->left == NULL || t->right == NULL)
			{
				tmp = t;
				t = (t->left == NULL) ? t->right : t->left;
				free(tmp);
			}
            /* node with two children: Get the inorder successor (smallest in the right subtree) */
			else 
			{
            	/* Copy the inorder successor's data to this node and delete the inorder successor */
				tmp = bst_min(t->right);
				t->data = tmp->data;
				t->right = avl_delete(t->right, t->data);	/* call with t->right, since we find it at right subtree */
			}
		}
		
		if (t != NULL)
		{
			set_height(t);
			t = avl_set_balance(t, data);
		}
	}
	return t;
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

void pre_order (const tree_t * t)
{
	if (t != NULL)
	{
		printf("%d ", t->data);
		pre_order(t->left);
		pre_order(t->right);
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

    t = avl_insert(t, 9);
    t = avl_insert(t, 5);
    t = avl_insert(t, 10);
    t = avl_insert(t, 0);
    t = avl_insert(t, 6);
    t = avl_insert(t, 11);
    t = avl_insert(t, -1);
    t = avl_insert(t, 1);
    t = avl_insert(t, 2);
 	 
 	 /* The constructed AVL Tree would be
	            9
	           /  \
	          1    10
	        /  \     \
	       0    5     11
	      /    /  \
	     -1   2    6
	*/

	printf("Preorder traversal of the constructed AVL: ");
	pre_order(t); putchar('\n');

	printf("Inorder  traversal of the constructed AVL: ");
	in_order(t); putchar('\n');

	t_print2D(t, 0);

	n = 10;
	printf("\n\nDelete %d\n\n", n);	
	t = avl_delete(t, n);

	/* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */

	t_print2D(t, 0);
}
