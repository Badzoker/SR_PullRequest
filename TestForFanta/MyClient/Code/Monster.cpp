#include "pch.h"
#include "../Header/Monster.h"
#include "Export_Utility.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev) : Engine::CGameObject(pGraphicDev)
{
}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->m_vScale = { 1.f, 1.f, 1.f };

	return S_OK;
}

_int CMonster::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

	Engine::CTransform* pPlayerTransform = dynamic_cast<Engine::CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", L"Player", L"Com_PlayerTransform"));
	NULL_CHECK_RETURN(pPlayerTransform, -1);

	_vec3 vPlayerPos;

	pPlayerTransform->Get_Info(INFO_POS, &vPlayerPos);

	m_pTransformCom->Chase_TargetPos(&vPlayerPos, 3.f, fTimeDelta);

	//Key_Input(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_PRIORITY, this);

	return iExit;
}

void CMonster::LateUpdate_GameObject()
{
	Engine::CGameObject::LateUpdate_GameObject();
}

void CMonster::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CMonster::Add_Component()
{
	CComponent* pComponent = NULL;

	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"Proto_MonsterTriCol"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_MonsterBuffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_MonsterTransform", pComponent });

	return S_OK;
}

void CMonster::Key_Input(const _float& fTimeDelta)
{
	
	//CGameObject* pSour = Get_Component()
	//CComponentManager* p;
	//if (GetAsyncKeyState(VK_LEFT))
	//{
	//	_vec3 vPosPlayer(0.f, 0.f, 0.f);
	//	CManagement* pTemp;
	//	Create_Management(m_pGraphicDev, &pTemp);
	//	//CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"Layer_Environment", L"Player", L"Com_PlayerTransform")
	//	CTransform* pp;
	//	pp = dynamic_cast<CTransform*>(pTemp->GetInstance()->Get_Component(ID_DYNAMIC, L"Layer_Environment", L"Player", L"Com_PlayerTransform"));
	//	//dynamic_cast<CTransform*>(pTemp->GetInstance()->Get_Component(ID_DYNAMIC, L"Layer_Environment", L"Player", L"Com_PlayerTransform"))->Get_Info(INFO_POS, &vPosPlayer);
	//
	//	pp->Get_Info(INFO_POS, &vPosPlayer);
	//	//pTransformPlayer->Get_Info(INFO_UP, &vPosPlayer);
	//	//pTransformPlayer = (Engine::Get_Component(ID_DYNAMIC, L"Layer_Environment", L"Monster", L"Com_MonsterTransform"));
	//	//pTransformPlayer->Get_Info(INFO_UP, &vPosMonster);
	//	_vec3 vDir = vPosPlayer - m_pTransformCom->m_vInfo[INFO_POS];
	//
	//
	//
	//	m_pTransformCom->Move_Position(D3DXVec3Normalize(&vDir, &vDir), fTimeDelta, 2.f);
	//}
	

	/*_vec3 vUp;
	m_pTransformCom->Get_Info(INFO_UP, &vUp);

	if (GetAsyncKeyState(VK_UP))
	{
		m_pTransformCom->Move_Position(D3DXVec3Normalize(&vUp, &vUp), fTimeDelta, 2.f);
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_pTransformCom->Rotation(ROT_X, D3DXToRadian(120.f * fTimeDelta));
	}*/
}

CMonster* CMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonster* pMonster = new CMonster(pGraphicDev);

	if (FAILED(pMonster->Ready_GameObject()))
	{
		Safe_Release(pMonster);
		MSG_BOX("Monster Create Failed");
		return nullptr;
	}

	return pMonster;
}

void CMonster::Free()
{
	Engine::CGameObject::Free();
}
