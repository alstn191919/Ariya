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
오브젝트 매니져 매뉴얼 작성자 : 강병민
2016 12 06
오브젝트 메뉴얼 사용 가이드 라인 제공
타입별 샘플 제공
ADDobject 만 해주시면 나머지 상호작용 처리및 OBB처리는  다 objectManager가 자동으로 처리해줍니다.
=============================================================================================================================================
*/

void c2FScene::SetUITest()
{
	D3DXVECTOR3 Scal;						//스케일... 
	D3DXVECTOR3 p(10, 0, 0);				//포지션 위치 설정용
	ST_SPHERE pt;							//피킹용 구 크기를 잡아줌

	D3DXVECTOR3 Min(-10, 0, -10);			//OBB 크기를 정해줌(위치는 오브젝트 월드좌표 자동으로 따라감)
	D3DXVECTOR3 Max(12, 30, 10);			//OBB 크기를 정해줌(위치는 오브젝트 월드좌표 자동으로 따라감)

	//1. OBB 충돌 오브젝트 추가 (바운딩 박스 안에 플레이어가 들어올시 이벤트 처리해줄수있습니다.)
	//ADDobject 오브젝트를 추가합니다.

	//여기부터 엘리베이터 부분임돠
	//엘리베이터 버튼(구피킹용으로 임시로 medkit 가져옴)
	Scal = D3DXVECTOR3(0.01, 0.01, 0.01);
	p = D3DXVECTOR3(63.6, -13.5, -105.5);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1.5f;
	ObjectManager->ADDobject("Medkit", "medkit1.x", p, Scal, pt, OBJ_TYPE::Switch, "E버튼을 누르시오");

	//엘리베이터 통
	Scal = D3DXVECTOR3(1.1, 1.1, 1.1);
	p = D3DXVECTOR3(62, -17, -108);
	ObjectManager->ADDobject("Elivator", "Elivator.X", p, Scal, pt, OBJ_TYPE::Room, "");

	//엘리베이터 문 2개
	Scal = D3DXVECTOR3(26.0f, 27.0f, 26.0f);
	p = D3DXVECTOR3(60.35f, -17, -105.5f);
	Min = D3DXVECTOR3(-0.035, 0, -0.035);
	Max = D3DXVECTOR3(0.035, 0.075, 0.035);
	//문1 (index 2)
	ObjectManager->ADDobject("Elivator/door", "elidoor.X", p, Scal, Min, Max);
	Scal = D3DXVECTOR3(26.0f, 27.0f, 26.0f);
	p = D3DXVECTOR3(62.95f, -17, -105.5f);
	//문2 (index 3)
	ObjectManager->ADDobject("Elivator/door", "elidoor.X", p, Scal, Min, Max);

	//엘리베이터 숫자 띄우기위한 폰트설정
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
ObjectManager->getOpen();

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);



	//2.상호작용 오브젝트 추가
	//인자값이 좀더 많이 필요합니다.

	/*p.y = -658 * 0.7;
	p.x = 357 * 0.7;
	p.z = 680 * 0.7;
	ObjectManager->ADDobject("door", "door.X", p		,	0.7, pt,			OBJ_TYPE::door, "문 왼쪽마우스 클릭");*/
	//인자값				 폴더명    파일명   위치벡터, 크기 ,구(체크용),	 오브젝트 타입 , 충돌시 메세지
	//오브젝트 타입은 OBJ_TYPE:: 하시면 보실수있습니다. 그냥 door 라고 써도 물론 됩니다.(보기 편하시라고 했어요)

	p.y = 10;
	p.x = 0;
	p.z = 0;


	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("cot", "baby_cot.X", p, Scal, pt, OBJ_TYPE::Switch, "E버튼을 눌러주세요");
	//스위치 타입 이벤트 처리는 각각 다른 처리할것같아 따로 안하고 메시지 출력만 해놨습니다.
	//해당 인덱스 얻어오셔서 처리해 주시면 되겠습니다!

	/*p.y = 0;
	p.x = 0;
	p.z = 1;


	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 10;

	ObjectManager->ADDobject("door3", "Door.obj", p, 1, pt, OBJ_TYPE::Switch, "문인것같다.");*/

	//화장실문
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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max,NULL);
	//ObjectManager->ADDobject("Beds", "screen.x", p, 0.1, pt, OBJ_TYPE::door, "문인것같다.");

	Scal = D3DXVECTOR3(0.1, 0.1, 0.1);
	p = D3DXVECTOR3(0, 0, 0);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("Medkit", "medkit1.x", p, Scal, pt, OBJ_TYPE::item, "");
	//         아이템 타입은 충돌시 클릭하게 되면 카메라 고정될텐데 esc 누르면 풀리게 해놨습니다.
	//처음방 문

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, D3DX_PI/2);


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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, -D3DX_PI);

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, D3DX_PI);

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, NULL);


	//여기 부터 밑에층 문
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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, D3DX_PI/2);

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, -D3DX_PI);

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, -D3DX_PI);


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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, -D3DX_PI);

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "문인것같다.", Min, Max, -D3DX_PI / 2);


	//밑에는 UI설정


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

void c2FScene::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pController = new cCrtController;
	m_pController->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	m_pHero = new cHero("Character/", "hero.X");
	m_pHero->SetAnimationIndex(5);							//기본(제자리)
	m_pHero->SetPosition(D3DXVECTOR3(0, 0, 0));

	m_pMap = new cMapRender;
	m_pMap->Setup("objMap/objmap.obj",
		"objMap/2FsurFace.obj",
		D3DXVECTOR3(2.0f, -126.5f, 9.0f),
		D3DXVECTOR3(15.0f, -126.5f, 7.0f), D3DXVECTOR3(-10.0f, 2.0f, 4.0f), 1.0f);

	//오브젝트 매니져 사용 메뉴얼 
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

	//맵렌더
	if (m_pMap)
		m_pMap->Render(m_pCamera->GetvEye(),1000.0f);
	//

	//캐릭 랜더
	D3DXMatrixScaling(&matS, charsizeX, charsizeY, charsizeZ);
	_zMat = *m_pController->GetWorldTM();
	_zMat = matS * _zMat;
	m_pHero->SetPosition(D3DXVECTOR3(_zMat._41, _zMat._42, _zMat._43));
	m_pHero->UpdateAndRender(&_zMat);	
	//

	// 그리드
	//m_pGrid->Render();
	//

	//obb 충돌시 처리는 어차피 플레이어에 대한 처리밖에 없으므로 그냥 논리형 반환값으로 가짐
	//obb 처리는 오브젝트 충돌시 못지나가게 하는용도와 앉을때 장애물 있을시 못일어나게 하는 용도 뿐이라 이렇게 처리함.

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


	D3DXMATRIXA16 a;
	D3DXMatrixIdentity(&a);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &a);

	m_fPassedActionTime += g_pTimeManager->GetDeltaTime();
	float t = m_fPassedActionTime / m_fActionTime;

	if (t > 0.0f && t <= 10.0f)
		m_vecText[0]->DrawSubset(0);
	else if (t > 10.0f && t <= 20.0f)
		m_vecText[1]->DrawSubset(0);
	else if (t > 20.0f && t <= 30.0f)
		m_vecText[2]->DrawSubset(0);
	else if (t > 30.0f && t <= 40.0f)
		m_vecText[3]->DrawSubset(0);

}

void c2FScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	}

	//키보드 처리
	//현재 임시값 space 누르고 있으면 달린다
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
					   //방향 설정 : 정면
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