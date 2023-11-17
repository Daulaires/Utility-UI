#pragma once

class Memory {
public:
	void InstallService(const wchar_t*, const wchar_t*, const wchar_t*);
	auto ReadMemory(DWORD address, DWORD procID) -> int;
	auto SilentMoveFile(string name, string path, string& newpath) -> void;
	auto WriteToFile(string, string, string) -> bool;
	auto ReadFile(string, string) -> string;
};