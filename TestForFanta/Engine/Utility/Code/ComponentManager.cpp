#include "../../Header/ComponentManager.h"


IMPLEMENT_SINGLETON(CComponentManager)

CComponentManager::CComponentManager()
{
}

CComponentManager::~CComponentManager()
{
	Free();
}

HRESULT CComponentManager::Ready_Proto(const _tchar* pComponentTag, CComponent* pComponent)
{
	CComponent* pInstance = Find_Proto(pComponentTag);

	if (nullptr != pInstance)
		return E_FAIL;

	m_mapPrototype.insert({pComponentTag, pComponent });
	
	return S_OK;
}

CComponent* CComponentManager::Clone_Proto(const _tchar* pComponentTag)
{
	CComponent* pComponent = Find_Proto(pComponentTag);
	NULL_CHECK_RETURN(pComponent, nullptr);

	return pComponent->Clone();
}

CComponent* CComponentManager::Find_Proto(const _tchar* pComponentTag)
{
	auto iter = find_if(m_mapPrototype.begin(), m_mapPrototype.end(), CTag_Finder(pComponentTag));

	if (iter == m_mapPrototype.end())
		return nullptr;

	return iter->second;
}

void CComponentManager::Free()
{
	for_each(m_mapPrototype.begin(), m_mapPrototype.end(), CDeleteMap());
	m_mapPrototype.clear();
}
