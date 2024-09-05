#include "../Header/Renderer.h"

IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
	Free();
}

void CRenderer::Add_RenderGroup(RENDERID eType, CGameObject* pGameObject)
{
	if (RENDER_END <= eType || nullptr == pGameObject)
		return;

	m_RenderGroupList[eType].push_back(pGameObject);

	pGameObject->AddRef();
}

void CRenderer::Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
{
	Render_Priority(pGraphicDev);
	Render_NoAlpha(pGraphicDev);
	Render_Alpha(pGraphicDev);
	Render_UI(pGraphicDev);

	Clear_RenderGroup();
}

void CRenderer::Clear_RenderGroup()
{
	for (_uint i = 0; i < RENDER_END; i++)
	{
		for_each(m_RenderGroupList[i].begin(), m_RenderGroupList[i].end(), CDeleteObj());
		m_RenderGroupList[i].clear();
	}
}

void CRenderer::Render_Priority(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (auto& pGameObject : m_RenderGroupList[RENDER_PRIORITY])
		pGameObject->Render_GameObject();
}

void CRenderer::Render_NoAlpha(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (auto& pGameObject : m_RenderGroupList[RENDER_NONALPHA])
		pGameObject->Render_GameObject();
}

void CRenderer::Render_Alpha(LPDIRECT3DDEVICE9& pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xc0);

	for (auto& pGameObject : m_RenderGroupList[RENDER_ALPHA])
		pGameObject->Render_GameObject();

	pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CRenderer::Render_UI(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (auto& pGameObject : m_RenderGroupList[RENDER_UI])
		pGameObject->Render_GameObject();
}

void CRenderer::Free()
{
	Clear_RenderGroup();
}
