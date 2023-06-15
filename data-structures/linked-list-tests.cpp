#include <iostream>
#include "linked-list-tests.h"
#include "linked-list.h"

using namespace std;

void LinkedListTests::runTests()
{
	int numTests = 0, passedTests = 0;

	if (basicFunctionalTest<int>(10))
		passedTests++;
	numTests++;

	cout << "passed tests / number of tests: " << passedTests << "/" << numTests << endl;
}

bool LinkedListTests::test1()
{
	return true;
}

