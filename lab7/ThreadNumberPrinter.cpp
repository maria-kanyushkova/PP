#include "ThreadNumberPrinter.h"
#include <iostream>
#include <string>

using namespace std;

ThreadNumberPrinter::ThreadNumberPrinter(int number)
	: m_number(number)
{
}

void ThreadNumberPrinter::Execute()
{
	cout << "thread number " + to_string(m_number) + " is working\n";
}
