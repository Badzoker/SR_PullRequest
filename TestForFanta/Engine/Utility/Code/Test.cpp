#include "../../Header/Test.h"

CTest::CTest()
{
}

CTest::CTest(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFile) : CVIBuffer(pGraphicDev)
{
	for(_int i = 0; i < 1; ++i)
		wsprintf(m_szName, pFile, i);
}

CTest::CTest(const CTest& rhs) : CVIBuffer(rhs)
{
	m_vecPlane = rhs.m_vecPlane;
}

CTest::~CTest()
{
}

HRESULT CTest::Ready_Buffer()
{
	m_dwTriangleCount = (2 * (VTXCNTX - 1) * (VTXCNTZ - 1)); //128 * 128 * 2
	m_dwVertexCount = VTXCNTX * VTXCNTZ; // 129 * 129
	m_dwVertexSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	//Read_HeightFile();

	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	if (FAILED(D3DXCreateTextureFromFileEx(m_pGraphicDev,
		m_szName, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, 0,
		D3DFMT_X8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0,
		NULL, NULL, &m_pHeight
	)))
	{
		MSG_BOX("»Ú¾Ó");
		return E_FAIL;
	}

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);


	VTXTEX* pVertex = NULL;
	_D3DLOCKED_RECT d3drc;


	m_pHeight->LockRect(0, &d3drc, NULL, D3DLOCK_READONLY);

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);
	for (_uint i = 0; i < VTXCNTX; i++)
	{
		for (_uint j = 0; j < VTXCNTZ; j++)
		{
			pVertex[j + (i * VTXCNTX)].vPosition = { (_float)j,
														((_float)(*((LPDWORD)d3drc.pBits + j + i * (d3drc.Pitch / 4)) & 0x000000ff)) / 10.f, //0x000000ff = 255
														(_float)i };
			pVertex[j + (i * VTXCNTX)].vTexUV = { ((_float)j / (VTXCNTX - 1)), ((_float)i / (VTXCNTX - 1)) }; //ÀÌ°Ô ¹ºÁö È®ÀÎÇÏ±â
		}
	}
	m_pVertexBuffer->Unlock();

	m_pHeight->UnlockRect(0);

	INDEX32* pIndex = NULL;
	m_vecPlane.reserve(m_dwTriangleCount);
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	_uint iTriangleCount(0);
	for (_uint j = 0; j < VTXCNTZ - 1; j++)
	{
		for (_uint i = 0; i < VTXCNTX - 1; i++)
		{
			//2n
			pIndex[iTriangleCount]._0 = i + (j * VTXCNTX);
			pIndex[iTriangleCount]._1 = i + 1 + VTXCNTX + (j * VTXCNTX);
			pIndex[iTriangleCount]._2 = i + 1 + (j * VTXCNTX);
			D3DXPlaneFromPoints(&m_tPlane[iTriangleCount], &pVertex[i + (j * VTXCNTX)].vPosition, &pVertex[i + 1 + VTXCNTX + (j * VTXCNTX)].vPosition, &pVertex[i + 1 + (j * VTXCNTX)].vPosition);
			//D3DXPlaneFromPoints(&m_vecPlane[iTriangleCount], &pVertex[i + (j * VTXCNTX)].vPosition, &pVertex[i + 1 + VTXCNTX + (j * VTXCNTX)].vPosition, &pVertex[i + 1 + (j * VTXCNTX)].vPosition);
			m_vecPlane.push_back(m_tPlane[iTriangleCount]);
			iTriangleCount++;

			//2n+1
			pIndex[iTriangleCount]._0 = i + (j * VTXCNTX);
			pIndex[iTriangleCount]._1 = i + VTXCNTX + (j * VTXCNTX);
			pIndex[iTriangleCount]._2 = i + 1 + VTXCNTX + (j * VTXCNTX);

			D3DXPlaneFromPoints(&m_tPlane[iTriangleCount], &pVertex[i + (j * VTXCNTX)].vPosition, &pVertex[i + VTXCNTX + (j * VTXCNTX)].vPosition, &pVertex[i + 1 + VTXCNTX + (j * VTXCNTX)].vPosition);
			//D3DXPlaneFromPoints(&m_vecPlane[iTriangleCount], &pVertex[i + (j * VTXCNTX)].vPosition, &pVertex[i + VTXCNTX + (j * VTXCNTX)].vPosition, &pVertex[i + 1 + VTXCNTX + (j * VTXCNTX)].vPosition);
			m_vecPlane.push_back(m_tPlane[iTriangleCount]);
			iTriangleCount++;
		}
	}
	
	m_pIndexBuffer->Unlock();

	return S_OK;
}

void CTest::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}


CTest* CTest::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFile)
{
	CTest* pTest = new CTest(pGraphicDev, pFile);

	if (FAILED(pTest->Ready_Buffer()))
	{
		Safe_Release(pTest);
		MSG_BOX("Test Create Failed");
		return nullptr;
	}
	return pTest;
}

CComponent* CTest::Clone()
{
	return new CTest(*this);
}

void CTest::Free()
{
	CVIBuffer::Free();
}
