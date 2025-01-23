#pragma once
#include "..\ImGui\imgui.h"
#include "..\ImGui\imgui_impl_win32.h"
#include "..\ImGui\imgui_impl_dx11.h"
#include "..\Utils\Globals\Globals.h"
#include <dwmapi.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

class Overlay
{
private:
	// OverlayWindow
	WNDCLASSEXA wc;
	HWND Hwnd;
	char Title[32] = "Spectro-lite";
	char Class[32] = "wnd-class";
	
public:
	bool CreateOverlay();
	void OverlayLoop();
	void DestroyOverlay();
	void OverlayManager();
	void InitFonts();
	void UIStyle();

};

extern ImFont* TopBarTitle;
extern ImFont* MenuTitles;
extern ImFont* ModuleText;
extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pd3dDeviceContext;
extern IDXGISwapChain* g_pSwapChain;
extern ID3D11RenderTargetView* g_mainRenderTargetView;