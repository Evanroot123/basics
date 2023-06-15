#pragma once

#include "linked-list.h"

using namespace std;

#define ASSERT(expression, numRuns)					\
	if (!(expression))						\
	{								\
		cout << "test failed at line: " << __LINE__ << endl;	\
		cout << "test failed during run: " << numRuns << endl;	\
		return false;						\
	}


class LinkedListTests
{
public:
	void runTests();
	bool test1();
	template <class T>
	bool basicFunctionalTest(int numRuns);
};

template <class T>
bool LinkedListTests::basicFunctionalTest(int numRuns)
{
	LinkedList<T> test;
	// line successfully executed before unhandled exception

	for (int i = 0; i < numRuns; i++)
	{
		// basic sanity checks
		test.clear();
		ASSERT(test.length() == 0 && test.empty(), i)
		T data;
		test.pushFront(data);
		ASSERT(test.length() == 1 && !test.empty(), i)
		test.clear();
		ASSERT(test.length() == 0 && test.empty(), i)
		test.pushFront(data);
		ASSERT(test.length() == 1 && !test.empty(), i)
		test.popFront();
		ASSERT(test.length() == 0 && test.empty(), i)
		test.pushFront(data);
		ASSERT(test.length() == 1 && !test.empty(), i)
		test.popBack();
		ASSERT(test.length() == 0 && test.empty(), i)
		test.pushBack(data);
		ASSERT(test.length() == 1 && !test.empty(), i)
		test.popFront();
		ASSERT(test.length() == 0 && test.empty(), i)
		test.pushBack(data);
		ASSERT(test.length() == 1 && !test.empty(), i)
		test.popBack();
		ASSERT(test.length() == 0 && test.empty(), i)
		test.pushFront(data);
		test.pushBack(data);
		test.pushFront(data);
		test.pushBack(data);
		ASSERT(test.length() == 4 && !test.empty(), i)
		test.popBack();
		test.popBack();
		test.popFront();
		test.popFront();
		ASSERT(test.length() == 0 && test.empty(), i)
		// alright at this point i think we've confirmed the empty and length functions are functioning properly lol
		test.insert(test.forwardIterator, data);
		ASSERT(test.length() == 1, i)
		test.insert(test.forwardIterator, data);
		ASSERT(test.length() == 2, i)
		test.clear();
		ASSERT(test.empty(), i)
		test.insert(test.forwardIterator, data);
		ASSERT(test.length() == 1, i)
		test.insert(test.forwardIterator, data);
		ASSERT(test.length() == 2, i)
		test.popFront();
		test.popFront();
		ASSERT(test.empty(), i)
		test.insert(test.forwardIterator, data);
		ASSERT(test.length() == 1, i)
		test.insert(test.forwardIterator, data);
		ASSERT(test.length() == 2, i)
		test.insert(test.reverseIterator, data);
		ASSERT(test.length() == 3, i)
		test.insert(test.reverseIterator, data);
		ASSERT(test.length() == 4, i)
	}

	return true;
}
