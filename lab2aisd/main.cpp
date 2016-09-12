#include <iostream>
#include <string>

using namespace std;

struct Operators
{
	int key;
	Operators *next;
};

void Push(Operators **p, int element)
{

}

void Pop(Operators **p)
{

}

int main()
{
	cout << "Enter operators!\n";
	string strOperators;
	getline(cin, strOperators);

	if (strOperators.length() == 0)
	{
		cout << "Empty operators!!\n";
		return 1;
	}
}