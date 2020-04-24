// ---------------------------------------------------------------------------

#ifndef NodeH
#define NodeH
template<class T>
class Node {
public:
	Node(T data = T()){this->data = data; this->prev = nullptr; this->next = nullptr;}
	~Node() {}
	Node *prev, *next;
	T data;
};
#endif
