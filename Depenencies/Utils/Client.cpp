#include "../Headers/Tools.h"

Client::Client(string n) {
    Info Info;
    Main Main{};
    Utils Utils;

    this->name = n.c_str();
    try {
        auto ip = "192.168.1.177"; // Change this to the server's IP
        auto port = 8000;
        this->socket = new SocketClient(this, ip, port);
        this->isClientRunning = this->socket->isConnected();
        if (!this->isClientRunning) {
            SetConsoleTitleA(("Client | " + this->name).c_str());
            // we will try to reconnect

            this->socket = new SocketClient(this, ip, port);
            if (!this->isClientRunning) {
                Utils.DisplayText(" U h o H");
            };

        };

        auto _time = std::chrono::system_clock::now();
        auto& _name = name;
        auto& _socket = socket->serverAddr;
        auto counter = 0;

        while (this->isRunning()) {
            if (!this->isClientRunning)
                return;

            // Calculate the duration in seconds
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _time).count();
            SetConsoleTitleA(("Client | " + _name + " | " + std::to_string(counter) + "s" + " | " + "hello " + Info.getSystemName()).c_str());

            Sleep(1000);
            counter++;
            if (duration >= 1) {
                this->socket->heartbeat();
                _time = std::chrono::system_clock::now();
            };
            continue;
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

auto SocketClient::tryConnect(void) -> bool {
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

auto SocketClient::isConnected(void) -> bool {
    if (!this->isSocketConnected)
        return false;

    int error = 0;
    int errorSize = sizeof(error);
    if (getsockopt(clientSocket, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&error), &errorSize) == 0) {
        return error == 0;
    }
    else {
        return false;
    };

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

auto SocketClient::sendData(string jsonObj) -> string {

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
    auto& _name = this->client->name;
    auto& _socket = this->serverAddr;
    time_t mytime = time(NULL);
    HANDLE ProcID = Info.getProcByName(L"Daulaires.exe");
    // convert to DWORD
    DWORD ProcID2 = GetProcessId(ProcID);
    // Map for the data we want to send 
    map<string, string> message;
    message["time"] = ctime(&mytime);
    message["name"] = _name;
    message["type"] = "client";
    message["socket"] = std::to_string((int)_socket.sin_addr.s_addr);
    message["SysType"] = Info.getSystemType();
    message["SysName"] = Info.getSystemName();
    message["Path"] = Info.getCurrentDirectory();
    message["SystemInfo"] = Info.getSystemInfo();
    message["ProcID"] = Info.JSONinfyDWORD(ProcID2);
    json j(message);

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

auto SocketClient::getFromRes(void) -> string {


    if (!this->isConnected())
        return "Not connected";

    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesReceived <= 0)
        return "Error receiving data";

    string receivedData(buffer, bytesReceived);
    auto& result = receivedData;
    if (!result.empty() || result == "")
        return result;

    return result;
};

auto SocketClient::closeConnection(void) -> void {
    if (!this->isConnected())
        return;

    closesocket(this->clientSocket);
    this->clientSocket = INVALID_SOCKET;

    WSACleanup();
    this->isSocketConnected = false;

};