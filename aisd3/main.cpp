
#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <queue>

const int DL = 20;          // ìàêñèìàëüíàÿ äëèíà

using namespace std;

struct Tree {
	char name[DL];
	int urov;
	Tree *fath;         // îòåö â èñõîäíîì äåðåâå
	Tree *left;
	Tree *right;
};

struct file {
	string path[DL];
	vector<string> allPath;
	string pathFac[DL];
	vector<string> allPathFac;
	int count = 0;
};

bool FindSubstring(string str, string sub) {
	int count = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == sub[count])
			count++;
		else count = 0;
		if (count == sub.size())
			return true;
	}
	return false;
}

void ReadFromFile(string nameFile, Tree **r) {
	ifstream f(nameFile);
	if (!f.is_open()) {
		cout << "Error open file" << endl;
		system("pause");
		exit(1);
	}
	char buf[DL];
	int i;
	int k;
	int m;
	int len;
	Tree *p, *q, *t;       // *root = 0 
	m = 0;                 // óðîâåíü âåðøèíû
	t = 0;
	while (!f.eof())
	{
		f.getline(buf, DL);
		len = strlen(buf);
		if (len == 0)
			break;            // åñëè êîíåö ôàéëà â ñëåäóþùåé ñòðîêå
		k = 0;
		while (buf[k] == '.')
			k++;     // k-óðîâåíü âåðøèíû
		p = new Tree;
		strncpy(p->name, &buf[k], len - k + 1);  // 0-(k-1) - òî÷êè, (k-1)-(len-1) - èìÿ, \0 - êîíåö ñòðîêè
		buf[0] = '\0';                  // åñëè êîíåö ôàéëà â ñëåäóþùåé ñòðîêå
		p->urov = k;
		p->left = 0;
		p->right = 0;
		if (k == 0)                    // êîðåíü
		{
			*r = p;
			t = *r;
			continue;
		}
		if (k > m)                  // ïåðåõîä íà ñëåäóþùèé óðîâåíü
		{
			t->left = p;
			p->fath = t;
		}
		else if (k == m)            // òîò æå óðîâåíü
		{
			t->right = p;
			p->fath = t->fath;  // îòåö òîò æå
		}
		else        // ïîäúåì ïî äåðåâó íà m-k óðîâíåé
		{
			q = t;
			for (i = 0; i < m - k; i++)
				q = q->fath;
			// q - ïðåäûäóùàÿ âåðøèíà òîãî æå óðîâíÿ
			p->fath = q->fath;   // îòåö òîò æå, ÷òî ó áðàòà
			q->right = p;
		}
		m = k;      // òåêóùèé óðîâåíü
		t = p;      // òåêóùàÿ âåðøèíà
	}
	f.close();
}

void OutputToConsole(Tree *p, file &file) {
	int i = 1;
	bool flag = file.path[i] == "";
	string bufString;
	vector<string> bufArray;
	while (!flag) {
		cout << file.path[i] + "/";
		if (file.path[i][0] == 'k' && (isdigit(file.path[i][1])))
			break;
		else {
			bufString += file.path[i] + "/";
		}
		flag = file.path[i] == "";
		++i;
	}

	if (file.count > 0) {
		bool isFind = false;
		for (int i = 0; i < file.allPath.size(); ++i) {
			if (file.allPath[i] == bufString) {
				isFind = true;
				break;
			}
		}
		if (!isFind) {
			file.allPath.push_back(bufString);
			file.allPathFac.push_back(file.pathFac[1]);
		}
		else {
			if (!FindSubstring(file.allPathFac.back(), file.pathFac[1])) {
				file.allPathFac.back() += ", " + file.pathFac[1];
			}
		}
	}
	else {
		file.allPath.push_back(bufString);
		file.allPathFac.push_back(file.pathFac[1]);
	}
	file.count += 1;
	cout << "-- " + file.pathFac[1] << endl;
}

void SearchByFaculties(Tree *faculties, file &file, Tree *audience) {
	if (faculties)
	{
		if (faculties->urov == 1) {
			file.pathFac[faculties->urov] = faculties->name;
		}
		if (((faculties->name)[0] == 'k') && (isdigit((faculties->name)[1]))) {
			if (string(audience->name) == string(faculties->name)) {
				OutputToConsole(faculties, file);
			}
		}
		SearchByFaculties(faculties->left, file, audience);
		SearchByFaculties(faculties->right, file, audience);
	}
}

void ComputerMapping(Tree *audience, file &file, Tree *faculties)
{
	if (audience)
	{
		file.path[audience->urov] = audience->name;
		if (((audience->name)[0] == 'k') && (isdigit((audience->name)[1]))) {
			SearchByFaculties(faculties, file, audience);
		}
		ComputerMapping(audience->left, file, faculties);
		ComputerMapping(audience->right, file, faculties);
	}
}

int main() {
	file file;
	Tree *treeOne = 0;
	Tree *treeTwo = 0;
	string nameFileComputers;
	string nameFileAudience;
	setlocale(LC_ALL, "rus");
	cout << "Ââåäèòå èìÿ ôàéëà, ñîäåðæàùåãî ñïèñîê ôàêóëüòåòîâ: ";
	//cin >> nameFileComputers;
	nameFileComputers = "faculties.txt";
	ReadFromFile(nameFileComputers, &treeOne);
	cout << "Ââåäèòå èìÿ ôàéëà, ñîäåðæàùåãî ñïèñîê àóäèòîðèè: ";
	//cin >> nameFileAudience;
	cout << endl;
	nameFileAudience = "room.txt";
	ReadFromFile(nameFileAudience, &treeTwo);
	ComputerMapping(treeTwo, file, treeOne);
	cout << "\n------ Âûâîä àóäèòîðèé ñ íåñêîëüêèìè ôàêóëüòåòàìè ------" << endl;
	for (int i = 0; i < file.allPath.size(); ++i) {
		if (FindSubstring(file.allPathFac[i], ",")) {
			cout << file.allPath[i] << " ";
			cout << file.allPathFac[i] << endl;
		}
	}
	system("pause");
	delete treeOne;
	delete treeTwo;
	return 0;
}