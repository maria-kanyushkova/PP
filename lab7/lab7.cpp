#include "ThreadNumberPrinter.h"
#include "Worker.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char** argv)
{
	int numberOfThreads = 16; // количество потоков

	IWorker* worker = new Worker();

	for (int i = 0; i < numberOfThreads; i++)
	{
		ITask* task = new ThreadNumberPrinter(i);
		Sleep(500); //or random sleep
		cout << worker->ExecuteTask(task) << endl;
	}

	delete worker;
}