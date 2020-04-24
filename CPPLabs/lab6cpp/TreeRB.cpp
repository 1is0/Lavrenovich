//---------------------------------------------------------------------------

#pragma hdrstop

#include "TreeRB.h"
#include "Node.h"
#include "UnitMain.h"
#define NIL &sentinel           /* all leafs are sentinels */

Tree::Tree()
{
	sentinel.left = &sentinel;
	sentinel.right = &sentinel;
	sentinel.parent = &sentinel;
	sentinel.key = 0;

	root = &sentinel;
}

Tree::~Tree()
{
    DeleteTree(root);
}

void Tree::DeleteTree(Node *n)
{
	if (!n || n == NIL)
		return;
	if (n->right && n->right != NIL)
		DeleteTree(n->right);
	if (n->left && n->left != NIL)
		DeleteTree(n->left);
	delete n;
}

void Tree::RotateLeft(Node *x) {

   /**************************
	*  rotate node x to left *
	**************************/

	Node *y = x->right;

	/* establish x->right link */
	x->right = y->left;
	if (y->left != NIL)
		y->left->parent = x;

	/* establish y->parent link */
	if (y != NIL)
		y->parent = x->parent;
	if (x->parent)
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else
		root = y;

	/* link x and y */
	y->left = x;
	if (x != NIL)
		x->parent = y;
}

