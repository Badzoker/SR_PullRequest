#include "../../Header/InputDev.h"

IMPLEMENT_SINGLETON(CInputDev)

Engine::CInputDev::CInputDev(void)
{
    ZeroMemory(m_byKeyState, sizeof(m_byKeyState));
}

Engine::CInputDev::~CInputDev(void)
{
    Free();
}

HRESULT Engine::CInputDev::Ready_InputDev(HINSTANCE hInst, HWND hWnd)
{
    FAILED_CHECK_RETURN(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInputSDK, NULL), E_FAIL);

    FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr), E_FAIL);

    m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

    m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

    m_pKeyBoard->Acquire();

    FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr), E_FAIL);

    m_pMouse->SetDataFormat(&c_dfDIMouse);

    m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

    m_pMouse->Acquire();

    return S_OK;
}

void Engine::CInputDev::Update_InputDev(void)
{
    m_pKeyBoard->GetDeviceState(256, m_byKeyState);
    m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

void Engine::CInputDev::Free(void)
{
    Safe_Release(m_pKeyBoard);
    Safe_Release(m_pMouse);
    Safe_Release(m_pInputSDK);
}
