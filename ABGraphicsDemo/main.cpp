#include "pch.h"

#include "Sample.h"
#ifdef _DEBUG
#include "vld.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	int result = 0;
	{
		entryPoint::Sample sample(hInstance, 1920, 1080, L"TestApp");

		if (!sample.Init())
		{
			return 0;
		}
		result = sample.Run();
	}

	_CrtDumpMemoryLeaks();

	return result;
}
#endif
