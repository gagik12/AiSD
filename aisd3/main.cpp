#include "stdafx.h"
#include <vector>

struct Tree
{
	char letter;
	int level;
	Tree *fath; //отец
	std::vector<Tree> *sons; // сыновья 
};



int main()
{

}
