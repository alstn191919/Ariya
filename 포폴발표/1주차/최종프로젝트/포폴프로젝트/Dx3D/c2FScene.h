#pragma once
class cCamera;
class cGrid;
class cCrtController;
class cSkinnedMesh;
class cMapRender;
class cSkinnedMesh2;
class cUITextView;
class cOBB;
class cHero;
class cUI;
class Monster;

#include "cUIButton.h"

#define RADIUS 0.3f

#define charsizeX 0.02f
#define charsizeY 0.018f
#define charsizeZ 0.02f

class c2FScene
{
private:
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCrtController*				m_pController;
	cHero*						m_pHero;
	cMapRender*					m_pMap;
	cOBB*						m_pObb;
	cOBB*						m_pObbEvent;			//������ �ʴ� OBB Event OBB�� ����
	Monster*					m_pMonster;
	
	D3DMATERIAL9				m_TextMtl;
	std::vector<ID3DXMesh*>		m_vecText;
	float						m_fPassedActionTime;
	float						m_fActionTime;
	bool						m_b1stFloor;
	bool						m_bisClicked;
	bool						m_Change;
	cUI *						m_pUI;
	int							time;
	D3DXVECTOR4					v_LightPos[10];
	D3DXVECTOR4					v_LightDir[10];
	float						v_LightPow[10];


	bool						m_isCrtRunning;
	bool						m_isCrtCrawling;
	D3DXMATRIXA16				_zMat;
	cSkinnedMesh2*				m_pSkinnedMesh;
	LPD3DXSPRITE				m_pSprite;
	cUIObject*					m_pUIRoot;
	cUITextView*				 pTextView;
	LPD3DXFONT					gpFont;

	bool						_isStartEvent;
	float						EventTime;
	D3DXVECTOR3					m_vCRTPos;
	bool						m_ThunderSwitch;
	bool						m_isThunderOn;
	float						m_fThunderTime;
	float						m_fTimeForThunder;
	float						m_fCrtNervousTime;
	bool						m_isCryingEnd;

private:
	void SetSound();						//2�� �� 3���� �ʿ��� ���� ����
	void ThunderEvent();
	void CryingEvent();

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetAddObj_2F();
	void SetAddObj_3F();
	void HeroManual();

	void ChangeMap();
	void addElivator();			//���������� �߰� ( �ڵ尡 �䵥 2���̻� ���Ƿ� �Լ��� ���λ�)  //�ۼ��� : ������
	void MonSterAI();			//���� AI
	void MonSterEvent();		//���� �̺�Ʈ ���� ������

	c2FScene();
	~c2FScene();
};

