#include "../../Header/FrameManager.h"

IMPLEMENT_SINGLETON(CFrameManager)

CFrameManager::CFrameManager()
{
}

CFrameManager::~CFrameManager()
{
	Free();
}

HRESULT CFrameManager::Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit)
{
	CFrame* pFrame = Find_Frame(pFrameTag);

	if (nullptr != pFrame)
		return E_FAIL;

	pFrame = CFrame::Create(fCallLimit);
	NULL_CHECK_RETURN(pFrame, E_FAIL);

	m_mapFrame.insert({ pFrameTag, pFrame });

	return S_OK;
}

_bool CFrameManager::IsPermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta)
{
	CFrame* pFrame = Find_Frame(pFrameTag);

	NULL_CHECK_RETURN(pFrame, false);

	return pFrame->IsPermit_Call(fTimeDelta);
}

CFrame* CFrameManager::Find_Frame(const _tchar* pFrameTag)
{
	auto iter = find_if(m_mapFrame.begin(), m_mapFrame.end(), CTag_Finder(pFrameTag));
	if (iter == m_mapFrame.end())
		return nullptr;

	return iter->second;
}

void CFrameManager::Free()
{
	for_each(m_mapFrame.begin(), m_mapFrame.end(), CDeleteMap());
	m_mapFrame.clear();
}
