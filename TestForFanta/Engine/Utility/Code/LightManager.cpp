#include "../../Header/LightManager.h"

IMPLEMENT_SINGLETON(CLightManager)

CLightManager::CLightManager()
{
}

CLightManager::~CLightManager()
{
	Free();
}

HRESULT CLightManager::Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex)
{
	CLight* pLight = CLight::Create(pGraphicDev, pLightInfo, iIndex);
	NULL_CHECK_RETURN(pLight, E_FAIL);

	m_LightList.push_back(pLight);

	return S_OK;
}

void CLightManager::Free()
{
	for_each(m_LightList.begin(), m_LightList.end(), CDeleteObj());
	m_LightList.clear();
}
