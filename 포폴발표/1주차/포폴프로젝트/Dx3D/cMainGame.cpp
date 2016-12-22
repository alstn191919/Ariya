#include "StdAfx.h"
#include "cMainGame.h"

cMainGame::cMainGame(void) : FPS(0.0f), FrameCnt(0), TimeElapsed(0.0f)
{
	
}

cMainGame::~cMainGame(void)
{
	g_pTextureManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
	g_pLightShaderManager->Destroy();
	ObjectManager->Destroy();
	g_pSceneManager->Destroy();

	g_pObjectManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	SetLight();
	//g_pSceneManager->ChangeScene(Scene_2F);
	g_pSceneManager->ChangeScene(Scene_Main);

}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	Getfps(g_pTimeManager->GetDeltaTime());




	ObjectManager->Update();
	g_pSceneManager->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	g_pSceneManager->Render();
	ObjectManager->Render();

	// fps
	char str[1024];
	sprintf_s(str, "FPS: %.2f", FPS);
	SetWindowText(g_hWnd, str);

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
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