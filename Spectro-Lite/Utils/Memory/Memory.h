#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include "../../SysCalls/syscalls_mem.h"

class Memory
{
private:
	char TargetClass[32]  = "grcWindow";	
	
	
public:
	DWORD PID;
	HANDLE pHandle;
	uint64_t BaseAddress;


	bool Init();
	uintptr_t GetModuleBase(const std::string module);

	template <typename T>
	constexpr const T SysRead(const uintptr_t& address) const noexcept
	{
		T value = { };
		if (NtReadVirtualMemory(pHandle, reinterpret_cast<PVOID>(address), &value, sizeof(T), NULL) == 0) {
			return value;
		}
		return T{}; // Return default value of T if read fails
	}

	template <typename T>
	constexpr void SysWrite(const uintptr_t& address, const T& value) const noexcept
	{
		SIZE_T bytesWritten = 0;
		NtWriteVirtualMemory(
			pHandle,
			reinterpret_cast<PVOID>(address),
			const_cast<T*>(&value),
			sizeof(T),
			&bytesWritten
		);
	}


	
	/*template <typename T>
	constexpr void Write(const uintptr_t& address, const T& value) const noexcept
	{
		WriteProcessMemory(pHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
	}*/
	bool ReadString(uintptr_t address, LPVOID buffer, SIZE_T size) const noexcept
	{
		SIZE_T size_read;
		return !!::ReadProcessMemory(pHandle, LPCVOID(address), buffer, size, &size_read) && size_read > 0;
	}
	
};


//template <typename T>
//constexpr const T Read(const uintptr_t& address) const noexcept
//{
//	T value = { };
//	ReadProcessMemory(pHandle, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
//	return value;
//}

extern Memory m;