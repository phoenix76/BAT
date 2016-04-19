#include "window_interface.h"

namespace BAT
{
	CWindow::CWindow(const std::wstring& name)
	{
		m_ClassName = name;
		pWindow = this;
	}

	void CWindow::SetResolution(uint32 width, uint32 height)
	{
		m_WindowWidth =	width;
		m_WindowHeight = height;
	}
	void CWindow::SetScreenMode(bool fullscreen)
	{
		m_Fullscreen = fullscreen;
	}
	EMakeWindowResult CWindow::Initialize()
	{
		m_WindowPosX = (GetSystemMetrics(SM_CXSCREEN) - m_WindowWidth) / 2;
		m_WindowPosY = (GetSystemMetrics(SM_CYSCREEN) - m_WindowHeight) / 2;

		if(FAILED(m_RegisterWindowClass()))
			return MAKE_WINDOW_ERROR_REGISTER_CLASS;
		if(FAILED(m_CreateAppWindow()))
			return MAKE_WINDOW_ERROR_CREATE_WINDOW;
		return MAKE_WINDOW_SUCCEDED;
	}
	EWindowMessage CWindow::ProcessMessage()
	{
		return MESSAGE_NONE;
	}
	bool CWindow::IsRun() const
	{
		return m_IsRunWindow;
	}
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void CWindow::WindowedToFullscreen()
	{
		//m_FullscreenSetup();
		m_Fullscreen = true;
	}
	void CWindow::FullscreenToWindowed(uint32 width, uint32 height)
	{

	}
	HRESULT CWindow::m_RegisterWindowClass()
	{
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hInstance = m_HInstance;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = m_ClassName.c_str();
		wc.lpszMenuName = NULL;
		wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor = NULL;
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		if(!RegisterClassEx(&wc))
			return E_FAIL;
		return S_OK;
	}
	HRESULT CWindow::m_CreateAppWindow()
	{
		if(m_Fullscreen)
		{

		}
		else
		{
			m_HWnd = CreateWindowEx(WS_EX_APPWINDOW, m_ClassName.c_str(), m_ClassName.c_str(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, m_WindowPosX, m_WindowPosY,
				m_WindowWidth, m_WindowHeight, NULL, NULL, m_HInstance, NULL);
			if(m_HWnd)
			{
				//FOR TEST ONLY!!!
				SetCursor(LoadCursor(NULL, IDC_ARROW));
				ShowWindow(m_HWnd, SW_SHOW);
				SetForegroundWindow(m_HWnd);
				SetFocus(m_HWnd);
				return S_OK;
			}
			else
				return E_FAIL;
		}
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return pWindow->MessageHandler(hWnd, msg, wParam, lParam);
	}
}