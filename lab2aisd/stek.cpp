#include "stek.h"

using namespace std;

void push(Stek* &NEXT, const string & VALUE)
{
	Stek *MyStack = new Stek;
	MyStack->value = VALUE;
	MyStack->next = NEXT;
	NEXT = MyStack;
}

string pop(Stek* &NEXT)
{
	Stek *MyStack = NEXT;
	string temp = NEXT->value;

	NEXT = NEXT->next;
	delete MyStack;
	return temp;
}

