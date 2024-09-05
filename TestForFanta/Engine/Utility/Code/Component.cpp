#include "../../Header/Component.h"

CComponent::CComponent() : m_pGraphicDev(nullptr), m_bClone(false)
{
}

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphicDev) : m_pGraphicDev(pGraphicDev), m_bClone(false)
{
	m_pGraphicDev->AddRef();
}

CComponent::CComponent(const CComponent& rhs) : m_pGraphicDev(rhs.m_pGraphicDev), m_bClone(true)
{
	m_pGraphicDev->AddRef();
}

CComponent::~CComponent()
{

}

void CComponent::Free()
{
	Safe_Release(m_pGraphicDev);
}
