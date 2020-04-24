//---------------------------------------------------------------------------

#ifndef TreeRBH
#define TreeRBH
#include <vcl.h>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>

#include "Node.h"

class Tree
{
	Node* root;
    Node sentinel;
	void RotateLeft(Node*);
	void RotateRight(Node*);
	void InsertFixup(Node*);
	void DeleteFixup(Node*);
	void DeleteTree(Node*);
public:
	Tree();
	~Tree();
	Node* GetRoot(){return root;}
	Node* InsertNode(AnsiString, int);
	void DeleteNode(Node*);
	Node* FindNode(int);

    void ShowTV(TTreeView *TV, Node *n = nullptr, TTreeNode *tn = nullptr);
    int LeftSubtreeVal(Node *n = nullptr);

	void Preorder(TMemo *Memo, Node* p);
	void Postorder(TMemo *Memo, Node* p);
	void Centered(TMemo *Memo, Node* p); // �� ����������� �����
};
#endif
