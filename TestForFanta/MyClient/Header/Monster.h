#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTriCol;
class CTransform;

END


class CMonster : public Engine::CGameObject
{
private:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMonster();

public:
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta);
	virtual void LateUpdate_GameObject();
	virtual void Render_GameObject();

private:
	HRESULT Add_Component();
	void Key_Input(const _float& fTimeDelta);

private:
	Engine::CTriCol* m_pBufferCom;
	Engine::CTransform* m_pTransformCom;

public:
	static CMonster* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

