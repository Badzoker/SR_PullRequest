#include "../../Header/VIBuffer.h"

CVIBuffer::CVIBuffer() : m_pVertexBuffer(nullptr), m_pIndexBuffer(nullptr), m_dwFVF(0), m_dwTriangleCount(0), m_dwVertexCount(0), m_dwVertexSize(0), m_dwIndexSize(0)
{
}

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev) : CComponent(pGraphicDev), m_pVertexBuffer(nullptr), m_pIndexBuffer(nullptr), m_dwFVF(0), m_dwTriangleCount(0), m_dwVertexCount(0), m_dwVertexSize(0), m_dwIndexSize(0)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer& rhs) : CComponent(rhs), m_pVertexBuffer(rhs.m_pVertexBuffer), m_pIndexBuffer(rhs.m_pIndexBuffer), m_dwFVF(rhs.m_dwFVF), m_dwTriangleCount(rhs.m_dwTriangleCount), m_dwVertexCount(rhs.m_dwVertexCount), m_dwVertexSize(rhs.m_dwVertexSize), m_dwIndexSize(rhs.m_dwIndexSize), m_IndexFormat(rhs.m_IndexFormat), m_pVTX(rhs.m_pVTX)
{
	m_pVertexBuffer->AddRef();
	m_pIndexBuffer->AddRef();
}

CVIBuffer::~CVIBuffer()
{
}

HRESULT CVIBuffer::Ready_Buffer()
{
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(m_dwVertexCount * m_dwVertexSize, 0, m_dwFVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL), E_FAIL);
	
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateIndexBuffer(m_dwTriangleCount * m_dwIndexSize, 0, m_IndexFormat, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL), E_FAIL);

	return S_OK;
}

void CVIBuffer::Render_Buffer()
{
	m_pGraphicDev->SetStreamSource(0, m_pVertexBuffer, 0, m_dwVertexSize);
	m_pGraphicDev->SetFVF(m_dwFVF);
	m_pGraphicDev->SetIndices(m_pIndexBuffer);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVertexCount, 0, m_dwTriangleCount);
}

void CVIBuffer::Free()
{
	Safe_Release(m_pVertexBuffer);
	Safe_Release(m_pIndexBuffer);

	CComponent::Free();
}
