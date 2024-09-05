#pragma once

#include "Management.h"
#include "ComponentManager.h"
#include "Renderer.h"
#include "LightManager.h"

#include "RcCol.h"
#include "Transform.h"

#include "TriCol.h"

#include "Texture.h"
#include "RcTex.h"
#include "RcArea.h"
#include "Test.h"
#include "Camera.h"
#include "CubeTex.h"
#include "Calculator.h"

BEGIN(Engine)

inline HRESULT Create_Management(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppManagement);

inline CComponent* Get_Component(COMPONENTID eID, const _tchar* pLayerTag, const _tchar* pGameObjectTag, const _tchar* pComponentTag);

inline HRESULT Add_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag, CGameObject* pGameObjcet);

inline HRESULT Set_Scene(CScene* pScene);
inline _int Update_Scene(const _float& fTimeDelta);
inline void LateUpdate_Scene();
inline void Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

//ComponentManager

inline HRESULT Ready_Proto(const _tchar* pComponentTag, CComponent* pComponent);
inline CComponent* Clone_Proto(const _tchar* pComponentTag);

//Renderer
inline void Add_RenderGroup(RENDERID eType, CGameObject* pGameObject);
inline void Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
inline void Clear_RenderGroup();

//LightManager
inline HRESULT Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex);

inline void Release_Utility();

#include "Export_Utility.inl"

END