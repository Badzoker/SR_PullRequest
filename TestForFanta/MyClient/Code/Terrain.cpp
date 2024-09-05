#include "pch.h"
#include "../Header/Terrain.h"
#include "Export_Utility.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev) : Engine::CGameObject(pGraphicDev)
{
}

CTerrain::~CTerrain()
{
}

HRESULT CTerrain::Ready_GameObject()
{
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    //m_pTransformCom->m_vScale = { 1.f, 1.f, 1.f };
    return S_OK;
}

_int CTerrain::Update_GameObject(const _float& fTimeDelta)
{

    //Key_Input(fTimeDelta);

    Engine::Add_RenderGroup(RENDER_NONALPHA, this);

    return Engine::CGameObject::Update_GameObject(fTimeDelta);;
}

void CTerrain::LateUpdate_GameObject()
{
    Engine::CGameObject::LateUpdate_GameObject();
}

void CTerrain::Render_GameObject()
{
    m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
    m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    FAILED_CHECK_RETURN(Setup_Material(), );

    m_pTextureCom->Set_Texture(1);
    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
    m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CTerrain::Add_Component()
{
    CComponent* pComponent = NULL;

    //pComponent = m_pBufferCom = dynamic_cast<CTest*>(Engine::Clone_Proto(L"Proto_TerrainTest"));
    //NULL_CHECK_RETURN(pComponent, E_FAIL);
    //m_mapComponent[ID_STATIC].insert({ L"Com_TerrainBuffer", pComponent });

    pComponent = m_pBufferCom = dynamic_cast<CRcArea*>(Engine::Clone_Proto(L"Proto_TerrainRcArea"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_TerrainBuffer", pComponent });

    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_TerrainTexture2"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_TerrainTexture", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_TerrainTransform", pComponent });

    return S_OK;
}

HRESULT CTerrain::Setup_Material()
{
    D3DMATERIAL9 tMaterial;
    ZeroMemory(&tMaterial, sizeof(D3DMATERIAL9));

    tMaterial.Diffuse = { 1.f, 1.f, 1.f, 1.f };
    tMaterial.Specular = { 1.f, 1.f, 1.f, 1.f };
    tMaterial.Ambient= { 0.2f, 0.2f, 0.2f, 1.f };

    tMaterial.Emissive = { 0.f, 0.f, 0.f, 0.f };
    tMaterial.Power = 0.f;

    m_pGraphicDev->SetMaterial(&tMaterial);

    return S_OK;
}

void CTerrain::Key_Input(const _float& fTimeDelta)
{
    _vec3 vUp;

    m_pTransformCom->Get_Info(INFO_UP, &vUp);

    if (GetAsyncKeyState(VK_UP))
    {
        m_pTransformCom->Move_Position(D3DXVec3Normalize(&vUp, &vUp), fTimeDelta, 5.f);
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        m_pTransformCom->Move_Position(D3DXVec3Normalize(&vUp, &vUp), fTimeDelta, -5.f);
    }
    if (GetAsyncKeyState('Q'))
    {
        m_pTransformCom->Rotation(ROT_X, D3DXToRadian(120.f * fTimeDelta));
    }
    if (GetAsyncKeyState('E'))
    {
        m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(120.f * fTimeDelta));
    }
    if (GetAsyncKeyState('A'))
    {
        m_pTransformCom->Rotation(ROT_Z, D3DXToRadian(120.f * fTimeDelta));
    }
}



CTerrain* CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CTerrain* pTerrain = new CTerrain(pGraphicDev);

    if (FAILED(pTerrain->Ready_GameObject()))
    {
        Safe_Release(pTerrain);
        MSG_BOX("Terrain Create Failed");
        return nullptr;
    }
    return pTerrain;
}

void CTerrain::Free()
{
    Engine::CGameObject::Free();
}
