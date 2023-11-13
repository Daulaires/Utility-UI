#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996) 
#pragma warning(disable:4313)
#pragma warning(disable:4477)

using namespace std;

#include <WinSock2.h>
#include <Windows.h>
#include <Psapi.h>
#include <filesystem>
#include <iostream> 
#include <cstdio>     
#include <fstream>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <map>
#include <chrono>
#include <thread>
#include <nlohmann/json.hpp>
#include <time.h>
#include <stdlib.h> 
using json = nlohmann::json;

#include "Utils.h"
#include "Info.h"
#include "Utils.h"
#include "Client.h"
#include "Main.h"