
#include "../Headers/Tools.h"

#include <locale>
#include <codecvt>
#include <Windows.h>
#include <tlhelp32.h>

auto Info::LaunchCmd() -> void
{
	string cmd;
	cout << "Enter command: ";
	getline(cin, cmd);
	cout << "Launching command: " << cmd << endl;
	system(std::string("c:\\windows\\system32\\cmd.exe /c " + cmd).c_str());
};

auto Info::ListAllProcIDS() -> LPCSTR
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return "Failed to get process IDs.";
	};

	cProcesses = cbNeeded / sizeof(DWORD);

	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			PrintProcessNameAndID(aProcesses[i]);
		}
	}
	return "Got process IDs.";
};

auto Info::PrintProcessNameAndID(DWORD processID) -> DWORD
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	// Get a handle to the process.

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	// Get the process name.

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	// save the process name and id
	auto processName = szProcessName;
	auto processId = processID;

	// if they aren't null return the process name and id
	if (processName != NULL && processId != NULL) {
		// 
	}
	else {
		cout << "Failed to get process name and ID." << endl;
	};

	// Release the handle to the process.
	CloseHandle(hProcess);
	return processId;
};

auto Info::JSONinfyDWORD(DWORD Str) -> string
{
	auto str_to_return = Str;

	// convert the process ID to a string 
	string convertedProcessId = std::to_string(str_to_return);

	return convertedProcessId;
};

bool Info::PrintModules(DWORD processID)
{
	HMODULE hMods[1024];
	HANDLE hProcess;
	DWORD cbNeeded;
	unsigned int i;

	// Print the process identifier.

	printf("\nProcess ID: %u\n", processID);

	// Get a handle to the process.

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
		return 1;

	// Get a list of all the modules in this process.

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.

			if (GetModuleFileNameEx(hProcess, hMods[i], szModName,
				sizeof(szModName) / sizeof(TCHAR)))
			{
				// Print the module name and handle value.

				_tprintf(TEXT("\t%s (0x%0p)\n"), szModName, hMods[i]);
			};
		};
	};

	// Release the handle to the process.

	CloseHandle(hProcess);

	return 0;
};

auto Info::ListAllProcModules() -> bool
{
	DWORD aProcesses[1024];
	DWORD cbNeeded;
	DWORD cProcesses;
	unsigned int i;

	// Get the list of process identifiers.

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return 1;

	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the names of the modules for each process.

	for (i = 0; i < cProcesses; i++)
	{
		PrintModules(aProcesses[i]);
	};

	return 0;
};

auto Info::assignName() -> string
{
	// generate a random string
	const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	string randomString = "";

	for (int i = 0; i < 10; ++i) {
		randomString += alphanum[rand() % (sizeof(alphanum) - 1)];
	};

	return randomString;
};

auto Info::getSystemName() -> string
{
	auto SystemName = "none";
	char buffer[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(buffer);
	// convert char array to std::string
	if (GetComputerNameA(buffer, &size))
	{
		SystemName = buffer;
	}
	else
	{
		SystemName = "Failed to get system name.";
	};

	return string(SystemName);
};

string Info::getCurrentDirectory() {

	char buffer[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, buffer);
	return string(buffer);
};

string Info::getSystemType() {
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);

	switch (siSysInfo.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64:
		SystemType = "64-bit";
		break;
	case PROCESSOR_ARCHITECTURE_ARM:
		SystemType = "ARM";
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		SystemType = "Intel Itanium-based";
		break;
	case PROCESSOR_ARCHITECTURE_INTEL:
		SystemType = "32-bit";
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		SystemType = "Unknown architecture";
		break;
	default:
		SystemType = "Unknown architecture";
		break;
	}

	return string(SystemType);
};

string Info::getSystemArchitecture() {
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);

	switch (siSysInfo.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64:
		SystemArchitecture = "x64";
		break;
	case PROCESSOR_ARCHITECTURE_ARM:
		SystemArchitecture = "ARM";
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		SystemArchitecture = "Intel Itanium-based";
	case PROCESSOR_ARCHITECTURE_INTEL:
		SystemArchitecture = "x86";
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		SystemArchitecture = "Unknown architecture";
		break;
	default:
		SystemArchitecture = "Unknown architecture";
		break;
	};

	return string(SystemArchitecture);
};

LPCSTR Info::getDrivers() {
	constexpr auto ARRAY_SIZE = 1024;
	LPVOID drivers[ARRAY_SIZE];
	DWORD cbNeeded;
	int cDrivers, i;

	if (EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers))
	{
		TCHAR szDriver[ARRAY_SIZE];

		cDrivers = cbNeeded / sizeof(drivers[0]);

		_tprintf(TEXT("There are %d drivers:\n"), cDrivers);
		for (i = 0; i < cDrivers; i++)
		{
			if (GetDeviceDriverBaseName(drivers[i], szDriver, sizeof(szDriver) / sizeof(szDriver[0])))
			{
				_tprintf(TEXT("%d: %s\n"), i + 1, szDriver);
			}
		}
	}
	else
	{
		_tprintf(TEXT("EnumDeviceDrivers failed; array size needed is %zd\n"), cbNeeded / sizeof(LPVOID));
		return "Failed to get drivers.";
	}
	return "Got drivers.";
};

HANDLE Info::getProcByName(const wchar_t* targetProcessName)
{
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnapshot == INVALID_HANDLE_VALUE)
	{
		cerr << "Error creating process snapshot." << endl;
		return nullptr;
	}

	PROCESSENTRY32 pe32{};
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnapshot, &pe32))
	{
		do
		{
			if (_wcsicmp(pe32.szExeFile, targetProcessName) == 0)
			{
				// Found the process with the specified name
				HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
				if (hProcess == nullptr)
				{
					cerr << "Error opening process." << endl;
				}
				else
				{
					// Print information about modules
					if (!PrintProcessNameAndID(pe32.th32ProcessID))
					{
						cerr << "Error printing modules." << endl;
						CloseHandle(hProcess);
						CloseHandle(hProcessSnapshot);
						return nullptr;
					}

					CloseHandle(hProcessSnapshot);
					return hProcess;
				}
			}

		} while (Process32Next(hProcessSnapshot, &pe32));
	}

	cerr << "Process not found." << endl;
	CloseHandle(hProcessSnapshot);
	return nullptr;
};