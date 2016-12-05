#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCrtController.h"
#include "cSkinnedMesh.h"
#include "cMapRender.h"

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pController(NULL)
	, m_pZealot(NULL)
	, m_pMap(NULL)
	, _isRuning(false), FrameCnt(0), TimeElapsed(0.0f), FPS(0.0f)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pController);
	SAFE_DELETE(m_pZealot);
	SAFE_DELETE(m_pMap);
	
	g_pSkinnedMeshManager->Destroy();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
	g_pLightShaderManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pController = new cCrtController;
	m_pController->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	m_pZealot = new cSkinnedMesh("Character/", "hero.X");
	m_pZealot->SetAnimationIndex(4);
	m_pZealot->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pMap = new cMapRender;
	m_pMap->Setup();

	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	Getfps(g_pTimeManager->GetDeltaTime());

	if(m_pController)
		m_pController->Update(NULL);
	
	if(m_pCamera)
		m_pCamera->Update(&m_pZealot->GetPosition());

	m_pController->SetfAngleX(m_pCamera->GetfAngleY());

	if (m_pMap)
		m_pMap->Update();

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
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	//¸Ê·»´õ
	if (m_pMap)
		m_pMap->Render(m_pCamera->GetvEye());
	//

	//Ä³¸¯ ·£´õ
	D3DXMatrixScaling(&matS, charsize, charsize, charsize);
	_zMat = *m_pController->GetWorldTM();
	_zMat = matS * _zMat;
	m_pZealot->SetPosition(D3DXVECTOR3(_zMat._41,_zMat._42,_zMat._43));
	m_pZealot->UpdateAndRender(&_zMat);
	//


	// ±×¸®µå
	m_pGrid->Render();
	//

	// fps
	char str[1024];
	sprintf_s(str, "FPS: %.2f", FPS);
	SetWindowText(g_hWnd, str);
	//

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