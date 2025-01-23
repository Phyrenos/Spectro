#include "Overlay.h"
#include "../ext/Spoofcall/spoofer.h"
LONG MenuStyle = WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST;
LONG ESPStyle = WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST;

ID3D11Device* g_pd3dDevice = NULL;
ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
IDXGISwapChain* g_pSwapChain = NULL;
ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
bool CreateDeviceD3D(HWND hWnd);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool Overlay::CreateOverlay()
{
    SPOOF_FUNC;
    // Get ClientSize
    GetClientRect(g.GameHwnd, &g.GameRect);
    ClientToScreen(g.GameHwnd, &g.GamePoint);

    // Create Overlay
    wc = { sizeof(WNDCLASSEXA), 0, WndProc, 0, 0, NULL, NULL, NULL, NULL, Title, Class, NULL};
    RegisterClassExA(&wc);
    Hwnd = CreateWindowExA(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_TOPMOST, wc.lpszClassName, wc.lpszMenuName, WS_POPUP | WS_VISIBLE, g.GamePoint.x, g.GamePoint.y, g.GameRect.right, g.GameRect.bottom, NULL, NULL, wc.hInstance, NULL);
    SetLayeredWindowAttributes(Hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
    MARGINS margin = { -1 };
    DwmExtendFrameIntoClientArea(Hwnd, &margin);

    if (!CreateDeviceD3D(Hwnd))
    {
        CleanupDeviceD3D();
        UnregisterClassA(wc.lpszClassName, wc.hInstance);
        
        return false;
    }

    ShowWindow(Hwnd, SW_SHOWDEFAULT);
    UpdateWindow(Hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    InitFonts();
    UIStyle();
   
    ImGui_ImplWin32_Init(Hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    return true;
}

void Overlay::DestroyOverlay()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(Hwnd);
    UnregisterClassA(wc.lpszClassName, wc.hInstance);
}

void Overlay::OverlayManager()
{
    SPOOF_FUNC;
    while (g.Run)
    {
        
        // Window Check
        HWND CheckHwnd = FindWindowA("grcWindow", nullptr);
        if (!CheckHwnd)
        {
            g.Run = false;
            break;
        }

        // StreamProof
        DWORD Flag = NULL;
        GetWindowDisplayAffinity(Hwnd, &Flag);
        if (g.StreamProof && Flag == WDA_NONE) {
            SetWindowDisplayAffinity(Hwnd, WDA_EXCLUDEFROMCAPTURE);
        }
        else if (!g.StreamProof && Flag == WDA_EXCLUDEFROMCAPTURE) {
            SetWindowDisplayAffinity(Hwnd, WDA_NONE);
        }

        // WindowStyle Changer
        LONG TmpLong = GetWindowLong(Hwnd, GWL_EXSTYLE);

        if (g.ShowMenu && MenuStyle != TmpLong)
            SetWindowLong(Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
        else if (!g.ShowMenu && ESPStyle != TmpLong)
            SetWindowLong(Hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
        
        // ShowMenu
        static bool menu_key = false;
        if (IsKeyDown(g.MenuKey) && !menu_key)
        {
            g.ShowMenu = !g.ShowMenu;
            menu_key = true;
        }
        else if (!IsKeyDown(g.MenuKey) && menu_key)
        {
            menu_key = false;
        }

        // Window Resizer
        RECT TmpRect{};
        POINT TmpPoint{};
        GetClientRect(CheckHwnd, &TmpRect);
        ClientToScreen(CheckHwnd, &TmpPoint);

        // Resizer
        if (TmpRect.left != g.GameRect.left || TmpRect.bottom != g.GameRect.bottom || TmpRect.top != g.GameRect.top || TmpRect.right != g.GameRect.right || TmpPoint.x != g.GamePoint.x || TmpPoint.y != g.GamePoint.y)
        {
            g.GameRect  = TmpRect;
            g.GamePoint = TmpPoint;
            SetWindowPos(Hwnd, nullptr, TmpPoint.x, TmpPoint.y, g.GameRect.right, g.GameRect.bottom, SWP_NOREDRAW);
        }

        Sleep(2);
    }
}


ImFont* TopBarTitle = nullptr;
ImFont* MenuTitles = nullptr;
ImFont* ModuleText = nullptr;
void Overlay::InitFonts()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;


    io.Fonts->AddFontDefault();


    //Change On Build

    TopBarTitle = io.Fonts->AddFontFromFileTTF("Fonts\\Inter.ttf", 30.f);
    IM_ASSERT(TopBarTitle != nullptr);
    MenuTitles = io.Fonts->AddFontFromFileTTF("Fonts\\Inter.ttf", 20.f);
    IM_ASSERT(MenuTitles != nullptr);
    ModuleText = io.Fonts->AddFontFromFileTTF("Fonts\\Inter.ttf", 10.f);
    IM_ASSERT(ModuleText != nullptr);



    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
}

void Overlay::UIStyle()
{

    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 15.0f;
    style.FrameRounding = 5.0f;
    style.ChildRounding = 5.0f;
    style.PopupRounding = 5.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 3.0f;
    style.FrameBorderSize = 1.0f;
}



void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
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
    SPOOF_FUNC;
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

bool CreateDeviceD3D(HWND hWnd)
{
    SPOOF_FUNC;
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

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    SPOOF_FUNC;
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
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}