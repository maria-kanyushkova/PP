#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	cout << (to_string((int)lpParam) + "\n");
	ExitThread(0); // функция устанавливает код завершения потока в 0
}

int main(int argc, CHAR* argv[])
{
	int param = atoi(argv[1]);

	HANDLE* handles = new HANDLE[param];
	for (int i = 0; i < param; i++) {
		handles[i] = CreateThread(NULL, 0, &ThreadProc, LPVOID(i), CREATE_SUSPENDED, NULL);
	}

	for (int i = 0; i < param; i++) {
		ResumeThread(handles[i]);
	}

	WaitForMultipleObjects(param, handles, true, INFINITE);
	return 0;
}
