#include "stdafx.h"
#include "cStartScene.h"
#include "cMapRender.h"
#include "cCamera.h"
#include "cCrtController.h"
#include "cGrid.h"
#include "cUIButton.h"
#include "cUIImageView.h"
cStartScene::cStartScene() : pMap(NULL)
, pCamera(NULL)
, m_pController(NULL)
, LogoSprite(NULL)
, Button(NULL)
, State(Button_NULL)
, CameraPosition(D3DXVECTOR3(40,10,80))
, CameraDirection(D3DXVECTOR3(-3, 0, -10))
{

}

cStartScene::~cStartScene()
{
	SAFE_DELETE(pMap);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(m_pController);

	SAFE_RELEASE(Button);
	SAFE_RELEASE(LogoSprite);
}

void cStartScene::Setup()
{
	pMap = new cMapRender;
	pMap->Setup("./objMap/MainMenu.obj", 
		NULL,D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(15.0f, 50.0f, 80.0f),
		5.0f);

	pCamera = new cCamera;
	pCamera->Setup();
	pCamera->Update(&CameraPosition, &CameraDirection);

	m_pController = new cCrtController;
	m_pController->Setup();

	Button = new cUIButton;
	Button->SetDelegate(this);
	Button->SetTexture("./Logo/main_m_over.png", "./Logo/main_m_in.png", "./Logo/main_m_in.png");

	D3DXMATRIXA16 _mat;
	D3DXMatrixTranslation(&_mat, 100, 200, 0);
	Button->SetLocalPos(D3DXVECTOR3(80, 200, 0));
	Button->SetWorld(_mat);
	D3DXCreateSprite(g_pD3DDevice, &LogoSprite);
	D3DXIMAGE_INFO _info;
	ZeroMemory(&_info, sizeof(D3DXIMAGE_INFO));
	Texture = g_pTextureManager->GetSpriteTexture("./Logo/Main_Logo.png", &_info);
	_imgSize.fWidth = _info.Width;
	_imgSize.fHeight = _info.Height;
	State = Button_MAIN;
}
void cStartScene::Update()
{
	pMap->Update();
	Button->Update();
	if (State == Button_END)
	{
		CameraPosition = D3DXVECTOR3(40, 15, -25);
		pCamera->Update(&CameraPosition, &CameraDirection);
	}
}
void cStartScene::Render()
{
	pMap->Render(D3DXVECTOR3(40, 10, 80),140.0f);

	D3DXMATRIXA16 m_matWorld;
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &m_matWorld);
	RECT rc;
	SetRect(&rc, 0, 0, _imgSize.fWidth, _imgSize.fHeight);
	LogoSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	LogoSprite->SetTransform(&m_matWorld);
	LogoSprite->Draw(Texture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	LogoSprite->End();

	Button->Render(LogoSprite);
}

void cStartScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (pCamera)
	{
		pCamera->WndProc(hWnd, message, wParam, lParam);
	}
}

void cStartScene:: OnClick(cUIButton* pSender)
{
	D3DXIMAGE_INFO _info;
	if (State == Button_MAIN)
	{
		Button->SetLocalPos(D3DXVECTOR3(80, 250, 0));
		Texture = g_pTextureManager->GetSpriteTexture("./Logo/Start_Logo.png", &_info);
		Button->SetTexture("./Logo/start_m_over.png",
			"./Logo/start_m_in.png",
			"./Logo/start_m_in.png");
		_imgSize.fWidth = _info.Width;
		_imgSize.fHeight = _info.Height;
		State = Button_START;
	}
	else if (State == Button_START)
	{
		State = Button_END;
		//g_pSceneManager->ChangeScene(Scene_2F);
	}
}