void Tree::RotateRight(Node *x) {

   /****************************
	*  rotate node x to right  *
	****************************/

	Node *y = x->left;

	/* establish x->left link */
	x->left = y->right;
	if (y->right != NIL)
		y->right->parent = x;

	/* establish y->parent link */
	if (y != NIL)
		y->parent = x->parent;
	if (x->parent)
	{
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else
		root = y;

	/* link x and y */
	y->right = x;
	if (x != NIL)
		x->parent = y;
}

void Tree::InsertFixup(Node *x)
{
   /*************************************
	*  maintain Red-Black tree balance  *
	*  after inserting node x           *
	*************************************/

	/* check Red-Black properties */
	while (x != root && x->parent->color == red) {
		/* we have a violation */
		if (x->parent == x->parent->parent->left) {
			Node *y = x->parent->parent->right;
			if (y->color == red) {

				/* uncle is RED */
				x->parent->color = black;
				y->color = black;
				x->parent->parent->color = red;
				x = x->parent->parent;
			}
			else
			{
				/* uncle is BLACK */
				if (x == x->parent->right)
				{
					/* make x a left child */
					x = x->parent;
					RotateLeft(x);
				}

				/* recolor and rotate */
				x->parent->color = black;
				x->parent->parent->color = red;
				RotateRight(x->parent->parent);
			}
		}
		else
		{
            /* mirror image of above code */
            Node *y = x->parent->parent->left;
			if (y->color == red)
			{
                /* uncle is RED */
				x->parent->color = black;
				y->color = black;
				x->parent->parent->color = red;
				x = x->parent->parent;
			}
			else
			{
                /* uncle is BLACK */
				if (x == x->parent->left)
				{
                    x = x->parent;
					RotateRight(x);
				}
				x->parent->color = black;
				x->parent->parent->color = red;
				RotateLeft(x->parent->parent);
			}
        }
    }
	root->color = black;
}

Node* Tree::InsertNode(AnsiString data, int key) {
	Node *current, *parent, *x;

   /***********************************************
	*  allocate node for data and insert in tree  *
	***********************************************/

	/* find where node belongs */
	current = root;
	parent = 0;
	while (current != NIL)
	{
		if (key == current->key)
			return (current);
		parent = current;
		current = (key < current->key) ? current->left : current->right;
	}

	/* setup new node */
	x = new Node(data, key);
	x->parent = parent;
	x->left = NIL;
	x->right = NIL;
	x->color = red;

	/* insert node in tree */
	if (parent)
	{
		if(x->key < parent->key)
            parent->left = x;
        else
            parent->right = x;
	}
	else
		root = x;

	InsertFixup(x);

	if (Form1->TV->Items->GetFirstNode())
		Form1->TV->Items->GetFirstNode()->Delete();
	ShowTV(Form1->TV);

    return(x);
}

void Tree::DeleteFixup(Node *x) {

   /*************************************
    *  maintain Red-Black tree balance  *
    *  after deleting node x            *
    *************************************/

	while (x != root && x->color == black)
	{
		if (x == x->parent->left)
		{
			Node *w = x->parent->right;
			if (w->color == red)
			{
				w->color = black;
				x->parent->color = red;
				RotateLeft (x->parent);
				w = x->parent->right;
			}
			if (w->left->color == black && w->right->color == black)
			{
				w->color = red;
				x = x->parent;
			}
			else
			{
				if (w->right->color == black)
				{
					w->left->color = black;
					w->color = red;
					RotateRight (w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = black;
				w->right->color = black;
				RotateLeft (x->parent);
				x = root;
			}
		}
		else
		{
			Node *w = x->parent->left;
			if (w->color == red)
			{
				w->color = black;
				x->parent->color = red;
				RotateRight (x->parent);
				w = x->parent->left;
			}
			if (w->right->color == black && w->left->color == black)
			{
				w->color = red;
				x = x->parent;
			}
			else
			{
				if (w->left->color == black)
				{
					w->right->color = black;
					w->color = red;
					RotateLeft (w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = black;
				w->left->color = black;
				RotateRight (x->parent);
				x = root;
			}
		}
	}
	x->color = black;
}

void Tree::DeleteNode(Node *z) {
	Node *x, *y;

   /*****************************
	*  delete node z from tree  *
	*****************************/

	if (!z || z == NIL)
		return;


	if (z->left == NIL || z->right == NIL)/* y has a NIL node as a child */
		y = z;
	else// find tree successor with a NIL node as a child
	{
		y = z->right;
		while (y->left != NIL)
			y = y->left;
	}

	if (y->left != NIL)// x is y's only child
		x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;

	if (y != z)
	{
		z->data = y->data;
        z->key = y->key;
	}


    if (y->color == black)
		DeleteFixup (x);

	delete y;

	if (Form1->TV->Items->GetFirstNode())
		Form1->TV->Items->GetFirstNode()->Delete();
	ShowTV(Form1->TV);
}

Node* Tree::FindNode(int key) {

   /*******************************
    *  find node containing data  *
    *******************************/

    Node *current = root;
	while(current != NIL)
		if(key == current->key)
			return (current);
        else
			current = (key < current->key) ? current->left : current->right;

	return nullptr;
}

// traverses
void Tree::Preorder(TMemo* Memo, Node* p) {
	if (!p || p == NIL)
		return;
	Memo->Lines->Add(p->data + " : " + IntToStr(p->key));
	Preorder(Memo, p->left);
	Preorder(Memo, p->right);
}

void Tree::Postorder(TMemo* Memo, Node* p) {
	if (!p || p == NIL)
		return;
	Postorder(Memo, p->left);
	Postorder(Memo, p->right);
	Memo->Lines->Add(p->data + " : " + IntToStr(p->key));
}

void Tree::Centered(TMemo* Memo, Node* p) {
	if (!p || p == NIL)
		return;
	Centered(Memo, p->left);
	Memo->Lines->Add(p->data + " : " + IntToStr(p->key));
	Centered(Memo, p->right);
}

void Tree::ShowTV(TTreeView* TV, Node *n, TTreeNode* tn)
{
	if (!n)
	{
		if (root == NIL || !root)
			return;
		else
			n = root;
	}
	TTreeNode* tmp;

	if (tn)
		tmp = TV->Items->AddChild(tn, n->data + " : " + IntToStr(n->key));
	else
		tmp = TV->Items->Add(nullptr, n->data + " : " + IntToStr(n->key));

	if (n->right != NIL && n->right)
		ShowTV(TV, n->right, tmp);
	if (n->left != NIL && n->left)
		ShowTV(TV, n->left, tmp);
}

int Tree::LeftSubtreeVal(Node *n)
{
	if (!n)
	{
		if (root == NIL || !root)
			return 0;
		else
			n = root->left;
	}

	if (n == NIL || !n)
		return 0;
	if (n != NIL && n && n->right == NIL && n->left == NIL)
        return 1;
	return 1 + LeftSubtreeVal(n->right) + LeftSubtreeVal(n->left);
}
#pragma package(smart_init)
