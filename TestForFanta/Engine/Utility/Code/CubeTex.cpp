#include "../../Header/CubeTex.h"

CCubeTex::CCubeTex()
{
}

CCubeTex::CCubeTex(LPDIRECT3DDEVICE9 pGraphicDev) : CVIBuffer(pGraphicDev)
{
}

CCubeTex::CCubeTex(const CCubeTex& rhs) : CVIBuffer(rhs)
{
}

CCubeTex::~CCubeTex()
{
}

HRESULT CCubeTex::Ready_Buffer()
{
	m_dwTriangleCount = 12;
	m_dwVertexCount = 8;
	m_dwVertexSize = sizeof(VTXCUBE);
	m_dwFVF = FVF_CUBE;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXCUBE* pVertex = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = { -1.f, 1.f, -1.f };
	pVertex[0].vTexUV = pVertex[0].vPosition;

	pVertex[1].vPosition = { 1.f, 1.f, -1.f };
	pVertex[1].vTexUV = pVertex[1].vPosition;

	pVertex[2].vPosition = { 1.f, -1.f, -1.f };
	pVertex[2].vTexUV = pVertex[2].vPosition;

	pVertex[3].vPosition = { -1.f, -1.f, -1.f };
	pVertex[3].vTexUV = pVertex[3].vPosition;

	pVertex[4].vPosition = { -1.f, 1.f, 1.f };
	pVertex[4].vTexUV = pVertex[4].vPosition;

	pVertex[5].vPosition = { 1.f, 1.f, 1.f };
	pVertex[5].vTexUV = pVertex[5].vPosition;

	pVertex[6].vPosition = { 1.f, -1.f, 1.f };
	pVertex[6].vTexUV = pVertex[6].vPosition;

	pVertex[7].vPosition = { -1.f, -1.f, 1.f };
	pVertex[7].vTexUV = pVertex[7].vPosition;

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	// -x
	pIndex[0]._0 = 4;
	pIndex[0]._1 = 0;
	pIndex[0]._2 = 3;

	pIndex[1]._0 = 4;
	pIndex[1]._1 = 3;
	pIndex[1]._2 = 7;

	// +x
	pIndex[2]._0 = 1;
	pIndex[2]._1 = 5;
	pIndex[2]._2 = 6;

	pIndex[3]._0 = 1;
	pIndex[3]._1 = 6;
	pIndex[3]._2 = 2;

	// -y
	pIndex[4]._0 = 3;
	pIndex[4]._1 = 2;
	pIndex[4]._2 = 6;

	pIndex[5]._0 = 3;
	pIndex[5]._1 = 6;
	pIndex[5]._2 = 7;

	// +y
	pIndex[6]._0 = 4;
	pIndex[6]._1 = 5;
	pIndex[6]._2 = 1;

	pIndex[7]._0 = 4;
	pIndex[7]._1 = 1;
	pIndex[7]._2 = 0;

	// -z
	pIndex[8]._0 = 0;
	pIndex[8]._1 = 1;
	pIndex[8]._2 = 2;

	pIndex[9]._0 = 0;
	pIndex[9]._1 = 2;
	pIndex[9]._2 = 3;

	// +z
	pIndex[10]._0 = 7;
	pIndex[10]._1 = 6;
	pIndex[10]._2 = 5;

	pIndex[11]._0 = 7;
	pIndex[11]._1 = 5;
	pIndex[11]._2 = 4;

	m_pIndexBuffer->Unlock();
    return S_OK;
}

void CCubeTex::Render_Buffer()
{
    CVIBuffer::Render_Buffer();
}

CCubeTex* CCubeTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CCubeTex* pCubeTex = new CCubeTex(pGraphicDev);
    if (FAILED(pCubeTex->Ready_Buffer()))
    {
        Safe_Release(pCubeTex);
        MSG_BOX("CubeTex Create Failed");
        return nullptr;
    }
    return pCubeTex;
}

CComponent* CCubeTex::Clone()
{
    return new CCubeTex(*this);
}

void CCubeTex::Free()
{
    CVIBuffer::Free();
}
