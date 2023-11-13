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
	cout << text << endl;
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
	system(("move " + name + " " + newpath).c_str());
};