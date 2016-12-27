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
#include "cUI.h"



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
, gpFont(NULL)
{
	//g_bOBBCollision = false;
	g_pSoundManager->Stop("mainTheme");
	D3DXCreateFont(g_pD3DDevice, 20, 10, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, (DEFAULT_PITCH | FF_DONTCARE),
		"Arial", &gpFont);
}

c2FScene::~c2FScene()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pController);
	SAFE_DELETE(m_pHero);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_RELEASE(m_pUIRoot);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(gpFont);
	for each(auto p in m_vecText)
	{
		SAFE_RELEASE(p);
	}}

/*
=============================================================================================================================================
������Ʈ �Ŵ��� �Ŵ��� �ۼ��� : ������
2016 12 06
������Ʈ �޴��� ��� ���̵� ���� ����
Ÿ�Ժ� ���� ����
ADDobject �� ���ֽø� ������ ��ȣ�ۿ� ó���� OBBó����  �� objectManager�� �ڵ����� ó�����ݴϴ�.
=============================================================================================================================================
*/

void c2FScene::SetAddObj_2F()
{
	D3DXVECTOR3 Scal;						//������... 
	D3DXVECTOR3 p(10, 0, 0);				//������ ��ġ ������
	ST_SPHERE pt;							//��ŷ�� �� ũ�⸦ �����

	D3DXVECTOR3 Min(-10, 0, -10);			//OBB ũ�⸦ ������(��ġ�� ������Ʈ ������ǥ �ڵ����� ����)
	D3DXVECTOR3 Max(12, 30, 10);			//OBB ũ�⸦ ������(��ġ�� ������Ʈ ������ǥ �ڵ����� ����)

	//1. OBB �浹 ������Ʈ �߰� (�ٿ�� �ڽ� �ȿ� �÷��̾ ���ý� �̺�Ʈ ó�����ټ��ֽ��ϴ�.)
	//ADDobject ������Ʈ�� �߰��մϴ�.
	addElivator();
	//������� ���������� �κ��ӵ�
	//���������� ��ư(����ŷ������ �ӽ÷� medkit ������)
	


	//2.��ȣ�ۿ� ������Ʈ �߰�
	//���ڰ��� ���� ���� �ʿ��մϴ�.

	/*p.y = -658 * 0.7;
	p.x = 357 * 0.7;
	p.z = 680 * 0.7;
	ObjectManager->ADDobject("door", "door.X", p		,	0.7, pt,			OBJ_TYPE::door, "�� ���ʸ��콺 Ŭ��");*/
	//���ڰ�				 ������    ���ϸ�   ��ġ����, ũ�� ,��(üũ��),	 ������Ʈ Ÿ�� , �浹�� �޼���
	//������Ʈ Ÿ���� OBJ_TYPE:: �Ͻø� ���Ǽ��ֽ��ϴ�. �׳� door ��� �ᵵ ���� �˴ϴ�.(���� ���Ͻö�� �߾��)



	Min = D3DXVECTOR3(-0.535, 0, -0.035);
	Max = D3DXVECTOR3(0.535, 0.075, 0.035);

	Scal = D3DXVECTOR3(0.4, 0.4, 0.4);
	p = D3DXVECTOR3(0, 2, 10);
	//28.0,3,-56.2
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;
	//std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, D3DXVECTOR3 Min, D3DXVECTOR3 Max, float Angle
	ObjectManager->ADDobject("Wheelchair", "wheelchair.x", p, Scal, Min, Max, D3DX_PI, D3DXVECTOR3(39.4, 3.3, -28.2));

	//p.y = 0;
	//p.x = 0;
	//p.z = 10;

	//Scal = D3DXVECTOR3(0.1, 0.1, 0.1);

	//pt.vCenter = p;
	//pt.isPicked = false;
	//pt.fRadius = 1;

	//ObjectManager->ADDobject("cot", "baby_cot.X", p, Scal, pt, OBJ_TYPE::OBJECT, "E��ư�� �����ּ���");
	//����ġ Ÿ�� �̺�Ʈ ó���� ���� �ٸ� ó���ҰͰ��� ���� ���ϰ� �޽��� ��¸� �س����ϴ�.
	//�ش� �ε��� �����ż� ó���� �ֽø� �ǰڽ��ϴ�!

	/*p.y = 0;
	p.x = 0;
	p.z = 1;
	

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 10;

	ObjectManager->ADDobject("door3", "Door.obj", p, 1, pt, OBJ_TYPE::Switch, "���ΰͰ���.");*/

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max,NULL,D3DXVECTOR3(-8.7f,6.0f,-3.5f));
	//ObjectManager->ADDobject("Beds", "screen.x", p, 0.1, pt, OBJ_TYPE::door, "���ΰͰ���.");

	Scal = D3DXVECTOR3(0.1, 0.1, 0.1);
	p = D3DXVECTOR3(0, 0, -3);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("Medkit", "medkit1.x", p, Scal, pt, OBJ_TYPE::item, "", D3DXVECTOR3(-2.3f, 6.0f, -2.3f));
	//         ������ Ÿ���� �浹�� Ŭ���ϰ� �Ǹ� ī�޶� �������ٵ� esc ������ Ǯ���� �س����ϴ�.
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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI / 2, D3DXVECTOR3(-27.7f, 3.3f, 3.5f));


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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI, D3DXVECTOR3(-4.3f, 6.0f, -18.6f));

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI, D3DXVECTOR3(-4.3f, 6.0f, -18.6f));

	p.z = -23.5;
	p.y = -0.6;
	p.x = -28.5;
	//0.468685;07.50739;5.85491;
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x + 2;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 3;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.1, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, NULL,D3DXVECTOR3(-27.3f,6.0f,-31.6f));


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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI / 2, D3DXVECTOR3(-20.7f, -12.4f, -55.2f));

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI, D3DXVECTOR3(32.7f, -12.4f, -40.2f));

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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI, D3DXVECTOR3(32.7f, -12.4f, -40.2f));


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
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI, D3DXVECTOR3(32.7f, -12.4f, -40.2f));

	//	77, -17.5, -51
	// -6.9, -16.9, -57.7
	p.x = 76.5;
	p.y = -17.5;
	p.z = -57;

	//0.468685;07.50739;5.85491;����
	pt.vCenter = p;
