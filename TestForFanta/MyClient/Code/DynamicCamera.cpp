#include "pch.h"
#include "../Header/DynamicCamera.h"
#include "Export_System.h"

CDynamicCamera::CDynamicCamera(LPDIRECT3DDEVICE9 pGraphicDev) : CCamera(pGraphicDev), m_bFix(true), m_bCheck(false)
{
}

CDynamicCamera::~CDynamicCamera()
{
}

HRESULT CDynamicCamera::Ready_GameObject(const _vec3* pEye, const _vec3* pAt, const _vec3* pUp, const _float& fFov, const _float& fAspect, const _float& fNear, const _float& fFar)
{
	m_vEye = *pEye;
	m_vAt = *pAt;
	m_vUp = *pUp;

	m_fFov = fFov;
	m_fAspect = fAspect;
	m_fNear = fNear;
	m_fFar = fFar;

	FAILED_CHECK_RETURN(CCamera::Ready_GameObject(), E_FAIL)

	return S_OK;
}

_int CDynamicCamera::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CCamera::Update_GameObject(fTimeDelta);
	Key_Input(fTimeDelta);

	return iExit;
}

void CDynamicCamera::LateUpdate_GameObject()
{
	if (m_bFix == false)
	{
		Mouse_Fix();
		Mouse_Move();
	}
	CCamera::LateUpdate_GameObject();
}

void CDynamicCamera::Key_Input(const _float& fTimeDelta)
{
	_matrix matWorld;
	D3DXMatrixInverse(&matWorld, 0, &m_matView);

	if (Engine::Get_DIKeyState(DIK_W) & 0x80)
	{
		_vec3 vLook;
		memcpy(&vLook, &matWorld.m[2][0], sizeof(_vec3));

		_vec3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * fTimeDelta * 5.f; //fSpeed;

		m_vEye += vLength;
		m_vAt += vLength;
	}
	if (Engine::Get_DIKeyState(DIK_S) & 0x80)
	{
		_vec3 vLook;
		memcpy(&vLook, &matWorld.m[2][0], sizeof(_vec3));

		_vec3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * fTimeDelta * 5.f; //fSpeed;

		m_vEye -= vLength;
		m_vAt -= vLength;
	}
	if (Engine::Get_DIKeyState(DIK_D) & 0x80)
	{
		_vec3 vRight;
		memcpy(&vRight, &matWorld.m[0][0], sizeof(_vec3));

		_vec3 vLength = *D3DXVec3Normalize(&vRight, &vRight) * fTimeDelta * 5.f; //fSpeed;

		m_vEye += vLength;
		m_vAt += vLength;
	}
	if (Engine::Get_DIKeyState(DIK_A) & 0x80)
	{
		_vec3 vRight;
		memcpy(&vRight, &matWorld.m[0][0], sizeof(_vec3));

		_vec3 vLength = *D3DXVec3Normalize(&vRight, &vRight) * fTimeDelta * 5.f; //fSpeed;

		m_vEye -= vLength;
		m_vAt -= vLength;
	}
	if (Engine::Get_DIKeyState(DIK_TAB) & 0x80)
	{
		ShowCursor(m_bFix);

		if (m_bCheck)
			return;

		m_bCheck = true;


		if (m_bFix)
			m_bFix = false;
		else
			m_bFix = true;
	}
	else
		m_bCheck = false;

	if (false == m_bFix)
		return;
}

void CDynamicCamera::Mouse_Move()
{
	_matrix matWorld;
	D3DXMatrixInverse(&matWorld, 0, &m_matView);
	_long dwMouseMove(0);

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
	{
		_vec3 vRight;
		memcpy(&vRight, &matWorld.m[0][0], sizeof(_vec3));

		_vec3 vLook = m_vAt - m_vEye;

		_matrix matRot;
		D3DXMatrixRotationAxis(&matRot, &vRight, D3DXToRadian(dwMouseMove / 10.f));
		D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

		m_vAt = m_vEye + vLook;
	}
	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
	{
		_vec3 vUp = {0.f, 1.f, 0.f};

		_vec3 vLook = m_vAt - m_vEye;

		_matrix matRot;
		D3DXMatrixRotationAxis(&matRot, &vUp, D3DXToRadian(dwMouseMove / 10.f));
		D3DXVec3TransformNormal(&vLook, &vLook, &matRot);

		m_vAt = m_vEye + vLook;
	}
}

void CDynamicCamera::Mouse_Fix()
{
	POINT pt{WINCX >> 1, WINCY >> 1};
	ClientToScreen(g_hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
}

CDynamicCamera* CDynamicCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3* pEye, const _vec3* pAt, const _vec3* pUp, const _float& fFov, const _float& fAspect, const _float& fNear, const _float& fFar)
{
	CDynamicCamera* pCamera = new CDynamicCamera(pGraphicDev);
	if (FAILED(pCamera->Ready_GameObject(pEye, pAt, pUp, fFov, fAspect, fNear, fFar)))
	{
		Safe_Release(pCamera);
		MSG_BOX("DynamicCamera Create Failed");
		return nullptr;
	}
	return pCamera;
}

void CDynamicCamera::Free()
{
	CCamera::Free();
}
