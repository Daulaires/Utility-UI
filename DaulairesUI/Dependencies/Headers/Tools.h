#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996) 

using namespace std;

#include <WinSock2.h>
#include <filesystem>
#include <Windows.h>
#include <Psapi.h>
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
#include <sstream>
#include <unordered_map>

using json = nlohmann::json;
#include "Utils.h"
#include "Info.h"
#include "Utils.h"
#include "Client.h"
#include "Main.h"
#include "Memory.h"
#include "Window.h"
#include "./Hooks/messageBoxHooks.h"