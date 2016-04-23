#include <bat_window_api.h>

namespace BAT
{
	CWindow::CWindow() { pWindow = this; }
	bool CWindow::InitializeWindow(const std::wstring& windowName, HCURSOR cursor, ECreateWindowConfiguration config, uint32 width, uint32 height)
	{
		m_HInstance = GetModuleHandle(NULL);
		m_ClassName = windowName;
		m_HCursor = cursor;
		if(config == WC_CREATE_WINDOW_CONFIG_1)
		{
			m_WindowWidth = 640U;
			m_WindowHeight = 480U;
		}
		else if(config == WC_CREATE_WINDOW_CONFIG_2)
		{
			m_WindowWidth = 800U;
			m_WindowHeight = 600U;
		}
		else if(config == WC_CREATE_WINDOW_CONFIG_3)
		{
			m_WindowWidth = 1920U;
			m_WindowHeight = 1080U;
		}
		else if(config == WC_CREATE_WINDOW_WITH_USER_SETTINGS)
		{
			m_WindowWidth = width;
			m_WindowHeight = height;
		}
		else if(config == WC_CREATE_WINDOW_FULLSCREEN)
		{
			m_WindowWidth = GetSystemMetrics(SM_CXSCREEN);
			m_WindowHeight = GetSystemMetrics(SM_CYSCREEN);
			m_WindowPosX = m_WindowPosY = 0U;
			m_Fullscreen = true;
		}
		if(config != WC_CREATE_WINDOW_FULLSCREEN)
		{
			m_WindowPosX = (GetSystemMetrics(SM_CXSCREEN) - m_WindowWidth) / 2;
			m_WindowPosY = (GetSystemMetrics(SM_CYSCREEN) - m_WindowHeight) / 2;
		}

		if(FAILED(m_RegisterWindowClass()))
			return false;
		if(FAILED(m_CreateAppWindow()))
			return false;

		SetCursor(m_HCursor);
		return true;
	}
	
	MSG CWindow::ProcessMessage()
	{
		MSG msg;
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg;
	}
	bool CWindow::IsRun() const
	{
		return m_IsRunWindow;
	}
	void CWindow::ChangeCursor(HCURSOR cursor)
	{
		m_HCursor = cursor;
		SetCursor(m_HCursor);
	}

	void CWindow::ShowAppCursor()
	{
		while(ShowCursor(TRUE) < 0);
		m_VisibleCursor = true;
	}
	void CWindow::HideAppCursor()
	{
		while(ShowCursor(FALSE) >= 0);
		m_VisibleCursor = false;
	}

	HWND& CWindow::GetHWND()			{ return m_HWnd; }
	uint8 CWindow::GetWidth() const		{ return m_WindowWidth; }
	uint8 CWindow::GetHeight() const	{ return m_WindowHeight; }
	uint8 CWindow::GetXPos() const		{ return m_WindowPosX; }
	uint8 CWindow::GetYPos() const		{ return m_WindowPosY; }

	POINT CWindow::GetMouseCoordinates() const
	{
		POINT pt;
		pt.x = m_CurPosX;
		pt.y = m_CurPosY;
		return pt;
	}

	void CWindow::SystemAlert(const wchar_t* msg, const wchar_t* head)
	{
		MessageBox(NULL, msg, head, MB_OK);
	}

	LRESULT CALLBACK CWindow::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_CLOSE:
			m_IsRunWindow = false;
			return 0;

		case WM_MOUSEMOVE:
			m_UpdateCursorCoordinates();
			if(m_HCursor != GetCursor())
				SetCursor(m_HCursor);
			return 0;

		case WM_MOVE:
		case WM_SIZE:
			GetClientRect(m_HWnd, &m_WindowRect);
			m_WindowPosX = m_WindowRect.left;
			m_WindowPosY = m_WindowRect.top;
			return 0;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		
	}
	void CWindow::Stop()
	{
		m_IsRunWindow = false;
	}
	void CWindow::Shutdown()
	{
		PostQuitMessage(0);
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
				m_WindowPosX, m_WindowPosY, m_WindowWidth, m_WindowHeight, NULL, NULL, m_HInstance, NULL);
			if(m_HWnd)
			{
				ShowWindow(m_HWnd, SW_SHOW);
				SetForegroundWindow(m_HWnd);
				SetFocus(m_HWnd);
				m_IsRunWindow = true;
				GetWindowRect(m_HWnd, &m_WindowRect);
				m_UpdateCursorCoordinates();
				m_VisibleCursor = true;
				return S_OK;
			}
		}
		else
		{
			m_HWnd = CreateWindowEx(WS_EX_APPWINDOW, m_ClassName.c_str(), m_ClassName.c_str(), WS_OVERLAPPEDWINDOW, m_WindowPosX, m_WindowPosY,
				m_WindowWidth, m_WindowHeight, NULL, NULL, m_HInstance, NULL);
			if(m_HWnd)
			{
				ShowWindow(m_HWnd, SW_SHOW);
				SetForegroundWindow(m_HWnd);
				SetFocus(m_HWnd);
				m_IsRunWindow = true;
				GetWindowRect(m_HWnd, &m_WindowRect);
				m_UpdateCursorCoordinates();
				m_VisibleCursor = true;
				return S_OK;
			}
		}
		return E_FAIL;
	}
	void CWindow::m_UpdateCursorCoordinates()
	{
		POINT pt;
		GetCursorPos(&pt);
		m_CurPosX = pt.x - m_WindowPosX;
		m_CurPosY = pt.y - m_WindowPosY;
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return pWindow->MessageHandler(hWnd, msg, wParam, lParam);
	}
}