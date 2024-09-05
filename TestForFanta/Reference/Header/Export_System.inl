HRESULT Ready_GraphicDev(HWND _hWnd, WINMODE _eMode, const _uint& _iSizeX, const _uint& _iSizeY, CGraphicDev** _ppGraphicDev)
{
	return CGraphicDev::GetInstance()->Ready_GraphicDev(_hWnd, _eMode, _iSizeX, _iSizeY, _ppGraphicDev);
}

void Render_Begin(D3DXCOLOR _Color)
{
	CGraphicDev::GetInstance()->Render_Begin(_Color);
}

void Render_End()
{
	CGraphicDev::GetInstance()->Render_End();
}

_float Get_TimeDelta(const _tchar* pTimerTag)
{
	return CTimerManager::GetInstance()->Get_TimeDelta(pTimerTag);
}

void Set_TimeDelta(const _tchar* pTimerTag)
{
	CTimerManager::GetInstance()->Set_TimeDelta(pTimerTag);
}

HRESULT Ready_Timer(const _tchar* pTimerTag)
{
	return CTimerManager::GetInstance()->Ready_Timer(pTimerTag);
}

HRESULT Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit)
{
	return CFrameManager::GetInstance()->Ready_Frame(pFrameTag, fCallLimit);
}

_bool IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta)
{
	return CFrameManager::GetInstance()->IsPermit_Call(pFrameTag, fTimeDelta);
}

HRESULT Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFontTag, const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight)
{
	return CFontManager::GetInstance()->Ready_Font(pGraphicDev, pFontTag, pFontType, iWidth, iHeight, iWeight);
}

void Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color)
{
	CFontManager::GetInstance()->Render_Font(pFontTag, pString, pPos, Color);
}

_byte Get_DIKeyState(_ubyte byKeyID)
{
	return CInputDev::GetInstance()->Get_DIKeyState(byKeyID);
}

_byte Get_DIMouseState(MOUSEKEYSTATE eMouseKeyState)
{
	return CInputDev::GetInstance()->Get_DIMouseState(eMouseKeyState);
}

_long Get_DIMouseMove(MOUSEMOVESTATE eMouseMoveState)
{
	return CInputDev::GetInstance()->Get_DIMouseMove(eMouseMoveState);
}

HRESULT Ready_InputDev(HINSTANCE hInst, HWND hWnd)
{
	return CInputDev::GetInstance()->Ready_InputDev(hInst, hWnd);
}

void Update_InputDev(void)
{
	CInputDev::GetInstance()->Update_InputDev();
}


void Release_System()
{
	CGraphicDev::GetInstance()->DestroyInstance();
	CTimerManager::GetInstance()->DestroyInstance();
	CFrameManager::GetInstance()->DestroyInstance();
	CInputDev::GetInstance()->DestroyInstance();
	CFontManager::GetInstance()->DestroyInstance();
}