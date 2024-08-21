
#include "imgui_internal.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <dwmapi.h>
#include "imgui_settings.h"
#include "icon_font.h"
#include "poppins_font.h"
#include "roboto_font.h"

#include "imgui_freetype.h"
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <urlmon.h>
#include <cstdlib> 
#include <thread>
#include <string>
#include <fstream>
#include <Shlwapi.h> // Para PathRemoveFileSpec y PathAppend
#pragma comment(lib, "Shlwapi.lib")
#include <iostream>

#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

#include "circle_load.h"
#include "minecraft_bg.h"
#include "logo.h"

#include "snow.hpp"

#define SNOW_LIMIT 20

#include "auth.hpp"
#include <string>
#include "utils.hpp"
#include "skStr.h"

#include <iostream>
#include "PYT.h"
#include "skStr.h"
#include "lazy.h"
//
#pragma comment (lib, "PYT.lib")
#include <thread>
#include "ThemidaSDK.h"
void ExecuteCommandHidden(const std::string& command) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    ZeroMemory(&pi, sizeof(pi));

    // Convert command string to a format suitable for CreateProcess
    char commandBuffer[1024];
    strcpy_s(commandBuffer, command.c_str());

    // Start the child process
    if (!CreateProcess(NULL, commandBuffer, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        return;
    }
}
std::string Asrock() {
    // Define characters that can be used for replacement
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Seed the random number generator
    std::srand(std::time(0));

    // Define the base string with 'X' characters to be replaced
    std::string Asrock1 = "MB0-X11111X1XX";

    // Iterate through each character in the base string
    for (char& c : Asrock1) {
        if (c == 'X') {
            // Replace 'X' with a random character from the set
            c = characters[rand() % characters.size()];
        }
    }

    return Asrock1;
}
std::string Lenovo() {
    // Define characters that can be used
    std::string characters = "0123456789PFTSFGAL";

    // Seed the random number generator
    std::srand(std::time(0));

    // Generate the random number
    std::string Lenovo1;
    for (int i = 0; i < 8; ++i) {
        Lenovo1 += characters[rand() % characters.size()];
    }

    return Lenovo1;
}
std::string MSI() {
    // Define characters that can be used
    std::string characters = "0123456789ABCDEFGHIJKLMSIWZ";

    // Seed the random number generator
    std::srand(std::time(0));

    // Generate the first part (xxxxxxxxx)
    std::string firstPart;
    for (int i = 0; i < 7; ++i) {
        firstPart += characters[rand() % characters.size()];
    }

    // Generate the second part (xxxxxxxxxx)
    std::string secondPart;
    for (int i = 0; i < 10; ++i) {
        secondPart += characters[rand() % characters.size()];
    }

    // Concatenate both parts with an underscore in between
    std::string randomNumber = firstPart + "_" + secondPart;

    return randomNumber;
}

std::string Regular() {
    const std::string charset = "0123456789ABCDEFMSI";
    const int length = 14;
    std::string result;

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < length; ++i) {
        result += charset[std::rand() % charset.size()];
    }

    return result;
}

using namespace KeyAuth;

void do_if_caught() {
    system("start https://discord.gg/XUG6feA8Ub"); // En Windows
}

ID3D11ShaderResourceView* circle_loading = nullptr;
ID3D11ShaderResourceView* minecraft_pic = nullptr;
ID3D11ShaderResourceView* lg = nullptr;

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace ImStyle;

#include <thread>
#include <chrono>
#include <random>

HWND ui_hwnd;
RECT rc;

static DWORD tick_count = GetTickCount();

std::vector<Snowflake::Snowflake> snow;

void move_window() {

    ImGui::SetCursorPos(ImVec2(0, 0));
    if (ImGui::InvisibleButton("##invisible window", ImVec2(window::size.x, window::size.y)));

    if (ImGui::IsItemActive()) {

        GetWindowRect(ui_hwnd, &rc);
        MoveWindow(ui_hwnd, rc.left + ImGui::GetMouseDragDelta().x, rc.top + ImGui::GetMouseDragDelta().y, window::size.x, window::size.y, TRUE);

        Snowflake::ChangeWindowPos(snow, ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
    }

}

void RenderBlur(HWND hwnd)
{
    struct ACCENTPOLICY
    {
        int na;
        int nf;
        int nc;
        int nA;
    };
    struct WINCOMPATTRDATA
    {
        int na;
        PVOID pd;
        ULONG ul;
    };

    const HINSTANCE hm = LoadLibrary("user32.dll");
    if (hm)
    {
        typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);

        const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hm, "SetWindowCompositionAttribute");
        if (SetWindowCompositionAttribute)
        {
            ACCENTPOLICY policy = { 3, 0, 0, 0 }; // and even works 4,0,155,0 (Acrylic blur)
            WINCOMPATTRDATA data = { 19, &policy,sizeof(ACCENTPOLICY) };
            SetWindowCompositionAttribute(hwnd, &data);
        }
        FreeLibrary(hm);
    }
}


#pragma comment(lib, "urlmon.lib")

namespace fonts {
    ImFont* poppins = nullptr;
    ImFont* roboto = nullptr;
    ImFont* icon = nullptr;
    ImFont* icon2 = nullptr;
    ImFont* icon3 = nullptr;
}

