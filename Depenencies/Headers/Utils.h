#pragma once

#include "Tools.h"

class Utils
{
public:
	auto Split(string, string) -> vector<string>;
	auto DisplayText(string) -> void;
	auto WaitForInput() -> string;
	auto GetInput(string) -> string;
	auto WriteFile(string name, string path, string text) -> void;
	auto GetSystemType() -> string;
	auto MoveExe(string, string, string) -> void;
};