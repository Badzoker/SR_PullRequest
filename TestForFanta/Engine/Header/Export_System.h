#pragma once

#include "GraphicDev.h"
#include "TimerManager.h"
#include "FrameManager.h"
#include "FontManager.h"
#include "InputDev.h"

BEGIN(Engine)

//GraphicDev
inline HRESULT Ready_GraphicDev(HWND _hWnd, WINMODE _eMode, const _uint& _iSizeX, const _uint& _iSizeY, CGraphicDev** _ppGraphicDev);
inline void Render_Begin(D3DXCOLOR _Color);
inline void Render_End();

//TimerManager
inline _float Get_TimeDelta(const _tchar* pTimerTag);
inline void Set_TimeDelta(const _tchar* pTimerTag);
inline HRESULT Ready_Timer(const _tchar* pTimerTag);

//FrameManager
inline HRESULT Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);
inline _bool IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);

//FontManager
inline HRESULT Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFontTag, const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight);
inline void Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color);

//InputDev
inline _byte Get_DIKeyState(_ubyte byKeyID);
inline _byte Get_DIMouseState(MOUSEKEYSTATE eMouseKeyState);
inline _long Get_DIMouseMove(MOUSEMOVESTATE eMouseMoveState);
inline HRESULT Ready_InputDev(HINSTANCE hInst, HWND hWnd);
inline void Update_InputDev(void);

inline void Release_System();

#include "Export_System.inl"

END