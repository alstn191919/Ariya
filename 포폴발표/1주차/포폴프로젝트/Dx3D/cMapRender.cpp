#include "stdafx.h"
#include "cMapRender.h"
#include "cObjMap.h"
#include "cObjLoader.h"
#include "cHeightMap.h"
#include "cMtlTex.h"

cMapRender::cMapRender() :  
m_pMapMesh(NULL)
, gpLightingShader(NULL)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
}

cMapRender::~cMapRender()
{
	SAFE_RELEASE(m_pMapMesh);

	for each(auto p in gpLightingShader)
	{
		SAFE_RELEASE(p.Shader);
	}

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
}

void cMapRender:: Setup()
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixTranslation(&matT, MapPositionX, MapPositionY, MapPositionZ);
	D3DXMatrixScaling(&matS, Mapsize, Mapsize, Mapsize);
	mat = matS * matT;

	cObjLoader objloader;
	m_pMapMesh = objloader.Load("objMap/testFloor.obj", m_vecMtlTex, &mat);
	ST_SHADER s_shader(D3DXVECTOR3(-15.0f, 6.0f, 10.0f));
	s_shader.Shader = g_pLightShaderManager->Getshader("./shader/Lighting.fx");
	gpLightingShader.push_back(s_shader);
}
void cMapRender::Update()
{
	
}
void cMapRender::Render(D3DXVECTOR3 _gWorldCameraPosition)
{
	//Ä«¸Þ¶ó ´« ¹Þ¾Æ¿È
	D3DXVECTOR4 gWorldCameraPosition(D3DXVECTOR4(
		_gWorldCameraPosition.x
		, _gWorldCameraPosition.y
		, _gWorldCameraPosition.z,
		1));

	// ¿ùµå,ºä,ÇÁ·ÎÁ§¼Ç ¸ÞÆ®¸¯½º 
	D3DXMATRIXA16	matWorld, matView, matProjection;
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	// ½¦ÀÌ´õ ·»´õ¸µ
	for each(auto p in gpLightingShader)
	{
		p.Shader->SetMatrix("gWorldMatrix", &matWorld);
		p.Shader->SetMatrix("gViewMatrix", &matView);
		p.Shader->SetMatrix("gProjectionMatrix", &matProjection);

		p.Shader->SetVector("gWorldLightPosition", &p.Position);
		p.Shader->SetVector("gWorldCameraPosition", &gWorldCameraPosition);

		UINT numPasses = 0;
		p.Shader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				p.Shader->BeginPass(i);
				{
					for (size_t i = 0; i < m_vecMtlTex.size(); ++i)
					{
						g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMtl());
						g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
						m_pMapMesh->DrawSubset(i);
					}
				}
				p.Shader->EndPass();
			}
		}
		p.Shader->End();
	}
}