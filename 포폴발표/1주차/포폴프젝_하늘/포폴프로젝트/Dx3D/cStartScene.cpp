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
	////////////////////���� ��ġ///////////////////////
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
	////////////////////���� ����///////////////////////
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
	////////////////////���� ����////////////////////////
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
���� �Ŵ��� �Ŵ��� : ���ϴ�
2016 12 23
	g_pSoundManager
wav ���ϸ� ����մϴ�.
���� �Ÿ� �� �浹�� ���� ����/�д� ���� �ڵ�� �߰����� �ʾҽ��ϴ�.
==============================================
*/
void cStartScene::SoundManual()
{
	//���� �߰� ���
	//													LPSTR	LPSTR	D3DXVECTOR3		SOUND_MAP
	//g_pSoundManager->AddSound("���ϸ�", "���");
	//g_pSoundManager->AddSound("���ϸ�", "���", "�� ���� ��ġ");
	//g_pSoundManager->AddSound("���ϸ�", "���", "�� ���� ��ġ", "�����");
	//���ϸ��� .wav�� ������ �ʾƵ� ����մϴ�.
	//g_pSoundManager->AddSound("mainTheme", "./Sound/");

	//���� �÷���
	//DSBPLAY_LOOPING �÷��� ������ �ݺ� ����մϴ�.
	//�� ���� ����� �÷��� ���ڰ��� ����θ� �˴ϴ�.
	//										LPSTR ���ϸ�, DWORD �÷���
	g_pSoundManager->Play("mainTheme", DSBPLAY_LOOPING);

	//���� ����
	//										LPSTR ���ϸ�
	//g_pSoundManager->Stop("mainTheme");

	//���Ƿ� ���� �� �д� �����ϱ�
	//��� ������ G_SOUND_VOLUME * ������ ����˴ϴ�.
	//���ÿ��� : 1~10 ������ ���� ���� ����. �Ҽ��� �� �ڸ����� ����˴ϴ�.
	//													LPSTR ���ϸ�,		long ����
	g_pSoundManager->SetVolume("mainTheme", 10);

	//�д�: �¿� ���� �Ҹ� ũ���Դϴ�. 
	//-10,000 ~ 10,000 ���� ������ �� �ֽ��ϴ�. 
	//0�� �⺻���̸�, �ּҰ��� �������� ���ʿ���, �ִ񰪿� �������� �����ʿ��� �Ҹ��� ���ϴ�.
	//										LPSTR ���ϸ�, long �дװ� 
	//g_pSoundManager->SetPan("mainTheme", 0);

	//�������� �������� ���� ����� ���� �Լ��� ����� �� �����ϴ�. (������)

	//���� ������ ����
	//���� ���������� ĳ���� ��ġ���� ���� ����/�д� ������ �����մϴ�.
	//���� �ҽ����� �߰��Ǿ����� �ʽ��ϴ�.
	//													LPSTR ���ϸ�, �����ǰ�
	//g_pSoundManager->SetPosition("mainTheme", D3DXVECTOR3(0, 0, 0));

	//���� �����ǿ� ���� ����/�д� ����
	//�ش� �� ������Ʈ �κп� �־��ּž� �մϴ�. (������ ������Ʈ �ʿ�)
	//												LPSTR ���ϸ�, ��� ĳ����/ī�޶��� ��ġ
	//g_pSoundManager->SetVolumeAndPan("mainTheme", D3DXVCETOR3(CRTPosition));

}