#include "stdafx.h"
#include "cMapRender.h"
#include "cObjMap.h"
#include "cObjLoader.h"
#include "cHeightMap.h"
#include "cMtlTex.h"

cMapRender::cMapRender() :
m_pMapMesh(NULL)
, gLightColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f))
, gpShadowRenderTarget(NULL)
, gpShadowDepthStencil(NULL)
, gpApplyShadowShader(NULL)
, gpCreateShadowShader(NULL)
, gpBackShadowRenderTarget(NULL)
, gpBackShadowDepthStencil(NULL)
, gpBackCreateShadowShader(NULL)
, LogoSprite(NULL)
, gpFont(NULL)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
}

cMapRender::~cMapRender()
{
	SAFE_RELEASE(m_pMapMesh);

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	SAFE_RELEASE(LogoSprite);
	SAFE_RELEASE(gpFont);
	SAFE_RELEASE(gpShadowDepthStencil);
	SAFE_RELEASE(gpShadowRenderTarget);
	SAFE_RELEASE(gpBackShadowRenderTarget);
	SAFE_RELEASE(gpBackShadowDepthStencil);
}
//(맵obj,서페이스맵obj,맵위치,서페이스맵위치,맵크기)
void cMapRender::Setup(char* fileName, char* surFace,
	D3DXVECTOR3 Position, D3DXVECTOR3 sPosition, float Scale)
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
	D3DXCreateFont(g_pD3DDevice, 20, 10, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, (DEFAULT_PITCH | FF_DONTCARE),
		"Arial", &gpFont);
}
void cMapRender::Update()
{

}
void cMapRender::Render(D3DXVECTOR4* _gWorldLightPosition,D3DXVECTOR4* _gWorldLightDir, D3DXVECTOR3 _gWorldCameraPosition, float lightRange, float* lightPower)
{
	shaderRender(_gWorldLightPosition,_gWorldLightDir, _gWorldCameraPosition, lightRange, lightPower);
	if (GetKeyState(VK_F3) && 8888)
	{
		FrontDebugRender();
	}
	else if (GetKeyState(VK_F4) && 8888)
	{
		BackDebugRender();
	}
	else if (GetKeyState('2'))
	{
		D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

		// 텍스트를 출력할 위치
		RECT rct;
		rct.left = 5;
		rct.right = WIN_WIDTH / 3;
		rct.top = 5;
		rct.bottom = WIN_HEIGHT / 3;

		// 키 입력 정보를 출력
		char str[1024];
		sprintf(str, "%f %f %f", _gWorldCameraPosition.x, _gWorldCameraPosition.y, _gWorldCameraPosition.z);
		gpFont->DrawText(NULL, str, -1, &rct, 0, fontColor);
	}
}

void cMapRender::shaderRender(D3DXVECTOR4* _gWorldLightPosition,D3DXVECTOR4* _gWorldLightDir, D3DXVECTOR3 _gWorldCameraPosition, float lightRange, float* lightPower)
{
	// 맵의 월드행렬
	D3DXMATRIXA16 matTorusWorld;
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matTorusWorld);
	D3DXMatrixIdentity(&matTorusWorld);

	// 광원-투영 행렬을 만든다.
	D3DXMATRIXA16 matLightProjection;
	{
		D3DXMatrixPerspectiveFovLH(&matLightProjection, D3DX_PI / 4.0f, 1, 1, 1000);
	}

	// 그림자 만들기 쉐이더 전역변수들을 설정
	gpCreateShadowShader->SetMatrix("gWorldMatrix", &matTorusWorld);
	gpCreateShadowShader->SetMatrix("gLightProjectionMatrix", &matLightProjection);

	gpBackCreateShadowShader->SetMatrix("gWorldMatrix", &matTorusWorld);
	gpBackCreateShadowShader->SetMatrix("gLightProjectionMatrix", &matLightProjection);

	// 광원-뷰 행렬
	D3DXMATRIXA16 matLightView[10], ReverseMatLightView[10];
	for (size_t i = 0; i < 10; i++)
	{	
			D3DXVECTOR3 vRight;
			D3DXVECTOR3 vLookAt = _gWorldLightDir[i] - _gWorldLightPosition[i];
			D3DXVECTOR3 vEyePt(_gWorldLightPosition[i].x, _gWorldLightPosition[i].y, _gWorldLightPosition[i].z);
			D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
			D3DXVec3Cross(&vRight, &vUpVec, &vLookAt);
			D3DXVec3Cross(&vUpVec, &vLookAt, &vRight);
			D3DXMatrixLookAtLH(&matLightView[i], &vEyePt, &vLookAt, &vUpVec);
			vLookAt.x = -vLookAt.x; 
			vLookAt.z = -vLookAt.z;
			D3DXMatrixLookAtLH(&ReverseMatLightView[i], &vEyePt, &vLookAt, &vUpVec);
	}
		// 그림자 입히기 쉐이더 전역변수들을 설정
		gpCreateShadowShader->SetMatrixArray("LightViewMatrix", matLightView,10);
		gpCreateShadowShader->SetVectorArray("WorldLightPosition", _gWorldLightPosition, 10);

		gpBackCreateShadowShader->SetVectorArray("WorldLightPosition", _gWorldLightPosition, 10);
		gpBackCreateShadowShader->SetMatrixArray("LightViewMatrix", ReverseMatLightView, 10);
	
		gpApplyShadowShader->SetVectorArray("WorldLightPosition", _gWorldLightPosition,10);
		gpApplyShadowShader->SetMatrixArray("LightViewMatrix", matLightView,10);
		gpApplyShadowShader->SetFloatArray("AlphaBlend", lightPower, 10); // 빛 세기

