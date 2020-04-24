//---------------------------------------------------------------------------

#ifndef RingH
#define RingH
#include "DoublyLinkedList.h"
#include "Node.h"

template<class T>
class Ring: public DLList<T>
{
	Node<T>* current;
public:
	Ring();
	~Ring(){}
	void ShowAll(TListBox* LB){this->DLList<T>::Show(LB);}
	void Move(int i);
	void ShowCurrent(TLabel *label);
	void DeleteCurrent();
};

template<class T>
Ring<T>::Ring(): DLList<T>()
{
	this->head->prev = this->tail;
	this->tail->next = this->head;
	current = this->head;//for now
}

template<class T>
void Ring<T>::Move(int i)//either -1 or 1
{
	if (!this->size)
		return;

	if (i == 1)
		current = current->next;
	else
		current = current->prev;

	if (current == this->head)
		current = this->tail->prev;
	else if (current == this->tail)
		current = this->head->next;
}

template<class T>
void Ring<T>::ShowCurrent(TLabel *label)
{
	if (!this->size)
		label->Caption = "Nothing";
	else
        label->Caption = (UnicodeString)current->data;
}

template<class T>
void Ring<T>::DeleteCurrent()
{
	if (!this->size)
	{
		ShowMessage("Пусто!");
        return;
	}

    current->prev->next = current->next;
	current->next->prev = current->prev;

	this->size--;
	Node<T>* tmp = current->prev;
	delete current;
	current = tmp;

	if (current == this->head)
		current = this->tail->prev;
	else if (current == this->tail)
		current = this->head->next;
}
#endif
