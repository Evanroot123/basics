template <class T>
class Node
{
public:
	T data;
	Node* prev;
	Node* next;
};

template <class T>
class LinkedList
{
public:
	LinkedList();
	void clear();
	int length() const;
	void pushFront(T data);
	void pushBack(T data);
	void popFront();
	void popBack();
	void insert(T data); // inserts before the internalIterator
	T& get(); // returns value at current internalIterator
	T& forward(); // advances internalIterator then returns element
	T& reverse(); // reverse internalIterator then returns element
	T& begin(); // sets internalIterator to the head and also returns that element
	T& end(); // sets internalIterator to the tail and also returns that element
	void erase(); // erases value at internalIterator then advances
		

private:
	int count = 0;
	Node* head;
	Node* tail;
	Node* internalIterator;
};