//////////////////////////////////////////////////////////////////////
///////////////////전면부 그림자랜더 생성/////////////////////////////
//////////////////////////////////////////////////////////////////////

	// 현재 하드웨어 벡버퍼와 깊이버퍼
	LPDIRECT3DSURFACE9 pHWBackBuffer = NULL;
	LPDIRECT3DSURFACE9 pHWDepthStencilBuffer = NULL;
	g_pD3DDevice->GetRenderTarget(0, &pHWBackBuffer);
	g_pD3DDevice->GetDepthStencilSurface(&pHWDepthStencilBuffer);

	// 그림자 맵의 렌더타깃과 깊이버퍼를 사용한다.
	LPDIRECT3DSURFACE9 pShadowSurface = NULL;
	if (SUCCEEDED(gpShadowRenderTarget->GetSurfaceLevel(0, &pShadowSurface)))
	{
		g_pD3DDevice->SetRenderTarget(0, pShadowSurface);
		pShadowSurface->Release();
		pShadowSurface = NULL;
	}
	else
	{
		assert("전면부 렌더타깃 사용 실패" && false);
	}
	g_pD3DDevice->SetDepthStencilSurface(gpShadowDepthStencil);

	// 저번 프레임에 그렸던 그림자 정보를 지움
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		0xFFFFFFFF,
		1.0f, 0);

	for (size_t j = 0; j < m_vecMtlTex.size(); ++j)
	{
		UINT numPasses = 0;
		gpCreateShadowShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				gpCreateShadowShader->BeginPass(i);
				{
					
						m_pMapMesh->DrawSubset(j);
					
				}
				gpCreateShadowShader->EndPass();
			}
		}
		gpCreateShadowShader->End();
	}

	// 하드웨어 백버퍼/깊이버퍼를 사용한다.
	g_pD3DDevice->SetRenderTarget(0, pHWBackBuffer);
	g_pD3DDevice->SetDepthStencilSurface(pHWDepthStencilBuffer);

	pHWBackBuffer->Release();
	pHWBackBuffer = NULL;

	pHWDepthStencilBuffer->Release();
	pHWDepthStencilBuffer = NULL;

//////////////////////////////////////////////////////////////////////
///////////////////후면부 그림자랜더 생성/////////////////////////////
//////////////////////////////////////////////////////////////////////

	// 현재 하드웨어 벡버퍼와 깊이버퍼
	g_pD3DDevice->GetRenderTarget(0, &pHWBackBuffer);
	g_pD3DDevice->GetDepthStencilSurface(&pHWDepthStencilBuffer);

	// 그림자 맵의 렌더타깃과 깊이버퍼를 사용한다.
	pShadowSurface = NULL;
	if (SUCCEEDED(gpBackShadowRenderTarget->GetSurfaceLevel(0, &pShadowSurface)))
	{
		g_pD3DDevice->SetRenderTarget(0, pShadowSurface);
		pShadowSurface->Release();
		pShadowSurface = NULL;
	}
	else
	{
		assert("후면부 렌더타깃 사용 실패" && false);
	}
	g_pD3DDevice->SetDepthStencilSurface(gpBackShadowDepthStencil);

	// 저번 프레임에 그렸던 그림자 정보를 지움
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		0xFFFFFFFF,
		1.0f, 0);

	for (size_t j = 0; j < m_vecMtlTex.size(); ++j)
	{
		UINT numPasses = 0;
		gpBackCreateShadowShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				gpBackCreateShadowShader->BeginPass(i);
				{

					m_pMapMesh->DrawSubset(j);

				}
				gpBackCreateShadowShader->EndPass();
			}
		}
		gpBackCreateShadowShader->End();
	}

	// 하드웨어 백버퍼/깊이버퍼를 사용한다.
	g_pD3DDevice->SetRenderTarget(0, pHWBackBuffer);
	g_pD3DDevice->SetDepthStencilSurface(pHWDepthStencilBuffer);

	pHWBackBuffer->Release();
	pHWBackBuffer = NULL;

	pHWDepthStencilBuffer->Release();
	pHWDepthStencilBuffer = NULL;

