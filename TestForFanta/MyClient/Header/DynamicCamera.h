#pragma once
#include "Camera.h"
#include "Define.h"

class CDynamicCamera : public CCamera
{
private:
	explicit CDynamicCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CDynamicCamera();

public:
	virtual HRESULT Ready_GameObject(const _vec3* pEye, const _vec3* pAt, const _vec3* pUp, const _float& fFov = D3DXToRadian(60.f), const _float& fAspect = (_float)(WINCX / WINCY), const _float& fNear = 0.1f, const _float& fFar = 1000.f);
	virtual _int Update_GameObject(const _float& fTimeDelta);
	virtual void LateUpdate_GameObject();
	virtual void Render_GameObject() {}

private:
	void Key_Input(const _float& fTimeDelta);
	void Mouse_Move();
	void Mouse_Fix();

private:
	_bool m_bFix;
	_bool m_bCheck;

public:
	static CDynamicCamera* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3* pEye, const _vec3* pAt, const _vec3* pUp, const _float& fFov = D3DXToRadian(60.f), const _float& fAspect = (_float)(WINCX / WINCY), const _float& fNear = 0.1f, const _float& fFar = 1000.f);

private:
	virtual void Free();
};