namespace var {

    namespace login {
        char login[24] = { "" };
        std::string login_succes = "user";
    }

    namespace password {
        char password[16] = { "" };
        std::string pass_succes = "12345";
    }

    namespace launch {
        const char* name = "Launch";
        bool click = false;
    }

    namespace panel {
        char ID[26] = {""};
        bool change_id = false;
    }

}


void DownloadFileFromUrl(const char* url, const char* savePath) {
    URLDownloadToFile(NULL, url, savePath, 0, NULL);
}

#include <iostream>
#include <thread>
#include <stdexcept>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")


void ExecuteBatchFile(const char* batchFilePath) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    CreateProcess(NULL, const_cast<char*>(batchFilePath), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void visiblebat(const char* batchFilePath) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    // Comentar la línea que oculta la ventana
    // si.dwFlags = STARTF_USESHOWWINDOW;
    // si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    CreateProcess(NULL, const_cast<char*>(batchFilePath), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void BlockInput(bool block) {
    if (block)
        BlockInput(TRUE);
    else
        BlockInput(FALSE);
}

void checker() {
    try {
        DownloadFileFromUrl("https://clovics.org/hwidChecker.bat", "C:\\Windows\\hwidChecker.bat");

        system("start C:\\Windows\\hwidChecker.bat");
    }
    catch (std::exception& ex) {
        MessageBox(NULL, ("Error: " + std::string(ex.what())).c_str(), "Error", MB_OK | MB_ICONERROR);
    }
}


void asrock1() {
    system(skCrypt("curl --silent https://clovics.org/AsDeviceCheck.exe --output C:\\Windows\\System32\\AsDeviceCheck.exe >nul").decrypt());
    system(skCrypt("curl --silent https://clovics.org/AsDeviceChk.sys --output C:\\Windows\\System32\\AsDeviceChk.sys >nul").decrypt());


    std::string Asrock1 = Asrock();
    std::string a = "cd C:\\Windows\\System32\\ && AsDeviceCheck /BS " + Asrock1 + " > NUL 2>&1";
    std::string b = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SS \"Default string\" > NUL 2>&1";
    std::string c = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SU auto > NUL 2>&1";
    std::string d = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SK \"To Be Filled By O.E.M.\" > NUL 2>&1";
    std::string e = "cd C:\\Windows\\System32\\ && AsDeviceCheck /PSN \"To Be Filled By O.E.M.\" > NUL 2>&1";
    system(a.c_str());

    system(b.c_str());
    system(c.c_str());
    system(d.c_str());
    system(e.c_str());
    system("net stop winmgmt /y > nul");
    system("timeout /t 2 /nobreak > nul");
    system("net start winmgmt /y > nul");
    Sleep(1000);
    MessageBox(NULL, "Spoofed successfully!", "CXMPLEX", MB_OK | MB_ICONINFORMATION);

}
void Lenovo1() {
    system(skCrypt("curl --silent https://clovics.org/AsDeviceCheck.exe --output C:\\Windows\\System32\\AsDeviceCheck.exe >nul").decrypt());
    system(skCrypt("curl --silent https://clovics.org/AsDeviceChk.sys --output C:\\Windows\\System32\\AsDeviceChk.sys >nul").decrypt());


    std::string Lenovo2 = Lenovo();
    std::string a = "cd C:\\Windows\\System32\\ && AsDeviceCheck /BS " + Lenovo2 + " > NUL 2>&1";
    std::string b = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SS \"Default string\" > NUL 2>&1";
    std::string c = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SU auto > NUL 2>&1";
    std::string d = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SK \"To Be Filled By O.E.M.\" > NUL 2>&1";
    std::string e = "cd C:\\Windows\\System32\\ && AsDeviceCheck /PSN \"To Be Filled By O.E.M.\" > NUL 2>&1";
    system(a.c_str());

    system(b.c_str());
    system(c.c_str());
    system(d.c_str());
    system(e.c_str());
    system("net stop winmgmt /y > nul");
    system("timeout /t 2 /nobreak > nul");
    system("net start winmgmt /y > nul");
    Sleep(1000);
    MessageBox(NULL, "Spoofed successfully!", "CXMPLEX", MB_OK | MB_ICONINFORMATION);

}
void Gigabyte() {
 
    system(skCrypt("curl --silent https://clovics.org/AsDeviceCheck.exe --output C:\\Windows\\System32\\AsDeviceCheck.exe >nul").decrypt());
    system(skCrypt("curl --silent https://clovics.org/AsDeviceChk.sys --output C:\\Windows\\System32\\AsDeviceChk.sys >nul").decrypt());


    std::string a = "cd C:\\Windows\\System32\\ && AsDeviceCheck /BS \"Default string\" > NUL 2>&1";
    std::string b = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SS \"Default string\" > NUL 2>&1";
    std::string c = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SU auto > NUL 2>&1";
    std::string d = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SK \"To Be Filled By O.E.M.\" > NUL 2>&1";
    std::string e = "cd C:\\Windows\\System32\\ && AsDeviceCheck /PSN \"To Be Filled By O.E.M.\" > NUL 2>&1";
    system(a.c_str());

    system(b.c_str());
    system(c.c_str());
    system(d.c_str());
    system(e.c_str());
    system("net stop winmgmt /y > nul");
    system("timeout /t 2 /nobreak > nul");
    system("net start winmgmt /y > nul");
    Sleep(1000);
    MessageBox(NULL, "Spoofed successfully!", "CXMPLEX", MB_OK | MB_ICONINFORMATION);

}

