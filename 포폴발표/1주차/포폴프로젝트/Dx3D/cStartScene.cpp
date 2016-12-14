#include "stdafx.h"
#include "cStartScene.h"
#include "cMapRender.h"
#include "cCamera.h"
#include "cCrtController.h"
#include "cGrid.h"

cStartScene::cStartScene() : pMap(NULL)
, pCamera(NULL)
, m_pController(NULL)
, m_pGrid(NULL)
{

}

cStartScene::~cStartScene()
{
	SAFE_DELETE(pMap);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(m_pController);
}

void cStartScene::Setup()
{
	pMap = new cMapRender;
	pMap->Setup("./objMap/MainMenu.obj", 
		NULL,
		D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(5.0f, 2.0f, 90.0f),
		5.0f);

	pCamera = new cCamera;
	pCamera->Setup();
	pCamera->Update(&D3DXVECTOR3(43, 20, 90), &D3DXVECTOR3(-3, 0, -10));
	m_pController = new cCrtController;
	m_pController->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

}
void cStartScene::Update()
{
	pMap->Update();
	//m_pController->Update(NULL, NULL);
	//pCamera->Update(&D3DXVECTOR3(43,20,90), &D3DXVECTOR3(-4,0,-10));
	//m_pController->SetfAngleX(pCamera->GetfAngleY());
}
void cStartScene::Render()
{
	pMap->Render(D3DXVECTOR3(100,100,100),120.0f);
	m_pGrid->Render();
}

void cStartScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (pCamera)
	{
		pCamera->WndProc(hWnd, message, wParam, lParam);
	}
}