#pragma once

class Memory {
public:
	auto SilentMoveFile(string name, string path, string& newpath) -> void;
	auto SilentWriteToFile(string, string, string) -> bool;
	auto SilentReadFile(string, string) -> bool;
};