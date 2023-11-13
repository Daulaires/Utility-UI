

#include "Tools.h"


using namespace std;

class Info {

public:
	string IP = "Unknown";
	string SystemType = "Unknown";
	string SystemArchitecture = "Unknown";
public:
	auto isWindows() -> bool;
public:
	auto LaunchCmd() -> void;
	auto ListAllProcIDS() -> LPCSTR;
	auto PrintProcessNameAndID(DWORD) -> void;
	auto PrintModules(DWORD) -> bool;
	auto ListAllProcModules() -> bool;
public:
	auto assignName() -> string;
	auto getSystemInfo() -> string;
	auto getSystemName() -> string;
	auto getCurrentDirectory() -> string;
	auto getSystemType() -> string;
	auto getSystemArchitecture() -> string;
	auto getDrivers() -> LPCSTR;
};