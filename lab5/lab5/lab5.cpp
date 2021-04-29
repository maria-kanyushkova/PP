#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

CRITICAL_SECTION CriticalSection;

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	int* workingVariable = (int*)lpParam;
	int variable = *workingVariable;
	srand(time(0));

	for (int i = 0; i < 10000000; i++)
	{
		int j = *workingVariable;
		int k = variable;
		int a = rand() % 10 + 1;
		*workingVariable = j + a;
		variable = k + a;
	}

	cout << to_string(variable) + " " + to_string(*workingVariable) + "\n";

	ExitThread(0);
}

int main(int argc)
{
	int working_variable = 0;
	HANDLE hProcess = GetCurrentProcess();
	unsigned int nMaxProcessorMask = (1 << 2) - 1;
	SetProcessAffinityMask(hProcess, nMaxProcessorMask);

	InitializeCriticalSection(&CriticalSection);

	HANDLE* handles = new HANDLE[2];

	for (int i = 0; i < 2; i++)
	{
		handles[i] = CreateThread(NULL, i, &ThreadProc, &working_variable, CREATE_SUSPENDED, NULL);
	}

	for (int i = 0; i < 2; i++)
	{
		ResumeThread(handles[i]);
	}

	WaitForMultipleObjects(2, handles, true, INFINITE);

	cout << working_variable << endl;

	DeleteCriticalSection(&CriticalSection);

	return 0;
}
