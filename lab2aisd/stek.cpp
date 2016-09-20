#include "stek.h"

using namespace std;

void Push(Stek* &NEXT, const string & VALUE)
{
	Stek *MyStack = new Stek;
	MyStack->value = VALUE;
	MyStack->next = NEXT;
	NEXT = MyStack;
}

string Pop(Stek* &NEXT)
{
	Stek *MyStack = NEXT;
	string temp = NEXT->value;

	NEXT = NEXT->next;
	delete MyStack;
	return temp;
}

