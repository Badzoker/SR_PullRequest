#include "../../Header/RcTex.h"

CRcTex::CRcTex()
{
}

CRcTex::CRcTex(LPDIRECT3DDEVICE9 pGraphicDev) : CVIBuffer(pGraphicDev)
{
}

CRcTex::CRcTex(const CRcTex& rhs) : CVIBuffer(rhs)
{
}

CRcTex::~CRcTex()
{
}

HRESULT CRcTex::Ready_Buffer()
{
	m_dwTriangleCount = 2;
	m_dwVertexCount = 4;
	m_dwVertexSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXTEX* pVertex = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = { -1.f, 1.f, 0.f };
	pVertex[0].vTexUV = { 0.f, 0.f };

	pVertex[1].vPosition = { 1.f, 1.f, 0.f };
	pVertex[1].vTexUV = { 1.f, 0.f };

	pVertex[2].vPosition = { 1.f, -1.f, 0.f };
	pVertex[2].vTexUV = { 1.f, 1.f };

	pVertex[3].vPosition = { -1.f, -1.f, 0.f };
	pVertex[3].vTexUV = { 0.f, 1.f };

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	// 오른쪽 위
	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	// 왼쪽 아래
	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIndexBuffer->Unlock();
    return S_OK;
}

void CRcTex::Render_Buffer()
{
    CVIBuffer::Render_Buffer();
}

CRcTex* CRcTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CRcTex* pRcTex = new CRcTex(pGraphicDev);
    if (FAILED(pRcTex->Ready_Buffer()))
    {
        Safe_Release(pRcTex);
        MSG_BOX("RcTex Create Failed");
        return nullptr;
    }
    return pRcTex;
}

CComponent* CRcTex::Clone()
{
    return new CRcTex(*this);
}

void CRcTex::Free()
{
    CVIBuffer::Free();
}
