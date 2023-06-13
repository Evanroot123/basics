#include <iostream>
#include <vector>
#include "linked-list.h"

using namespace std;

int main()
{
	vector<int> shiboopy;
	shiboopy.push_back(1);
	shiboopy.push_back(2);
	shiboopy.push_back(3);
	shiboopy.push_back(4);
	shiboopy.push_back(5);

	vector<int>::iterator ptr;
	for (ptr = shiboopy.begin(); ptr < shiboopy.end(); ptr++)
	{
		cout << *ptr << " ";
	}

	//cout << shiboopy.begin() << endl;
	//cout << shiboopy.begin() + 1 << endl;
	//cout << shiboopy.begin() + 2 << endl;
	//cout << shiboopy.begin() + 3 << endl;
	//cout << shiboopy.begin() + 4 << endl;
	//cout << shiboopy.end() << endl;
}
