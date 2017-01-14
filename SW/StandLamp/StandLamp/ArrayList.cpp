/*
* Arduino Class for ArrayList
* Written: Obed Isai Rios
* Rewritten by SUF
*/


#include "Arduino.h"
#include "ArrayList.h"

ArrayList::ArrayList()
{
	this->size = 0;
}

ArrayList::~ArrayList(void)
{
	free(stringlist);
}

void ArrayList::Add(char* item)
{
	char **newlist;
	stringlist = (char**)realloc(stringlist, this->size * sizeof(char*));
	this->size++;
	stringlist[this->size] = item;
}

void ArrayList::Set(char* item, int index)
{
	stringlist[index] = item;
}

void ArrayList::Del(int index)
{
	this->size--;
	for (int i = index; i < this->size; i++)
	{
		stringlist[i] = stringlist[i + 1];
	}
	stringlist = (char**)realloc(stringlist, this->size * sizeof(char*));
}

void ArrayList::Clear()
{
	size = 0;
	free(stringlist);
}

char* ArrayList::operator[] (const int index)
{
	return stringlist[index];
}

int ArrayList::Count()
{
	return this->size;
}
