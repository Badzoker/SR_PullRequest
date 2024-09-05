#pragma once
#include "VIBuffer.h"


BEGIN(Engine)

class ENGINE_DLL CRcArea : public CVIBuffer
{
private:
	explicit CRcArea();
	explicit CRcArea(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRcArea(const CRcArea& rhs);
	virtual ~CRcArea();

public:
	virtual HRESULT Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	virtual void Render_Buffer();

public:
	static CRcArea* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX = VTXCNTX, const _ulong& dwCntZ = VTXCNTZ, const _ulong& dwVtxItv = VTXITV);
	virtual CComponent* Clone();

private:
	BITMAPFILEHEADER m_fH;
	BITMAPINFOHEADER m_iH;
	HANDLE m_hFile;


private:
	virtual void Free();
};

END