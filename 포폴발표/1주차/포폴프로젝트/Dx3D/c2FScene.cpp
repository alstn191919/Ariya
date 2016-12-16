#include "stdafx.h"
#include "c2FScene.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCrtController.h"
#include "cSkinnedMesh.h"
#include "cMapRender.h"
#include "cAllocateHierarchy2.h"
#include "cSkinnedMesh2.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"
#include "cOBB.h"
#include"cHero.h"

enum eUITag
{
	E_TEXTVIEW = 3,
	E_BUTTON1,
	E_BUTTON2,
};

c2FScene::c2FScene() : m_pCamera(NULL)
, m_pGrid(NULL)
, m_pController(NULL)
, m_pHero(NULL)
, m_pMap(NULL)
, m_isCrtRunning(false)
, m_isCrtCrawling(false)
, m_pSkinnedMesh(NULL)
, m_fPassedActionTime(0.0f)
, m_fActionTime(2.0f)
, m_b1stFloor(true)
, m_bisClicked(false)
{
	//g_bOBBCollision = false;
}

c2FScene::~c2FScene()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pController);
	SAFE_DELETE(m_pHero);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pSkinnedMesh);
}

/*
=============================================================================================================================================
������Ʈ �Ŵ��� �Ŵ��� �ۼ��� : ������
2016 12 06
������Ʈ �޴��� ��� ���̵� ���� ����
Ÿ�Ժ� ���� ����
ADDobject �� ���ֽø� ������ ��ȣ�ۿ� ó���� OBBó����  �� objectManager�� �ڵ����� ó�����ݴϴ�.
=============================================================================================================================================
*/

