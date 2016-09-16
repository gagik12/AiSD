#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct stek
{
	string value;
	struct stek *next; 
};

struct Operator
{
	string beginOperator;
	string endOperator;
};

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
	std::cout << temp; 
	return temp; 
}

vector<Operator> InitOperator()
{
	Operator structOperator;
	vector<Operator> opt;
	structOperator.beginOperator = "BEGIN";
	structOperator.endOperator = "END";
	opt.push_back(structOperator);

	structOperator.beginOperator = "REPEAT";
	structOperator.endOperator = "UNTIL";
	opt.push_back(structOperator);
	return opt;
}

string ReadWord(ifstream & inputFile, bool & isReadEof)
{
	string word = "";
	char ch;
	inputFile.get(ch);
	while (ch != ' ')
	{
		if ((ch == '\r') || (ch == '\n'))
		{
			break;
		}
		word += ch;
		inputFile.get(ch);
		if (inputFile.eof())
		{
			isReadEof = true;
			break;
		}
	}
	return word;
}

int CompareStrings(std::string const& a, std::string const& b)
{
	return !(strcmp(a.c_str(), b.c_str()));
}

int main()
{
	ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		cout << "File not open!!!";
		return 1;
	}
	vector<Operator> opt = InitOperator();
	stek *p = NULL;

	bool isReadEof = false;
	while (!isReadEof)
	{
		string word = ReadWord(inputFile, isReadEof);
		for (int i = 0; i != opt.size(); i++)
		{
			if (CompareStrings(opt[i].beginOperator, word))
			{
				push(p, word);
				cout << "YES\n";
			}
			else if (CompareStrings(opt[i].endOperator, word))
			{
				cout << "NO\n";

			}
			
		}
	}
	//push(p, "BEGIN");
	//pop(p);
	return 0;
}
