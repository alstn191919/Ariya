#include "StdAfx.h"
#include "cMainGame.h"
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
#include "cHero.h"

enum eUITag
{
	E_TEXTVIEW = 3,
	E_BUTTON1,
	E_BUTTON2,
};

cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pController(NULL)
	, m_pHero(NULL)
	, m_pMap(NULL)
	, _isRuning(false), FrameCnt(0), TimeElapsed(0.0f), FPS(0.0f)
	, m_pSkinnedMesh(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pController);
	SAFE_DELETE(m_pHero);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pSkinnedMesh);

	ObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
	g_pLightShaderManager->Destroy();
}

/*
=============================================================================================================================================
������Ʈ �Ŵ��� �Ŵ��� �ۼ��� : ������ 
  2016 12 06 
������Ʈ �޴��� ��� ���̵� ���� ����
Ÿ�Ժ� ���� ����
=============================================================================================================================================
*/
void cMainGame::SetUITest()
{
	D3DXVECTOR3 p(10, 0, 0);
	ST_SPHERE pt;

	//1. ��ɾ��� ������Ʈ �߰� (ȭ��� �׳� ���̴� ��)
	//ADDobject ������Ʈ�� �߰��մϴ�.
	ObjectManager->ADDobject("Lamp", "Lamp.X", p, 1);
	//		���ڰ�:      	 ������   ���ϸ� , ��ġ, ������Ʈ ũ��  -> �̷��� �߰��Ͻø� ��ɾ��� �׳� ������Ʈ�� �߰��˴ϴ�.

	p.x = -10;
	p.y = 10;

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 10;

	//2.��ȣ�ۿ� ������Ʈ �߰�
	//���ڰ��� ���� ���� �ʿ��մϴ�.
	ObjectManager->ADDobject("Beds", "screen.X", p		,	1, pt,			OBJ_TYPE::door, "�� ���ʸ��콺 Ŭ��");
	//���ڰ�				 ������    ���ϸ�   ��ġ����, ũ�� ,��(üũ��),	 ������Ʈ Ÿ�� , �浹�� �޼���
	//������Ʈ Ÿ���� OBJ_TYPE:: �Ͻø� ���Ǽ��ֽ��ϴ�. �׳� door ��� �ᵵ ���� �˴ϴ�.(���� ���Ͻö�� �߾��)

	p.y = 0;
	p.x = 0;
	p.z = 30;


	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 10;

	ObjectManager->ADDobject("cot", "baby_cot.X", p, 1, pt, OBJ_TYPE::Switch, "E��ư�� �����ּ���");
	//����ġ Ÿ�� �̺�Ʈ ó���� ���� �ٸ� ó���ҰͰ��� ���� ���ϰ� �޽��� ��¸� �س����ϴ�.
	//�ش� �ε��� �����ż� ó���� �ֽø� �ǰڽ��ϴ�!

	/*p.y = 0;
	p.x = 0;
	p.z = 1;


	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 10;

	ObjectManager->ADDobject("door", "door.x", p, 1, pt, OBJ_TYPE::Switch, "���ΰͰ���.");
*/
	p.z = -30;

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 10;

	ObjectManager->ADDobject("Medkit", "medkit1.x", p, 1, pt, OBJ_TYPE::item, "");
	//         ������ Ÿ���� �浹�� Ŭ���ϰ� �Ǹ� ī�޶� �������ٵ� esc ������ Ǯ���� �س����ϴ�.
	p.z = 0;



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
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pController = new cCrtController;
	m_pController->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	m_pHero = new cHero("Character/", "hero.X");
	m_pHero->SetAnimationIndex(4);
	m_pHero->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pMap = new cMapRender;
	m_pMap->Setup();

	//������Ʈ �Ŵ��� ��� �޴��� 
	SetUITest();

	SetLight();

}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	Getfps(g_pTimeManager->GetDeltaTime());

	if(m_pCamera)
		m_pCamera->Update(&m_pHero->GetPosition(),&m_pController->GetDirection());
	if (m_pController)
		m_pController->Update(NULL);
	m_pController->SetfAngleX(m_pCamera->GetfAngleY());
	m_pController->SetfAngleY(m_pCamera->GetfAngleX());

	if (m_pMap)
		m_pMap->Update();
	//ObjectManager->Update();



	//if (ObjectManager->isPinked() &&
	//	(ObjectManager->getPinkedObjType() == OBJ_TYPE::Switch) || (ObjectManager->getPinkedObjType() == OBJ_TYPE::door))
	//{
	//	pTextView->SetText(ObjectManager->getText());
	//}
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



	//�ʷ���
	if (m_pMap)
		m_pMap->Render(m_pCamera->GetvEye());
	//

	//ĳ�� ����
	D3DXMatrixScaling(&matS, charsize, charsize, charsize);
	_zMat = *m_pController->GetWorldTM();
	_zMat = matS * _zMat;
	m_pHero->SetPosition(D3DXVECTOR3(_zMat._41,_zMat._42,_zMat._43));
	m_pHero->UpdateAndRender(&_zMat);
	//


	// �׸���
	m_pGrid->Render();
	//

	//ObjectManager->Render();

	/*cOBB obb_Zealot, obb_Obj;
	D3DXMATRIXA16 matworld;
	obb_Zealot.Setup(m_pZealot);
	obb_Obj.Setup(D3DXVECTOR3(3, 0, 3), D3DXVECTOR3(6, 3, 6));
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matworld);
	obb_Obj.Update(&matworld);
	matworld._41 = m_pZealot->GetPosition().x;
	matworld._42 = m_pZealot->GetPosition().y;
	matworld._43 = m_pZealot->GetPosition().z;
	obb_Zealot.Update(&matworld);
	obb_Obj.DebugRender(D3DCOLOR_ARGB(255, 0, 255, 0));
	obb_Zealot.DebugRender(D3DCOLOR_ARGB(255, 0, 255, 0));
	if (cOBB::IsCollision(&obb_Zealot, &obb_Obj))
	{
		obb_Obj.DebugRender(D3DCOLOR_ARGB(255, 0, 255, 0));
		obb_Zealot.DebugRender(D3DCOLOR_ARGB(255, 0, 255, 0));
	}
	else
	{
		obb_Obj.DebugRender(D3DCOLOR_ARGB(255, 0, 255, 255));
		obb_Zealot.DebugRender(D3DCOLOR_ARGB(255, 0, 255, 255));
	}*/
	//if (m_pUIRoot && ObjectManager->isPinked() &&
	//	(ObjectManager->getPinkedObjType() == OBJ_TYPE::Switch) || (ObjectManager->getPinkedObjType() == OBJ_TYPE::door))
	//{
	//	m_pUIRoot->Render(m_pSprite);
	//}

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