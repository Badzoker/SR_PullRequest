#include "../../Header/Light.h"

CLight::CLight(LPDIRECT3DDEVICE9 pGraphicDev) : m_pGraphicDev(pGraphicDev), m_iIndex(0)
{
	ZeroMemory(&m_tLightInfo, sizeof(D3DLIGHT9));
	m_pGraphicDev->AddRef();
}

CLight::~CLight()
{
}

HRESULT CLight::Ready_Light(const D3DLIGHT9* pLightInfo, const _uint& iIndex)
{
	memcpy(&m_tLightInfo, pLightInfo, sizeof(D3DLIGHT9));

	m_iIndex = iIndex;

	m_pGraphicDev->SetLight(iIndex, pLightInfo);

	m_pGraphicDev->LightEnable(iIndex, TRUE);

	return S_OK;
}

CLight* CLight::Create(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex)
{
	CLight* pLight = new CLight(pGraphicDev);

	if (pLight->Ready_Light(pLightInfo, iIndex))
	{
		Safe_Release(pLight);
		MSG_BOX("Light Create Failed");
		return nullptr;
	}
	return pLight;
}

void CLight::Free()
{
	m_pGraphicDev->LightEnable(m_iIndex, FALSE);
	Safe_Release(m_pGraphicDev);
}
