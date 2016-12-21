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
, CameraPosition(1, 0, 23)
, CameraDirection(-2, 1, -7)
, NextCamPos(-1.0f, 0, -2.0f)
, lightDir(-5.0f, 6.0f, -8.0f)
, lightPos(3.2f, 3.5f, 23.0f)
, NextlightPos(1.5f,3.5f,23.0f)
, PrevlightPos(0,0,0)
, Time(0.0f)
, _isLerp(false)
, CamTime(0.0f)
, _isCamLerp(false)
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
		NULL, 
		D3DXVECTOR3(10.94f, -250.0f, -220.5f),
		D3DXVECTOR3(0, 0, 0),
		1.01f);

	pCamera = new cCamera;
	pCamera->Setup();
	pCamera->Update(&CameraPosition, &CameraDirection);

	//m_pController = new cCrtController;
	//m_pController->Setup();

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
	if (pMap)
	{
		pMap->Update();
	}

	if (Button)
	{
		Button->Update();
	}

	if (State == Button_END)
	{
		if (_isCamLerp)
		{
			CamTime += (0.0167 + (CamTime * 0.1f));
			float T = CamTime / 20;
			D3DXVec3Lerp(&CameraPosition, &PrevCamPos, &NextCamPos, T);
			pCamera->Update(&CameraPosition, &CameraDirection);
			if (T > 1.0f)
			{
				_isCamLerp = false;
				SAFE_DELETE(pMap);
				SAFE_DELETE(pCamera);
				SAFE_DELETE(m_pController);

				SAFE_RELEASE(Button);
				SAFE_RELEASE(LogoSprite);
				g_pSceneManager->ChangeScene(Scene_2F);
			}
		}
	}
	else if (State == Button_START || State == Button_END)
	{
		if (_isLerp)
		{
			Time += 0.0167;
			float T = Time / 6;
			D3DXVec3Lerp(&lightPos, &PrevlightPos, &NextlightPos, T);
			if (T > 1.0f)
			{
				_isLerp = false;
				Time = false;
			}
		}
	}

	if (GetKeyState(VK_UP) & 8888)
	{
		lightDir.z += 0.2f;
	}
	else if (GetKeyState(VK_DOWN) & 8888)
	{
		lightDir.z -= 0.2f;
	}
	else if (GetKeyState(VK_LEFT) & 8888)
	{
		lightDir.x += 0.2f;
	}
	else if (GetKeyState(VK_RIGHT) & 8888)
	{
		lightDir.x -= 0.2f;
	}
	else if (GetKeyState('W') & 8888)
	{
		lightPos.z += 0.2f;
	}
	else if (GetKeyState('S') & 8888)
	{
		lightPos.z -= 0.2f;
	}
	else if (GetKeyState('A') & 8888)
	{
		lightPos.x -= 0.2f;
	}
	else if (GetKeyState('D') & 8888)
	{
		lightPos.x += 0.2f;
	}
}
void cStartScene::Render()
{
	if (pMap)
	{
		pMap->Render(lightPos, lightDir, CameraPosition, 33.0f, 1.0f);
	}

	if (State != Button_END)
	{
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
		if (Button)
		{
			Button->Render(LogoSprite);
		}
	}
}

void cStartScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (pCamera)
	{
		pCamera->WndProc(hWnd, message, wParam, lParam);
	}
}

void cStartScene::OnClick(cUIButton* pSender)
{
	D3DXIMAGE_INFO _info;
	if (State == Button_MAIN)
	{
		Texture = g_pTextureManager->GetSpriteTexture("./Logo/Start_Logo.png", &_info);
		SAFE_RELEASE(Button);
		Button = new cUIButton;
		Button->SetDelegate(this);
		Button->SetTexture("./Logo/start_m_over.png",
			"./Logo/start_m_in.png",
			"./Logo/start_m_in.png");
		D3DXMATRIXA16 _mat;
		D3DXMatrixTranslation(&_mat, 80, 250, 0);
		Button->SetLocalPos(D3DXVECTOR3(80, 250, 0));
		Button->SetWorld(_mat);
		_imgSize.fWidth = _info.Width;
		_imgSize.fHeight = _info.Height;
		State = Button_START;
		PrevlightPos = lightPos;
		_isLerp = true;
	}
	else if (State == Button_START)
	{
		State = Button_END;
		_isCamLerp = true;
		PrevCamPos = CameraPosition;
		PrevCamPos.y -= 3.5f;
	}
}