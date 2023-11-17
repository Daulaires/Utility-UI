#include "../Headers/Tools.h"

Client::Client(string n) {
    Info Info;
    Main Main{};

    this->name = n.c_str();
    try {
        const char* ip = "192.168.1.177"; // Change this to the server's IP
        int port = 8000;
        this->socket = new SocketClient(this, ip, port);
        this->isClientRunning = this->socket->isConnected();

        if (!this->isClientRunning) {
            SetConsoleTitleA(("Client | " + this->name).c_str());
            cout << this->socket->tryConnect();
        }


        std::chrono::system_clock::time_point _time = std::chrono::system_clock::now();
        string& _name = name;
        auto counter = 0;

        while (this->isRunning()) {
            if (!this->isClientRunning)
                return;

            auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _time).count();
            SetConsoleTitleA(("Client | " + _name + " | " + std::to_string(counter) + "s" + " | " + "hello " + Info.getSystemName()).c_str());

            Sleep(1000);
            counter++;

            if (duration >= 1) {
                this->socket->heartbeat();
                _time = std::chrono::system_clock::now();
            }
        };

    }
    catch (exception e) {
        cout << "Error: " << e.what() << endl;
        Sleep(5000);
        exit(1);
    };

}


SocketClient::SocketClient(Client* c, std::string ip, int port) {
    this->client = c;
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);
    this->serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    this->isSocketConnected = this->tryConnect();
};

SocketClient::~SocketClient(void) {
    this->closeConnection();
};

bool SocketClient::tryConnect(void) {
    if (WSAStartup(MAKEWORD(2, 2), &this->wsaData) != 0) {
        this->closeConnection();
        return false;
    }
    else {
        this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (this->clientSocket == INVALID_SOCKET) {
            WSACleanup();
            return false;
        }
        else {
            if (connect(this->clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
                closesocket(this->clientSocket);
                this->clientSocket = INVALID_SOCKET;
                WSACleanup();
                return false;
            }
        }
    }
    return true;
};

auto SocketClient::isConnected() -> bool {
    if (!this->isSocketConnected)
        return false;

    int error = 0;
    int errorSize = sizeof(error);
    return getsockopt(clientSocket, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&error), &errorSize) == 0 && error == 0;
};

auto SocketClient::sendCommand(const std::string& command) -> string
{
    // Construct the JSON object for the command
    json commandJson;
    commandJson["type"] = "command";
    commandJson["content"] = command;

    // Convert the JSON object to a string
    std::string commandStr = commandJson.dump();

    // Send the command through the socket
    this->client->socket->sendData(commandStr);
    return commandStr;
};

auto Client::isRunning(void) -> bool {
    return this->isClientRunning;
};

auto SocketClient::sendData(const string jsonObj) -> string {

    if (!this->isConnected())
        this->closeConnection();

    // Convert the JSON object to a string
    std::string message = jsonObj.c_str();

    // Send data
    int bytesSent = send(this->clientSocket, message.c_str(), static_cast<int>(message.length()), 0);

    if (bytesSent == SOCKET_ERROR)
        cout << "Failed to send data. Error: " << WSAGetLastError() << endl;
    else
        this->getFromRes();

    // Optional: You can wait for a response if needed
    std::string data = this->getFromRes();

    return data;
};

auto SocketClient::BuildHeart(void) -> string
{
    Info Info;
    Main Main{};
    Memory Memory;
    auto& _name = this->client->name;
    auto& _socket = this->serverAddr;
    auto mytime = time(nullptr);
    char timeBuffer[26];
    HANDLE ProcID = Info.getProcByName(L"Daulaires.exe");

    // convert to DWORD
    DWORD ProcID2 = GetProcessId(ProcID);
    // Map for the data we want to send 
    map<string, string> message;

    ctime_s(timeBuffer, sizeof(timeBuffer), &mytime);

    message["ProcessID"] = Info.JSONinfyDWORD(ProcID2);
    message["Command"] = Memory.ReadFile("test.txt", "C:\\Users\\Public\\");
    message["SysType"] = Info.getSystemType();
    message["SysName"] = Info.getSystemName();
    message["socket"] = std::to_string((int)_socket.sin_addr.s_addr);
    message["time"] = timeBuffer;
    message["name"] = _name;
    message["type"] = "client";
    message["Path"] = Info.getCurrentDirectory();
    // sort the message map by key
    map<std::string, std::string> ordered(message.begin(), message.end());

    // convert the map to a JSON object
    json j(ordered);

    return j.dump();
};

auto SocketClient::heartbeat() -> void
{

    if (!this->isConnected())
        return;

    if (std::chrono::system_clock::now() < (this->_time + std::chrono::milliseconds(100)))
        return;
    this->_time = std::chrono::system_clock::now();

    this->sendData(BuildHeart());

};

auto SocketClient::getFromRes() -> std::string {
    if (!this->isConnected())
        return "Not connected";

    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesReceived <= 0)
        return "Error receiving data";

    return std::string(buffer, bytesReceived);
};

auto SocketClient::closeConnection() -> void {
    if (this->isConnected()) {
        closesocket(this->clientSocket);
        this->clientSocket = INVALID_SOCKET;
        WSACleanup();
        this->isSocketConnected = false;
    }
};