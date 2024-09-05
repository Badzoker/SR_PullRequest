#pragma once
#include "GameObject.h"
BEGIN(Engine)

class CRcTex;
class CTexture;
class CRcCol;
class CTransform;
class CTest;
class CCubeTex;

END

class CSkyBox : public Engine::CGameObject
{
private:
	explicit CSkyBox(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSkyBox();

public:
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta);
	virtual void LateUpdate_GameObject();
	virtual void Render_GameObject();
private:
	HRESULT Add_Component();
private:
	//Engine::CRcCol* m_pBufferCom;
	//Engine::CRcTex* m_pBufferCom;
	Engine::CCubeTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CTransform* m_pTransformCom;

public:
	static CSkyBox* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

