#include <unsorted-list.h>

template <class T>
UnsortedListArray<T>::UnsortedListArray(int size)
{
	length = size;
	list = new T[length];
	current = 0;
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
	
}

template <class T>
int UnsortedListArray<T>::count() const
{

}

template <class T>
T UnsortedListArray<T>::get(T item, bool& found)
{
	
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

}

template <class T>
T UnsortedListArray<T>::getNext()
{

}
