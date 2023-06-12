#include <iostream>
#include <vector>
#include "linked-list.h"

using namespace std;

class Test
{
public:
	int x;
	int hello()
	{
		return x;
	}
};

Test func1()
{
	Test test;
	test.x = 7;
	return test;
}

int main()
{
	Test x = func1();
	cout << x.hello() << endl;
}
