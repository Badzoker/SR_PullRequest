#include "../../Header/RcArea.h"

CRcArea::CRcArea()
{
}

CRcArea::CRcArea(LPDIRECT3DDEVICE9 pGraphicDev) : CVIBuffer(pGraphicDev)
{
}

CRcArea::CRcArea(const CRcArea& rhs) : CVIBuffer(rhs), m_fH(rhs.m_fH), m_iH(rhs.m_iH), m_hFile(rhs.m_hFile)
{

}

CRcArea::~CRcArea()
{
}

HRESULT CRcArea::Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	m_dwTriangleCount = (2 * (dwCntX - 1) * (dwCntZ - 1)); //128 * 128 * 2
	m_dwVertexCount = dwCntX * dwCntZ; // 129 * 129
	m_dwVertexSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	//Height Map
	m_hFile = CreateFile(L"../Bin/Resource/Texture/Terrain/Height.bmp", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == m_hFile)
	{
		MSG_BOX("HeightMap Create Failed");
	}

	_ulong dwByte(0);

	ReadFile(m_hFile, &m_fH, sizeof(BITMAPFILEHEADER), &dwByte, NULL);
	ReadFile(m_hFile, &m_iH, sizeof(BITMAPINFOHEADER), &dwByte, NULL);

	_ulong* pPixel = new _ulong[m_iH.biWidth * m_iH.biHeight];

	ReadFile(m_hFile, pPixel, sizeof(_ulong) * m_iH.biWidth * m_iH.biHeight, &dwByte, NULL);

	CloseHandle(m_hFile);

	//Height Map End

	VTXTEX* pVertex = NULL;
	_ulong dwIndex(0);
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
	for (_ulong i = 0; i < dwCntZ; i++)
	{
		for (_ulong j = 0; j < dwCntX; j++)
		{
			dwIndex = i * dwCntX + j;

			pVertex[dwIndex].vPosition = { (_float)j * dwVtxItv,
											(_float)(pPixel[dwIndex] & 0x000000ff) / 20.f, //0x000000ff = 255
											(_float)i * dwVtxItv };
			pVertex[dwIndex].vTexUV = { ((_float)j / (dwCntX - 1)) * 5.f, ((_float)i / (dwCntZ - 1)) * 5.f}; //이게 뭔지 확인하기

		}
	}
	m_pVTX = pVertex;

	Safe_Delete_Array(pPixel);

	INDEX32* pIndex = NULL;

	_ulong dwTriangleCount(0);

	_vec3 vTmp, vDst, vNormal;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	for (_uint i = 0; i < dwCntZ - 1; i++)
	{
		for (_uint j = 0; j < dwCntX - 1; j++)
		{
			dwIndex = i * dwCntX + j;
			//2n
			pIndex[dwTriangleCount]._0 = dwIndex + dwCntX;
			pIndex[dwTriangleCount]._1 = dwIndex + dwCntX + 1;
			pIndex[dwTriangleCount]._2 = dwIndex + 1;
			
			vTmp = pVertex[pIndex[dwTriangleCount]._1].vPosition - pVertex[pIndex[dwTriangleCount]._0].vPosition;
			vDst = pVertex[pIndex[dwTriangleCount]._2].vPosition - pVertex[pIndex[dwTriangleCount]._1].vPosition;
			D3DXVec3Cross(&vNormal, &vTmp, &vDst);

			pVertex[pIndex[dwTriangleCount]._0].vNormal += vNormal;
			pVertex[pIndex[dwTriangleCount]._1].vNormal += vNormal;
			pVertex[pIndex[dwTriangleCount]._2].vNormal += vNormal;

			dwTriangleCount++;
			//2n+1
			pIndex[dwTriangleCount]._0 = dwIndex + dwCntX;
			pIndex[dwTriangleCount]._1 = dwIndex + 1;
			pIndex[dwTriangleCount]._2 = dwIndex;

			vTmp = pVertex[pIndex[dwTriangleCount]._1].vPosition - pVertex[pIndex[dwTriangleCount]._0].vPosition;
			vDst = pVertex[pIndex[dwTriangleCount]._2].vPosition - pVertex[pIndex[dwTriangleCount]._1].vPosition;
			D3DXVec3Cross(&vNormal, &vTmp, &vDst);

			pVertex[pIndex[dwTriangleCount]._0].vNormal += vNormal;
			pVertex[pIndex[dwTriangleCount]._1].vNormal += vNormal;
			pVertex[pIndex[dwTriangleCount]._2].vNormal += vNormal;

			dwTriangleCount++;
		}
	}

	for (_ulong i = 0; i < m_dwVertexCount; ++i)
		D3DXVec3Normalize(&pVertex[i].vNormal, &pVertex[i].vNormal);

	m_pVertexBuffer->Unlock();
	m_pIndexBuffer->Unlock();

	return S_OK;
}

void CRcArea::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}

CRcArea* CRcArea::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	CRcArea* pRcArea = new CRcArea(pGraphicDev);

	if (FAILED(pRcArea->Ready_Buffer(dwCntX, dwCntZ, dwVtxItv)))
	{
		Safe_Release(pRcArea);
		MSG_BOX("RcArea Create Failed");
		return nullptr;
	}
	return pRcArea;
}

CComponent* CRcArea::Clone()
{
	return new CRcArea(*this);
}

void CRcArea::Free()
{
	CVIBuffer::Free();
}
