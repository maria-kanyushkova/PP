#include "Bitmap.h"
#include "BlurTask.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include "time.h"
#include "ThreadsPool.h"

using namespace std;

enum class ExecuteMode
{
	CreateNewThread,
	UseThreadsPool
};

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	struct Params* params = (struct Params*)lpParam;
	BlurTask task(2, params);
	task.Execute();
	ExitThread(0);
}

void RunWithCreatingNewThreads(vector<Params> blurParams)
{
	// создание потоков
	HANDLE* handles = new HANDLE[blurParams.size()];
	for (size_t i = 0; i < blurParams.size(); i++)
	{
		handles[i] = CreateThread(NULL, i, &ThreadProc, &blurParams[i], CREATE_SUSPENDED, NULL);
	}

	// запуск потоков
	for (size_t i = 0; i < blurParams.size(); i++)
	{
		ResumeThread(handles[i]);
	}

	// ожидание окончания работы потоков
	WaitForMultipleObjects(blurParams.size(), handles, true, INFINITE);
}

void RunWithUsingThreadsPool(vector<Params> blurParams, int threadsPoolCount)
{
	ThreadsPool pool(threadsPoolCount);
	pool.Blur(blurParams);
}

vector<Params> GetBlurParams(Bitmap* in, int blocksCount)
{
	int partHeight = in->GetHeight() / blocksCount;
	int heightRemaining = in->GetHeight() % blocksCount;

	vector<Params> arrayParams;

	for (int i = 0; i < blocksCount; i++)
	{
		Params params;
		params.in = in;
		params.startWidth = 0;
		params.endWidth = in->GetWidth();
		params.startHeight = partHeight * i;
		params.endHeight = partHeight * (i + 1) + ((i == blocksCount - 1) ? heightRemaining : 0);

		arrayParams.push_back(params);
	}
	return arrayParams;
}

ExecuteMode StringToExecuteMode(string const& str)
{
	if (str == "newThread")
	{
		return ExecuteMode::CreateNewThread;
	}
	if (str == "pool")
	{
		return ExecuteMode::UseThreadsPool;
	}
	throw runtime_error("Cannot convert string \"" + str + "\" to execute mode");
}

void RunThreads(vector<Params> const& blurParams, ExecuteMode executeMode, int threadsPoolCount)
{
	switch (executeMode)
	{
	case ExecuteMode::CreateNewThread:
		RunWithCreatingNewThreads(blurParams);
		break;
	case ExecuteMode::UseThreadsPool:
		RunWithUsingThreadsPool(blurParams, threadsPoolCount);
		break;
	default:
		break;
	}
}

int main(int argc, const char** argv)
{
	unsigned int start = clock();

	Bitmap bmp{ "or/b.bmp" };

	auto blurParams = GetBlurParams(&bmp, 5); // количество блоков
	RunThreads(blurParams, StringToExecuteMode("newThread"), 0); //newThread или pool | количество потоков в пуле (0)

	bmp.Save("bl/img.bmp");

	unsigned int end = clock();
	unsigned int duration = end - start;
	cout << duration << endl;

	return 0;
}
