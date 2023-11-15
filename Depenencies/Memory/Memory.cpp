#include "../Headers/Tools.h"

void Memory::InstallService(const wchar_t* name, const wchar_t* description)
{
	SC_HANDLE schSCManager, schService;
	wchar_t szPath[MAX_PATH];

	if (GetModuleFileName(NULL, szPath, MAX_PATH) == 0) {
		// Handle error
		return;
	}

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (schSCManager) {
		schService = CreateService(
			schSCManager,
			name,
			description,
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			szPath,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		);

		if (schService) {
			// Start the service
			StartService(schService, 0, NULL);

			// Close the service handle
			CloseServiceHandle(schService);
		}
		else {
			// Handle error
		}

		// Close the service control manager handle
		CloseServiceHandle(schSCManager);
	}
	else {
		// Handle error
	}
};

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

auto Memory::WriteToFile(string name, string path, string data) -> bool
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

auto Memory::ReadFile(string name, string path) -> string
{
	ifstream file;
	stringstream content;

	file.open(path + "\\" + name);

	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			content << line << endl;
		}
		file.close();
		return content.str();
	}
	else
	{
		cout << "Unable to open file.";
		return ""; // Return an empty string to indicate failure.
	}
};


