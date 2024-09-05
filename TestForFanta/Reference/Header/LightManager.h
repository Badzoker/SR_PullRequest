#pragma once
#include "Light.h"

BEGIN(Engine)

class ENGINE_DLL CLightManager : public CBase
{
	DECLARE_SINGLETON(CLightManager)

private:
	explicit CLightManager();
	virtual ~CLightManager();

public:
	HRESULT Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex);

private:
	list<CLight*> m_LightList;

private:
	virtual void Free();

};

END