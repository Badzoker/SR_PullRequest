#include "../../Header/Calculator.h"

CCalculator::CCalculator(LPDIRECT3DDEVICE9 pGraphicDev) : CComponent(pGraphicDev)
{
}

CCalculator::~CCalculator()
{
}

HRESULT CCalculator::Ready_Calculator()
{

    return S_OK;
}

_float CCalculator::Compute_HeightOnTerrain(const _vec3* pPos, const _vec3* pTerrainVtxPos, const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
    _ulong dwIndex = _ulong(pPos->z / dwVtxItv) * dwCntX + _ulong(pPos->x / dwVtxItv);

    _float fRatioX = _float(pPos->x - pTerrainVtxPos[dwIndex + dwCntX].x) / dwVtxItv;
    _float fRatioZ = _float(pTerrainVtxPos[dwIndex + dwCntX].z - pPos->z) / dwVtxItv;

    D3DXPLANE plane;
    
    if (fRatioX > fRatioZ)
    {
        //우상단
        D3DXPlaneFromPoints(&plane, &pTerrainVtxPos[dwIndex + dwCntX], &pTerrainVtxPos[dwIndex + dwCntX + 1], &pTerrainVtxPos[dwIndex + 1]);
    }
    else
    {
        //좌하단
        D3DXPlaneFromPoints(&plane, &pTerrainVtxPos[dwIndex + dwCntX], &pTerrainVtxPos[dwIndex + 1], &pTerrainVtxPos[dwIndex]);
    }


    //y = (-ax -cz - d) / b
    return _float(-plane.a * pPos->x -plane.c * pPos->z - plane.d) / plane.b;
}

CCalculator* CCalculator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CCalculator* pCal = new CCalculator(pGraphicDev);
    if (FAILED(pCal->Ready_Calculator()))
    {
        Safe_Release(pCal);
        MSG_BOX("Calculator Created Failed");
        return nullptr;
    }
    return pCal;
}

CCalculator* CCalculator::Clone()
{
    return new CCalculator(*this);
}

void CCalculator::Free()
{
    CComponent::Free();
}
