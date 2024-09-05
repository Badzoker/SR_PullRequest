#include "Export_Utility.h"

IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement() : m_pScene(nullptr)
{
}

CManagement::~CManagement()
{
	Free(); //Singleton 으로 선언했기에 소멸자에 Free가 포함
}

CComponent* CManagement::Get_Component(COMPONENTID eID, const _tchar* pLayerTag, const _tchar* pGameObjectTag, const _tchar* pComponentTag)
{
	NULL_CHECK_RETURN(m_pScene, nullptr);


	return m_pScene->Get_Component(eID, pLayerTag, pGameObjectTag, pComponentTag);
}

HRESULT CManagement::Add_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag, CGameObject* pGameObjcet)
{
	NULL_CHECK_RETURN(m_pScene, E_FAIL);

	m_pScene->Add_GameObject(pLayerTag, pObjTag, pGameObjcet);

	return S_OK;
}

HRESULT CManagement::Set_Scene(CScene* pScene)
{
	Safe_Release(m_pScene);

	m_pScene = pScene;

	return S_OK;
}

_int CManagement::Update_Scene(const _float& fTimeDelta)
{
	NULL_CHECK_RETURN(m_pScene, -1);


	return m_pScene->Update_Scene(fTimeDelta);
}

void CManagement::LateUpdate_Scene()
{
	NULL_CHECK(m_pScene);
	m_pScene->LateUpdate_Scene();
}

void CManagement::Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	NULL_CHECK(m_pScene);
	m_pScene->Render_Scene();
}

void CManagement::Free()
{
	Safe_Release(m_pScene);
}
