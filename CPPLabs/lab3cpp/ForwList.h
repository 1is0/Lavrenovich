//---------------------------------------------------------------------------

#ifndef ForwListH
#define ForwListH
#include "UnitMain.h"
#include "Data.h"
class ForwList
{
	class Node
	{
	public:
		Node* next;
		Data data;
		Node(Data data = Data(), Node* next = NULL) {this->data = data; this->next = next;}
		~Node(){}
	};
	int size;
	Node *head;

public:

	ForwList();
	~ForwList();
	void PushBack(Data data);
	int GetSize() const {return size;}
	void ShowAll();
	void FindName(TRichEdit* RE, const std::string &name);
	void FindAmountInStock(TRichEdit* RE, int amount);
	void FindCost(TRichEdit* RE, int cost);
};
#endif