//////////////////////////////////////////////////////////////////////
//////////////////////////그림자 랜더링///////////////////////////////
//////////////////////////////////////////////////////////////////////

	// 뷰,프로젝션 행렬
	D3DXMATRIXA16 matView, matProjection;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
		
	// 그림자 입히기 쉐이더 전역변수들을 설정
	gpApplyShadowShader->SetMatrix("gViewProjectionMatrix", &(matView * matProjection));
	gpApplyShadowShader->SetMatrix("gLightProjectionMatrix", &matLightProjection);
	gpApplyShadowShader->SetMatrix("gWorldMatrix", &matTorusWorld);
	gpApplyShadowShader->SetVector("gWorldCameraPosition", &D3DXVECTOR4(_gWorldCameraPosition, 1));

	gpApplyShadowShader->SetFloat("gRange", lightRange); // 빛 범위 설정
	gpApplyShadowShader->SetFloat("ApplyShadowShader_ApplyShadowTorus_Pixel_Shader_gRange", lightRange);

	gpApplyShadowShader->SetTexture("ShadowMap_Tex", gpShadowRenderTarget);
	gpApplyShadowShader->SetTexture("BackShadowMap_Tex", gpBackShadowRenderTarget);

	for (size_t j = 0; j < m_vecMtlTex.size(); j++)
	{
		gpApplyShadowShader->SetTexture("DiffuseMap_Tex", m_vecMtlTex[j]->GetTexture());
		gpApplyShadowShader->SetTexture("SpecularMap_Tex", m_vecMtlTex[j]->GetTextureS());
		gpApplyShadowShader->SetTexture("NormalMap_Tex", m_vecMtlTex[j]->GetTextureN());
		// 쉐이더를 시작
		UINT numPasses = 0;
		gpApplyShadowShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				gpApplyShadowShader->BeginPass(i);
				{
					m_pMapMesh->DrawSubset(j);
				}
				gpApplyShadowShader->EndPass();
			}
		gpApplyShadowShader->End();
		}
	}
}

void cMapRender::Shadowinit(char* ApplyShaderFilename, char* CreateShaderFilename, char* BackCreateShaderFilename)
{
	//셰이더 파일 로딩
	gpApplyShadowShader = g_pLightShaderManager->Getshader(ApplyShaderFilename);
	gpCreateShadowShader = g_pLightShaderManager->Getshader(CreateShaderFilename);
	gpBackCreateShadowShader = g_pLightShaderManager->Getshader(BackCreateShaderFilename);

	// 렌더타깃을 만든다.
	const int shadowMapSize = 1024;

	//앞
	if (FAILED(g_pD3DDevice->CreateTexture(shadowMapSize, shadowMapSize,
		1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F,
		D3DPOOL_DEFAULT, &gpShadowRenderTarget, NULL)))
	{
		assert("렌더타깃 생성실패" && false);
	}

	// 그림자 맵과 동일한 크기의 깊이버퍼도 만들어줘야 한다.
	if (FAILED(g_pD3DDevice->CreateDepthStencilSurface(shadowMapSize, shadowMapSize,
		D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, TRUE,
		&gpShadowDepthStencil, NULL)))
	{
		assert("깊이버퍼 생성실패" && false);
	}

	//뒤
	if (FAILED(g_pD3DDevice->CreateTexture(shadowMapSize, shadowMapSize,
		1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F,
		D3DPOOL_DEFAULT, &gpBackShadowRenderTarget, NULL)))
	{
		assert("렌더타깃 생성실패" && false);
	}

	// 그림자 맵과 동일한 크기의 깊이버퍼도 만들어줘야 한다.
	if (FAILED(g_pD3DDevice->CreateDepthStencilSurface(shadowMapSize, shadowMapSize,
		D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, TRUE,
		&gpBackShadowDepthStencil, NULL)))
	{
		assert("깊이버퍼 생성실패" && false);
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

void cMapRender::FrontDebugRender()
{
	if (!LogoSprite)
	{
		D3DXCreateSprite(g_pD3DDevice, &LogoSprite);
	}
	D3DXMATRIXA16 m_matWorld;
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &m_matWorld);
	RECT rc;
	SetRect(&rc, 0, 0, 1024, 1024);

	LogoSprite->Begin(D3DXSPRITE_SORT_TEXTURE);
	LogoSprite->SetTransform(&m_matWorld);
	LogoSprite->Draw(gpShadowRenderTarget,
		&rc,
		NULL,
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	LogoSprite->End();
}

void cMapRender::BackDebugRender()
{
	if (!LogoSprite)
	{
		D3DXCreateSprite(g_pD3DDevice, &LogoSprite);
	}
	D3DXMATRIXA16 m_matWorld;
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &m_matWorld);
	RECT rc;
	SetRect(&rc, 0, 0, 1024, 1024);

	LogoSprite->Begin(D3DXSPRITE_SORT_TEXTURE);
	LogoSprite->SetTransform(&m_matWorld);
	LogoSprite->Draw(gpBackShadowRenderTarget,
		&rc,
		NULL,
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	LogoSprite->End();
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