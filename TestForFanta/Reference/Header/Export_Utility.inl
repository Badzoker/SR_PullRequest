HRESULT Create_Management(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppManagement)
{
	CManagement* pManagement = CManagement::GetInstance();

	NULL_CHECK_RETURN(pManagement, E_FAIL);

	*ppManagement = pManagement;

	return S_OK;
}

CComponent* Get_Component(COMPONENTID eID, const _tchar* pLayerTag, const _tchar* pGameObjectTag, const _tchar* pComponentTag)
{
	return CManagement::GetInstance()->Get_Component(eID, pLayerTag, pGameObjectTag, pComponentTag);
}

HRESULT Add_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag, CGameObject* pGameObjcet)
{
	return CManagement::GetInstance()->Add_GameObject(pLayerTag, pObjTag, pGameObjcet);
}

HRESULT Set_Scene(CScene* pScene)
{
	return CManagement::GetInstance()->Set_Scene(pScene);
}

_int Update_Scene(const _float& fTimeDelta)
{
	return CManagement::GetInstance()->Update_Scene(fTimeDelta);
}

void LateUpdate_Scene()
{
	CManagement::GetInstance()->LateUpdate_Scene();
}

void Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CManagement::GetInstance()->Render_Scene(pGraphicDev);
}

HRESULT Ready_Proto(const _tchar* pComponentTag, CComponent* pComponent)
{
	return CComponentManager::GetInstance()->Ready_Proto(pComponentTag, pComponent);
}

CComponent* Clone_Proto(const _tchar* pComponentTag)
{
	return CComponentManager::GetInstance()->Clone_Proto(pComponentTag);
}

void Add_RenderGroup(RENDERID eType, CGameObject* pGameObject)
{
	CRenderer::GetInstance()->Add_RenderGroup(eType, pGameObject);
}

void Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
{
	CRenderer::GetInstance()->Render_GameObject(pGraphicDev);
}

void Clear_RenderGroup()
{
	CRenderer::GetInstance()->Clear_RenderGroup();
}

HRESULT Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex)
{
	return CLightManager::GetInstance()->Ready_Light(pGraphicDev, pLightInfo, iIndex);
}


void Release_Utility()
{
	CManagement::DestroyInstance();
	CComponentManager::DestroyInstance();
	CRenderer::DestroyInstance();
	CLightManager::DestroyInstance();
}