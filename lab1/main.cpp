/*            ВЫПОЛНИЛ ДОЛГАНОВ ВАДИМ НИКОЛАЕВИЧ
                       ВАРИАНТ 21
Строки текстового  файла  содержат  фамилии  студентов.
Определить   порядковый   номер   байта,  начиная  с  которого
располагается первая  по  алфавиту  фамилия.  Заменить  данную
фамилию  в исходном файле символами '*',  не переписывая этого
файла (8).*/

#include "stdafx.h"

static const char REPLACEMENT = '*';

struct Surname
{
	std::string word;
	long startBytes;
	int amountChar;
};

FILE* OpenFile(std::string const& fileName) // Открыть файл
{
	FILE* file;
	fopen_s(&file, fileName.c_str(), "r+b");
	return file;
}

int CompareStrings(std::string const& a, std::string const& b) // Сравнение строк
{
	return (strcmp(a.c_str(), b.c_str()));
}

std::string ReadSurname(FILE* const& file, long & positionCurr) // чтение фамилия из файла
{
	std::string str = "";
	char ch;
	while (((ch = getc(file)) != '\n') && (ch != '\r') &&  (ch != EOF))
	{
		str += ch;
		positionCurr = ftell(file);
	}
	return str;
}

void SaveInStructure(Surname & surname, std::string const& str1, long const& position)
{
	surname.word = str1;
	surname.amountChar = str1.length();
	surname.startBytes = position - str1.length();
}

std::string GetStringReplacement(std::string const& surname)
{
	std::string buf = "";
	for (int i = 0; i != surname.length(); i++)	 
	{
		buf += REPLACEMENT;
	}
	return buf;

}

bool IsReplaced(std::string const& surname)
{
	 bool isReplaced = false;
	 std::string replacement = GetStringReplacement(surname);
	 if (CompareStrings(surname, replacement) == 0)
	 {	
		 isReplaced = true;	 
		 
	 }
	 return isReplaced;
}

Surname SearchSurname(FILE* & file)
{
	long positionCurr;
	std::string str1 = ReadSurname(file, positionCurr);
	std::string str2 = "";
	while (IsReplaced(str1))
	{
		str1 = ReadSurname(file, positionCurr);
	}
	long positionMaxSurname = positionCurr;
	while (!feof(file))
	{
		str2 = ReadSurname(file, positionCurr);
		if (!IsReplaced(str2) && (CompareStrings(str1, str2) > 0) && (str2 != "") || ((str1 == "") && (str2 != "")))
		{
			str1 = str2;
			positionMaxSurname = positionCurr;
		}
	}
	Surname surname;
	SaveInStructure(surname, str1, positionMaxSurname);
	return surname;
}



void ReplaceWord(FILE* & file, Surname const& surname) // Заменить слова
{
	std::string replacement = GetStringReplacement(surname.word);
	fseek(file, surname.startBytes, SEEK_SET);
	fwrite(replacement.c_str(), surname.amountChar, 1, file);
}

void OutputDataSurname(Surname const& surname)
{
	std::cout << "Word: " << surname.word.c_str() << std::endl;
	std::cout << "startBytes: " << surname.startBytes << std::endl;
	std::cout << "amountChar: " << surname.amountChar << std::endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Enter file name: ";
	std::string fileName;
	std::getline(std::cin, fileName);

	if (fileName.length() == 0)
	{
		std::cout << "Empty file name: " << std::endl;
		return 1;
	}
	FILE * file = OpenFile(fileName);
	if (file != NULL)
	{
		Surname surname = SearchSurname(file);
		if (surname.amountChar > 1)
		{
			ReplaceWord(file, surname);
			OutputDataSurname(surname);
		}
		fclose(file);
	}
	else
	{
		std::cout << "An error with the file!!!" << std::endl;
		return 1;
	}
	system("pause");
	return 0;
}