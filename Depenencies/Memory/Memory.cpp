#include "../Headers/Tools.h"

auto Memory::SilentMoveFile(string name, string path, string& newpath) -> void {
	freopen("nul", "w", stdout);
	system(("move " + name + " " + newpath).c_str());
	freopen("CON", "w", stdout);
};