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
	void resetFront();
	void resetBack();
	void insertBefore(T& data); // inserts before the iterator
	void insertBefore(T&& data); // inserts before the iterator
	void insertAfter(T& data); // inserts after the iterator
	void insertAfter(T&& data); // inserts after the iterator
	void forward(); // advances forwardIterator
	Node<T>* begin(); // returns head if not nullptr or end
	Node<T>* end(); // returns end
	void reverse(); // advances reverseIterator
	Node<T>* rbegin(); // returns begin
	Node<T>* rend(); // returns tail if not nullptr or begin
	void erase(Node<T>* iterator); // erases value at iterator then advances
	// this has mutated into the way that I am going to access the data
	Node<T>* forwardIterator;
	Node<T>* reverseIterator;
	
private:
	void init();
	int count = 0;
	Node<T>* head;
	Node<T>* tail;
	Node<T>* begin; // points 1 past head
	Node<T>* end; // points 1 past tail
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
	begin = new Node(dummy);
	begin->prev = nullptr;
	begin->next = nullptr;
	end = new Node(dummy);
	end->prev = nullptr;
	end->next = nullptr;
	init();
}

template <class T>
LinkedList<T>::~LinkedList()
{
	delete begin;
	delete end;
}

template <class T>
void LinkedList<T>::init()
{
	count = 0;
	head = end;
	tail = begin;
	forwardIterator = nullptr;
	reverseIterator = nullptr;
	head->prev = begin;
	tail->next = end;
}

template <class T>
void LinkedList<T>::clear()
{
	//Node<T>* temp;

	//while(head && head != end)
	//{
	//	temp = head->next;
	//	delete head;
	//	head = temp;
	//}

	// alternate method
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
	//if (!head && !tail)
	//{
	//	head = new Node<T>(data);
	//	head->prev = nullptr;
	//	head->next = nullptr;
	//	tail = head;
	//}
	//else
	//{
	//	Node<T>* temp = new Node<T>(data);
	//	temp->prev = nullptr;
	//	temp->next = head;
	//	head->prev = temp;
	//	head = temp;
	//}
	
	

	count++;
}

template <class T>
void LinkedList<T>::pushFront(T&& data)
{
	// if head is null tail is too
	if (!head)
	{
		head = new Node<T>(data);
		head->prev = nullptr;
		head->next = nullptr;
		tail = head;
	}
	else
	{
		Node<T>* temp = new Node<T>(data);
		temp->prev = nullptr;
		temp->next = head;
		head->prev = temp;
		head = temp;
	}

	count++;
}

template <class T>
void LinkedList<T>::pushBack(T& data)
{
	if (!head)
	{
		tail = new Node<T>(data);
		tail->prev = nullptr;
		tail->next = nullptr;
		head = tail;
	}
	else
	{
		Node<T>* temp = new Node<T>(data);
		temp->next = nullptr;
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}

	count++;
}

template <class T>
void LinkedList<T>::pushBack(T&& data)
{
	if (!head)
	{
		tail = new Node<T>(data);
		tail->prev = nullptr;
		tail->next = nullptr;
		head = tail;
	}
	else
	{
		Node<T>* temp = new Node<T>(data);
		temp->next = nullptr;
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}

	count++;
}

template <class T>
void LinkedList<T>::popFront()
{
	if (head)
	{
		if (head->next)
		{
			Node<T>* temp = head->next;
			head->next = nullptr;
			delete head;
			head = temp;
			head->prev = nullptr;
		}
		else
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}

		count--;
	}
}

template <class T>
void LinkedList<T>::popBack()
{
	if (tail)
	{
		if (tail->prev)
		{
			Node<T>* temp = tail->prev;
			tail->prev = nullptr;
			delete tail;
			tail = temp;
			tail->next = nullptr;
		}
		else
		{
			delete tail;
			head = nullptr;
			tail = nullptr;
		}

		count--;
	}
}

template <class T>
void LinkedList<T>::resetFront()
{
	iterator = head;
}

template <class T>
void LinkedList<T>::resetBack()
{
	iterator = tail;
}

template <class T>
void LinkedList<T>::insertBefore(T& data)
{
	if (!head)
	{
		Node<T>* temp = new Node(data);
		head = temp;
		tail = temp;
		iterator = temp;
		temp->next = nullptr;
		temp->prev = nullptr;
	}
	else if (iterator && iterator->prev)
	{
		Node<T>* temp = iterator->prev;
		Node<T>* newNode = new Node(data);
		newNode->prev = temp;
		newNode->next = iterator;
		iterator->prev = newNode;
		temp->next = newNode;
	}
	else // iterator invalid but head is not
	{
		Node<T>* newNode = new Node(data);
		head->prev = newNode;
		newNode->next = head;
		newNode->prev = nullptr;
		head = newNode;
	}
	
	count++;
}

template <class T>
void LinkedList<T>::insertBefore(T&& data)
{
	if (!head)
	{
		Node<T>* temp = new Node(data);
		head = temp;
		tail = temp;
		iterator = temp;
		temp->next = nullptr;
		temp->prev = nullptr;
	}
	else if (iterator && iterator->prev)
	{
		Node<T>* temp = iterator->prev;
		Node<T>* newNode = new Node(data);
		newNode->prev = temp;
		newNode->next = iterator;
		iterator->prev = newNode;
		temp->next = newNode;
	}
	else // iterator invalid but head is not
	{
		Node<T>* newNode = new Node(data);
		head->prev = newNode;
		newNode->next = head;
		newNode->prev = nullptr;
		head = newNode;
	}

	count++;
}

template <class T>
void LinkedList<T>::insertAfter(T& data)
{
	if (!tail)
	{
		Node<T>* temp = new Node(data);
		head = temp;
		tail = temp;
		iterator = temp;
		temp->next = nullptr;
		temp->prev = nullptr;
	}
	else if (iterator && iterator->next)
	{
		Node<T>* temp = iterator->next;
		Node<T>* newNode = new Node(data);
		newNode->prev = iterator;
		newNode->next = temp;
		iterator->next = newNode;
		temp->prev = newNode;
	}
	else
	{
		Node<T>* newNode = new Node(data);
		tail->next = newNode;
		newNode->next = nullptr;
		newNode->prev = tail;
		tail = newNode;
	}

	count++;
}

template <class T>
void LinkedList<T>::insertAfter(T&& data)
{
	if (!tail)
	{
		Node<T>* temp = new Node(data);
		head = temp;
		tail = temp;
		iterator = temp;
		temp->next = nullptr;
		temp->prev = nullptr;
	}
	else if (iterator && iterator->next)
	{
		Node<T>* temp = iterator->next;
		Node<T>* newNode = new Node(data);
		newNode->prev = iterator;
		newNode->next = temp;
		iterator->next = newNode;
		temp->prev = newNode;
	}
	else
	{
		Node<T>* newNode = new Node(data);
		tail->next = newNode;
		newNode->next = nullptr;
		newNode->prev = tail;
		tail = newNode;
	}

	count++;
}

template <class T>
T& LinkedList<T>::get()
{
	return iterator->data;
}

template <class T>
T& LinkedList<T>::forward()
{
	Node<T>* temp = iterator;
	iterator = iterator->next;
	return temp->data;
}

template <class T>
T& LinkedList<T>::reverse()
{
	Node<T>* temp = iterator;
}

template <class T>
T& LinkedList<T>::begin()
{

}

template <class T>
T& LinkedList<T>::end()
{

}


