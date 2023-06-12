template <class T>
class UnsortedListArray
{
public:
	UnsortedListArray(int size=10);
	~UnsortedListArray();
	void clear();
	int count() const;
	T get(int position);
	void put(T item);
	void remove(T item);
	void reset();
	T getNext();
private:
	int size; // how much memory this is taking up
	int length; // how many elements have been allocated
	T* list;
	int current; // location of the "iterator" over the list
};

template <class T>
UnsortedListArray<T>::UnsortedListArray(int size)
{
	this->size = size;
	list = new T[size];
	current = 0;
	length = 0;
}

template <class T>
UnsortedListArray<T>::~UnsortedListArray()
{
	delete[] list;
	list = nullptr;
}

template <class T>
void UnsortedListArray<T>::clear()
{
	delete[] list;
	list = nullptr;
	size = 0;
	length = 0;	
}

template <class T>
int UnsortedListArray<T>::count() const
{
	return length;
}

template <class T>
T UnsortedListArray<T>::get(int position)
{
	if (position < size && > -1)
		return list[position];
}

template <class T>
void UnsortedListArray<T>::put(T item)
{
	
}

template <class T>
void UnsortedListArray<T>::remove(T item)
{
	
}

template <class T>
void UnsortedListArray<T>::reset()
{
	current = 0;
}

template <class T>
T UnsortedListArray<T>::getNext()
{
	
}
