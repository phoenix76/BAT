#ifndef _BAT_INPUT_MGR_H
#define _BAT_INPUT_MGR_H

#define INITGUID
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include <bat_window_api.h>
#include <bat_types.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace BAT
{
	enum EMouseParams
	{
		MP_LBUTTON = 0,
		MP_MBUTTON = 2,
		MP_RBUTTON = 1,
		MP_CURPOS =	 3,
		MP_MWHEEL =  4
	};

	class CInputManager
	{
	public:
		CInputManager() {}

		bool InitializeInputSystem(HWND hWnd, HINSTANCE hInstance);

		void UpdateInput(int32 w, int32 h);

		bool GetKeyState(DWORD code);

		bool GetMouseState(EMouseParams param);
		void GetMouseState(EMouseParams param, int32& x, int32& y);
		void GetMouseState(EMouseParams param, int32& wheel);

		void Shutdown();
	private:
		HRESULT m_InitializeKeyboard(HWND hwnd);
		HRESULT m_InitializeMouse(HWND hwnd);

	public:
		IDirectInput8*			m_pDIInterface;
		IDirectInputDevice8*	m_pKeyboard;
		IDirectInputDevice8*	m_pMouse;

		DIMOUSESTATE m_MouseState;
		unsigned char m_Keys[256];
		int32 m_xCurPos, m_yCurPos;

	};

}

#endif