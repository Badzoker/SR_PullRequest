#include "../../Header/Frame.h"

CFrame::CFrame() : m_fCallLimit(0.f), m_fAccTimerDelta(0.f)
{
}

CFrame::~CFrame()
{
}

HRESULT CFrame::Ready_Frame(const _float& fCallLimit)
{
    m_fCallLimit = 1.f / fCallLimit;

    return S_OK;
}

_bool CFrame::IsPermit_Call(const _float& fTimeDelta)
{
    m_fAccTimerDelta += fTimeDelta;

    if (m_fAccTimerDelta >= m_fCallLimit)
    {
        m_fAccTimerDelta = 0.f;
        return true;
    }
    return false;
}

CFrame* CFrame::Create(const _float& fCallLimit)
{
    CFrame* pFrame = new CFrame;

    if (FAILED(pFrame->Ready_Frame(fCallLimit)))
    {
        Safe_Release(pFrame);
        return nullptr;
    }
    return pFrame;
}

void CFrame::Free()
{
}
