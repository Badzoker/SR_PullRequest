#include "pch.h"
#include "../Header/Player.h"
#include "Export_Utility.h"
#include "Export_System.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev) : Engine::CGameObject(pGraphicDev), m_pVertexPos(nullptr)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
	Key_Input(fTimeDelta);

	//Moving(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return  Engine::CGameObject::Update_GameObject(fTimeDelta);
}

void CPlayer::LateUpdate_GameObject()
{
	if (nullptr == m_pVertexPos)
	{
		Engine::CRcArea* pTerrainPos = dynamic_cast<CRcArea*>(Engine::Get_Component(ID_STATIC, L"Layer_GameLogic", L"Terrain", L"Com_TerrainBuffer"));
		VTXTEX* pVertex = pTerrainPos->Get_VertexPointer();
		m_pVertexPos = new _vec3[VTXCNTX * VTXCNTZ];
		for (_int i = 0; i < VTXCNTX * VTXCNTZ; i++)
			m_pVertexPos[i] = pVertex[i].vPosition;
	}
	_vec3 vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	_float fTemp(0.f);
	fTemp = m_pCalculatorCom->Compute_HeightOnTerrain(&vPos, m_pVertexPos, VTXCNTX, VTXCNTZ);
	m_pTransformCom->Set_Position(vPos.x, fTemp + 1.f, vPos.z);

	Engine::CGameObject::LateUpdate_GameObject();
}

void CPlayer::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

HRESULT CPlayer::Add_Component()
{
	CComponent* pComponent = NULL;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_PlayerRcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_PlayerRcBuffer", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_PlayerTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_PlayerTextureBuffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_PlayerTransform", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Engine::Clone_Proto(L"Proto_Calculaotr"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_PlayerCalculator", pComponent });

	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	_vec3 vLook;
	_vec3 vRight;
	m_pTransformCom->Get_Info(INFO_LOOK, &vLook);
	m_pTransformCom->Get_Info(INFO_RIGHT, &vRight);
	if (GetAsyncKeyState(VK_UP))
	{
		m_pTransformCom->Move_Position(D3DXVec3Normalize(&vLook, &vLook), fTimeDelta, 10.f);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_pTransformCom->Move_Position(D3DXVec3Normalize(&vLook, &vLook), fTimeDelta, -10.f);
	}
	if (Engine::Get_DIKeyState(DIK_RIGHT) & 0x80)
	{
		m_pTransformCom->Move_Position(D3DXVec3Normalize(&vRight, &vRight), fTimeDelta, 10.f);
	}
	if (Engine::Get_DIKeyState(DIK_LEFT) & 0x80)
	{
		m_pTransformCom->Move_Position(D3DXVec3Normalize(&vRight, &vRight), fTimeDelta, -10.f);
	}

	if (GetAsyncKeyState('Q'))
	{
		m_pTransformCom->Rotation(ROT_X, D3DXToRadian(120.f * fTimeDelta));
	}

	if (GetAsyncKeyState('E'))
	{
		m_pTransformCom->Rotation(ROT_Z, D3DXToRadian(120.f * fTimeDelta));
	}

	if (Engine::Get_DIKeyState(DIK_SPACE) & 0x80)
	{
		Launch_Bullet(fTimeDelta);
	}
	
}

HRESULT CPlayer::Launch_Bullet(const _float& fTimeDelta)
{
	_int iTemp(0);
	for (auto& iter : m_BulletList)
	{
		if (dynamic_cast<CBullet4*>(iter)->Set_Render_True())
		{
			return S_OK;
		}
		else
		{
			iTemp++;
		}
	}

	CGameObject* pGameObject = nullptr;

	wstring str = L"Bullet";

	str += to_wstring(iTemp);

	pGameObject = CBullet4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(Add_GameObject(L"Layer_GameLogic", str.c_str(), pGameObject), E_FAIL);

	m_BulletList.push_back(pGameObject);

	return S_OK;
}


CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer* pPlayer = new CPlayer(pGraphicDev);
	if (FAILED(pPlayer->Ready_GameObject()))
	{
		Safe_Release(pPlayer);
		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pPlayer;
}

void CPlayer::Free()
{
	Safe_Delete_Array(m_pVertexPos);
	for_each(m_BulletList.begin(), m_BulletList.end(), CDeleteObj());
	m_BulletList.clear();
	Engine::CGameObject::Free();
}
