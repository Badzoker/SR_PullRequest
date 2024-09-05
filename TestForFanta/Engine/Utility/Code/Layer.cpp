#include "../../Header/Layer.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
}

CComponent* CLayer::Get_Component(COMPONENTID eID, const _tchar* pObjTag, const _tchar* pComponentTag)
{
    
    auto iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

    if (iter == m_mapObject.end())
        return nullptr;

    return iter->second->Get_Component(eID, pComponentTag);
}

HRESULT CLayer::Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObjcet)
{
    NULL_CHECK_RETURN(pGameObjcet, E_FAIL);

    m_mapObject.insert({ pObjTag, pGameObjcet });

    return S_OK;
}

HRESULT CLayer::Ready_Layer()
{
    return S_OK;
}

_int CLayer::Update_Layer(const _float& fTimeDelta)
{
    _int iResult(0);

    for (auto& pObj : m_mapObject)
    {
        iResult = pObj.second->Update_GameObject(fTimeDelta);

        if (iResult & 0x80000000)
            return iResult;
    }

    return iResult;
}

void CLayer::LateUpdate_Layer()
{
    for (auto& pObj : m_mapObject)
        pObj.second->LateUpdate_GameObject();
}

void CLayer::Render_Layer()
{
    for (auto& pObj : m_mapObject)
        pObj.second->Render_GameObject();

}

CLayer* CLayer::Create()
{
    CLayer* pLayer = new CLayer;

    if (FAILED(pLayer->Ready_Layer()))
    {
        Safe_Release(pLayer);
        MSG_BOX("Layer Create Failed");
        return nullptr;
    }

    return pLayer;
}

void CLayer::Free()
{
    for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
    m_mapObject.clear();
}
