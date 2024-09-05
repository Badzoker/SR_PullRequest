#pragma once
#include "Base.h"
#include "Export_Utility.h"

class CLoading : public CBase
{
public:
	enum LOADINGID {LOADING_STAGE, LOADING_BOSS, LOADING_END};
private:
	explicit CLoading(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLoading();

public:
	LOADINGID Get_LoadinID() { return m_eLoadingID; }
	CRITICAL_SECTION* Get_Crt() { return &m_Crt; }
	_bool Get_Finish() { return m_bFinish; }
	const _tchar* Get_String() { return m_szLoading; }

public:
	HRESULT Ready_Loading(LOADINGID eLoading);
	_uint Loading_Stage();

public:
	static unsigned int __stdcall Thread_Main(void* pArg); //여러운영체제에서 가능토록 void포인터를 매개변수로 받아줌

private:
	LPDIRECT3DDEVICE9 m_pGraphicDev;
	_bool m_bFinish;

	HANDLE m_hThread;
	LOADINGID m_eLoadingID;

	CRITICAL_SECTION m_Crt;

	_tchar m_szLoading[128];

public:
	static CLoading* Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID);

private:
	virtual void Free();
};

