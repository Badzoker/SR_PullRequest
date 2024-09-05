#pragma once
#include "Base.h"
#include "Scene.h"

BEGIN(Engine)

class ENGINE_DLL CManagement : public CBase
{
	DECLARE_SINGLETON(CManagement)
private:
	explicit CManagement();
	virtual ~CManagement();

public:
	CComponent* Get_Component(COMPONENTID eID, const _tchar* pLayerTag, const _tchar* pGameObjectTag, const _tchar* pComponentTag);

	HRESULT Add_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag, CGameObject* pGameObjcet);

	HRESULT Set_Scene(CScene* pScene);

	_int Update_Scene(const _float& fTimeDelta);
	void LateUpdate_Scene();
	void Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CScene* m_pScene;

public:
	virtual void Free();

};

END