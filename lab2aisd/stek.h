#pragma once
#include <string>
#include <fstream>
#include <iostream>

struct Stek
{
	std::string value;
	struct Stek *next;
};

void push(Stek* &NEXT, const std::string & VALUE);
std::string pop(Stek* &NEXT);