#include "Depenencies/Headers/Tools.h"
using namespace std;

auto Main::Windows() -> bool
{
    Info info;
    Utils utils;
    map<string, function<void()>> commands;

    utils.DisplayText(info.getCurrentDirectory());
    utils.DisplayText(info.getSystemArchitecture());
    utils.DisplayText(info.getSystemType());

    // Horrible way of listening for commands
    utils.MoveExe("Daulaires.exe", info.getCurrentDirectory(), "C:\\Users\\Public\\");
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
    cout << "You are not using Windows" << endl;
    return 0;
};

int main() {
    Info Info;
    Main Main{};

    // allow another console to run the client
    std::thread clientThread([&]() {
        Client(Info.assignName());
    });

    // detach from this thread in order to go to the Commands loop
    clientThread.detach();

    if (Info.getSystemName() == "DEBIAN") {
        Main.NotWindows();
        return 1;
    };

    // loop through the Info functions to check what the system is
    if (Info.isWindows()) {
        Main.Windows();
    };

    return 0;
};