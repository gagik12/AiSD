#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "stek.h"
#include <algorithm>

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

void HandlingExceptions(ifstream & inputFile, char & ch, int & position)
{
	if (ch == '/')
	{
		//inputFile.get(ch);
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

string ReadWord(ifstream & inputFile, bool & isReadEof, int & position)
{
	string word = "";
	char ch;
	inputFile.get(ch);
	HandlingExceptions(inputFile, ch, position);
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
	transform(word.begin(), word.end(), word.begin(), toupper);
	return word;
}

int CompareStrings(std::string const& a, std::string const& b)
{
	return !(strcmp(a.c_str(), b.c_str()));
}

bool IsEmpty(ifstream& file)
{
	return file.peek() == std::ifstream::traits_type::eof();
}


ifstream OpenFile(std::string const& fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "File not open!!!";
		exit(1);
	}
	if (IsEmpty(file))
	{
		cout << "Empty file!!!";
		exit(1);
	}
	return file;
}

void PrintResult(int position)
{
	cout << "Validation FAILED!!!" << endl;
	cout << "Error: " << position << " line";
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";
		return 1;
	}
	ifstream inputFile = OpenFile(argv[1]);
	vector<Operator> opt = InitOperator();
	Stek *stek = NULL;
	bool isReadEof = false;
	string wordFromStack;
	int position = 0;
	while (!isReadEof)
	{
		string word = ReadWord(inputFile, isReadEof, position);		
		for (int i = 0; i != opt.size(); i++)
		{
			if (CompareStrings(opt[i].beginOperator, word))
			{
				Push(stek, word);
				++position;
				break;
			}
			else if (CompareStrings(opt[i].endOperator, word))
			{
				if (stek != NULL)
				{
					wordFromStack = Pop(stek);
					++position;
					if (!(CompareStrings(wordFromStack, opt[i].beginOperator)))
					{
						PrintResult(position);
						return 1;
					}
				}
				else
				{
					PrintResult(position);
					return 1;
				}
			}

		}
	}
	if (stek == NULL)
	{
		cout << "Validation PASSED!!!" << endl;
	}
	else
	{
		PrintResult(position);
		return 1;
	}
	return 0;
}
