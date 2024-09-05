#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL CFrame : public CBase
{
private:
	explicit CFrame();
	virtual ~CFrame();

public:
	HRESULT Ready_Frame(const _float& fCallLimit);
	_bool IsPermit_Call(const _float& fTimeDelta);

private:
	_float m_fCallLimit;
	_float m_fAccTimerDelta; //누적 시간느낌

public:
	static CFrame* Create(const _float& fCallLimit);

private:
	virtual void Free();

};

END