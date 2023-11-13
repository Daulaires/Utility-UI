#include "../Headers/Tools.h"

auto Memory::ReadMemory(DWORD address, DWORD procID) -> int
{
	// Read memory
	HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, procID);
	int value = 0;

	// Use uintptr_t for pointer arithmetic
	uintptr_t addressToRead = static_cast<uintptr_t>(address);

	// Use correct pointer type
	ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(addressToRead), &value, sizeof(value), 0);

	CloseHandle(hProcess);
	return value;
}


auto Memory::SilentMoveFile(string name, string path, string& newpath) -> void {
	freopen("nul", "w", stdout);
	system(("move " + name + " " + newpath).c_str());
	freopen("CON", "w", stdout);
};

auto Memory::SilentWriteToFile(string name, string path, string data) -> bool
{
	ofstream file;
	file.open(path + "\\" + name);

	if (file.is_open())
	{
		file << data;
		file.close();
		return true;
	}
	else
	{
		cout << "Unable to open file.";
		return false;
	};

	file.close();
	return true;
};

auto Memory::SilentReadFile(string name, string path) -> bool
{
	ifstream file;

	file.open(path + "\\" + name);

	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			cout << line << endl;
		};
		file.close();
		return true;
	}
	else
	{
		cout << "Unable to open file.";
		return false;
	};

	file.close();
	return true;
};


