#include "FibonachiHeap.h"

#include <crtdbg.h>

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

int StartProcess()
{
	char command;
	int key;
	char buf[BUF_SIZE] = { 0 };
	Heap_t* heap = InitHeap();
	Node_t* heapMin = NULL;
	while (fgets(buf, BUF_SIZE, stdin))
	{
		sscanf(buf, "%c %d", &command, &key);
		switch (command)
		{
		case 'a':
			AddElem(heap, key);
			break;
		case 'e':
			heapMin = ExtractMin(heap);
			printf("MIN: %d\n", heapMin->key);
			break;
		default:
			DeleteHeap(heap);
			return -1;
		}
	}
	DeleteHeap(heap);
	return 0;
}

void MemoryLeaks(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}

int main(void)
{
	if (StartProcess())
	{
		MemoryLeaks();
		return -1;
	}
	MemoryLeaks();
	return 0;
}