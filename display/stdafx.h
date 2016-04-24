#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

using namespace std;

class Display
{
private:
	bool lock;
	char* buffer;
	thread timer;

	template <typename Func> void locked(Func);
	void draw();
public:
	const int size = 64; // number of characters on the display

	void clear();
	void print(char*, int, int);

	Display();
	Display(unsigned int);
	~Display();
};