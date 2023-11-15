#pragma once


class messageBoxAHook
{
public:
	int hookedMessageBoxA(HWND, LPCSTR, LPCSTR, UINT);
};