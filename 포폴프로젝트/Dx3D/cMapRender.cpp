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
//(¸Êobj,¼­ÆäÀÌ½º¸Êobj,¸ÊÀ§Ä¡,¼­ÆäÀÌ½º¸ÊÀ§Ä¡,¸ÊÅ©±â)
void cMapRender::Setup(char* fileName, char* surFace,
	D3DXVECTOR3 Position, D3DXVECTOR3 sPosition, D3DXVECTOR3 lightPosition, float Scale)
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixTranslation(&matT, Position.x, Position.y, Position.z);
	D3DXMatrixScaling(&matS, Scale, Scale, Scale);
	mat = matS * matT;

	cObjLoader objloader;
	m_pMapMesh = objloader.Load(fileName, m_vecMtlTex, &mat);
	if (surFace != NULL)
	{
		Load(surFace, sPosition);
	}
	ST_SHADER s_shader(lightPosition);
	s_shader.Shader = g_pLightShaderManager->Getshader("./shader/NormalMapping_Blend.fx");
	gpLightingShader.push_back(s_shader);
}
void cMapRender::Update()
{

}
void cMapRender::Render(D3DXVECTOR3 _gWorldCameraPosition,float lightRange)
{
	//Ä«¸Þ¶ó ´« ¹Þ¾Æ¿È
	D3DXVECTOR4 gWorldCameraPosition(D3DXVECTOR4(
		_gWorldCameraPosition.x
		, _gWorldCameraPosition.y
		, _gWorldCameraPosition.z,
		1));

	// ¿ùµå,ºä,ÇÁ·ÎÁ§¼Ç ¸ÞÆ®¸¯½º 
	D3DXMATRIXA16 matWorld, matView, matProjection;
	D3DXMATRIXA16 matWorldView, matWorldViewProjection;
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
	D3DXMatrixMultiply(&matWorldView, &matWorld, &matView);
	D3DXMatrixMultiply(&matWorldViewProjection, &matWorldView, &matProjection);
	
	// ½¦ÀÌ´õ ·»´õ¸µ
	for each(auto p in gpLightingShader)
	{
		p.Shader->SetMatrix("gWorldMatrix", &matWorld);
		p.Shader->SetMatrix("gWorldViewProjectionMatrix", &matWorldViewProjection);
		p.Shader->SetFloat("gRange", lightRange); // ºû ¹üÀ§ ¼³Á¤
		p.Shader->SetFloat("gAlphaBlend", 0.8f); // ºû ¼¼±â ¾ËÆÄ°ª
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

bool cMapRender::GetHeight(IN float x, OUT float& y, IN float z)
{
	D3DXVECTOR3 vRayPos(x, y + 5, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	float u, v, d;
	for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecSurface[i];
		D3DXVECTOR3 v1 = m_vecSurface[i + 1];
		D3DXVECTOR3 v2 = m_vecSurface[i + 2];
		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			if (d > 6)
			{
				//return false;
			}
			else
			{
				y = (y + 5) - d;
				return true;
			}
		}
	}
	y = 0;
	return false;
}

void cMapRender::Load(char* szSurface, D3DXVECTOR3 Position)
{
	std::vector<D3DXVECTOR3>	vecV;

	FILE* fp = NULL;

	fopen_s(&fp, szSurface, "r");

	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'm')
		{
		}
		else if (szBuf[0] == 'u')
		{
		}
		else if (szBuf[0] == 'g')
		{
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't')
			{
			}
			else if (szBuf[1] == 'n')
			{
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3];
			sscanf_s(szBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; ++i)
			{
				D3DXVECTOR3 p = vecV[aIndex[i] - 1];
				D3DXMATRIXA16 pmat;
				D3DXMatrixIdentity(&pmat);
				pmat._41 = Position.x;
				pmat._42 = Position.y;
				pmat._43 = Position.z;
				D3DXVec3TransformCoord(&p, &p, &pmat);
				m_vecSurface.push_back(p);
			}
		}
	
	}
	fclose(fp);
}