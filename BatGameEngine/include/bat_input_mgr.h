#ifndef _BAT_INPUT_MGR_H
#define _BAT_INPUT_MGR_H

#define INITGUID
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include <bat_types.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace BAT
{

	class CInputManager
	{
	public:
		CInputManager() {}

		bool InitializeInputSystem(HWND& hWnd, HINSTANCE& hInstance);

		void UpdateInput();

		bool GetKeyState(DWORD code);

		void Shutdown();
	private:
		HRESULT m_InitializeKeyboard(HWND& hwnd);
		HRESULT m_InitializeMouse(HWND& hwnd);

	public:
		IDirectInput8*			m_pDIInterface;
		IDirectInputDevice8*	m_pKeyboard;
		IDirectInputDevice8*	m_pMouse;

		unsigned char m_keys[256];


	};

}

#endif