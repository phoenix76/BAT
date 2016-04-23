#ifndef _WINDOW_INTERFACE_H_
#define _WINDOW_INTERFACE_H_

#include <Windows.h>
#include <string>
#include <bat_platform.h>
#include <bat_types.h>

namespace BAT
{

	enum ECreateWindowConfiguration
	{
		WC_CREATE_WINDOW_CONFIG_1,
		WC_CREATE_WINDOW_CONFIG_2,
		WC_CREATE_WINDOW_CONFIG_3,
		WC_CREATE_WINDOW_FULLSCREEN,
		WC_CREATE_WINDOW_WITH_USER_SETTINGS
	};

	class CWindow
	{
	public:
		CWindow();
		/*”станавливает заголовок окна, курсор, разрешение, опционально ширина и высота, если указана пользовательска€ конфигураци€*/
		bool InitializeWindow(const std::wstring& windowName, HCURSOR cursor, ECreateWindowConfiguration config, uint32 width = 0U, uint32 height = 0U);

		/*ѕолучает сообщени€, если они есть. ¬озвращает MSG дл€ обработки.*/
		MSG ProcessMessage();

		bool IsRun() const;

		void ChangeCursor(HCURSOR newCursor);

		void ShowAppCursor();

		void HideAppCursor();

		HWND& GetHWND();

		uint8 GetWidth() const;
		uint8 GetHeight() const;
		uint8 GetXPos() const;
		uint8 GetYPos() const;

		POINT GetMouseCoordinates() const;

		LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		void SystemAlert(const wchar_t*, const wchar_t*);

		void Stop();

		void Shutdown();

	private:
		HRESULT m_RegisterWindowClass();
		HRESULT m_CreateAppWindow();

		void m_SetWindowRects();
		void m_UpdateCursorCoordinates();

		std::wstring m_ClassName;

		HWND m_HWnd;
		HINSTANCE m_HInstance;
		HCURSOR m_HCursor;

		bool m_IsRunWindow;
		bool m_Fullscreen = false;
		bool m_VisibleCursor;

		uint32 m_WindowWidth;
		uint32 m_WindowHeight;
		uint32 m_ScreenWidth;
		uint32 m_ScreenHeight;

		uint32 m_WindowPosX;
		uint32 m_WindowPosY;
		uint32 m_CurPosX;
		uint32 m_CurPosY;

		RECT m_WindowRect;
	};

	static CWindow* pWindow;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

#endif