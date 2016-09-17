/*           ДОЛГАНОВ ВАДИМ НИКОЛАЕВИЧ
                   ВАРИАНТ 27
Программа  на ПАСКАЛЕ включает такие сочетания ключевых
слов,  как  REPEAT..UNTIL  и   BEGIN..END.   Некоторые   части
программы  могут быть закомментированы,  а другая часть текста
может представлять из себя константы в  апострофах.  Требуется
проверить правильность вложенности данных конструкций с учетом
допустимости взаимных вложений (11).*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "stek.h"


using namespace std;


struct Operator
{
	string beginOperator;
	string endOperator;
};

vector<Operator> InitOperator()
{
	Operator structOperator;
	vector<Operator> opt;
	structOperator.beginOperator = "BEGIN";
	structOperator.endOperator = "END";
	opt.push_back(structOperator);

	structOperator.beginOperator = "BEGIN";
	structOperator.endOperator = "END;";
	opt.push_back(structOperator);

	structOperator.beginOperator = "BEGIN";
	structOperator.endOperator = "END.";
	opt.push_back(structOperator);

	structOperator.beginOperator = "REPEAT";
	structOperator.endOperator = "UNTIL";
	opt.push_back(structOperator);
	return opt;
}

void HandlingExceptions(ifstream & inputFile, char ch)
{
	if (ch == '/')
	{
		inputFile.get(ch);
		if (ch == '/')
		{
			while (ch != '\n')
			{
				inputFile.get(ch);
			}
		}
	}
	else if (ch == '{')
	{
		while (ch != '}')
		{
			inputFile.get(ch);
		}
	}
	else if (ch == '\'')
	{
		inputFile.get(ch);
		while (ch != '\'')
		{
			inputFile.get(ch);
		}
	}
}

string ReadWord(ifstream & inputFile, bool & isReadEof)
{
	string word = "";
	char ch;
	inputFile.get(ch);
	HandlingExceptions(inputFile, ch);
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
	string wordFromStack;
	while (!isReadEof)
	{
		string word = ReadWord(inputFile, isReadEof);
		for (int i = 0; i != opt.size(); i++)
		{
			if (CompareStrings(opt[i].beginOperator, word))
			{
				push(p, word);
				cout << word << endl;
				break;
			}
			else if (CompareStrings(opt[i].endOperator, word))
			{
				if (p != NULL)
				{
					wordFromStack = pop(p);
				}
				else
				{
					cout << "Validation FAILED!!!" << endl;
					return 1;
				}
			}

		}
	}
	if (p == NULL)
	{
		cout << "Validation PASSED!!!" << endl;
	}
	else
	{
		cout << "Validation FAILED!!!" << endl;
		return 1;
	}
	//push(p, "BEGIN");
	//pop(p);
	return 0;
}