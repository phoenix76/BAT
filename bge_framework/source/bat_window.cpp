#include <bat_window.h>

namespace BAT_ENGINE
{
	CMainWindow::CMainWindow()
	{
		m_hInstance = GetModuleHandle(NULL);
		window = this;
	}
	LRESULT CALLBACK CMainWindow::WindowHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
		case WM_CLOSE:
			ChangeDisplaySettings(NULL, 0);
			m_IsRun = false;
			return 0;

		case WM_MOUSEMOVE:
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			return 0;

		case WM_MOVE:
		case WM_SIZE:
			return 0;

		default:

		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	EWindowCreateResult CMainWindow::CreateAppWindow()
	{
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hInstance = m_hInstance;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = m_TitleName.c_str();
		wc.lpszMenuName = NULL;
		wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor = NULL;
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		if(!RegisterClassEx(&wc))
			return WINDOW_CREATE_RESULT_ERROR_REG_CLASS;

		if(m_Fullscreen)
		{
			m_Width = GetSystemMetrics(SM_CXSCREEN);
			m_Height = GetSystemMetrics(SM_CYSCREEN);
			uint32 m_WindowPosX = 0U;
			uint32 m_WindowPosY = 0U;

			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (unsigned long)m_Width;
			dmScreenSettings.dmPelsHeight = (unsigned long)m_Height;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
			m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_TitleName.c_str(), m_TitleName.c_str(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
				m_WindowPosX, m_WindowPosY, m_Width, m_Height, NULL, NULL, m_hInstance, NULL);
			if(m_hWnd)
			{
				ShowWindow(m_hWnd, SW_SHOW);
				SetForegroundWindow(m_hWnd);
				SetFocus(m_hWnd);
				m_IsRun = true;
			}
			else
				return WINDOW_CREATE_RESULT_ERROR_CREATE_WND;
		}
		else
		{
			uint32 m_WindowPosX = (GetSystemMetrics(SM_CXSCREEN) - m_Width) / 2;
			uint32 m_WindowPosY = (GetSystemMetrics(SM_CYSCREEN) - m_Height) / 2;
			m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_TitleName.c_str(), m_TitleName.c_str(), WS_OVERLAPPEDWINDOW, m_WindowPosX, m_WindowPosY,
				m_Width, m_Height, NULL, NULL, m_hInstance, NULL);
			if(m_hWnd)
			{
				ShowWindow(m_hWnd, SW_SHOW);
				SetForegroundWindow(m_hWnd);
				SetFocus(m_hWnd);
				m_IsRun = true;
			}
			else
				return WINDOW_CREATE_RESULT_ERROR_CREATE_WND;
		}
		return WINDOW_CREATE_RESULT_SUCCEEDED;
	}
	void CMainWindow::SetupWindow(bool fullscreen, const std::wstring& titleName, uint32 width, uint32 height)
	{
		m_TitleName = titleName;
		m_Width = width;
		m_Height = height;
		m_Fullscreen = fullscreen;
	}
}