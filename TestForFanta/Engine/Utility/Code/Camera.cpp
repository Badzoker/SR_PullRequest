#include "../../Header/Camera.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev) : Engine::CGameObject(pGraphicDev), m_fAspect(0.f), m_fFar(0.f), m_fFov(0.f), m_fNear(0.f)
{
	m_vAt = { 0.f, 0.f, 0.f };
	m_vUp = { 0.f, 0.f, 0.f };
	m_vEye = { 0.f, 0.f, 0.f };

	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matView);
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_GameObject()
{
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFov, m_fAspect, m_fNear, m_fFar);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

_int CCamera::Update_GameObject(const _float& fTimeDleta)
{
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	return 0;
}

void CCamera::LateUpdate_GameObject()
{
}

void CCamera::Free()
{
	CGameObject::Free();
}
