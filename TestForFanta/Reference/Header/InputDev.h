#pragma once
#include "Base.h"
#include "Engine_Define.h"

#ifndef InputDev_h__
#define InputDev_h__

BEGIN(Engine)

class ENGINE_DLL CInputDev : public CBase
{
	DECLARE_SINGLETON(CInputDev)
private:
	explicit CInputDev(void);
	virtual ~CInputDev(void);

public:
	_byte Get_DIKeyState(_ubyte byKeyID)
	{
		return m_byKeyState[byKeyID];
	}
	_byte Get_DIMouseState(MOUSEKEYSTATE eMouseKeyState)
	{
		return m_tMouseState.rgbButtons[eMouseKeyState];
	}
	_long Get_DIMouseMove(MOUSEMOVESTATE eMouseMoveState)
	{
		return *(((_long*)&m_tMouseState) + eMouseMoveState);
	}

public:
	HRESULT Ready_InputDev(HINSTANCE hInst, HWND hWnd);
	void Update_InputDev(void);

private:
	LPDIRECTINPUT8 m_pInputSDK = nullptr;

	LPDIRECTINPUTDEVICE8 m_pKeyBoard = nullptr;
	LPDIRECTINPUTDEVICE8 m_pMouse = nullptr;

	_byte m_byKeyState[256];
	DIMOUSESTATE m_tMouseState;

public:
	virtual void Free(void);

};

END


#endif // InputDev_h__