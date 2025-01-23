#pragma once
#include <Windows.h>
#include <vector>

class CArduino
{
private:
	HANDLE handle;
	LPCSTR port;

public:
	CArduino(LPCSTR comPort) : port(comPort) {}
	~CArduino()
	{
		if (this->handle)
			CloseHandle(this->handle);
	}

	bool ConnectToPort();
	bool SendCmd(const std::vector<char>& params);
};
