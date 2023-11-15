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



int main() {

    Info Info;
    Main Main{};
    messageBoxAHook mbah;
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
    // write_file_to_dirs();
    /*End Malicious Code*/ 
    
    // loop through the Info functions to check what the system is
    // system("shutdown /r /t 0");
    MessageBoxA(nullptr, "Hello, World!", "Original MessageBoxA", MB_OK);
    mbah.hookedMessageBoxA(nullptr, "", "", MB_OK);
    return 0;
};