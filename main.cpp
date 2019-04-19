#include <iostream>
#include "BinTree.h"

using namespace std;

int main()
{
	int arr[] = {1, 12, -53543, 576, 7425};

	bin_tree tamerlan(sizeof(arr) / sizeof(int), arr);

	cout << tamerlan << endl;

	system("pause");
	return 0;
}
