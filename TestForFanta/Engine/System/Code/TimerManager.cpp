#include "../../Header/TimerManager.h"

IMPLEMENT_SINGLETON(CTimerManager)

CTimerManager::CTimerManager()
{
}

CTimerManager::~CTimerManager()
{
	Free();
}

_float CTimerManager::Get_TimeDelta(const _tchar* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	NULL_CHECK_RETURN(pTimer, 0.f);

	return pTimer->GetTimeDelta();
}

void CTimerManager::Set_TimeDelta(const _tchar* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	NULL_CHECK(pTimer);

	pTimer->Update_Timer();
}

HRESULT CTimerManager::Ready_Timer(const _tchar* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);

	if (pTimer != nullptr)
		return E_FAIL;

	pTimer = CTimer::Create();
	NULL_CHECK_RETURN(pTimer, E_FAIL);

	m_mapTimer.insert({ pTimerTag, pTimer });

	return S_OK;

}

CTimer* CTimerManager::Find_Timer(const _tchar* pTimerTag)
{
	auto iter = find_if(m_mapTimer.begin(), m_mapTimer.end(), CTag_Finder(pTimerTag));

	if (iter == m_mapTimer.end())
		return nullptr;

	return iter->second;
}

void CTimerManager::Free()
{
	for_each(m_mapTimer.begin(), m_mapTimer.end(), CDeleteMap());
	m_mapTimer.clear();
}
