#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTriCol : public CVIBuffer
{
private:
	explicit CTriCol();
	explicit CTriCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTriCol(const CTriCol& rhs);
	virtual ~CTriCol();

public:
	virtual HRESULT Ready_Buffer();
	virtual void Render_Buffer();

public:
	static CTriCol* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CComponent* Clone();

private:
	virtual void Free();
};

END