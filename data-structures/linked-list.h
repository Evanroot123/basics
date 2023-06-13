template <class T>
class Node
{
public:
	Node(T& data);
	Node(T&& data);
	T data;
	Node* prev;
	Node* next;
};

template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void clear();
	int length() const;
	bool empty() const;
	void pushFront(T& data);
	void pushFront(T&& data);
	void pushBack(T& data);
	void pushBack(T&& data);
	void popFront();
	void popBack();
	void insert(Node<T>* iterator, T& data); // inserts before the iterator
	void insert(Node<T>* iterator, T&& data); // inserts before the iterator
	void forward(); // advances forwardIterator
	Node<T>* begin(); // returns first element if exists or end
	Node<T>* end(); // returns end
	void reverse(); // advances reverseIterator
	Node<T>* rbegin(); // returns begin
	Node<T>* rend(); // returns last element if exists or begin
	void erase(Node<T>* iterator); // erases value at iterator then advances
	// this has mutated into the way that I am going to access the data
	Node<T>* forwardIterator;
	Node<T>* reverseIterator;
	
private:
	void init();
	int count = 0;
	Node<T>* head;
	Node<T>* tail;
};

template <class T>
Node<T>::Node(T& data)
{
	this->data = data;
}

template <class T>
Node<T>::Node(T&& data)
{
	this->data = data;
}

template <class T>
LinkedList<T>::LinkedList()
{
	T dummy;
	head = new Node<T>(dummy);
	tail = new Node<T>(dummy);
	head->prev = nullptr;
	head->next = tail;
	tail->prev = head;
	tail->next = nullptr;
	init();
}

template <class T>
LinkedList<T>::~LinkedList()
{
	delete head;
	delete tail;
}

template <class T>
void LinkedList<T>::init()
{
	count = 0;
	forwardIterator = head->next;
	reverseIterator = tail->prev;
}

template <class T>
void LinkedList<T>::clear()
{
	// TODO: implement manual version without calling functions to compare performance
	if (!empty())
	{
		for (forwardIterator = begin(); forwardIterator != end(); forwardIterator = forward())
		{
			erase(forwardIterator);
		}
	}

	init();
}

template <class T>
int LinkedList<T>::length() const
{
	return count;
}

template <class T>
bool LinkedList<T>::empty() const
{
	return count == 0;
}

template <class T>
void LinkedList<T>::pushFront(T& data)
{
	Node<T>* newNode = new Node<T>(data);
	newNode->prev = head;
	newNode->next = head->next;
	head->next->prev = newNode;
	head->next = newNode;
	count++;
}

template <class T>
void LinkedList<T>::pushFront(T&& data)
{
	Node<T>* newNode = new Node<T>(data);
	newNode->prev = head;
	newNode->next = head->next;
	head->next->prev = newNode;
	head->next = newNode;
	count++;
}

template <class T>
void LinkedList<T>::pushBack(T& data)
{
	Node<T>* newNode = new Node<T>(data);
	newNode->prev = tail->prev;
	newNode->next = tail;
	tail->prev->next = newNode;
	tail->prev = newNode;
	count++;
}

template <class T>
void LinkedList<T>::pushBack(T&& data)
{
	Node<T>* newNode = new Node<T>(data);
	newNode->prev = tail->prev;
	newNode->next = tail;
	tail->prev->next = newNode;
	tail->prev = newNode;
	count++;
}

template <class T>
void LinkedList<T>::popFront()
{
	if (!empty())
	{
		Node<T>* temp = head->next;
		head->next = temp->next;
		temp->next->prev = head;
		delete temp;
		count--;
	}
}

template <class T>
void LinkedList<T>::popBack()
{
	if (!empty())
	{
		Node<T>* temp = tail->prev;
		tail->prev = temp->prev;
		temp->prev->next = tail;
		delete temp;
		count--;
	}
}

template <class T>
void LinkedList<T>::insert(Node<T>* iterator, T& data)
{
	Node<T>* newNode = new Node<T>(data);
	Node<T>* temp = iterator->prev;
	newNode->prev = temp;
	newNode->next = iterator;
	temp->next = newNode;
	iterator->prev = newNode;
	count++;
}

template <class T>
void LinkedList<T>::insert(Node<T>* iterator, T&& data)
{
	Node<T>* newNode = new Node<T>(data);
	Node<T>* temp = iterator->prev;
	newNode->prev = temp;
	newNode->next = iterator;
	temp->next = newNode;
	iterator->prev = newNode;
	count++;
}

template <class T>
void LinkedList<T>::forward()
{
	forwardIterator = forwardIterator->next;
}

template <class T>
Node<T>* LinkedList<T>::begin()
{
	if (head->next)
		return head->next;
	return tail;
}

template <class T>
Node<T>* LinkedList<T>::end()
{
	return tail;
}

template <class T>
void LinkedList<T>::reverse()
{
	reverseIterator = reverseIterator->prev;
}

template <class T>
Node<T>* LinkedList<T>::rbegin()
{
	return head;
}

template <class T>
Node<T>* LinkedList<T>::rend()
{
	if (tail->prev)
		return tail->prev;
	return head;
}

template <class T>
void LinkedList<T>::erase(Node<T>* iterator)
{
	if (!empty())
	{
		Node<T>* temp = iterator->prev;
		temp->next = iterator->next;
		iterator->prev = temp;
		delete iterator;
		count--;
	}	
}
