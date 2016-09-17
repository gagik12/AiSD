#pragma once
#include <string>
#include <fstream>
#include <iostream>

struct stek
{
	std::string value;
	struct stek *next;
};

void push(stek* &NEXT, const std::string & VALUE);
std::string pop(stek* &NEXT);