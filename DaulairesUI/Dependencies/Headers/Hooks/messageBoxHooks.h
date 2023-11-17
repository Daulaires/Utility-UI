#pragma once


class messageBoxAHook
{
public:
	int hookedMessageBoxA(HWND, LPCSTR, LPCSTR, UINT);
	int hookedMessageBoxW(HWND, LPCWSTR, LPCWSTR, UINT);
	int hookedMessageBoxExA(HWND, LPCSTR, LPCSTR, UINT, WORD);
};