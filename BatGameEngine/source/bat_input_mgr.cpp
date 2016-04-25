#include <bat_input_mgr.h>
#include <bat_memory.h>

namespace BAT
{
	bool CInputManager::InitializeInputSystem(HWND& hWnd, HINSTANCE& hInstance)
	{
		HRESULT result;
		result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDIInterface, NULL);
		if(FAILED(result))
			return false;

		result = m_InitializeKeyboard(hWnd);
		if(FAILED(result))
			return false;

		result = m_InitializeMouse(hWnd);
		if(FAILED(result))
			return false;

		return true;
	}
	void CInputManager::UpdateInput()
	{
		HRESULT result;
		unsigned char keys[256];
		m_pKeyboard->Poll();
		result = m_pKeyboard->GetDeviceState(sizeof(keys), (LPVOID)&m_keys);
	}
	bool CInputManager::GetKeyState(DWORD key)
	{
		return (m_keys[key] & 0x80) ? true : false;
	}
	void CInputManager::Shutdown()
	{
		m_pKeyboard->Unacquire();
		//m_pMouse->Unacquire();
		_RELEASE(m_pKeyboard);
		//_RELEASE(m_pMouse);
		_RELEASE(m_pDIInterface);
	}
	HRESULT CInputManager::m_InitializeKeyboard(HWND& hwnd)
	{
		DIPROPDWORD dipdw;
		ZeroMemory(&dipdw, sizeof(DIPROPDWORD));
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = (unsigned long)256;

		HRESULT result;
		result = m_pDIInterface->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
		if(FAILED(result))
			return E_FAIL;

		result = m_pKeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
		if(FAILED(result))
		{
			m_pKeyboard->Release();
			return E_FAIL;
		}

		result = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(result))
		{
			m_pKeyboard->Release();
			return E_FAIL;
		}

		result = m_pKeyboard->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(result))
		{
			m_pKeyboard->Release();
			return E_FAIL;
		}

		result = m_pKeyboard->Acquire();
		if(FAILED(result))
		{
			m_pKeyboard->Release();
			return E_FAIL;
		}
		
		return S_OK;
	}
	HRESULT CInputManager::m_InitializeMouse(HWND& hwnd)
	{
		HRESULT result;
		result = m_pDIInterface->CreateDevice(GUID_SysMouse, &m_pKeyboard, NULL);
		if(FAILED(result))
			return E_FAIL;

		result = m_pKeyboard->SetDataFormat(&c_dfDIMouse);
		if(FAILED(result))
		{
			m_pKeyboard->Release();
			return E_FAIL;
		}

		result = m_pKeyboard->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(result))
		{
			m_pKeyboard->Release();
			return E_FAIL;
		}

		result = m_pKeyboard->Acquire();
		if(FAILED(result))
		{
			m_pKeyboard->Release();
			return E_FAIL;
		}

		return S_OK;
	}
}