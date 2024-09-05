#include "../../Header/RcCol.h"

CRcCol::CRcCol()
{
}

CRcCol::CRcCol(LPDIRECT3DDEVICE9 pGraphicDev) :CVIBuffer(pGraphicDev)
{
}

CRcCol::CRcCol(const CRcCol& rhs) : CVIBuffer(rhs)
{
}

CRcCol::~CRcCol()
{
}

HRESULT CRcCol::Ready_Buffer()
{
    m_dwTriangleCount = 2;
    m_dwVertexCount = 4;
    m_dwVertexSize = sizeof(VTXCOL);
    m_dwFVF = FVF_COL;

    m_dwIndexSize = sizeof(INDEX32);
    m_IndexFormat = D3DFMT_INDEX32;

    FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

    VTXCOL* pVertex = NULL;

    m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

    pVertex[0].vPosition = { -1.f, 1.f, 0.f };
    pVertex[0].dwColor = D3DXCOLOR(1.f,1.f,0.f,1.f);

    pVertex[1].vPosition = { 1.f, 1.f, 0.f };
    pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 1.f, 1.f);

    pVertex[2].vPosition = { 1.f, -1.f, 0.f };
    pVertex[2].dwColor = D3DXCOLOR(1.f, 1.f, 0.f, 1.f);

    pVertex[3].vPosition = { -1.f, -1.f, 0.f };
    pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 1.f, 1.f);

    m_pVertexBuffer->Unlock();

    INDEX32* pIndex = NULL;

    m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

    pIndex[0]._0 = 0;
    pIndex[0]._1 = 1;
    pIndex[0]._2 = 2;

    pIndex[1]._0 = 0;
    pIndex[1]._1 = 2;
    pIndex[1]._2 = 3;

    m_pIndexBuffer->Unlock();

    return S_OK;
}

void CRcCol::Render_Buffer()
{
    CVIBuffer::Render_Buffer();
}

CRcCol* CRcCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CRcCol* pRcCol = new CRcCol(pGraphicDev);

    if (FAILED(pRcCol->Ready_Buffer()))
    {
        Safe_Release(pRcCol);
        MSG_BOX("RcCol Create Failed");
        return nullptr;
    }

    return pRcCol;
}

CComponent* CRcCol::Clone()
{
    return new CRcCol(*this);
}

void CRcCol::Free()
{
    CVIBuffer::Free();
}