void c2FScene::SetUITest()
{
	D3DXVECTOR3 Scal;						//������... 
	D3DXVECTOR3 p(10, 0, 0);				//������ ��ġ ������
	ST_SPHERE pt;							//��ŷ�� �� ũ�⸦ �����

	D3DXVECTOR3 Min(-10, 0, -10);			//OBB ũ�⸦ ������(��ġ�� ������Ʈ ������ǥ �ڵ����� ����)
	D3DXVECTOR3 Max(12, 30, 10);			//OBB ũ�⸦ ������(��ġ�� ������Ʈ ������ǥ �ڵ����� ����)

	//1. OBB �浹 ������Ʈ �߰� (�ٿ�� �ڽ� �ȿ� �÷��̾ ���ý� �̺�Ʈ ó�����ټ��ֽ��ϴ�.)
	//ADDobject ������Ʈ�� �߰��մϴ�.

	//������� ���������� �κ��ӵ�
	//���������� ��ư(����ŷ������ �ӽ÷� medkit ������)
	Scal = D3DXVECTOR3(0.01, 0.01, 0.01);
	p = D3DXVECTOR3(63.6, -13.5, -105.5);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1.5f;
	ObjectManager->ADDobject("Medkit", "medkit1.x", p, Scal, pt, OBJ_TYPE::Switch, "E�����ּ���");

	//���������� ��
	Scal = D3DXVECTOR3(1.1, 1.1, 1.1);
	p = D3DXVECTOR3(62, -17, -108);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 0;
	ObjectManager->ADDobject("Elivator", "Elivator.X", p, Scal, pt, OBJ_TYPE::Room, "341", D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), -D3DX_PI / 2);

	//���������� �� 2��
	Scal = D3DXVECTOR3(26.0f, 27.0f, 26.0f);
	p = D3DXVECTOR3(60.35f, -17, -105.5f);
	Min = D3DXVECTOR3(-0.035, 0, -0.035);
	Max = D3DXVECTOR3(0.035, 0.075, 0.035);
	//��1 (index 2)
	ObjectManager->ADDobject("Elivator/door", "elidoor.X", p, Scal, pt, OBJ_TYPE::Eledoor, "" ,Min, Max, -D3DX_PI / 2);
	Scal = D3DXVECTOR3(26.0f, 27.0f, 26.0f);
	p = D3DXVECTOR3(62.95f, -17, -105.5f);
	//��2 (index 3)
	ObjectManager->ADDobject("Elivator/door", "elidoor.X", p, Scal, pt, OBJ_TYPE::Eledoor, "" , Min, Max, -D3DX_PI / 2);

	//���������� ���� �������� ��Ʈ����
	LOGFONT	lf;
	HDC hdc = CreateCompatibleDC(0);
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 0.1;
	lf.lfWidth = 0.1;
	lf.lfWeight = 1;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = DEFAULT_CHARSET;

	strcpy(lf.lfFaceName, "Times New Roman");

	HFONT hFont, hFontOld;
	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	

	m_vecText.resize(4);

	D3DXCreateText(g_pD3DDevice, hdc, "1", 0.1f, 0.01f, &m_vecText[0], 0, 0);
	D3DXCreateText(g_pD3DDevice, hdc, "2", 0.1f, 0.01f, &m_vecText[1], 0, 0);
	D3DXCreateText(g_pD3DDevice, hdc, "3", 0.1f, 0.01f, &m_vecText[2], 0, 0);
	D3DXCreateText(g_pD3DDevice, hdc, "4", 0.1f, 0.01f, &m_vecText[3], 0, 0);

	ZeroMemory(&m_TextMtl, sizeof(_D3DMATERIAL9));
	m_TextMtl.Ambient = m_TextMtl.Diffuse = m_TextMtl.Specular = D3DXCOLOR(0.6f, 0.1f, 0.1f, 1.0f);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);



	//2.��ȣ�ۿ� ������Ʈ �߰�
	//���ڰ��� ���� ���� �ʿ��մϴ�.

	//ȭ��ǹ�
	p.z = 0;
	p.y = -0.6;
	p.x = -17;
	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x + 2;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 1;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(0.8, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max,NULL);
	//ó���� ��

	p.z = 5;
	p.y = -0.6;
	p.x = -23;
	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.vCenter.z = pt.vCenter.z - 3.8;
	pt.isPicked = false;
	pt.fRadius = 1.5;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.3, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI/2);


	p.z = -23.5;
	p.y = -0.6;
	p.x = -16.5;
	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x - 3;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 1;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.5, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI);

	p.z = -23.5;
	p.y = -0.6;
	p.x = 8;
	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x - 3;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 1;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.5, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI);

	p.z = -23.5;
	p.y = -0.6;
	p.x = -30;
	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x + 2;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 3;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.9, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, NULL);


	//���� ���� �ؿ��� ��
	// -6.9, -16.9, -57.7
	p.x = -6;
	p.y = -17.5;
	p.z = -53;
	
	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x + 2;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.vCenter.z = pt.vCenter.z - 2;
	pt.isPicked = false;
	pt.fRadius = 2;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.5, 1, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI/2);

	//6.3   , -16.9 , -44.3
	p.x = 11;
	p.y = -17.5;
	p.z = -45;

	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x - 3;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 2;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.5, 1, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI);

	//35.8  , -17.5 , -44.5

	p.x = 41;
	p.y = -17.5;
	p.z = -45;

	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x - 3;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 2;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.5, 1, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI);


	//63.7 , -17.5 ,44.5

	p.x = 68;
	p.y = -17.5;
	p.z = -45;

	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x - 3;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 2;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.5, 1, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI);

	//	77, -17.5, -51
	// -6.9, -16.9, -57.7
	p.x = 76.5;
	p.y = -17.5;
	p.z = -57;

	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
//	pt.vCenter.x = pt.vCenter.x + 2;
	pt.vCenter.y = pt.vCenter.y + 4;
	pt.vCenter.z = pt.vCenter.z + 3.8;
	pt.isPicked = false;
	pt.fRadius = 2;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.5, 1, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI / 2);


	//�ؿ��� UI����


	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIImageView* pImageView = new cUIImageView;
	D3DXIMAGE_INFO stImageInfo;
	ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetSpriteTexture(
		"./UI/panel-info.png.png",
		&stImageInfo);
	pImageView->SetTexture(pTexture);
	pImageView->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	pImageView->SetLocalPos(D3DXVECTOR3(100, 50, 0));
	m_pUIRoot = pImageView;


	pTextView = new cUITextView;
	pTextView->SetText("");
	pTextView->SetFont(g_pFontManager->GetFont(cFontManager::E_FT_NORMAL));
	pTextView->SetLocalPos(D3DXVECTOR3(100, 100, 0));
	pTextView->SetSize(ST_SIZE(321, 200));
	pTextView->SetDrawTextFormat(DT_CENTER | DT_TOP | DT_WORDBREAK);
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	pTextView->SetTag(E_TEXTVIEW);
	pTextView->AutoRelease();
	//	m_pUIRoot = pTextView;
	m_pUIRoot->AddChild(pTextView);
	//ObjectManager->evt();
	//ObjectManager->v_Event[0]->update();
	//ObjectManager->m_Event["������"]->update();
}

