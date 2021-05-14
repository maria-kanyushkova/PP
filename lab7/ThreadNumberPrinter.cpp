#include "ThreadNumberPrinter.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

ThreadNumberPrinter::ThreadNumberPrinter(int number)
	: m_number(number)
{
}

void ThreadNumberPrinter::Execute()
{
	Sleep(1000);
	cout << "thread number " + to_string(m_number) + " is working\n";
}
