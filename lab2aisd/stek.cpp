#include "stek.h"

using namespace std;

void push(stek* &NEXT, const string & VALUE)
{
	stek *MyStack = new stek;
	MyStack->value = VALUE;
	MyStack->next = NEXT;
	NEXT = MyStack;
}

string pop(stek* &NEXT)
{
	stek *MyStack = NEXT;
	string temp = NEXT->value;

	NEXT = NEXT->next;
	delete MyStack;
	return temp;
}

