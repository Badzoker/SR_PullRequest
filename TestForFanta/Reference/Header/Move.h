#pragma once
#include "Transform.h"

BEGIN(Engine)

class ENGINE_DLL CMove : public CTransform
{
private:
	explicit CMove();
	explicit CMove(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMove(const CMove& rhs);
	virtual ~CMove();

public:
	virtual _int Update_Component(const _float& fTimeDelta);
	virtual void LateUpdate_Component();

	void Moving_Player(const _float& fTimeDelta);
public:
	static CMove* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};

END