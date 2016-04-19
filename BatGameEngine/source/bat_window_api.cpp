#include <bat_window_api.h>

namespace BAT
{
	CWindow::CWindow(const std::wstring& name)
	{
		m_ClassName = name;
		pWindow = this;
	}

	void CWindow::SetResolution(uint32 width, uint32 height)
	{
		m_WindowWidth = width;
		m_WindowHeight = height;
	}
	void CWindow::SetScreenMode(bool fullscreen)
	{
		m_Fullscreen = fullscreen;
	}
	EMakeWindowResult CWindow::Initialize()
	{
		m_HInstance = GetModuleHandle(NULL);
		if(!m_Fullscreen)
		{
			m_WindowPosX = (GetSystemMetrics(SM_CXSCREEN) - m_WindowWidth) / 2;
			m_WindowPosY = (GetSystemMetrics(SM_CYSCREEN) - m_WindowHeight) / 2;
		}
		else
		{
			m_WindowWidth = m_ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
			m_WindowHeight = m_ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
			m_WindowPosX = m_WindowPosY = 0;
		}
		m_HCursor = LoadCursor(NULL, IDC_ARROW);

		if(FAILED(m_RegisterWindowClass()))
			return MAKE_WINDOW_ERROR_REGISTER_CLASS;
		if(FAILED(m_CreateAppWindow()))
			return MAKE_WINDOW_ERROR_CREATE_WINDOW;

		return MAKE_WINDOW_SUCCEDED;
	}
	UINT CWindow::ProcessMessage()
	{
		MSG msg;
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg.message;
	}
	bool CWindow::IsRun() const
	{
		return m_IsRunWindow;
	}
	LRESULT CALLBACK CWindow::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_CLOSE:
			m_IsRunWindow = false;
			return 0;

		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
				m_IsRunWindow = false;
			MessageBox(NULL, L"Msg", L"msg", MB_OK);
			return 0;

		case WM_MOUSEMOVE:
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(m_HWnd, &pt);
			m_CurPosX = pt.x;
			m_CurPosY = pt.y;
			return 0;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		
	}
	void CWindow::Shutdown()
	{
		if(m_Fullscreen)
			ChangeDisplaySettings(NULL, 0);
		DestroyWindow(m_HWnd);
		UnregisterClass(m_ClassName.c_str(), m_HInstance);
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
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (unsigned long)m_WindowWidth;
			dmScreenSettings.dmPelsHeight = (unsigned long)m_WindowHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
			m_HWnd = CreateWindowEx(WS_EX_APPWINDOW, m_ClassName.c_str(), m_ClassName.c_str(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
				m_WindowPosX, m_WindowPosY, m_ScreenWidth, m_ScreenHeight, NULL, NULL, m_HInstance, NULL);
			if(m_HWnd)
			{
				//FOR TEST ONLY!!!
				SetCursor(m_HCursor);
				ShowWindow(m_HWnd, SW_SHOW);
				SetForegroundWindow(m_HWnd);
				SetFocus(m_HWnd);
				m_IsRunWindow = true;
				m_SetWindowRects();
				return S_OK;
			}
		}
		else
		{
			m_HWnd = CreateWindowEx(WS_EX_APPWINDOW, m_ClassName.c_str(), m_ClassName.c_str(), WS_OVERLAPPEDWINDOW, m_WindowPosX, m_WindowPosY,
				m_WindowWidth, m_WindowHeight, NULL, NULL, m_HInstance, NULL);
			if(m_HWnd)
			{
				//FOR TEST ONLY!!!
				SetCursor(m_HCursor);
				ShowWindow(m_HWnd, SW_SHOW);
				SetForegroundWindow(m_HWnd);
				SetFocus(m_HWnd);
				m_IsRunWindow = true;
				m_SetWindowRects();
				return S_OK;
			}
		}
		return E_FAIL;
	}
	void CWindow::m_SetWindowRects()
	{
		GetWindowRect(m_HWnd, &m_WindowRect);
		GetClientRect(m_HWnd, &m_ClientRect);
	}
	void CWindow::m_UpdateCursorCoordinates()
	{
		
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return pWindow->MessageHandler(hWnd, msg, wParam, lParam);
	}
}