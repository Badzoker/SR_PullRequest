#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTest : public CVIBuffer
{
private:
	explicit CTest();
	explicit CTest(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFile);
	explicit CTest(const CTest& rhs);
	virtual ~CTest();

public:
	virtual HRESULT Ready_Buffer();
	virtual void Render_Buffer();

public:
	D3DXPLANE* Get_PlaneArray() { return m_tPlane; }
	vector<D3DXPLANE>* Get_PlaneVector() { return &m_vecPlane; }

public:
	static CTest* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFile);
	virtual CComponent* Clone();

private:
	//vector<_float> m_vecHeight;
	TCHAR m_szName[128] = L"";
	LPDIRECT3DTEXTURE9 m_pHeight = nullptr;
public:
	D3DXPLANE m_tPlane[(VTXCNTX-1) * (VTXCNTZ-1) * 2];
	vector<D3DXPLANE> m_vecPlane;

private:
	virtual void Free();
};

END