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
		������ ��� ��������� �������������� ����������
		------------------------------------------------------*/

		/*��������� ����������.*/
		void SetResolution(uint32 width, uint32 height);

		/*����  fullscreen == true, ������ � ������ ����������� �� �������� ������*/
		void SetScreenMode(bool fulllscreen);

		/*-----------------------------------------------------
		������������� � ����� ����
		------------------------------------------------------*/

		/*������� ���� � ��������� ����� �����������.
		���������� ��� ������ � ������ �������, ���� CREATE_WINDOW_SUSSEDED � ������ ������.*/
		EMakeWindowResult Initialize();

		/*�������� ���������, ���� ��� ����. ���������� ��� ��������� � ���� EWindowMessage ���� ��������� ����.
		���� ���, ���������� EWindowMessage::MESSAGE_NONE*/
		EWindowMessage ProcessMessage();
		
		/*���������� true ��� false ���� ���� �������� ��� ������� ��������������*/
		bool IsRun() const;

		LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		/*-----------------------------------------------------
		������ ����� ���������� ���� � ��������
		------------------------------------------------------*/

		/*������������ �� �������� ������ � �������������*/
		void WindowedToFullscreen();

		/*������������ �� �������������� ������ � �������*/
		void FullscreenToWindowed(uint32 width, uint32 height);

	private:
		/*������������ ������� �����*/
		HRESULT m_RegisterWindowClass();

		/*������� ����, ����������*/
		HRESULT m_CreateAppWindow();

		/*������������� m_WindowRect � m_ClientRect*/
		void m_SetWindowRects();

		/*��������� ��� �������������� ������*/
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