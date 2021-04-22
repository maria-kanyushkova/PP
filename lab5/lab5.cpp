#include <iostream>
#include <mutex>
#include <string>
#include <tchar.h>
#include <vector>
#include <windows.h>

using namespace std;

class Thread
{
public:
	Thread(int threadNumber, int* workingVariable)
		: m_threadNumber(threadNumber)
		, m_workingVariable(workingVariable)
	{
	}

	void UpdateValues()
	{
		m_value = *m_workingVariable;
		int delta = rand() % 10 + 1; // random from [1;10]
		m_value += delta;
		*m_workingVariable = m_value;
	}

	void PrintValues() const
	{
		cout << to_string(m_threadNumber)
				+ " workingVariable = " + to_string(*m_workingVariable)
				+ " value = " + to_string(m_value) + "\n";
		if (*m_workingVariable != m_value)
		{
			cout << to_string(m_threadNumber) + " error: working variable != value\n";
		}
	}

private:
	int m_threadNumber;
	int* m_workingVariable;
	int m_value = 0;
};

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	auto thread = *static_cast<Thread*>(lpParam);
	thread.UpdateValues();
	thread.PrintValues();
	ExitThread(0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int x;
	cin >> x;
	if (argc != 2)
	{
		return 1;
	}
	int numberOfThreads = stoi(argv[1]);
	int workingVariable = 1;

	vector<Thread> threads;
	for (int i = 0; i < numberOfThreads; i++)
	{
		threads.emplace_back(i, &workingVariable);
	}

	HANDLE* handles = new HANDLE[numberOfThreads];
	for (int i = 0; i < numberOfThreads; i++)
	{
		handles[i] = CreateThread(NULL, 0, &ThreadProc, &threads[i], CREATE_SUSPENDED, NULL);
		ResumeThread(handles[i]);
	}
	WaitForMultipleObjects(numberOfThreads, handles, true, INFINITE);

	return 0;
}
