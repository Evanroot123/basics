#include <iostream>
#include <vector>
#include "linked-list.h"

using namespace std;

int main()
{
	LinkedList<int> test;
	test.pushBack(87);
	Node<int>* shiboopy = test.begin();
	cout << shiboopy->data << endl;
	shiboopy = test.rend();
	cout << shiboopy->data << endl;
	test.popBack();
	cout << test.length() << endl;
	test.pushFront(88);
	shiboopy = test.begin();
	cout << shiboopy->data << endl;
	shiboopy = test.rend();
	cout << shiboopy->data << endl;
}
