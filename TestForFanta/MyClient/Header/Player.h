#pragma once
#include "GameObject.h"
#include "Bullet4.h"
BEGIN(Engine)

class CRcTex;
class CTexture;
class CRcCol;
class CTransform;
class CTest;
class CCalculator;
END

class CPlayer : public Engine::CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer();

public:
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta);
	virtual void LateUpdate_GameObject();
	virtual void Render_GameObject();
private:
	HRESULT Add_Component();
	void Key_Input(const _float& fTimeDelta);
	HRESULT Launch_Bullet(const _float& fTimeDelta);
private:
	//Engine::CRcCol* m_pBufferCom;
	Engine::CRcTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CTransform* m_pTransformCom;
	Engine::CCalculator* m_pCalculatorCom;

	_vec3* m_pVertexPos;
	list<CGameObject*> m_BulletList;
public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

