#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer : public CComponent
{
protected:
	explicit CVIBuffer();
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer();

public:
	virtual HRESULT Ready_Buffer();
	virtual void Render_Buffer();

	VTXTEX* Get_VertexPointer() { return m_pVTX; }
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;

	_ulong m_dwVertexCount;
	_ulong m_dwVertexSize; //¸¶Ä¡ sizeof(int)
	_ulong m_dwTriangleCount;
	_ulong m_dwFVF;

	_ulong m_dwIndexSize;

	D3DFORMAT m_IndexFormat;


	//
	VTXTEX* m_pVTX;
public:
	virtual void Free();
};

END