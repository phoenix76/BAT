#ifndef _WINDOW_INTERFACE_H_
#define _WINDOW_INTERFACE_H_

#include <Windows.h>
#include <string>
#include <bat_platform.h>
#include <bat_types.h>

namespace BAT
{
	enum BAT_DLL EMakeWindowResult
	{
		MAKE_WINDOW_SUCCEDED = 0,
		MAKE_WINDOW_ERROR_REGISTER_CLASS,
		MAKE_WINDOW_ERROR_CREATE_WINDOW,
	};

	enum BAT_DLL EWindowMessage
	{
		MESSAGE_NONE = 0,

	};

	class BAT_DLL CWindow
	{
	public:
		CWindow(const std::wstring& name = L"BAT Engine");
		/*-----------------------------------------------------
		Методы для установки первоначальных параметров
		------------------------------------------------------*/

		/*Установка разрешения.*/
		void SetResolution(uint32 width, uint32 height);

		/*Если  fullscreen == true, ширина и высота вычисляются по размерам экрана*/
		void SetScreenMode(bool fulllscreen);

		/*-----------------------------------------------------
		Инициализация и опрос окна
		------------------------------------------------------*/

		/*Создает окно с заданными ранее параметрами.
		Возвращает код ошибки в случае неудачи, либо CREATE_WINDOW_SUSSEDED в случае успеха.*/
		EMakeWindowResult Initialize();

		/*Получает сообщения, если они есть. Возвращает код сообщения в виде EWindowMessage если сообщение есть.
		Если нет, возвращает EWindowMessage::MESSAGE_NONE*/
		EWindowMessage ProcessMessage();
		
		/*Возвращает true или false если окно работает или закрыто соответственно*/
		bool IsRun() const;

		LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		/*-----------------------------------------------------
		Методы смены параметров окна в рантайме
		------------------------------------------------------*/

		/*Переключение из оконного режима в полноэкранный*/
		void WindowedToFullscreen();

		/*Переключение из полноэкранного режима в оконный*/
		void FullscreenToWindowed(uint32 width, uint32 height);

	private:
		/*Регистрирует оконный класс*/
		HRESULT m_RegisterWindowClass();

		/*Создает окно, отображает*/
		HRESULT m_CreateAppWindow();

		/*Устанавливает m_WindowRect и m_ClientRect*/
		void m_SetWindowRects();

		/*Настройки для полноэкранного режима*/
		void m_FullscreenSetup();

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
	BAT_DLL LRESULT  CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

#endif