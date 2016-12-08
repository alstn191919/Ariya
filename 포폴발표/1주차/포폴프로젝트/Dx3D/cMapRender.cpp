#include "stdafx.h"
#include "cMapRender.h"
#include "cObjMap.h"
#include "cObjLoader.h"
#include "cHeightMap.h"
#include "cMtlTex.h"

cMapRender::cMapRender() :  
m_pMapMesh(NULL)
, gpLightingShader(NULL)
, gLightColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f))
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
}

cMapRender::~cMapRender()
{
	SAFE_RELEASE(m_pMapMesh);

	/*for each(auto p in gpLightingShader)
	{
		SAFE_RELEASE(p.Shader);
	}*/

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
	m_pMapMesh = objloader.Load("objMap/objmap.obj", m_vecMtlTex, &mat);
	//ST_SHADER s_shader(D3DXVECTOR3(500.0f, 500.0f, -500.0f));
	ST_SHADER s_shader(D3DXVECTOR3(-15.0f, 2.0f, -7.0f));
	s_shader.Shader = g_pLightShaderManager->Getshader("./shader/NormalMapping_test.fx");
	//s_shader.Shader = g_pLightShaderManager->Getshader("./shader/SpecularMapping.fx");
	gpLightingShader.push_back(s_shader);
	//ST_SHADER s_shader2(D3DXVECTOR3(-45.0f, 5.0f, 10.0f));
	//s_shader2.Shader = g_pLightShaderManager->Getshader("./shader/SpecularMapping.fx");
	//gpLightingShader.push_back(s_shader2);
}
void cMapRender::Update()
{
	
}
void cMapRender::Render(D3DXVECTOR3 _gWorldCameraPosition)
{
	//ī�޶� �� �޾ƿ�
	D3DXVECTOR4 gWorldCameraPosition(D3DXVECTOR4(
		_gWorldCameraPosition.x
		, _gWorldCameraPosition.y
		, _gWorldCameraPosition.z,
		1));

	// ����,��,�������� ��Ʈ���� 
	D3DXMATRIXA16	matWorld, matView, matProjection;
	D3DXMATRIXA16 matWorldView, matWorldViewProjection;
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
	D3DXMatrixMultiply(&matWorldView, &matWorld, &matView);
	D3DXMatrixMultiply(&matWorldViewProjection, &matWorldView, &matProjection);

	// ���̴� ������
	for each(auto p in gpLightingShader)
	{
		p.Shader->SetMatrix("gWorldMatrix", &matWorld);
		p.Shader->SetMatrix("gWorldViewProjectionMatrix", &matWorldViewProjection);
		p.Shader->SetFloat("gRange", 20.0f);
		p.Shader->SetVector("gWorldLightPosition", &p.Position);
		p.Shader->SetVector("gWorldCameraPosition", &gWorldCameraPosition);

		p.Shader->SetVector("gLightColor", &gLightColor);
		for (size_t j = 0; j < m_vecMtlTex.size(); ++j)
		{
			p.Shader->SetTexture("DiffuseMap_Tex", m_vecMtlTex[j]->GetTexture());
			p.Shader->SetTexture("SpecularMap_Tex", m_vecMtlTex[j]->GetTextureS());
			p.Shader->SetTexture("NormalMap_Tex", m_vecMtlTex[j]->GetTextureN());
			UINT numPasses = 0;
			p.Shader->Begin(&numPasses, NULL);
			for (UINT i = 0; i < numPasses; ++i)
			{
				p.Shader->BeginPass(i);
				{
					m_pMapMesh->DrawSubset(j);
				}
				p.Shader->EndPass();
			}
			p.Shader->End();
		}
	}
}