//	pt.vCenter.x = pt.vCenter.x + 2;
	pt.vCenter.y = pt.vCenter.y + 4;
	pt.vCenter.z = pt.vCenter.z + 3.8;
	pt.isPicked = false;
	pt.fRadius = 2;


	Min = D3DXVECTOR3(0, 0, -1);
	Max = D3DXVECTOR3(-0.5, 3, 3);

	Scal = D3DXVECTOR3(1.5, 1, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI / 2, D3DXVECTOR3(60.7f, -12.4f, -55.2f));

	Min = D3DXVECTOR3(3, -2, -0.5);
	Max = D3DXVECTOR3(-3, 1, 0);

	Scal = D3DXVECTOR3(2, 2, 2);
	p = D3DXVECTOR3(-65.5, 1, -29.1);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("t", "chair.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, -D3DX_PI / 2, D3DXVECTOR3(-49.7f, 6.0f, -28.7f));



	Scal = D3DXVECTOR3(2, 2, 2);
	p = D3DXVECTOR3(59.6, 1, -29);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("t", "chair.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, D3DX_PI / 2, D3DXVECTOR3(39.4f, 6.0f, -28.2f));

	Scal = D3DXVECTOR3(2, 2, 2);
	p = D3DXVECTOR3(59.6, 1, -36);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("t", "chair.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, D3DX_PI / 2, D3DXVECTOR3(39.4f, 6.0f, -28.2f));


	Scal = D3DXVECTOR3(2, 2, 2);
	p = D3DXVECTOR3(3, -16, -64.7);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("t", "chair.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, D3DX_PI, D3DXVECTOR3(39.4f, 6.0f, -28.2f));

	Scal = D3DXVECTOR3(2, 2, 2);
	p = D3DXVECTOR3(16.6, -16, -64.7);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("t", "chair.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, D3DX_PI, D3DXVECTOR3(32.7f, -11.4f, -55.2f));

	Scal = D3DXVECTOR3(2, 2, 2);
	p = D3DXVECTOR3(43.4, -16, -64.7);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("t", "chair.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, D3DX_PI, D3DXVECTOR3(32.7f, -11.4f, -55.2f));

	Scal = D3DXVECTOR3(2, 2, 2);
	p = D3DXVECTOR3(68, -16, -64.7);

	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("t", "chair.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, D3DX_PI, D3DXVECTOR3(32.7f, -11.4f, -55.2f));
	//BalanceBarBox
	Min = D3DXVECTOR3(0, 0, 0);
	Max = D3DXVECTOR3(0, 0, 0);
	Scal = D3DXVECTOR3(1, 1, 0.1);
	p = D3DXVECTOR3(28, 0, -56.2);
	//28.0,3,-56.2
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("BalanceBarBox", "BalanceBox.x", p, Scal, pt, OBJ_TYPE::item, "", Min, Max, D3DX_PI, D3DXVECTOR3(-8.7f, 6.0f, 3.5f));

	//-16.2,3.3,-3.16
	Scal = D3DXVECTOR3(1, 1, 0.1);
	p = D3DXVECTOR3(-16.2, 0, -5.16);
	//28.0,3,-56.2
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;

	ObjectManager->ADDobject("BalanceBarBox", "BalanceBox.x", p, Scal, pt, OBJ_TYPE::item, "", Min, Max, D3DX_PI, D3DXVECTOR3(-13.2f, 6.0f, -28.6f));


	//������ �� ��(ħ��)
	p.y = 0;
	p.x = 3.3;
	p.z = -5.5;
	Scal = D3DXVECTOR3(0.09, 0.09, 0.09);
	Min = D3DXVECTOR3(5, 3, 5);
	Max = D3DXVECTOR3(-1, 0, -1);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 0;
	ObjectManager->ADDobject("cot", "baby_cot.X", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, NULL, D3DXVECTOR3(-2.3f, 6.0f, -2.3f));

	//������ �� ��(Ŀư)
	p.y = 2;
	p.x = 2.7f;
	p.z = -2.5;
	Scal = D3DXVECTOR3(0.15, 0.15, 0.15);
	Min = D3DXVECTOR3(1, 3, 10);
	Max = D3DXVECTOR3(-1, 0, -10);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 0;
	ObjectManager->ADDobject("Beds", "screen.X", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, D3DX_PI / 2, D3DXVECTOR3(-8.7f, 6.0f, 3.5f));

	//������ �� ��(å��)
	p.y = 0;
	p.x = 5.99f;
	p.z = 6.6;
	Scal = D3DXVECTOR3(0.062, 0.062, 0.062);
	Min = D3DXVECTOR3(10, 10, 10);
	Max = D3DXVECTOR3(-10, 0, -10);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 0;
	ObjectManager->ADDobject("Elivator/door", "desk.X", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, NULL, D3DXVECTOR3(-8.7f, 6.0f, 3.5f));

	//������ �� ��(����)
	p.y = 2.3;
	p.x = 4.99f;
	p.z = 2.5f;
	Scal = D3DXVECTOR3(0.022, 0.022, 0.022);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 0;
	ObjectManager->ADDobject("Lamp", "lamp.X", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, D3DX_PI, D3DXVECTOR3(-8.7f, 6.0f, 3.5f));


	//�޵�Ŷ
	Scal = D3DXVECTOR3(0.08, 0.08, 0.08);
	p = D3DXVECTOR3(4.4, 0, 5.8);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;
	ObjectManager->ADDobject("Medkit", "medkit1.x", p, Scal, pt, OBJ_TYPE::item, "", D3DXVECTOR3(-2.3f, 6.0f, -2.3f));
	//������ Ÿ���� �浹�� Ŭ���ϰ� �Ǹ� ī�޶� �������ٵ� esc ������ Ǯ���� �س����ϴ�.


	//����
	Scal = D3DXVECTOR3(0.0092, 0.0092, 0.0092);
	p = D3DXVECTOR3(3, 0.2, 3.2);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;
	ObjectManager->ADDobject("t", "Chair_1.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, NULL, D3DXVECTOR3(-8.7f, 6.0f, 3.5f));

	//ĳ���
	Min = D3DXVECTOR3(1, 1, 1);
	Max = D3DXVECTOR3(-1, 0, -1);
	Scal = D3DXVECTOR3(0.72, 0.72, 0.72);
	p = D3DXVECTOR3(-2.3, 1.3, -5.5);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 1;
	ObjectManager->ADDobject("Basiccabinet", "basic cabinet (X).x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, NULL, D3DXVECTOR3(-2.3f, 6.0f, -2.3f));


	//Key_B_02.x

	//Scal = D3DXVECTOR3(1, 1, 1);
	//p = D3DXVECTOR3(0, 0, 0);

	//pt.vCenter = p;
	//pt.isPicked = false;
	//pt.fRadius = 1;

	//ObjectManager->ADDobject("Key_X", "singlkey.x", p, Scal, pt, OBJ_TYPE::item, "");


	//ObjectManager->ADDobject("BalanceBarBox", "BalanceBox.x", p, Scal, pt, OBJ_TYPE::item, "");
	//ObjectManager->ADDobject("BalanceBarBox", "BalanceBox.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max,NULL);
	//�ؿ��� UI����


	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIImageView* pImageView = new cUIImageView;
	D3DXIMAGE_INFO stImageInfo;
	ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetSpriteTexture(
		//"./UI2/panel-info.png.png",
		"./UI/UI_IN.tga",
		&stImageInfo);
	pImageView->SetTexture(pTexture);
	pImageView->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat, 100, 0, 0);
	pImageView->SetWorld(mat);
	pImageView->SetLocalPos(D3DXVECTOR3(200, 50, 0));
	m_pUIRoot = pImageView;


	pTextView = new cUITextView;
	pTextView->SetText("");
	pTextView->SetFont(g_pFontManager->GetFont(cFontManager::E_FT_NORMAL));
	
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat,300, 300, 0);
	pTextView->SetWorld(mat);
	pTextView->SetSize(ST_SIZE(321, 200));
	pTextView->SetDrawTextFormat(DT_CENTER | DT_TOP | DT_WORDBREAK);
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	pTextView->SetTag(E_TEXTVIEW);
	pTextView->AutoRelease();
	//	m_pUIRoot = pTextView;
	m_pUIRoot->AddChild(pTextView);

	m_pUI = new cUI;
	m_pUI->Setup();


	//ObjectManager->evt();
	//ObjectManager->v_Event[0]->update();
	//ObjectManager->m_Event["������"]->update();
}
void c2FScene::SetAddObj_3F()
{
	D3DXVECTOR3 Scal(1,1,1);						//������... 
	D3DXVECTOR3 p(39, -17.1, -74.4);		//������ ��ġ ������
	ST_SPHERE pt;							//��ŷ�� �� ũ�⸦ �����

	D3DXVECTOR3 Min(-10, 0, -10);			//OBB ũ�⸦ ������(��ġ�� ������Ʈ ������ǥ �ڵ����� ����)
	D3DXVECTOR3 Max(12, 30, 10);			//OBB ũ�⸦ ������(��ġ�� ������Ʈ ������ǥ �ڵ����� ����)

	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x + 4;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.isPicked = false;
	pt.fRadius = 1;


	Min = D3DXVECTOR3(0.25, 0, -1);
	Max = D3DXVECTOR3(-0.25, 3, 3);

	Scal = D3DXVECTOR3(1.4, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, NULL,D3DXVECTOR3(0,0,0));


	p = D3DXVECTOR3(84.5, -17, -79.5);
	pt.vCenter = p;
	pt.vCenter.z = pt.vCenter.z - 2;
	pt.vCenter.y = pt.vCenter.y + 3;


	Scal = D3DXVECTOR3(1.1, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI / 2, D3DXVECTOR3(0, 0, 0));

	p = D3DXVECTOR3(14.5, -17, -74.6);
	pt.vCenter = p;
	pt.vCenter.x = pt.vCenter.x + 4;
	pt.vCenter.y = pt.vCenter.y + 3;

	Scal = D3DXVECTOR3(1.4, 0.65, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, NULL, D3DXVECTOR3(0, 0, 0));

	//-57, -13.1 , -74.8   ��
	p = D3DXVECTOR3(-58.1, -16.8, -70.6);
	pt.vCenter = p;
	pt.vCenter.z = pt.vCenter.z - 3;
	pt.vCenter.y = pt.vCenter.y + 3;

	Scal = D3DXVECTOR3(1.4, 0.6, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI / 2, D3DXVECTOR3(0, 0, 0));

	//-52.2  ,-13.1,  -24.9 ü��
	Min = D3DXVECTOR3(-0.535, 0, -0.035);
	Max = D3DXVECTOR3(0.535, 0.075, 0.035);

	Scal = D3DXVECTOR3(2, 2, 2);
	p = D3DXVECTOR3(-52, -15.7, -25.9);
	pt.vCenter = p;
	pt.isPicked = false;
	pt.fRadius = 2;
	ObjectManager->ADDobject("t", "chair.x", p, Scal, Min, Max, NULL, D3DXVECTOR3(0, 0, 0));
	//ObjectManager->ADDobject("t", "chair.x", p, Scal, pt, OBJ_TYPE::OBJECT, "", Min, Max, -D3DX_PI / 2);

	//-60 , -13.1 , -4.7 ��

	//�޸��� �� 3��

	p = D3DXVECTOR3(-62, -16.8, -38.6);
	pt.vCenter = p;
	//pt.vCenter.x = pt.vCenter.x - 8;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.vCenter.z = pt.vCenter.z - 4;

	Min = D3DXVECTOR3(0.25, 0, -1);
	Max = D3DXVECTOR3(-0.25, 3, 3);


	Scal = D3DXVECTOR3(1.8, 0.6, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI / 2, D3DXVECTOR3(0, 0, 0));

	p = D3DXVECTOR3(-74.7, -16.8, -38.4);
	pt.vCenter = p;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.vCenter.z = pt.vCenter.z - 4;

	Scal = D3DXVECTOR3(1.8, 0.6, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI / 2, D3DXVECTOR3(0, 0, 0));

	p = D3DXVECTOR3(-92.3, -16.8, -39.0);
	pt.vCenter = p;
	pt.vCenter.y = pt.vCenter.y + 3;
	pt.vCenter.z = pt.vCenter.z - 4;


	Scal = D3DXVECTOR3(1.6, 0.6, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, D3DX_PI / 2, D3DXVECTOR3(0, 0, 0));
	//-60, -13.1, -4.7 ��

	//	- 62.7, -13.1, -44.1��

	//	- 81.3, -13.1 - 44.7��



	//��������
	//-93.1 , -13.1 -44.4
	p = D3DXVECTOR3(-61.4, -16.8, -3.9);
	pt.vCenter = p;
	pt.vCenter.z = pt.vCenter.z + 3;
	pt.vCenter.y = pt.vCenter.y + 3;

	Scal = D3DXVECTOR3(1.4, 0.6, 0.7);
	ObjectManager->ADDobject("door", "door.x", p, Scal, pt, OBJ_TYPE::door, "���ΰͰ���.", Min, Max, -D3DX_PI / 2, D3DXVECTOR3(0, 0, 0));
}
/*
==============================
cHero Ŭ���� ��� �Ŵ��� : ���ϴ�
2016 12 22
�̵� �� ��� ������ ���������� �ذ��մϴ�.
==============================
*/
void c2FScene::HeroManual()
{
	//������Ʈ�� �浹�Ͽ� ��� ��ȣ�ۿ��� ��Ű�� ���� ���
	
	//if(�浹��)
	//SetInteraction(CRT_INTERACTION interaction)

	//CRT_INTERACTION�� stdafx.h�� ���ǵ� �̳ѹ��Դϴ�.
	//ACTION_DOOR, ACTION_DESK, ACTION_ITEM, ACTION_CATCH, ACTION_NONE �� �ֽ��ϴ�.
	//��ȣ�ۿ��� ���� �ڿ��� �ݵ��! SetInteraction(ACTION_NONE); �� �� �ּ���.
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
		D3DXVECTOR3(-30.94f, -255.0f, 38.5f),
		D3DXVECTOR3(15.0f, -126.5f, 7.0f), 1.0f);
	m_pMap->Shadowinit("./shader/ApplyShadow.fx", "./shader/CreateShadow.fx");
	//������Ʈ �Ŵ��� ��� �޴��� 
	SetAddObj_2F();

	m_pObb = new cOBB;
	m_pObb->Setup(m_pHero->GetMesh());

	m_pObbObj = new cOBB;
	m_pObbObj->Setup(m_pHero->GetMesh());

}
void c2FScene::Update()
{

	if (GetKeyState(VK_UP) & 8888)
	{
		ObjectManager->getObject(1)->SetLightPositon(ObjectManager->getObject(1)->GetLightPositon() + D3DXVECTOR3(0, 0, 1));
	}
	else if (GetKeyState(VK_DOWN) & 8888)
	{
		ObjectManager->getObject(1)->SetLightPositon(ObjectManager->getObject(1)->GetLightPositon() + D3DXVECTOR3(0, 0, -1));
	}
	else if (GetKeyState(VK_LEFT) & 8888)
	{
		ObjectManager->getObject(1)->SetLightPositon(ObjectManager->getObject(1)->GetLightPositon() + D3DXVECTOR3(1, 0, 0));
	}
	else if (GetKeyState(VK_RIGHT) & 8888)
	{
		ObjectManager->getObject(1)->SetLightPositon(ObjectManager->getObject(1)->GetLightPositon() + D3DXVECTOR3(-1, 0, 0));
	}
	else if (GetKeyState('P') & 8888)
	{
		ObjectManager->getObject(1)->SetLightPositon(ObjectManager->getObject(1)->GetLightPositon() + D3DXVECTOR3(0, 1, 0));
	}
	else if (GetKeyState('L') & 8888)
	{
		ObjectManager->getObject(1)->SetLightPositon(ObjectManager->getObject(1)->GetLightPositon() + D3DXVECTOR3(0, -1, 0));
	}


	if (m_pController)
		m_pController->Update(m_pMap, m_pObb);

	if (m_pCamera)
		m_pCamera->Update(&m_pHero->GetPosition(), &m_pController->GetDirection());

	m_pController->SetfAngleX(m_pCamera->GetfAngleY());

	if (m_pMap)
		m_pMap->Update();

	if (GetAsyncKeyState(VK_F10))
	{
		ChangeMap();
	}
	

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
	m_pMap->Render(D3DXVECTOR3(0.7f, 4.3f, -3.4f), D3DXVECTOR3(-10.6f, 2.3f, 4.9f), m_pCamera->GetvEye(), 1000.0f, 0.8f);
	int a = ObjectManager->Getselect_index();
	if ( a!= NonSlect && ObjectManager->getObject(a)->GetObjType()==OBJ_TYPE::item)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		
		m_pUI->Render();
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		ObjectManager->getObject(a)->ObjVIEWRender(m_pCamera->GetvLookat());
	
	}
	if (GetKeyState('3'))
	{
		D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

		// �ؽ�Ʈ�� ����� ��ġ
		RECT rct;
		rct.left = 5;
		rct.right = WIN_WIDTH / 3;
		rct.top = 10;
		rct.bottom = WIN_HEIGHT / 3;

		// Ű �Է� ������ ���
		char str[1024];
		sprintf(str, "%f %f %f", ObjectManager->getObject(1)->GetLightPositon().x, ObjectManager->getObject(1)->GetLightPositon().y, ObjectManager->getObject(1)->GetLightPositon().z);
		gpFont->DrawText(NULL, str, -1, &rct, 0, fontColor);
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
	D3DXMatrixTranslation(&matET, 61.75f, -11.3f, -105.f);
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
				if (m_Change)
					ChangeMap();
				m_Change = false;
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

	if (m_pHero)
	{
		m_pHero->WndProc(hWnd, message, wParam, lParam);
	}

	//Ű���� ó��
	//���� �ӽð� R ������ �޸���. c������ ��ũ����
	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'R':
		{
			//m_isCrtRunning = true;
			m_pController->SetSpeed(0.5f);
			break;
		}
		case 'C':
		{
			//m_isCrtRunning = false;
			//m_isCrtCrawling = true;
			m_pController->SetSpeed(0.2f);
			break;
		}
		}
	}//case WM_KEYDOWN:
	break;

	case WM_KEYUP:
	{
		switch (wParam)
		{
		case  'R':
		{
			//m_isCrtRunning = false;
			m_pController->SetSpeed(0.3f);
			break;
		}
		case 'C':
		{
			//m_isCrtCrawling = false;
			m_pController->SetSpeed(0.3f);
			break;
		}
		}
	}//case WM_KEYUP:
	break;
	case WM_LBUTTONDOWN:
	{
						   int x = LOWORD(lParam);
						   int y = HIWORD(lParam);
	}
		break;
	}
}


void c2FScene::addElivator()
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
	ObjectManager->ADDobject("Medkit", "medkit1.x", p, Scal, pt, OBJ_TYPE::Switch, "E�����ּ���", D3DXVECTOR3(-2.3f, 6.0f, -2.3f));

	//���������� ��
	Scal = D3DXVECTOR3(1.1, 1.1, 1.1);
	p = D3DXVECTOR3(62, -17, -108);
	ObjectManager->ADDobject("Elivator", "Elivator.X", p, Scal, OBJ_TYPE::Room, -D3DX_PI / 2, D3DXVECTOR3(63.5f, -14.3f, -102.1f));

	//���������� �� 2��
	Scal = D3DXVECTOR3(26.0f, 27.0f, 26.0f);
	p = D3DXVECTOR3(60.35f, -17, -105.5f);
	Min = D3DXVECTOR3(-0.035, 0, -0.035);
	Max = D3DXVECTOR3(0.035, 0.075, 0.035);

	//��1 (index 2)
	ObjectManager->ADDobject("Elivator/door", "elidoor.X", p, Scal, pt, OBJ_TYPE::Eledoor, "", Min, Max, -D3DX_PI / 2, D3DXVECTOR3(56.0f, -11.4f, -97.2f));
	Scal = D3DXVECTOR3(26.0f, 27.0f, 26.0f);
	p = D3DXVECTOR3(62.95f, -17, -105.5f);
	//��2 (index 3)

	ObjectManager->ADDobject("Elivator/door", "elidoor.X", p, Scal, pt, OBJ_TYPE::Eledoor, "", Min, Max, -D3DX_PI / 2, D3DXVECTOR3(56.0f, -11.4f, -97.2f));

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
	ObjectManager->getOpen();

	ZeroMemory(&m_TextMtl, sizeof(_D3DMATERIAL9));
	m_TextMtl.Ambient = m_TextMtl.Diffuse = m_TextMtl.Specular = D3DXCOLOR(0.6f, 0.1f, 0.1f, 1.0f);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
}

void c2FScene::ChangeMap()
{
	SAFE_DELETE(m_pMap);
	m_pMap = new cMapRender;
	//m_pMap = new cMapRender;
	//D3DXVECTOR3(-13.84f, -552.6f, 182.5f) //��.obj ��ġ

	//�ϴ� �Լ� ������ �������� �ӽ÷� �ּ�
	m_pMap->Setup("objMap/3FMap.obj",
		"objMap/3Fsurf.obj",
		D3DXVECTOR3(-13.84f, -553.f, 182.7f),
		D3DXVECTOR3(-13.84f, -553.f, 182.7f), 1.0f);

	ObjectManager->DestroyObject();

	addElivator();

	SetAddObj_3F();
	
}
