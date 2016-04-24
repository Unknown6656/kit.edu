#include "stdafx.h"

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;


Display::Display()
	: Display(200)
{
}

Display::Display(unsigned int ival)
{
	buffer = new char[size];
	lock = false;

	function<void(void)> func(this->draw);

	timer = thread([func, ival]()
	{
		while (true)
		{
			func();

			sleep_for(milliseconds(ival));
		}
	});
	timer.detach();
}

Display::~Display(void)
{
	timer.~thread();
}

template <typename Func>
void Display::locked(Func lambda)
{
	while (lock)
		_sleep(0);

	lock = true;

	lambda();

	lock = false;
}

void Display::clear()
{
	locked([&]()
	{
		for (int i = 0; i < size; i++)
			buffer[i] = '\0';
	});
}

void Display::print(char* str, int len, int offs)
{
	locked([&]()
	{
		for (int i = 0; i < len; i++)
			if (i >= size - offs)
				return;
			else
				buffer[i + offs] = str[offs];
	});
}

void Display::draw()
{
	locked([&]()
	{
		// dump the locked buffer into the display

		// I dunno, do I ?
	});
}