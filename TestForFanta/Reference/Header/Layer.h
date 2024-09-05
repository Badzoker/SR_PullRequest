#pragma once
#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer();

public:
	CComponent* Get_Component(COMPONENTID eID, const _tchar* pObjTag, const _tchar* pComponentTag);

	HRESULT Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObjcet);

	HRESULT Ready_Layer();
	_int Update_Layer(const _float& fTimeDelta);
	void LateUpdate_Layer();
	void Render_Layer();

private:
	map<const _tchar*, CGameObject*> m_mapObject;

public:
	static CLayer* Create();

private:
	virtual void Free();
};

END