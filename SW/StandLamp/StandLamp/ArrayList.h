#pragma once

#include "Arduino.h"

class ArrayList {
public:
	ArrayList(); //ArrayStringList(void);
	~ArrayList(void);
	void Add(char* item);
	void Set(char* item, int index);
	void Del(int index);
	void Clear();
	char* operator[] (const int index);
	int Count();
private:
	char** stringlist;
	int size;
};