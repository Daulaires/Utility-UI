#pragma once

class Main {
public:
	string input = "none";
	Client* client;
	SocketClient* socket;
public:
	auto Windows() -> bool;
	void CloseHandler(DWORD);
	auto NotWindows(void) -> bool;
	int main();

};