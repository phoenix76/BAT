#ifndef _WINDOW_INTERFACE_H_
#define _WINDOW_INTERFACE_H_

#include <Windows.h>
#include <string>
#include <bat_platform.h>
#include <bat_types.h>

namespace BAT
{
	enum EMakeWindowResult
	{
		MAKE_WINDOW_SUCCEDED = 0,
		MAKE_WINDOW_ERROR_REGISTER_CLASS,
		MAKE_WINDOW_ERROR_CREATE_WINDOW,
	};

	enum EWindowMessage
	{
		MESSAGE_NONE = 0,

	};

	class CWindow
	{
	public:
		CWindow(const std::wstring& name = L"BAT Engine");
		/*-----------------------------------------------------
		Методы для установки первоначальных параметров
		------------------------------------------------------*/

		void SetResolution(uint32 width, uint32 height);
		void SetScreenMode(bool fulllscreen);

		/*Создает окно с заданными ранее параметрами.
		Возвращает код ошибки в случае неудачи, либо CREATE_WINDOW_SUSSEDED в случае успеха.*/
		EMakeWindowResult Initialize();

		/*Получает сообщения, если они есть. Возвращает код сообщения в виде EWindowMessage если сообщение есть.
		Если нет, возвращает EWindowMessage::MESSAGE_NONE*/
		UINT ProcessMessage();

		bool IsRun() const;

		LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
		bool m_Fullscreen;

		uint32 m_WindowWidth;
		uint32 m_WindowHeight;
		uint32 m_ScreenWidth;
		uint32 m_ScreenHeight;

		uint32 m_WindowPosX;
		uint32 m_WindowPosY;
		uint32 m_CurPosX;
		uint32 m_CurPosY;

		RECT m_WindowRect;
		RECT m_ClientRect;
	};

	static CWindow* pWindow;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

#endif