void asus() {
    system("curl --silent https://clovics.org/ASUSPDF2.bat --output C:\\Windows\\ASUSPDF2.bat >nul 2>&1");
    system("curl --silent https://clovics.org/AsusPDF.bat --output C:\\Windows\\AsusPDF.bat >nul 2>&1");
    system("curl --silent https://clovics.org/AsDeviceChk.sys --output C:\\Windows\\AsDeviceChk.sys >nul 2>&1");
    system("curl --silent https://clovics.org/AsDeviceCheck.exe --output C:\\Windows\\AsDeviceCheck.exe >nul 2>&1");

    const char* batchFilePath = "C:\\Windows\\AsusPDF.bat";

    // Execute the batch file
    int result = system(batchFilePath);
    MessageBox(NULL, "Restart PC!", "CXMPLEX", MB_OK | MB_ICONINFORMATION);
}
       


void option2() {

    system(skCrypt("curl --silent https://clovics.org/AsDeviceCheck.exe --output C:\\Windows\\System32\\AsDeviceCheck.exe >nul").decrypt());
    system(skCrypt("curl --silent https://clovics.org/AsDeviceChk.sys --output C:\\Windows\\System32\\AsDeviceChk.sys >nul").decrypt());


        std::string randomNumber = MSI();
        std::string a = "cd C:\\Windows\\System32\\ && AsDeviceCheck /BS " + randomNumber + " > NUL 2>&1";
        std::string b = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SS \"Default string\" > NUL 2>&1";
        std::string c = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SU auto > NUL 2>&1";
        std::string d = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SK \"To Be Filled By O.E.M.\" > NUL 2>&1";
        std::string e = "cd C:\\Windows\\System32\\ && AsDeviceCheck /PSN \"To Be Filled By O.E.M.\" > NUL 2>&1";
        system(a.c_str());

        system(b.c_str());
        system(c.c_str());
        system(d.c_str());
        system(e.c_str());
        system("net stop winmgmt /y > nul");
        system("timeout /t 2 /nobreak > nul");
        system("net start winmgmt /y > nul");
        Sleep(1000);
        MessageBox(NULL, "Spoofed successfully!", "CXMPLEX", MB_OK | MB_ICONINFORMATION);

    }
void Default() {

    system(skCrypt("curl --silent https://clovics.org/AsDeviceCheck.exe --output C:\\Windows\\System32\\AsDeviceCheck.exe >nul").decrypt());
    system(skCrypt("curl --silent https://clovics.org/AsDeviceChk.sys --output C:\\Windows\\System32\\AsDeviceChk.sys >nul").decrypt());

    std::string Regular1 = Regular();
    std::string a = "cd C:\\Windows\\System32\\ && AsDeviceCheck /BS " + Regular1 + " > NUL 2>&1";
    std::string b = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SS \"Default string\" > NUL 2>&1";
    std::string c = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SU auto > NUL 2>&1";
    std::string d = "cd C:\\Windows\\System32\\ && AsDeviceCheck /SK \"To Be Filled By O.E.M.\" > NUL 2>&1";
    std::string e = "cd C:\\Windows\\System32\\ && AsDeviceCheck /PSN \"To Be Filled By O.E.M.\" > NUL 2>&1";
    system(a.c_str());

    system(b.c_str());
    system(c.c_str());
    system(d.c_str());
    system(e.c_str());
    system("net stop winmgmt /y > nul");
    system("timeout /t 2 /nobreak > nul");
    system("net start winmgmt /y > nul");
    Sleep(1000);
    MessageBox(NULL, "Spoofed successfully!", "CXMPLEX", MB_OK | MB_ICONINFORMATION);

}
    


 
    


void mac() {
    system(skCrypt("curl --silent https://clovics.org/mac.bat --output C:\\Windows\\System32\\mac.bat >nul").decrypt());

    ExecuteBatchFile("C:\\Windows\\System32\\mac.bat");
}



void ip() {
    try {
        system(skCrypt("curl --silent https://clovics.org/ARP-Ban-Fix.bat --output C:\\Windows\\System32\\ARP-Ban-Fix.bat >nul").decrypt());

        system("C:\\Windows\\System32\\ARP-Ban-Fix.bat");
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::remove("C:\\Windows\\ARP-Ban-Fix.bat");
        system("cmd /c ipconfig /flushdns");
        Sleep(5000);

        system("cmd /c ipconfig /registerdns");
        Sleep(5000);

        system("cmd /c ipconfig /release");
        Sleep(5000);

        system("cmd /c ipconfig /renew");
        Sleep(5000);

        system("cmd /c netsh winsock reset");
        Sleep(10000);
  
    }
    catch (std::exception& ex) {
        MessageBox(NULL, ("Error: " + std::string(ex.what())).c_str(), "Error", MB_OK | MB_ICONERROR);
    }
}


