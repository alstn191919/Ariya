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
, LogoSprite(NULL)
, Button(NULL)
, Texture(NULL)
, State(Button_NULL)
, CameraPosition(1, 0, 23)
, CameraDirection(-2, 1, -7)
, NextCamPos(-1.0f, 0, -5.0f)
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

	SAFE_RELEASE(Button);
	SAFE_RELEASE(LogoSprite);

	g_pSoundManager->Stop("mainTheme");
}

void cStartScene::Setup()
{
	pMap = new cMapRender;
	pMap->Setup("./objMap/MainMenu.obj",
		NULL, 
		D3DXVECTOR3(10.94f, -250.0f, -220.5f),
		D3DXVECTOR3(0, 0, 0),
		1.01f);
	pMap->Shadowinit("./shader/ApplyShadow.fx", "./shader/CreateShadow.fx", "./shader/CreateShadow.fx");
	////////////////////조명 위치///////////////////////
	v_LightPos[0] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[1] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[2] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[3] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[4] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[5] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[6] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[7] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[8] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	v_LightPos[9] = D3DXVECTOR4(3.2f, 3.5f, 23.0f,1.0f);
	////////////////////조명 방향///////////////////////
	v_LightDir[0] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[1] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[2] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[3] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[4] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[5] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[6] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[7] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[8] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	v_LightDir[9] = D3DXVECTOR4(-5.0f, 6.0f, -8.0f,0);
	////////////////////조명 세기////////////////////////
	v_LightPow[0] = 1.0f;
	v_LightPow[1] = 1.0f;
	v_LightPow[2] = 1.0f;
	v_LightPow[3] = 1.0f;
	v_LightPow[4] = 1.0f;
	v_LightPow[5] = 1.0f;
	v_LightPow[6] = 1.0f;
	v_LightPow[7] = 1.0f;
	v_LightPow[8] = 1.0f;
	v_LightPow[9] = 1.0f;
	pCamera = new cCamera;
	pCamera->Setup();
	pCamera->Update(&CameraPosition, &CameraDirection, NULL);

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

	ST_SPHERE _sphere;
	ZeroMemory(&_sphere, sizeof(ST_SPHERE));

	ObjectManager->ADDobject("Wheelchair", "wheelchair.x",
		D3DXVECTOR3(-2, 3, 18), D3DXVECTOR3(0.4f, 0.4f, 0.4f), 
		_sphere, OBJ_TYPE::OBJECT,
		"", 
		D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), 
		D3DX_PI + D3DX_PI / 2.5, 
		lightPos);

	SoundManual();
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
			pCamera->Update(&CameraPosition, &CameraDirection, NULL);
			g_pSoundManager->SetVolume("mainTheme", (10.0f - CamTime));
			if (T > 1.0f)
			{
				SAFE_DELETE(pMap);
				SAFE_DELETE(pCamera);

				SAFE_RELEASE(Button);
				SAFE_RELEASE(LogoSprite);
				ObjectManager->Destroy();
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
			ObjectManager->getObject(0)->SetLightPositon(lightPos);
			if (T > 1.0f)
			{
				_isLerp = false;
				Time = false;
			}
		}
	}
/*
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
	}*/
}
void cStartScene::Render()
{
	if (pMap)
	{
		pMap->Render(v_LightPos, v_LightDir, CameraPosition, 33.0f, v_LightPow);
	}

	if (State != Button_END)
	{
		D3DXMATRIXA16 m_matWorld;
		D3DXMatrixIdentity(&m_matWorld);
		//g_pD3DDevice->GetTransform(D3DTS_WORLD, &m_matWorld);
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


/*
=============================================
사운드 매니저 매뉴얼 : 최하늘
2016 12 23
	g_pSoundManager
wav 파일만 기능합니다.
현재 거리 및 충돌에 따른 볼륨/패닝 조절 코드는 추가되지 않았습니다.
==============================================
*/
void cStartScene::SoundManual()
{
	//사운드 추가 방법
	//													LPSTR	LPSTR	D3DXVECTOR3		SOUND_MAP
	//g_pSoundManager->AddSound("파일명", "경로");
	//g_pSoundManager->AddSound("파일명", "경로", "맵 상의 위치");
	//g_pSoundManager->AddSound("파일명", "경로", "맵 상의 위치", "사운드맵");
	//파일명에는 .wav를 붙이지 않아도 기능합니다.
	//g_pSoundManager->AddSound("mainTheme", "./Sound/");

	//사운드 플레이
	//DSBPLAY_LOOPING 플래그 지정시 반복 재생합니다.
	//한 번만 재생시 플래그 인자값을 비워두면 됩니다.
	//										LPSTR 파일명, DWORD 플래그
	g_pSoundManager->Play("mainTheme", DSBPLAY_LOOPING);

	//사운드 정지
	//										LPSTR 파일명
	//g_pSoundManager->Stop("mainTheme");

	//임의로 볼륨 및 패닝 적용하기
	//모든 볼륨은 G_SOUND_VOLUME * 값으로 변경됩니다.
	//사용시에는 : 1~10 사이의 수로 설정 가능. 소숫점 두 자리까지 적용됩니다.
	//													LPSTR 파일명,		long 볼륨
	g_pSoundManager->SetVolume("mainTheme", 10);

	//패닝: 좌우 사운드 소리 크기입니다. 
	//-10,000 ~ 10,000 까지 설정할 수 있습니다. 
	//0이 기본값이며, 최소값에 가까울수록 왼쪽에서, 최댓값에 가까울수록 오른쪽에서 소리가 납니다.
	//										LPSTR 파일명, long 패닝값 
	//g_pSoundManager->SetPan("mainTheme", 0);

	//포지션이 설정되지 않은 사운드는 이하 함수를 사용할 수 없습니다. (에러남)

	//사운드 포지션 설정
	//사운드 포지션으로 캐릭터 위치값에 따른 볼륨/패닝 변경이 가능합니다.
	//현재 소스에는 추가되어있지 않습니다.
	//													LPSTR 파일명, 포지션값
	//g_pSoundManager->SetPosition("mainTheme", D3DXVECTOR3(0, 0, 0));

	//사운드 포지션에 따른 볼륨/패닝 적용
	//해당 씬 업데이트 부분에 넣어주셔야 합니다. (지속적 업데이트 필요)
	//												LPSTR 파일명, 듣는 캐릭터/카메라의 위치
	//g_pSoundManager->SetVolumeAndPan("mainTheme", D3DXVCETOR3(CRTPosition));

}