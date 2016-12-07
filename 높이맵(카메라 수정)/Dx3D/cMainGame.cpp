#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cCube.h"
#include "cGrid.h"
#include "cCrtController.h"
#include "cPyramid.h"
#include "cObjMap.h"
#include "cAseLoader.h"
#include "cFrame.h"
#include "cRay.h"
#include "cMtlTex.h"
#include "cObjLoader.h"
#include "cAllocateHierarchy.h"
#include "cSkinnedMesh.h"
#include "cFrostumCulling.h"
#include "cHeightMap.h"

#define RADIUS 0.3f
#define Mapsize	1.0f
#define charsize 0.05f

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pRoot(NULL)
	, m_pGrid(NULL)
	, m_pController(NULL)
	, m_pPyramid(NULL)
	, m_pMap(NULL)
	, m_pAseRoot(NULL)
	, m_pMesh(NULL)
	, m_pMapMesh(NULL)
	, m_pHeight(NULL)
	, m_pZealot(NULL)
	, _isRuning(false), FrameCnt(0), TimeElapsed(0.0f), FPS(0.0f)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pRoot);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pController);
	SAFE_DELETE(m_pHeight);
	SAFE_DELETE(m_pZealot);
	for each(auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p);
	}
	SAFE_RELEASE(m_pPyramid);
	SAFE_RELEASE(m_pMap);
	SAFE_RELEASE(m_pAseRoot);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMapMesh);
	for each (auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
	g_pSkinnedMeshManager->Destroy();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pController = new cCrtController;
	m_pController->Setup();

	D3DXMATRIXA16 matS, matR, matT, mat;
	D3DXMatrixTranslation(&matT, 30, -150, -80.0f);
	D3DXMatrixScaling(&matS, Mapsize, Mapsize, Mapsize);
	D3DXMatrixRotationX(&matR, 0);
	mat = matS * matR * matT;

	//cObjMap* pObjMap = new cObjMap;
	//pObjMap->Load("./obj/2thFloor.obj", NULL, &mat);
	//m_pMap = pObjMap;

	cObjLoader objloader;
	m_pMapMesh = objloader.Load("obj/2thFloor.obj", m_vecMtlTex, &mat);

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	m_pZealot = new cSkinnedMesh("Character/", "hero.X");
	m_pZealot->SetAnimationIndex(4);
	m_pZealot->SetPosition(D3DXVECTOR3(0, 0, 0));

	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	Getfps(g_pTimeManager->GetDeltaTime());

	if(m_pController)
		m_pController->Update(m_pMap);
	
	if(m_pCamera)
		m_pCamera->Update(&m_pZealot->GetPosition(), &m_pController->GetDirection());

	m_pController->SetfAngleX(m_pCamera->GetfAngleY());
	m_pController->SetfAngleY(m_pCamera->GetfAngleX());


	g_pAutoReleasePool->Drain();

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	D3DXMATRIXA16 matI, matT, matS;
	D3DXMatrixIdentity(&matI);
	D3DXMatrixIdentity(&matT);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);


	for (size_t i = 0; i < m_vecMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMtl());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_pMapMesh->DrawSubset(i);
	}

	D3DXMatrixScaling(&matS, charsize, charsize, charsize);
	_zMat = *m_pController->GetWorldTM();
	_zMat = matS * _zMat;
	m_pZealot->SetPosition(D3DXVECTOR3(_zMat._41,_zMat._42,_zMat._43));
	m_pZealot->UpdateAndRender(&_zMat);

	// 그림을 그린다.
	m_pGrid->Render();

	char str[1024];
	sprintf_s(str, "FPS: %.2f", FPS);
	SetWindowText(g_hWnd, str);

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	}


	switch(message)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case 'W':
			{
						_isRuning = true;
						break;
			}
			case 'S':
			{
						_isRuning = true;
						break;
			}
			}
		}
		break;
	case WM_KEYUP:
	{
		   switch (wParam)
		   {
		   case 'W':
		   {
					   _isRuning = false;
					   break;
		   }
		   case 'S':
		   {
					   _isRuning = false;
					   break;
		   }
		   }
	}
		break;
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
		}
		break;
	}
}

void cMainGame::SetLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Direction = D3DXVECTOR3( 1,-1, 1);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void cMainGame:: Getfps(float deltaTime)
{
	FrameCnt++;
	TimeElapsed += deltaTime;
	if (TimeElapsed >= 1.0f)
	{
		FPS = (float)FrameCnt / TimeElapsed;

		TimeElapsed = 0.0f;
		FrameCnt = 0;
	}
}