void SaveSerials() {
    // Obtener la ruta de la carpeta temporal
    char tempPath[MAX_PATH];
    DWORD result = GetTempPath(MAX_PATH, tempPath);
    if (result == 0 || result > MAX_PATH) {
        MessageBox(NULL, "Error al obtener la ruta de la carpeta temporal.", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Construir la ruta completa del archivo .bat en la carpeta temporal
    std::string batFilePath = tempPath;
    batFilePath += "Check.bat";

    // Descargar el archivo .bat desde la URL a la carpeta temporal
    DownloadFileFromUrl(skCrypt("https://unban.es/Check%20(1).bat").decrypt(), batFilePath.c_str());


    // Ejecutar el archivo .bat desde la carpeta temporal en segundo plano
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    if (!CreateProcess(NULL, const_cast<char*>(batFilePath.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        MessageBox(NULL, "Error al ejecutar el archivo.", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Esperar a que el proceso termine
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Intentar eliminar el archivo .bat de la carpeta temporal
    if (!DeleteFile(batFilePath.c_str())) {
        MessageBox(NULL, "Error al eliminar el archivo.", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    MessageBox(NULL, "Serials saved successfully.", "Success", MB_OK);
}


std::string cpuSerial;
std::string biosSerial;
std::string baseboardSerial;
std::string systemUUID;
std::string MAC;
std::string IPV4;

bool executed = false;
std::string exec(const char* cmd);
// Función para ejecutar el comando una vez y almacenar su salida en variables globales
void executeCommands() {
    if (!executed) {
        cpuSerial = exec("wmic cpu get serialnumber");
        biosSerial = exec("wmic bios get serialnumber");
        baseboardSerial = exec("wmic baseboard get serialnumber");
        systemUUID = exec("wmic path win32_computersystemproduct get uuid");
        MAC = exec("getmac");
        
        executed = true;
    }
}

// Función para ejecutar el comando y obtener su salida como una cadena
std::string exec(const char* cmd) {
    std::string result;
    HANDLE hReadPipe, hWritePipe;

    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        throw std::runtime_error("CreatePipe failed");
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError = hWritePipe;
    si.hStdOutput = hWritePipe;
    si.dwFlags |= STARTF_USESTDHANDLES;

    if (!CreateProcess(NULL, const_cast<LPSTR>(cmd), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        throw std::runtime_error("CreateProcess failed");
    }

    CloseHandle(hWritePipe);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    DWORD bytesRead = 0;
    char buffer[128];
    while (ReadFile(hReadPipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead != 0) {
        result.append(buffer, bytesRead);
    }

    CloseHandle(hReadPipe);

    return result;
}

// Funciones para obtener la información del sistema
std::string getCPUSerial() {
    executeCommands();
    return cpuSerial;
}

std::string getBIOSSerial() {
    executeCommands();
    return biosSerial;
}

std::string getBaseboardSerial() {
    executeCommands();
    return baseboardSerial;
}

std::string getSystemUUID() {
    executeCommands();
    return systemUUID;
}

std::string getmac() {
    executeCommands();
    return MAC;
}

std::string ipconfig() {
    executeCommands();
    return IPV4;
}

int tabs = 0, tab_subscription = 0;
int sub_tabs = 0;

float timer_loading = 0.f;

static int product_list = 0;

bool product_selection = true;

POINT mouse;
DWORD win_flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    void PYTGuard_Check();
    void PYTGuard_AntiDump();
    void PYTGuard_MapFile(const std::vector<unsigned char>&downloadedData);
    void check_security_integrity();
    void customer_node_valid(std::string lowkey);
    //Initialize_PYT(skCrypt("lowkey").decrypt());
    auto name = skCrypt("THROWOFF CXMPLEX");
    auto ownerid = skCrypt("rKJwW6lelA");
    auto secret = skCrypt("cb0c91f0ae41fb12a2722d859026607ebb1dfa9df369c6ff0ae2a149e1d55a57");
    auto version = skCrypt("1.0");
    auto url = skCrypt("https://keyauth.win/api/1.2/"); // change if you're self-hostingç

    api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());

    WNDCLASSEXW wc;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = nullptr;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = L"ImGui";
    wc.lpszClassName = L"Example";
    wc.hIconSm = LoadIcon(0, IDI_APPLICATION);

    RegisterClassExW(&wc);
    ui_hwnd = CreateWindowExW(NULL, wc.lpszClassName, L".", WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (window::size.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (window::size.y / 2), window::size.x, window::size.y, 0, 0, 0, 0);
  //  RenderBlur(hwnd);

    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(ui_hwnd, &margins);
    POINT mouse;
    rc = { 0 };
    GetWindowRect(ui_hwnd, &rc);
    if (IsRunAsAdmin()) {

    }
    else {
        MessageBoxA(NULL, "Run As Administrator", "CXMPLEX Error", MB_OK);
        exit(1);
    }
    if (!CreateDeviceD3D(ui_hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(ui_hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(ui_hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImFontConfig cfg;
    cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;

    fonts::poppins = io.Fonts->AddFontFromMemoryTTF(&poppins, sizeof poppins, 23, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    fonts::roboto = io.Fonts->AddFontFromMemoryTTF(&roboto, sizeof roboto, 45, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    fonts::icon = io.Fonts->AddFontFromMemoryTTF(&ico, sizeof ico, 35, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    fonts::icon2 = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 39, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    fonts::icon3 = io.Fonts->AddFontFromMemoryTTF(&icon3, sizeof icon3, 23, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplWin32_Init(ui_hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 5.f/*minimum size*/, 20.f/*maximum size*/, 0/*imgui window x position*/, 0/*imgui window y position*/, window::size.x, window::size.y, Snowflake::vec3(0.f, 0.029f)/*gravity*/, IM_COL32(100, 100, 100, 50));

    bool done = false;
    while (!done)
    {

        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            ImGuiContext& g = *GImGui;

            D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
            if (circle_loading == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, circle, sizeof(circle), &info, pump, &circle_loading, 0);
            if (minecraft_pic == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, minecraft_bg, sizeof(minecraft_bg), &info, pump, &minecraft_pic, 0);
            if (lg == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo, sizeof(logo), &info, pump, &lg, 0);

            ImGui::GetStyle().WindowPadding = ImVec2(0, 0);
            ImGui::GetStyle().WindowBorderSize = 0.f;
            ImGui::GetStyle().ItemSpacing = ImVec2(15, 15);
            ImGui::GetStyle().ScrollbarSize = 7.f;

            ImGui::SetNextWindowSize(ImVec2(window::size.x, window::size.y));
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

            ImGui::Begin("menu DirectX11", nullptr, win_flags);
            {
                GetWindowRect(ui_hwnd, &rc);

                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(window::size.x, window::size.y), ImGui::GetColorU32(window::background), window::rounding);

                GetCursorPos(&mouse);
                Snowflake::Update(snow, Snowflake::vec3(mouse.x, mouse.y)/*mouse x and y*/, Snowflake::vec3(rc.left, rc.top));

                const int vtx_idx_1 = ImGui::GetWindowDrawList()->VtxBuffer.Size;
                ImGui::GetWindowDrawList()->AddRect(ImVec2(1, 1), ImVec2(window::size.x, window::size.y), ImGui::GetColorU32(ImStyle::window::background), window::rounding, ImDrawFlags_None, 2.f);
                ImGui::ShadeVertsLinearColorGradientKeepAlpha(ImGui::GetWindowDrawList(), vtx_idx_1, ImGui::GetWindowDrawList()->VtxBuffer.Size, ImVec2(1, 1), ImVec2(window::size.x / 2, window::size.y / 2), ImGui::GetColorU32(ImStyle::general_color), ImColor(24, 24, 24, 0));

                ImGui::SetCursorPos(ImVec2(window::size.x - (45 * 2), 15));
                ImGui::BeginGroup();
                {

                 if (ImGui::TextButton("B", true, ImVec2(25, 25))) ShowWindow(ui_hwnd, SW_MINIMIZE);

                   ImGui::SameLine();

                    if (ImGui::TextButton("A", true, ImVec2(25, 25))) {
                        ShowWindow(ui_hwnd, SW_HIDE);
                        done = true;
                    };
                }
                ImGui::EndGroup();

                static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

                tab_alpha = ImClamp(tab_alpha + (4.f * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);
                tab_add = ImClamp(tab_add + (std::round(350.f) * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);

                if (tab_alpha == 0.f && tab_add == 0.f) active_tab = tabs;

                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * ImGui::GetStyle().Alpha);

                if (active_tab == 0) {
                    tabs = 2;
                    active_tab = 2;

                }
         

                else if (active_tab == 2) {

                    if (product_selection) {

                        ImGui::GetWindowDrawList()->AddImage(lg, ImVec2(19, 17), ImVec2(89, 87), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImStyle::general_color));

                        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(10, 100), ImVec2(100, 101), ImGui::GetColorU32(window::border), window::rounding);
                        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(105, 10), ImVec2(106, window::size.y - 10), ImGui::GetColorU32(window::border), window::rounding);
                        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(10, window::size.y - 101), ImVec2(100, window::size.y - 100), ImGui::GetColorU32(window::border), window::rounding);

                        ImGui::SetCursorPos(ImVec2(27, window::size.y - 78));
                        if (ImGui::TextButton("C", true, ImVec2(35, 35))) {
                            system("start https://discord.gg/Am4SMZn2Ps"); // En Windows
                        }


                        ImGui::SetCursorPos(ImVec2(30, 194));

                        ImGui::BeginGroup();
                        {
                            if (ImGui::tabs(0 == tab_subscription, "G##1", ImVec2(50, 50))) tab_subscription = 0, sub_tabs = 0;
                        
                            if (ImGui::tabs(2 == tab_subscription, "I##1", ImVec2(50, 50))) tab_subscription = 2 , sub_tabs = 2;

                        }
                        ImGui::EndGroup();

                        ImGui::SetCursorPos(ImVec2(130, 24));
                      
                        ImGui::BeginGroup();
                        {
                            if (tab_subscription == 0) {

                                if (ImGui::SubTabs(0 == sub_tabs, "Announcements")) sub_tabs = 0;

                                ImGui::SameLine(0, 20);

                        
                            }
                            else if (tab_subscription == 1) {

                                if (ImGui::SubTabs(0 == sub_tabs, "Subscription")) sub_tabs = 0;

                                ImGui::SameLine(0, 20);

                                if (ImGui::SubTabs(1 == sub_tabs, "Info")) sub_tabs = 1;

                            }
                            else if (tab_subscription == 2) {

                                //if (ImGui::SubTabs(1 == sub_tabs, "Compatibility")) sub_tabs = 1;

                              //  ImGui::SameLine(0, 20);
                              
                                if (ImGui::SubTabs(2 == sub_tabs, "Spoofer")) sub_tabs = 2;
                                
                                ImGui::SameLine(0, 20);
                                if (ImGui::SubTabs(3 == sub_tabs, "Misc")) sub_tabs = 3;

                                ImGui::SameLine(0, 20);

                                if (ImGui::SubTabs(4 == sub_tabs, "Checker")) sub_tabs = 4;
                               
                            }
                    


                        }
                        ImGui::EndGroup();

                        ImGui::SetCursorPos(ImVec2((150 / 2) + (105 / 2), (150 / 2)));

                        if (sub_tabs == 0 && tab_subscription == 0) {

                            ImGui::BeginChild("Change-Logs", ImVec2(window::size.x - 150, window::size.y - 150));
                            {
                                for (int i = 0; i < 1; i++)
                                    ImGui::ChangeList("Advertisement:", "Still in Beta Version, any error contact me.", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2) - 5, 70));

                            }
                            ImGui::EndChild();

                        }

                        else if (sub_tabs == 1 && tab_subscription == 0) {

                            ImGui::BeginChild("Announcements-Page", ImVec2(window::size.x - 150, window::size.y - 150));
                            {
                                for (int i = 0; i < 1; i++)
                                    ImGui::ChangeList("Description:", "Added Custom Serials For Every Motherboard", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2) - 5, 70));


                            }
                            ImGui::EndChild();

                        }

                        if (sub_tabs == 3 && tab_subscription == 2) {

                            ImGui::BeginChild("Misc", ImVec2(window::size.x - 150, window::size.y - 150));
                            {
                      

                                ImGui::OpenPopup("Error");
                              
                                if (ImGui::Button("Obtain A Licsence Key", ImVec2(550, 50))) {
                             
                                    system("start https://discordapp.com/channels/1209351765716238397/1209355361325162546");
                                        
                                }
                                if (ImGui::Button("Instructions", ImVec2(550, 50))) {

                                    system("start https://docs.google.com/document/d/1IDFhxE5wEnpU2JSQzUDl2q3xCR0_gqzkAoRJ9KOery8/edit?usp=sharing");

                                }
                         
                            }
                            
                            ImGui::EndChild();

                        }
                        bool refreshSerials = false; // Variable para controlar si se debe actualizar los números de serie

                        if (sub_tabs == 4 && tab_subscription == 2) {
                            ImGui::BeginChild("Checker", ImVec2(window::size.x - 150, window::size.y - 150));
                            {
                          
                              

                                ImGui::OpenPopup("Error");
                            

                                    //executed = false; // Restablecemos executed a false para permitir la ejecución de los comandos nuevamente
                                    executeCommands();
                                //    refreshSerials = false; // Desactivamos la actualización para que no se repita innecesariamente
                                    if (ImGui::Button("Refresh Serials")) {
                                        // Al presionar el botón, activamos la actualización de los números de serie
                                        refreshSerials = true;
                                    }

                                    if (refreshSerials) {
                                        // Si se debe actualizar, ejecutamos los comandos y actualizamos las variables
                                        executed = false; // Restablecemos executed a false para permitir la ejecución de los comandos nuevamente
                                        executeCommands();
                                        refreshSerials = false; // Desactivamos la actualización para que no se repita innecesariamente
                                    }

                                // Mostramos los números de serie
                                ImVec4 textColor(255 / 255.0f, 255 / 255.0f, 255 / 255.0f, 1.0f);
                                ImGui::TextColored(textColor, "CPU: %s", cpuSerial.c_str());
                                ImGui::TextColored(textColor, "BIOS: %s", biosSerial.c_str());
                                ImGui::TextColored(textColor, "Baseboard: %s", baseboardSerial.c_str());
                                ImGui::TextColored(textColor, "SMBIOS: %s", systemUUID.c_str());
                                ImGui::TextColored(textColor, "MAC: %s", MAC.c_str());
                                ImGui::TextColored(textColor, "%s", IPV4.c_str());
                            }

                            ImGui::EndChild();
                        }

                        else if (sub_tabs == 2 && tab_subscription == 2) {
                            static bool spoof_panel = true;
                            if (spoof_panel) {
 
                                HKEY hKey;
                                LONG regOpenResult = RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\lowkey", 0, KEY_READ, &hKey);
                                if (regOpenResult == ERROR_SUCCESS) {
                                    DWORD dataSize = 256; // Tamaño máximo esperado de la clave, puedes ajustarlo según tus necesidades
                                    char savedKey[256]; // Buffer para almacenar la clave leída del registro
                                    DWORD keyType;
                                    LONG regQueryValueResult = RegQueryValueExA(hKey, "SavedKey", NULL, &keyType, (LPBYTE)savedKey, &dataSize);
                                    if (regQueryValueResult == ERROR_SUCCESS && keyType == REG_SZ) {
                                        // Establecer la clave recuperada en tu aplicación, por ejemplo, en una variable global
                                        strcpy_s(var::login::login, sizeof(var::login::login), savedKey);
                                        // Asegúrate de que tu aplicación tenga acceso a la clave recuperada aquí
                                    }
                                    // Cerrar la clave del registro
                                    RegCloseKey(hKey);
                                }
                                else {
                                    // Manejar el error al abrir la clave del registro
                                    // Por ejemplo, mostrar un mensaje de error o continuar sin la clave guardada
                                }
                                void PYTGuard_Check();
                                void PYTGuard_AntiDump();
                                void PYTGuard_MapFile(const std::vector<unsigned char>&downloadedData);
                                void check_security_integrity();
                            
                          
                                ImGui::PushFont(fonts::roboto);
                                
                                ImGui::ShadowText("CXMPLEX SPOOFER", ImGui::GetColorU32(ImStyle::text::text_active), ImGui::GetColorU32(ImStyle::window::shadow_text), 110.f, ImVec2((window::size.x / 2.0 - (ImGui::CalcTextSize("CRYPTIC SPOOFER").x) / 2), 80));
                                void PYTGuard_Check();
                                void PYTGuard_AntiDump();
                                void PYTGuard_MapFile(const std::vector<unsigned char>& downloadedData);
                                void check_security_integrity();
                                void node_check();
                                void PYTGuard_detect_hooks();
                                void customer_node_valid(std::string lowkey);
                                ImGui::PopFont();
                                float keyInputStartX = (window::size.x / 2) - (280 / 2);
                                ImGui::SetCursorPos(ImVec2(keyInputStartX, (window::size.y / 2) - (75 / 2) - (ImGui::GetStyle().ItemSpacing.y / 2) * 2));
                                ImGui::BeginGroup();
                                ImGui::InputTextEx("##0", "Key", var::login::login, 24, ImVec2(280, 35), ImGuiInputTextFlags_None);
                                static bool remember = true;
                                ImGui::Checkbox("Remember me", &remember);
                                if (remember) {
                                    HKEY hKey;
                                    // Abrir la clave del registro o crearla si no existe
                                    LONG regOpenResult = RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\lowkey", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
                                    if (regOpenResult == ERROR_SUCCESS) {
                                        // Escribir la clave en el registro
                                        DWORD dataSize = strlen(var::login::login) + 1; // Tamaño de la cadena de la clave + 1 para el carácter nulo
                                        LONG regSetValueResult = RegSetValueExA(hKey, "SavedKey", 0, REG_SZ, (const BYTE*)var::login::login, dataSize);
                                        if (regSetValueResult != ERROR_SUCCESS) {
                                            // Manejar el error al escribir en el registro
                                            // Por ejemplo, mostrar un mensaje de error
                                            ImGui::OpenPopup("Registry Error");
                                        }
                                        // Cerrar la clave del registro
                                        RegCloseKey(hKey);
                                    }
                                    else {
                                        // Manejar el error al abrir la clave del registro
                                        // Por ejemplo, mostrar un mensaje de error
                                        ImGui::OpenPopup("Registry Error");
                                    }
                                }

                                if (ImGui::Button(var::launch::name, ImVec2(280, 35))) {
                                   
                                 
                               

                                    void PYTGuard_Check();
                                    void PYTGuard_AntiDump();
                                    void PYTGuard_MapFile(const std::vector<unsigned char>&downloadedData);
                                    void check_security_integrity();
                                    KeyAuthApp.init();
                         
                                    KeyAuthApp.license(var::login::login); // Assuming login is the key
                                    void PYTGuard_Check();
                                    void PYTGuard_AntiDump();
                                    void PYTGuard_MapFile(const std::vector<unsigned char>& downloadedData);
                                    void check_security_integrity();
                                    if (KeyAuthApp.data.success) {
                                        spoof_panel = false;
                              
   
                                    }
                                }

                                ImGui::EndGroup();

                                if (ImGui::BeginPopupModal("Registry Error", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                                    ImGui::Text("Error occurred while accessing Windows Registry.");
                                    if (ImGui::Button("OK", ImVec2(120, 0))) {
                                        ImGui::CloseCurrentPopup();
                                    }
                                    ImGui::EndPopup();
                                }

                                if (ImGui::BeginPopupModal("Error", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                                    ImGui::Text("Authentication failed. Please check your credentials and try again.");
                                    if (ImGui::Button("OK", ImVec2(120, 0))) {
                                        ImGui::CloseCurrentPopup();
                                    }
                                    ImGui::EndPopup();
                                }
                            }
                            else {
                             if (tab_subscription == 15) {

                                //if (ImGui::SubTabs(1 == sub_tabs, "Compatibility")) sub_tabs = 1;

                              //  ImGui::SameLine(0, 20);

                              ImGui::SameLine(0, 20);
                              if (ImGui::SubTabs(3 == sub_tabs, "Misc")) sub_tabs = 3;

                              ImGui::SameLine(0, 20);

                              if (ImGui::SubTabs(4 == sub_tabs, "Checker")) sub_tabs = 4;



                            }
                               
                     
                                    
                                // Mueve el contenido más abajo
                                ImGui::SetCursorPosX((window::size.x - 400) * 0.5f + 20);
                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20); // Ajusta la posición vertical

                                ImGui::BeginGroup();
                                {
                                    
                                    ImGui::Text("Select your motherboard");
                                    const char* options[] = { "GIGABYTE", "MSI", "ASUS", "AsRock","Lenovo","Other Motherboard" };
                                    static int selectedOption = 0; // Opción predeterminada

                                    ImGui::Combo("Select", &selectedOption, options, IM_ARRAYSIZE(options));
                                    if (ImGui::Button("Apply", ImVec2(415, 50))) { // Mantén el tamaño original del botón
                         
                                        switch (selectedOption) {
                                        case 0:
                                            SetScreenToBlack();
                                            Gigabyte();
                                          
                                            break;
                                        case 1:
                                            SetScreenToBlack();
                                            option2();
                                        
                                            break;
                                        case 2:
                                            SetScreenToBlack();
                                            asus();
                                     
                                            break;
                                        case 3:
                                            SetScreenToBlack();
                                            asrock1();
                                    
                                            break;
                                        case 4:
                                            SetScreenToBlack();
                                            Lenovo1();
                                     
                                            break;
                                        case 5:
                                            SetScreenToBlack();
                                            Default();
                                            
                         
                                            break;

                                        }
                                    
                                    }
                                    ImVec2 line_start(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() - 7);
                                    ImVec2 line_end(ImGui::GetCursorPosX() + 413, ImGui::GetCursorPosY() - 7); // Ajusta la posición final de la línea
                                //    ImGui::GetWindowDrawList()->AddLine(line_start, line_end, IM_COL32(100, 150, 255, 255));

                                    if (ImGui::Button("Save Serials", ImVec2(415, 50))) { // Mantén el tamaño original del botón
                                        SaveSerials();
                                    }
                                    if (ImGui::Button("Network Virtualization", ImVec2(415, 50))) { // Mantén el tamaño original del botón
                                        mac();
                                        ip();
                                    }
                                }
                                ImGui::EndGroup();
                            }


                            }
                        else if (sub_tabs == 1 && tab_subscription == 2) {

                            ImGui::BeginChild("Spoofer##0", ImVec2(window::size.x - 150, window::size.y - 150));
                            {

                                if (ImGui::Selector(0 == product_list, "Call Of Duty: All Franchises", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 0;
                                }

                                if (ImGui::Selector(1 == product_list, "Apex Legends", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 1;
                                }

                                if (ImGui::Selector(2 == product_list, "Dead By Daylight", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 2;
                                }

                                if (ImGui::Selector(3 == product_list, "Escape From Tarkov", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 3;
                                }

                                if (ImGui::Selector(4 == product_list, "PUBG", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 4;
                                }

                                if (ImGui::Selector(5 == product_list, "Rainbow Six Siege", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 5;
                                }

                                if (ImGui::Selector(6 == product_list, "Super People", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 6;
                                }

                                if (ImGui::Selector(7 == product_list, "Destiny", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 7;
                                }

                                if (ImGui::Selector(8 == product_list, "Scum", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 8;
                                }

                                if (ImGui::Selector(9 == product_list, "ARMA", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 9;
                                }

                                if (ImGui::Selector(10 == product_list, "Smite", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 10;
                                }

                                if (ImGui::Selector(11 == product_list, "Battefield", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 11;
                                }

                                if (ImGui::Selector(12 == product_list, "DayZ", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 12;
                                }

                                if (ImGui::Selector(13 == product_list, "Fortnite & Tournaments", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 13;
                                }

                                if (ImGui::Selector(14 == product_list, "RUST", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 14;
                                }

                                if (ImGui::Selector(15 == product_list, "Valorant [NEW CHIP]", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 15;
                                }

                                if (ImGui::Selector(16 == product_list, "Warframe", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 16;
                                }

                                if (ImGui::Selector(17 == product_list, "Overwatch", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 17;
                                }

                                if (ImGui::Selector(18 == product_list, "Ark: Survival Evolved", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 18;
                                }

                                if (ImGui::Selector(19 == product_list, "New World", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 19;
                                }

                                if (ImGui::Selector(20 == product_list, "Fall Guys", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 20;
                                }

                                if (ImGui::Selector(22 == product_list, "Other", ImVec2(ImGui::GetContentRegionMax().x - (ImGui::GetStyle().WindowPadding.x * 2), 40))) {
                                    product_list = 22;
                                }

                            }
                            ImGui::EndChild();
                        }
                    }
                }

                ImGui::PopStyleVar();

                move_window();
            }

            ImGui::End();

        }
        ImGui::Render();
        const float clear_color_with_alpha[4] = { 0 };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(ui_hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}


bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
    void PYTGuard_Check();
    void PYTGuard_AntiDump();
    void PYTGuard_MapFile(const std::vector<unsigned char>&downloadedData);
    void check_security_integrity();
    void node_check();
    void PYTGuard_detect_hooks();
    void customer_node_valid(std::string lowkey);
}