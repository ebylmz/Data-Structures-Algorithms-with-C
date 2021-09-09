#include <stdio.h>
#include <stdlib.h>

/*
	The AVL trees are more balanced compared to Red-Black Trees, 
	but they may cause more rotations during insertion and deletion. 
	So if your application involves frequent insertions and deletions, then Red-Black trees should be preferred.
	And if the insertions and deletions are less frequent and search is a more frequent operation,
 	then AVL tree should be preferred over Red-Black Tree.
*/

typedef enum {RED, BLACK} rbt_color_t;

typedef struct tree_t {
	int data;
	rbt_color_t color;
	struct tree_t * left, * right, * parent;
} tree_t;

void swap (int * a, int *b) {int tmp = *a; *a = *b; *b = tmp;}

void rbt_recolor (tree_t * t) { if (t != NULL) t->color = (t->color + 1) % 2;}

int is_black (tree_t * t) {return t == NULL || t->color == BLACK;}

tree_t * bst_min (tree_t * t) {return t && t->left ? bst_min(t->left) : t;}

tree_t * get_sibling (tree_t * t) {return t && t->parent ? (t->parent->left != t ? t->parent->left : t->parent->right) : (NULL);}

tree_t * get_root (tree_t * t) {return t && t->parent ? get_root(t->parent) : t;}

tree_t * rotate_left (tree_t * root) 
{
	tree_t * newroot, * traveler;

	newroot = root->right;
	traveler = newroot->left;

	newroot->left = root;
	root->right = traveler;

	newroot->parent = root->parent;
	root->parent = newroot;

	/* since we rotate the tree the parent of preroot child changes, so we need to update  */
	if (newroot->parent != NULL)	
	{
		if (newroot->parent->left == root)	
			newroot->parent->left = newroot;
		else
			newroot->parent->right = newroot;
	}

	return newroot;
}

tree_t * rotate_right (tree_t * root) 
{
	tree_t * newroot, * traveler;

	newroot = root->left;
	traveler = newroot->right;

	newroot->right = root;
	root->left = traveler;

	newroot->parent = root->parent;
	root->parent = newroot;

	if (newroot->parent != NULL)
	{
		if (newroot->parent->left == root)	/* it still points root we need to change */
			newroot->parent->left = newroot;
		else
			newroot->parent->right = newroot;
	}

	return newroot;
}


tree_t * rbt_set_insertion_balance (tree_t * c) 
{
	tree_t 	* root = c,
		 	* gp, * s, * p = c->parent; /* family members */
	
	if (p != NULL && p->color == RED) /* if not, tree is already balanced  */
	{
		gp = p->parent;	/* if p is red gp must be exist, o.w. root becomes red and this is invalid in rbt */

		s = get_sibling(p);	/* get sibling of parent */

		if (s == NULL || s->color == BLACK)	/* rotate and recolor */
		{
			/* define the rotation type */
			if (p->data < gp->data) /* LL or LR */
			{
				if (c->data > p->data) /* LR */
					p = rotate_left(p);
				p = rotate_right(gp);	/* after rotation gp become siblings of child */
		
				rbt_recolor(p);
				rbt_recolor(p->right);
			}
			else /* RR or RL */
			{
				if (c->data < p->data) /* RL */
					p = rotate_right(p);
				p = rotate_left(gp);

				rbt_recolor(p);
				rbt_recolor(p->left);
			}
		}
		else /* recolor parent and his siblings */
		{
			rbt_recolor(p);
			rbt_recolor(s);

			if (gp->parent != NULL)	/* if it's not root node also recolor it and check */
			{
			 	rbt_recolor(gp);
			 	if (gp->color == RED)
			 		root = rbt_set_insertion_balance(gp);
			}
		} 
		
	}
	root = get_root(c); /* update the root */

	return root;
}

