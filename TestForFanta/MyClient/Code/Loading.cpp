#include "pch.h"
#include "../Header/Loading.h"

CLoading::CLoading(LPDIRECT3DDEVICE9 pGraphicDev) : m_pGraphicDev(pGraphicDev), m_bFinish(false)
{
	m_pGraphicDev->AddRef();
}

CLoading::~CLoading()
{
}

HRESULT CLoading::Ready_Loading(LOADINGID eLoading)
{
	InitializeCriticalSection(&m_Crt);

	m_eLoadingID = eLoading;

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_Main, this, 0, NULL);

	return S_OK;
}

_uint CLoading::Loading_Stage()
{
	lstrcpy(m_szLoading, L"Buffer Loading............");
	//Buffer
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_BackGroundRcArea", Engine::CRcArea::Create(m_pGraphicDev)), E_FAIL);

	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerRcCol", Engine::CRcCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerRcTex", Engine::CRcTex::Create(m_pGraphicDev)), E_FAIL);
	//종한 Bullet4 RcTex
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Bullet4RcTex", Engine::CRcTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MonsterTriCol", Engine::CTriCol::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainRcArea", Engine::CRcArea::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_SkyBoxCubeTex", Engine::CCubeTex::Create(m_pGraphicDev)), E_FAIL);
	
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTest", Engine::CTest::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Height2.bmp")), E_FAIL);

	lstrcpy(m_szLoading, L"Texture Loading............");
	//Texture
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_BackGroundTexture", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Terrain0.png", TEX_NORMAL)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerTexture", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player0.png", TEX_NORMAL)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_SkyBoxTexture", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TEX_CUBE, 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Terrain0.png", TEX_NORMAL)), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture2", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TEX_NORMAL, 2)), E_FAIL);
	//종한 Bullet4
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Bullet4Texture", Engine::CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player1.jpg", TEX_NORMAL)), E_FAIL);
	
	lstrcpy(m_szLoading, L"ETC Loading............");
	//Etc
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Transform", Engine::CTransform::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Calculaotr", Engine::CCalculator::Create(m_pGraphicDev)), E_FAIL);
	


	lstrcpy(m_szLoading, L"Loading Complete!!");
	m_bFinish = true;

	return 0;
}

unsigned int __stdcall CLoading::Thread_Main(void* pArg)
{
	CLoading* pLoading = reinterpret_cast<CLoading*>(pArg);

	_uint iFlag(0);

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadinID())
	{
	case LOADING_STAGE:
		iFlag = pLoading->Loading_Stage();
		break;
	case LOADING_BOSS:

		break;
	}

	LeaveCriticalSection(pLoading->Get_Crt());

	return iFlag;
}

CLoading* CLoading::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID)
{
	CLoading* pLoading = new CLoading(pGraphicDev);
	if (FAILED(pLoading->Ready_Loading(eID)))
	{
		Safe_Release(pLoading);
		MSG_BOX("Loading Create Failed");
		return nullptr;
	}
	
	return pLoading;
}

void CLoading::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}