void c2FScene::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pController = new cCrtController;
	m_pController->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	m_pHero = new cHero("Character/", "hero.X");
	m_pHero->SetAnimationIndex(5);							//�⺻(���ڸ�)
	m_pHero->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pMap = new cMapRender;
	m_pMap->Setup("objMap/objmap.obj",
		"objMap/2FsurFace.obj",
		D3DXVECTOR3(2.0f, -126.5f, 9.0f),
		D3DXVECTOR3(15.0f, -126.5f, 7.0f),D3DXVECTOR3(2.1f, 4.0f, 3.1f), 1.0f);

	//������Ʈ �Ŵ��� ��� �޴��� 
	SetUITest();

	m_pObb = new cOBB;
	m_pObb->Setup(m_pHero->GetMesh());

	m_pObbObj = new cOBB;
	m_pObbObj->Setup(m_pHero->GetMesh());

}
void c2FScene::Update()
{
	if (m_pController)
		m_pController->Update(m_pMap, m_pObb);

	if (m_pCamera)
		m_pCamera->Update(&m_pHero->GetPosition(), &m_pController->GetDirection());

	m_pController->SetfAngleX(m_pCamera->GetfAngleY());

	if (m_pMap)
		m_pMap->Update();

	ObjectManager->Update();
	

	if (ObjectManager->isPinked() &&
		(ObjectManager->getPinkedObjType() == OBJ_TYPE::Switch) || (ObjectManager->getPinkedObjType() == OBJ_TYPE::door))
	{
		pTextView->SetText(ObjectManager->getText());
	}

	g_pAutoReleasePool->Drain();
}
void c2FScene::Render()
{
	D3DXMATRIXA16 matI, matT, matS;
	D3DXMatrixIdentity(&matI);
	D3DXMatrixIdentity(&matT);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	//�ʷ���
	if (m_pMap)
		m_pMap->Render(m_pCamera->GetvEye(),30.0f);

	if (ObjectManager->Getselect_index()==6)
	{
		ObjectManager->getObject(6)->ObjVIEWRender(m_pCamera->GetvLookat());
	}
	//

	//ĳ�� ����
	D3DXMatrixScaling(&matS, charsizeX, charsizeY, charsizeZ);
	_zMat = *m_pController->GetWorldTM();
	_zMat = matS * _zMat;
	m_pHero->SetPosition(D3DXVECTOR3(_zMat._41, _zMat._42, _zMat._43));
	m_pHero->UpdateAndRender(&_zMat);	
	

	// �׸���
	//m_pGrid->Render();
	//

	//obb �浹�� ó���� ������ �÷��̾ ���� ó���ۿ� �����Ƿ� �׳� ���� ��ȯ������ ����
	//obb ó���� ������Ʈ �浹�� ���������� �ϴ¿뵵�� ������ ��ֹ� ������ ���Ͼ�� �ϴ� �뵵 ���̶� �̷��� ó����.

	g_pD3DDevice->SetTexture(0, NULL);
	if (ObjectManager->GetCollision())
	{
		m_pObb->DebugRender(D3DCOLOR_XRGB(255, 0, 0));
	}
	else
	{
		m_pObb->DebugRender(D3DCOLOR_XRGB(255, 255, 255));
	}

	ObjectManager->Render();


	/*if (cOBB::IsCollision(m_pObb, ObjectManager->GetInstance()->`))
	{
	m_pObbObj->DebugRender(D3DCOLOR_XRGB(255, 0, 0));
	}
	else
	{
	m_pObbObj->DebugRender(D3DCOLOR_XRGB(255, 255, 255));
	}*/

	if (m_pUIRoot && ObjectManager->isPinked() &&
		(ObjectManager->getPinkedObjType() == OBJ_TYPE::Switch) || (ObjectManager->getPinkedObjType() == OBJ_TYPE::door))
	{
		m_pUIRoot->Render(m_pSprite);
	}


	//���� ���������� �����ϴ°� ( ���������� �� )
	D3DXMATRIXA16 matES,matET,matER, matEWorld;
	D3DXMatrixScaling(&matES, 0.4f, 0.4f, 0.4f);
	D3DXMatrixIdentity(&matET);
	D3DXMatrixTranslation(&matET, 61.75f, -11.4f, -105.f);
	D3DXMatrixRotationY(&matER, D3DX_PI);
	matEWorld = matES * matER * matET;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matEWorld);
	g_pD3DDevice->SetMaterial(&m_TextMtl);

	if (ObjectManager->getPinkedObjType() == OBJ_TYPE::Switch)
	{
		if (GetAsyncKeyState('E') & 0x8000)
		{
			m_bisClicked = true;
		}
	}
	float t = 0;
	if (m_b1stFloor)
	{
		if (m_bisClicked)
		{
			m_fPassedActionTime += g_pTimeManager->GetDeltaTime();
			t = m_fPassedActionTime / m_fActionTime;

			if (t <= 3.0f)
				m_vecText[0]->DrawSubset(0);
			else if (t > 3.0f && t <= 6.0f)
				m_vecText[1]->DrawSubset(0);
			else if (t > 6.0f && t <= 9.0f)
				m_vecText[2]->DrawSubset(0);
			else if (t > 9.0)
			{
				m_vecText[3]->DrawSubset(0);
				t = 10;
				ObjectManager->setIndexOpen(true);
				if (ObjectManager->getPinkedObjType() == OBJ_TYPE::Switch)
				{
					if (GetAsyncKeyState('E') & 0x8000)
					{
						ObjectManager->setIndexOpen(false);
						m_bisClicked = true;
						m_b1stFloor = false;
						m_fPassedActionTime = 0;
					}
				}
			}

		}
	}
	else
	{
		if (m_bisClicked)
		{
			m_fPassedActionTime += g_pTimeManager->GetDeltaTime();
			t = m_fPassedActionTime / m_fActionTime;

			if (t <= 3.0f)
				m_vecText[3]->DrawSubset(0);
			else if (t > 3.0f && t <= 6.0f)
				m_vecText[2]->DrawSubset(0);
			else if (t > 6.0f && t <= 9.0f)
				m_vecText[1]->DrawSubset(0);
			else if (t > 9.0f)
			{
				m_vecText[0]->DrawSubset(0);
				t = 10;
				ObjectManager->setIndexOpen(true);
			}

		}
	}

	//���� ���������� �����ϴ°� ( ���������� ���� ���� )
	D3DXMatrixScaling(&matES, 0.4f, 0.4f, 0.4f);
	D3DXMatrixIdentity(&matET);
	D3DXMatrixTranslation(&matET, 61.55f, -11.56f, -105.9f);
	matEWorld = matES * matET;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matEWorld);

	if (ObjectManager->getPinkedObjType() == OBJ_TYPE::Switch)
	{
		if (GetAsyncKeyState('E') & 0x8000)
		{
			m_bisClicked = true;
		}
	}
	//float t = 0;
	if (m_b1stFloor)
	{
		if (m_bisClicked)
		{
			m_fPassedActionTime += g_pTimeManager->GetDeltaTime();
			t = m_fPassedActionTime / m_fActionTime;

			if (t <= 3.0f)
				m_vecText[0]->DrawSubset(0);
			else if (t > 3.0f && t <= 6.0f)
				m_vecText[1]->DrawSubset(0);
			else if (t > 6.0f && t <= 9.0f)
				m_vecText[2]->DrawSubset(0);
			else if (t > 9.0)
			{
				m_vecText[3]->DrawSubset(0);
				t = 10;
				ObjectManager->setIndexOpen(true);
				if (ObjectManager->getPinkedObjType() == OBJ_TYPE::Switch)
				{
					if (GetAsyncKeyState('E') & 0x8000)
					{
						ObjectManager->setIndexOpen(false);
						m_bisClicked = true;
						m_b1stFloor = false;
						m_fPassedActionTime = 0;
					}
				}
			}

		}
	}
	else
	{
		if (m_bisClicked)
		{
			m_fPassedActionTime += g_pTimeManager->GetDeltaTime();
			t = m_fPassedActionTime / m_fActionTime;

			if (t <= 3.0f)
				m_vecText[3]->DrawSubset(0);
			else if (t > 3.0f && t <= 6.0f)
				m_vecText[2]->DrawSubset(0);
			else if (t > 6.0f && t <= 9.0f)
				m_vecText[1]->DrawSubset(0);
			else if (t > 9.0f)
			{
				m_vecText[0]->DrawSubset(0);
				t = 10;
				ObjectManager->setIndexOpen(true);
			}

		}
	}


}


