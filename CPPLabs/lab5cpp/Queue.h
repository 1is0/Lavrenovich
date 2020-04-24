//---------------------------------------------------------------------------

#ifndef QueueH
#define QueueH
#include "DoublyLinkedList.h"
#include "Node.h"

template<class T>
class Queue: private DLList<T>
{
public:
	Queue(): DLList<T>(){}
	~Queue(){}

	void Push(T data){ this->PushFront(data);}
	T Pop(){return this->PopBack();}
	T Top(){return this->BackInfo();}
	void Show(TListBox* LB){this->DLList<T>::Show(LB);}
    int Size(){return this->DLList<T>::Size();}
};

#endif
