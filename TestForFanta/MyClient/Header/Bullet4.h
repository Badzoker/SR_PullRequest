#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTransform;
class CTexture;
class CRcTex;

END


class CBullet4 : public Engine::CGameObject
{
private:
	explicit CBullet4(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBullet4();

public:
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta);
	virtual void LateUpdate_GameObject();
	virtual void Render_GameObject();

	_bool Set_Render_True();

	HRESULT Set_Position_Player();
private:
	HRESULT Add_Component();
	HRESULT Bullet_Launch(const _float& fTimeDelta);
private:
	Engine::CTransform* m_pTransformCom;
	Engine::CRcTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;

	_bool m_bIsRender;
	_float m_fTimer;

public:
	static CBullet4* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

