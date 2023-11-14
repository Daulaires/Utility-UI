#pragma once

class Memory {
public:
	auto ReadMemory(DWORD address, DWORD procID) -> int;
	auto SilentMoveFile(string name, string path, string& newpath) -> void;
	auto WriteToFile(string, string, string) -> bool;
	auto ReadFile(string, string) -> string;
};