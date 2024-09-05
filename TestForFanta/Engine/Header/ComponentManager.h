#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CComponentManager : public CBase
{
	DECLARE_SINGLETON(CComponentManager)
private:
	explicit CComponentManager();
	virtual ~CComponentManager();

public:
	HRESULT Ready_Proto(const _tchar* pComponentTag, CComponent* pComponent);
	CComponent* Clone_Proto(const _tchar* pComponentTag);

private:
	CComponent* Find_Proto(const _tchar* pComponentTag);
private:
	map<const _tchar*, CComponent*> m_mapPrototype;
private:
	virtual void Free();
};

END