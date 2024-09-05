#include "pch.h"
#include "../Header/MainApp.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
	//Free();
}

HRESULT CMainApp::Ready_MainApp()
{
	//FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);
	//m_pDeviceClass->AddRef();
	//m_pGraphicDev = m_pDeviceClass->Get_GraphicDev();
	//m_pGraphicDev->AddRef();
	


	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL);



	//m_vertexBuffer->AddRef();
	//Setup();


	return S_OK;
}

int CMainApp::Update_MainApp(float _fTimeDelta)
{
	Engine::Update_InputDev();

	m_pManagementClass->Update_Scene(_fTimeDelta);
	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
	m_pManagementClass->LateUpdate_Scene();
}

void CMainApp::Render_MainApp()
{
	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 0.f, 1.f));

	m_pManagementClass->Render_Scene(m_pGraphicDev);

	

	Engine::Render_End();
}



HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagement)
{
	Engine::CScene* pScene = nullptr;

	pScene = CLogo::Create(pGraphicDev);

	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Create_Management(pGraphicDev, ppManagement), E_FAIL);
	(*ppManagement)->AddRef();

	FAILED_CHECK_RETURN((*ppManagement)->Set_Scene(pScene), E_FAIL);




	return S_OK;
}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	(*ppGraphicDev)->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Font Add
	FAILED_CHECK_RETURN(Engine::Ready_Font(*ppGraphicDev, L"Font_Default", L"¸íÁ¶", 20, 20, FW_NORMAL), E_FAIL);

	//Input Add
	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL);

	return S_OK;
}



CMainApp* CMainApp::Create()
{
	CMainApp* pMainApp = new CMainApp;

	if (FAILED(pMainApp->Ready_MainApp()))
	{
		Safe_Release(pMainApp);

		return nullptr;
	}
	return pMainApp;
}

void CMainApp::Free()
{
	Safe_Release(m_pDeviceClass);
	Safe_Release(m_pGraphicDev);
	//Safe_Release(m_vertexBuffer);
	Safe_Release(m_pManagementClass);
	
	Engine::Release_Utility();
	Engine::Release_System();
}
