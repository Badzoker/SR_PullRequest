#pragma once
#include "pch.h"
#include "Base.h"
#include "Engine_Define.h"
#include "Define.h"
#include "Export_System.h"
#include "Export_Utility.h"
#include "Logo.h"

class CMainApp : public CBase
{
private:
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT Ready_MainApp();
	int		Update_MainApp(float _fTimeDelta);
	void	LateUpdate_MainApp();
	void	Render_MainApp();

	//

protected:
	HRESULT Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagement);
	HRESULT SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);

private:
	CGraphicDev* m_pDeviceClass;
	CManagement* m_pManagementClass;
	LPDIRECT3DDEVICE9 m_pGraphicDev;

	//IDirect3DVertexBuffer9* m_vertexBuffer = 0;
	//IDirect3DIndexBuffer9* m_indexBuffer = 0;

public:
	static CMainApp* Create();
private:
	virtual void Free();
};

