
#include "stdafx.h"   
#include <fstream>
#include <iostream>
#include <string>
const int DL = 20;          // максимальная длина

using namespace std;

struct Tree
{
	string name;
	int urov;
	string vertex;   // Вершина И, ИЛИ
	Tree *fath;         // отец в исходном дереве
	Tree *left;
	Tree *right;
};

int read_from_file(ifstream & F, Tree **r);  // чтение из файла, формирование дерева
void back_from_bin(Tree *p);            // выдача исходное дерева из бинарного 

int main(int argc, char* argv[])
{
	Tree *root = 0;
	std::ifstream file;
	setlocale(LC_ALL, "rus");
	if (argc == 2)
	{
		printf("\nNumber parameters is wrong");
		getchar();
		return -1;
	}
	file.open("tree.txt");
	if (!file.is_open())
	{
		printf("\nCan not open file %s", argv[1]);
		getchar();
		return -1;
	}
	read_from_file(file, &root);
	printf("Вывод из бинарного дерева сильно ветвящегося\n");
	back_from_bin(root);
}

string ReadName(char buf[DL], int &k, bool &isVertex)
{
	string name = "";
	while (buf[k] != '\0')
	{
		if (buf[k] != ' ')
		{
			name += buf[k];
		}
		else
		{
			isVertex = true;
			break;
		}
		k++;
	}
	return name;
}

string ReadVertex(char buf[DL], int k, bool isVertex)
{
	string vertex;
	if (isVertex)
	{
		k++;
		while (buf[k] != '\0')
		{
			vertex += buf[k];
			k++;
		}
	}
	return vertex;
}

int read_from_file(ifstream & F, Tree **r)
{
	char buf[DL];
	int i, k, m, len;
	Tree *p, *q, *t;       // *root = 0 
	m = 0;                 // уровень вершины
	t = 0;

	bool isVertex;

	while (!F.eof())
	{
		F.getline(buf, DL);

		string vertex = "";
		len = strlen(buf);
		if (len == 0) break;            // если конец файла в следующей строке
		k = 0;
		while (buf[k] == '.') k++;     // k-уровень вершины
		p = new Tree;

		isVertex = false;
		int l = k;
		p->name = ReadName(buf, l, isVertex);
		p->vertex = ReadVertex(buf, l, isVertex);

		buf[0] = '\0';                  // если конец файла в следующей строке
		p->urov = k;
		p->left = 0;
		p->right = 0;
		if (k == 0)                    // корень
		{
			*r = p;
			t = *r;
			continue;
		}
		if (k > m)                  // переход на следующий уровень
		{
			t->left = p;
			p->fath = t;
		}
		else if (k == m)            // тот же уровень
		{
			t->right = p;
			p->fath = t->fath;  // отец тот же
		}
		else        // подъем по дереву на m-k уровней
		{
			q = t;
			for (i = 0; i < m - k; i++) q = q->fath;
			// q - предыдущая вершина того же уровня
			p->fath = q->fath;   // отец тот же, что у брата
			q->right = p;
		}
		m = k;      // текущий уровень
		t = p;      // текущая вершина
	}
	
	return 0;
}

void back_from_bin(Tree *p)
{
	int i;
	string urov;
	string name = "";
	if (p)
	{
		for (i = 0; i < p->urov; i++) urov += '.';
		cout << urov;
		cout << p->name << " ";
		cout << p->vertex << endl;
		
		back_from_bin(p->left);
		back_from_bin(p->right);
	}

}

/*void print_right_bin(Tree *p, int level)
{
	if (p)
	{
		print_right_bin(p->left, level + 1);
		for (int i = 0; i < level; i++)
			printf("%c", '.');
		printf("%s\n", p->name);
		print_right_bin(p->right, level + 1);
	}
}

void print_up_bin(Tree *p, int level)
{
	if (p)
	{
		print_up_bin(p->left, level + 1);
		print_up_bin(p->right, level + 1);
		for (int i = 0; i < level; i++)
			printf("%c", '.');
		printf("%s\n", p->name);
	}
}

void print_down_bin(Tree *p, int level)
{
	if (p)
	{
		for (int i = 0; i < level; i++)
			printf("%c", '.');
		printf("%s\n", p->name);
		print_down_bin(p->left, level + 1);
		print_down_bin(p->right, level + 1);
	}
}
*/