tree_t * rbt_insert (tree_t * t, int data)
{
	tree_t * p = NULL, * tmp = t;

	while (tmp != NULL)
	{
		if (data != tmp->data)
		{
			p = tmp;	/* before iterate tmp, keep the parent */
			
			if (data > tmp->data)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
	}

	tmp = (tree_t *) malloc(sizeof(tree_t));

	if (tmp != NULL)
	{
		tmp->data = data;

		tmp->parent = p;
		tmp->left = tmp->right = NULL;

		if (p != NULL)
		{
			tmp->color = RED; /* new nodes are initialy red, except root node */		
			
			if (data > p->data)
				p->right = tmp;
			else
				p->left = tmp;
		}
		else
			tmp->color = BLACK;

		t = rbt_set_insertion_balance(tmp);		/* set balance and update the root */
		/* 	the difference between AVL and RBT is that in AVL balance function
		 	executes each recursive iteration but in RBT this only works max two times 
		 	since set balance function first look if parent color is red and we now granparent cannot red
		 	if parent is red, but after recoloring it can be so it executes max 2 times 
		*/
	}

	return t;
} 


/* case 1: dnode is RED */
	/* deleting red node is does not change the black height of that path, so just delete */
/* case 2: DB is root node just remove the DB property and set as BLACK */
/* case 3: sibling is BLACK and his childs are BLACK or NULL */
/* case 4: sibling is RED */
/* case 5: sibling is BLACK, far child from DB is BLACK and near child is RED */
/* case 6: sibling is BLACK far child is RED */
tree_t * apply_case1 (tree_t * DB) 
{
	tree_t * root, * tmp = DB;
	DB = DB->right != NULL ? DB->right : DB->left;
	free(tmp)

	root = get_root(DB);

	printf("case 1 applied\n");

	return root;
}

tree_t * apply_case2 (tree_t * DB) 
{
	tree_t * root;

	/*
	printf("case 2 applied\n");
	*/
	printf("NOT IMPLEMENTED YET\n");

	return root;
}

tree_t * apply_case3 (tree_t * DB, tree_t * p, tree_t * s)
{
	tree_t * root;
	s->color = red;

	
	if (p->color == BLACK)
		root = rbt_set_deletion_balance(p);
	else
		p->color = BLACK;

	root = get_root(DB);
	free(t)

	printf("case 3 applied\n");

	return root;
} 

tree_t * apply_case4 (tree_t * DB, tree_t * p, tree_t * s)
{
	tree_t * root;

	swap(&p->color, &DB->color);

	if (DB->data < p->data) /* rotate parent towards DB */
		p = rotate_left(p);
	else
		p = rotate_right(p);

	/* CHECK IF DB IS EXIST ?? */

	printf("case 4 applied\n");

	return root;
} 

tree_t * apply_case5 (tree_t * DB, tree_t * p, tree_t * s, tree_t * c_near, tree_t * c_far)
{
	tree_t * root;
	
	swap(s->color, c_near->color);

	if (DB->data < s->data) /* rotate sibling opposite direction to DB */
		s = rotate_right(s);
	else
		s = rotate_left(s);

	root = apply_case6(DB, p, s, c_near, c_far);
	
	printf("case 5 applied\n");

	return root;
} 

tree_t * apply_case6 (tree_t * DB, tree_t * p, tree_t * s, tree_t * c_near, tree_t * c_far)
{
	tree_t * root;

	swap(p->color, s->color);

	if (DB->data < p->data) /* rotate parent towards DB */
		p = rotate_left(p);
	else
		p = rotate_right(p);


	c_far->color = BLACK;
	root = get_root(DB);
	free(DB);

	printf("case 6 applied\n");

	return root;
} 


tree_t * rbt_set_deletion_balance (tree_t * dnode)
{
	tree_t * p = dnode->parent, * s, * c_near, * c_far, * root = NULL; /* sibling of dnode and his child's */

	if (p == NULL) /* case 1 */
		root = apply_case1(dnode);
	else
	{
		if (dnode->color == RED) /* case 2 */
			root = apply_case2(dnode);
		else
		{
			s = get_sibling(dnode);

			if (s == NULL)	/* I'M NOT SURE THIS IS SUITABLE FOR CASE 3  ****************************** */
				root = apply_case3(dnode, p, s);
			else
			{
				if (s->color == RED) /* case 4 */
					root = apply_case4(dnode, p, s);
				else
				{ 
					if (dnode->data < s->data) /* define the far child and near child */
						c_far = s->right, c_near = s->left;
					else
						c_far = s->left, c_near = s->right;

					if (is_black(s->right) && is_black(s->left)) /* case 3 */
						root = apply_case3(dnode);
					else if (is_black(c_far) && !is_black(c_near)) /* case 5 */
						root = apply_case5(dnode, p, s, c_near, c_far);
					else if (!is_black(c_far)) /* case 6 */
						root = apply_case6(dnode, p, s, c_near, c_far);
				}
			}
		}
	}

	return root;
}

tree_t *rbt_delete (tree_t * t, int data)
{
	tree_t * tmp, *successor;

	if (t != NULL)
	{
		tmp = t;
		while (tmp != NULL && tmp->data != data)
			tmp = data > t->data ? tmp->right : t->left;

		if (tmp != NULL) /* if delete data exist */
		{
			/* if node has one child or no child that node will free o.w. we need to copy the value of inorder successor */
			if (tmp->right == NULL || tmp->left == NULL)
				t = rbt_set_deletion_balance(tmp);
				/* in deletion black delete node becomes DB (double black), our purpose is
				   somehow rearrange the tree and destroying all the DB stituation
				   there are 6 case for deletion */					
			else
			{
				successor = bst_min(tmp->right); /* get the inorder successor */
				tmp->data = successor->data;
				t = rbt_delete(tmp->right, tmp->data);
			}
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


void rbt_print2D (const tree_t * t, int n)
{
	int i;

	if (t != NULL)
	{
		rbt_print2D(t->right, n + 1);

		for (i = 0; i < n; ++i) 
			printf("----- ");
		printf("%d ", t->data);
		printf(t->color == RED ? "(R)\n" : "(B)\n");
		
		rbt_print2D(t->left, n + 1);
	}
}

int main (void)
{
	tree_t * t = NULL;

	t = rbt_insert(t, 1);
	printf("\n"); in_order(t);

	t = rbt_insert(t, 4);
	printf("\n"); in_order(t); 

	t = rbt_insert(t, 6);
	printf("\n"); in_order(t); 

	t = rbt_insert(t, 3);
	printf("\n"); in_order(t); 

	t = rbt_insert(t, 5);
	printf("\n"); in_order(t); 

	t = rbt_insert(t, 7);
	printf("\n"); in_order(t); 

	t = rbt_insert(t, 8);
	printf("\n"); in_order(t); 

	t = rbt_insert(t, 2);
	printf("\n"); in_order(t); 

	t = rbt_insert(t, 9);
	printf("\n"); in_order(t); 

	printf("\n\n");
	rbt_print2D(t, 0);

	printf("\ndelete 5\n\n");
	rbt_delete(t, 5);
	rbt_print2D(t, 0);
	getchar();

	printf("delete 6\n\n");
	rbt_delete(t, 6);
	rbt_print2D(t, 0);
	getchar();
	
	printf("delete 9\n\n");
	rbt_delete(t, 9);
	rbt_print2D(t, 0);
	getchar();
}