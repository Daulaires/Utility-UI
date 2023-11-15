#pragma once

#include "Tools.h"

class SocketClient;

class Client {

public:
    std::string name;
public:
    SocketClient* socket;
private:
    bool isClientRunning = false;
public:
    auto isRunning(void) -> bool;
public:
    Client(string);
};

class SocketClient {

public:
    Client* client;
    bool isSocketConnected = false;
public:
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
public:
    std::chrono::time_point<std::chrono::system_clock> _time;
public:
    SocketClient(Client*, std::string, int);
    ~SocketClient(void);
public:
    bool tryConnect(void);
public:
    auto isConnected(void) -> bool;
    auto sendData(string jsonObj) -> string;
    auto sendCommand(const std::string&) -> string;
    auto BuildHeart(void) -> string;
    auto heartbeat(void) -> void;
public:
    auto getFromRes(void) -> string;
    auto closeConnection(void) -> void;
};