void c2FScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	}

	//Ű���� ó��
	//���� �ӽð� space ������ ������ �޸���
	switch (message)
	{
	case WM_KEYDOWN:
	{
		   switch (wParam)
		   {
		   case VK_SPACE:
		   {
			   m_isCrtRunning = true;
							m_pHero->SetState(CRT_STATE::CRT_RUN);
							break;
		   }
		   case 'W':
		   {
					   //���� ���� : ����
					   m_pHero->SetDirection(ENUM_DIRECTION::DR_FORWARD);
					   if (!m_isCrtRunning)
					   {
						   if (m_isCrtCrawling)
						   {
							   m_pHero->SetState(CRT_STATE::CRT_CRAWL);
						   }
						   else
						   {
							   m_pHero->SetState(CRT_STATE::CRT_WALK);
						   }
					   }
					   break;
		   }
		   case 'S':
		   {
					   m_pHero->SetDirection(ENUM_DIRECTION::DR_BACKWARD);

					   if (!m_isCrtRunning)
					   {
						   if (m_isCrtCrawling)
						   {
							   m_pHero->SetState(CRT_STATE::CRT_CRAWL);
						   }
						   else
						   {
							   m_pHero->SetState(CRT_STATE::CRT_WALK);
						   }
					   }
					   break;
		   }
		   case 'A':
		   {
					   m_pHero->SetDirection(ENUM_DIRECTION::DR_LEFT);

					   if (!m_isCrtRunning)
					   {
						   if (m_isCrtCrawling)
						   {
							   m_pHero->SetState(CRT_STATE::CRT_CRAWL);
						   }
						   else
						   {
							   m_pHero->SetState(CRT_STATE::CRT_WALK);
						   }
					   }
		   }
		   case 'D':
		   {
					   m_pHero->SetDirection(ENUM_DIRECTION::DR_RIGHT);

					   if (!m_isCrtRunning)
					   {
						   if (m_isCrtCrawling)
						   {
							   m_pHero->SetState(CRT_STATE::CRT_CRAWL);
						   }
						   else
						   {
							   m_pHero->SetState(CRT_STATE::CRT_WALK);
						   }
					   }
		   }
	   }
	}
		break;

	case WM_KEYUP:
	{
					 switch (wParam)
					 {
					 case VK_SPACE:
					 {
									 m_isCrtRunning = false;
									  m_pHero->SetState(CRT_STATE::CRT_IDLE);
									  break;
					 }
					 case 'W':
					 {
								 if (!m_isCrtCrawling)
								 {
									 m_pHero->SetState(CRT_STATE::CRT_IDLE);
								 }
								 break;
					 }
					 case 'S':
					 {
								 if (!m_isCrtCrawling)
								 {
									 m_pHero->SetState(CRT_STATE::CRT_IDLE);
								 }
								 break;
					 }
					 case 'A':
					 {
								 if (!m_isCrtCrawling)
								 {
									 m_pHero->SetState(CRT_STATE::CRT_IDLE);
								 }
					 }
					 case 'D':
					 {
								 if (!m_isCrtCrawling)
								 {
									 m_pHero->SetState(CRT_STATE::CRT_IDLE);
								 }
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