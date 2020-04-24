//---------------------------------------------------------------------------

#ifndef DoublyLinkedListH
#define DoublyLinkedListH
#include <vcl.h>
#include "Node.h"
template<class T>
class DLList
{
protected:
	Node<T> *head, *tail;
	int size;
public:
	DLList();
	~DLList();
	virtual void PushFront(T data);
	virtual void PushBack(T data);
	virtual T PopFront();
	virtual T PopBack();
	virtual T FrontInfo(){return (size) ? head->next->data : T();}
	virtual T BackInfo(){return (size) ? tail->prev->data : T();}
	virtual void PushIdx(int offset, T data);
	virtual T PopIdx(int offset);
	virtual T IdxInfo(int offset);
	virtual void Show(TListBox* LB);
	virtual int Size(){return size;}
};



//*******************************METHODS**************************************
template<class T>
DLList<T>::DLList()
{
	size = 0;
	head = new Node<T>();
	tail = new Node<T>();
	head->next = tail;
	tail->prev = head;
}

template<class T>
DLList<T>::~DLList()
{
	if (size)
	{
		Node<T>* current = head;
		while(current)
		{
			Node<T>* next = current->next;
			delete current;
			current = next;
		}
	}
}

template<class T>
void DLList<T>::PushFront(T data)
{
	Node<T>* toPush = new Node<T>(data);
	if (!size)
	{
		toPush->next = tail;
		toPush->prev = head;
		head->next = toPush;
		tail->prev = toPush;
		size++;
		return;
	}
	toPush->prev = head;
	toPush->next = head->next;
	toPush->next->prev = toPush;
	head->next = toPush;

	size++;
}

template<class T>
void DLList<T>::PushBack(T data)
{
	Node<T>* toPush = new Node<T>(data);
	if (!size)
	{
		toPush->next = tail;
		toPush->prev = head;
		head->next = toPush;
		tail->prev = toPush;
		size++;
		return;
	}
	toPush->next = tail;
	toPush->prev = tail->prev;
	tail->prev->next = toPush;
	tail->prev = toPush;

	size++;
}

template<class T>
T DLList<T>::PopFront()
{
	if (!size)
		return T();
	Node<T>* toPop = head->next;
	head->next = toPop->next;
	head->next->prev = head;
	T tmp = toPop->data;
	delete toPop;
    size--;
    return tmp;
}

template<class T>
T DLList<T>::PopBack()
{
	if (!size)
		return T();
	Node<T>* toPop = tail->prev;
	tail->prev = toPop->prev;
	tail->prev->next = tail;
    T tmp = toPop->data;
	delete toPop;
    size--;
    return tmp;
}

template<class T>
void DLList<T>::PushIdx(int offset, T data)
{
	if (offset < 0 || offset > size)
	{
		ShowMessage("Inappropriate index. Size = " + IntToStr(size) + ".");
        return;
	}
    if (offset == 0) {
		PushFront(data);
		return;
	}
	if (offset == size - 1)
	{
	   PushBack(data);
	   return;
	}
	Node<T>* current = head->next;
	for (int i = 0; i < offset; i++)
		 current = current->next;//finding our element
	Node<T>* toPush = new Node(data);

	Node<T>* node1 = current->prev;
	Node<T>* node2 = current->next;
	node1->next = toPush;
	node2->prev = toPush;
    toPush->prev = node1;
	toPush->next = node2;

	size++;
}

template<class T>
T DLList<T>::PopIdx(int offset)
{
	if (offset < 0 || offset >= size)
	{
		ShowMessage("Inappropriate index. Size = " + IntToStr(size) + ".");
		return T();
	}
	if (offset == 0)
		return PopFront();
	if (offset == size - 1)
	    return PopBack();

	Node<T>* current = head->next;
	for (int i = 0; i < offset; i++)
		 current = current->next;//finding our element
	current->prev->next = current->next;
	current->next->prev = current->prev;
	T tmp = current->data;

	delete current;
	size--;

	return tmp;
}

template<class T>
T DLList<T>::IdxInfo(int offset)
{
	if (!size) {
		ShowMessage("������ ����.");
		return T();
	}
	if (offset < 0 || offset >= size) {
		ShowMessage("Inappropriate index. Size = " + IntToStr(size) + ".");
		return T();
	}
	Node<T>* current = head->next;
	for (int i = 0; i < offset; i++)
		 current = current->next;
    return current->data;
}

template<class T>
void DLList<T>::Show(TListBox* LB)
{
	LB->Items->Clear();
	if (!size) {
		ShowMessage("�����!");
		return;
	}
	Node<T>* current = head;
	for (int i = 0; i < size; i++)
	{
        current = current->next;
		LB->Items->Add((UnicodeString)current->data);
	}
}

#endif
