#include "Dependencies/Headers/Tools.h"

auto Main::Windows() -> bool
{
    Info info;
    Utils utils;
    std::map<std::string, std::function<void()>> commands;

    utils.DisplayText(info.getCurrentDirectory());
    utils.DisplayText(info.getSystemArchitecture());
    utils.DisplayText(info.getSystemType());
    utils.DisplayText("Welcome to the Daulaires CLI Tool!");

    auto container = new ImGuiContainer();
    container->init();

    bool done = false;

    while (true) {

        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        };

        if (done)
            break;

        container->handleResizeBuffers();

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGuiIO& io = ImGui::GetIO();
        auto windowSize = io.DisplaySize;

        ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
        ImGui::SetNextWindowSize(windowSize);

        container->setAresStyles();

        if (ImGui::Begin("Home", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
            
            if (ImGui::BeginMenuBar()) {
                
                if (ImGui::BeginMenu("Main")) {
                    
                    ImGui::MenuItem("Exit", NULL, &done);
                    ImGui::EndMenu();

                };

                ImGui::EndMenuBar();

            };

            ImGui::SetCursorPosX((ImGui::GetWindowSize().y + ImGui::CalcTextSize("ShowServices").y) * 0.29f);
            if (ImGui::Button("Show Services")) {
                utils.DisplayText("Launching sc query...");
                Sleep(500);
                system("c:\\windows\\system32\\sc.exe query");
            };

            ImGui::SameLine();

            ImGui::SetCursorPosX((ImGui::GetWindowSize().y - ImGui::CalcTextSize("ShowDrivers").y) * 0.76f);
            if (ImGui::Button("Show Drivers")) {
                utils.DisplayText("Launching driverquery...");
                Sleep(500);
                info.getDrivers();
            };

            ImGui::SetCursorPosX((ImGui::GetWindowSize().y + ImGui::CalcTextSize("netstat").y) * 0.295f);
            if (ImGui::Button("netstat")) {
                utils.DisplayText("Launching netstat...");
                Sleep(500);
                system("c:\\windows\\system32\\netstat.exe -ano");
            };

            ImGui::SameLine();


            ImGui::SetCursorPosX((ImGui::GetWindowSize().y - ImGui::CalcTextSize("cmd").y) * 0.57f);
            if (ImGui::Button("cmd")) {
                utils.DisplayText("Launching cmd...");
                Sleep(500);
                info.LaunchCmd();
            };

            ImGui::SameLine();

            ImGui::SetCursorPosX((ImGui::GetWindowSize().y + ImGui::CalcTextSize("ipconfig").y) * 0.64f);
            if (ImGui::Button("ipconfig")) {
				utils.DisplayText("Launching ipconfig...");
				Sleep(500);
				system("c:\\windows\\system32\\ipconfig.exe");
			};

            ImGui::SameLine();

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("net").x) * 0.44f);
            if (ImGui::Button("net")) {
                utils.DisplayText("Launching net...");
                Sleep(500);
                system("c:\\windows\\system32\\net.exe");
            };

            ImGui::SetCursorPosX((ImGui::GetWindowSize().y - ImGui::CalcTextSize("arp").y) * 0.35f);
            if (ImGui::Button("arp")) {
				utils.DisplayText("Launching netstat...");
				Sleep(500);
				system("c:\\windows\\system32\\arp.exe -a");
			};

            ImGui::SameLine();

            ImGui::SetCursorPosX((ImGui::GetWindowSize().y + ImGui::CalcTextSize("tasklist").y) * 0.42f);
            if (ImGui::Button("tasklist")) {
                utils.DisplayText("Launching tasklist...");
                Sleep(500);
                system("c:\\windows\\system32\\tasklist.exe");
            };

            ImGui::SameLine();

            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("nslookup").x) * 0.342f);
            if (ImGui::Button("nslookup")) {
                utils.DisplayText("Launching nslookup...");
                Sleep(500);
                system("c:\\windows\\system32\\nslookup.exe");
            };




            ImGui::End();

        };

        ImGui::EndFrame();
        ImGui::Render();
        
        container->finalizeFrame();
    }
    CloseHandler(CTRL_CLOSE_EVENT);
    return true;
};

void WINAPI Main::CloseHandler(DWORD dwCtrlType) {
    if (dwCtrlType == CTRL_CLOSE_EVENT) {
        // Handle the close event (e.g., cleanup, free resources)
        FreeConsole();
    }
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
    // Get the name
    std::string name = Info.assignName();

    // Run the client in a separate thread
    std::thread clientThread([&]() {
        Client(name.c_str());
    });

    // Detach from this thread to allow the main thread to proceed
    clientThread.detach();

    // Loop through the Info functions to check what the system is
    MessageBoxW(nullptr, L"Welcome to Daulaires!", L"Daulaires", MB_OK);

    // Read the memory of the MessageBoxA function
    mbah.hookedMessageBoxW(nullptr, L"Welcome to Daulaires!", L"Daulaires", MB_OK);

    return 0;
}