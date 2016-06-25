#ifndef BAT_WINDOW_H
#define BAT_WINDOW_H

#include <Windows.h>
#include <string>
#include <bat_sys_macroses.h>
#include <bat_typedefs.h>

namespace BAT_ENGINE
{
	enum EWindowCreateResult
	{
		WINDOW_CREATE_RESULT_ERROR_REG_CLASS,
		WINDOW_CREATE_RESULT_ERROR_CREATE_WND,
		WINDOW_CREATE_RESULT_SUCCEEDED
	};

	class DLLEXP CMainWindow
	{
	public:
		CMainWindow();
		bool IsRun() { return m_IsRun; }
		LRESULT CALLBACK WindowHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:
		EWindowCreateResult CreateAppWindow();
		void SetupWindow(bool fullscreen, const std::wstring& titleName, uint32 width = 0U, uint32 height = 0U);

	private:
		HINSTANCE m_hInstance;
		HWND m_hWnd;

		bool m_Fullscreen;
		uint32 m_Width;
		uint32 m_Height;
		std::wstring m_TitleName;

		bool m_IsRun;
	};

	CMainWindow* window;
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return window->WindowHandler(hwnd, msg, wParam, lParam);
	}
}

#endif