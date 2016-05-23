#include <bat_input_mgr.h>
#include <bat_memory.h>

namespace BAT
{
	bool CInputManager::InitializeInputSystem(HWND hWnd, HINSTANCE hInstance)
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
	void CInputManager::UpdateInput(int32 x, int32 y)
	{
		m_pKeyboard->Poll();
		m_pKeyboard->GetDeviceState(sizeof(m_Keys), (LPVOID)&m_Keys);
		m_pMouse->Poll();
		m_pMouse->GetDeviceState(sizeof(m_MouseState), (LPVOID)&m_MouseState);
		m_xCurPos = x;
		m_yCurPos = y;
	}
	bool CInputManager::GetKeyState(DWORD key)
	{
		return (m_Keys[key] & 0x80) ? true : false;
	}
	bool CInputManager::GetMouseState(EMouseParams param)
	{
		return (m_MouseState.rgbButtons[(int)param] & 0x80) ? true : false;
	}
	void CInputManager::GetMouseState(EMouseParams param, int32& x, int32& y)
	{
		if(param == MP_CURPOS)
		{
			x = m_xCurPos;
			y = m_yCurPos;
		}
	}
	void CInputManager::GetMouseState(EMouseParams param, int32& wheel)
	{
		if(param == MP_MWHEEL)
			wheel = m_MouseState.lZ;
	}
	void CInputManager::Shutdown()
	{
		m_pKeyboard->Unacquire();
		m_pMouse->Unacquire();
		m_pKeyboard->Release();
		m_pMouse->Release();
		m_pDIInterface->Release();
	}
	HRESULT CInputManager::m_InitializeKeyboard(HWND hwnd)
	{

		HRESULT result;
		result = m_pDIInterface->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
		if(FAILED(result))
			return E_FAIL;

		result = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(result))
		{
			m_pKeyboard->Release();
			return E_FAIL;
		}

		result = m_pKeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
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
	HRESULT CInputManager::m_InitializeMouse(HWND hwnd)
	{
		HRESULT result;
		result = m_pDIInterface->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
		if(FAILED(result))
			return E_FAIL;

		result = m_pMouse->SetDataFormat(&c_dfDIMouse);
		if(FAILED(result))
		{
			m_pMouse->Release();
			return E_FAIL;
		}

		result = m_pMouse->SetCooperativeLevel(hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(result))
		{
			m_pMouse->Release();
			return E_FAIL;
		}

		result = m_pMouse->Acquire();
		if(FAILED(result))
		{
			m_pMouse->Release();
			return E_FAIL;
		}

		return S_OK;
	}
}