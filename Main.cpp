#include "Depenencies/Headers/Tools.h"

auto Main::Windows() -> bool
{
    Info info;
    Utils utils;
    Memory memory;
    std::map<std::string, std::function<void()>> commands;

    utils.DisplayText(info.getCurrentDirectory());
    utils.DisplayText(info.getSystemArchitecture());
    utils.DisplayText(info.getSystemType());
    utils.DisplayText("Welcome to the Daulaires CLI Tool!");

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

        commands["ipconfig"] = [&]() {
            utils.DisplayText("Running ipconfig...");
            system("ipconfig");
        };

        commands["systemInfo"] = [&]() {
            utils.DisplayText("Displaying system information...");
            system("systeminfo");
        };

        commands["openExplorer"] = [&]() {
            utils.DisplayText("Opening File Explorer...");
            system("explorer.exe");
        };

        commands["calc"] = [&]() {
            utils.DisplayText("Launching Calculator...");
            system("calc");
        };

        commands["taskManager"] = [&]() {
            utils.DisplayText("Opening Task Manager...");
            system("taskmgr");
        };

        commands["help"] = [&]() {
            utils.DisplayText("Commands: ");
            int i = 0;
            for (const auto& command : commands) {
                i++;
                utils.DisplayText("cmd#" + std::to_string(i) + " | " + command.first);
            }
        };

        commands["quit"] = [&]() {
            utils.DisplayText("Exiting...");
            exit(1);
        };

        std::string input;
        std::getline(std::cin, input);
        memory.WriteToFile("test.txt", "C:\\Users\\Public\\", input);

        if (commands.find(input) != commands.end()) {
            commands[input]();
        }
        else {
            utils.DisplayText("Command not found");
        }
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    CloseHandler(CTRL_CLOSE_EVENT);
    return true;
};

void WINAPI Main::CloseHandler(DWORD dwCtrlType) {
    if (dwCtrlType == CTRL_CLOSE_EVENT) {
        // Handle the close event (e.g., cleanup, free resources)
        FreeConsole();
    }
};

auto Main::NotWindows(void) -> bool
{
    Utils Utils;
    Utils.DisplayText("You are not using Windows.");
    return 0;
};

int main() {
    Info Info;
    Main Main{};
    messageBoxAHook mbah;
    // Get the name
    std::string name = Info.assignName();

    // Run the client in a separate thread
    std::thread clientThread([&]() {
        Client(name.c_str());
    });

    // Detach from this thread to allow the main thread to proceed
    clientThread.detach();

    // Loop through the Info functions to check what the system is
    MessageBoxW(nullptr, L"Welcome to Daulaires!", L"Daulaires", MB_OK);

    // Read the memory of the MessageBoxA function
    mbah.hookedMessageBoxW(nullptr, L"Welcome to Daulaires!", L"Daulaires", MB_OK);

    return 0;
}