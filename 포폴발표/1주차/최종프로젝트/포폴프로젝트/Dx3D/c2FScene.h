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
	cOBB*						m_pObbEvent;			//쓰지도 않던 OBB Event OBB로 수정
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
	void SetSound();						//2층 및 3층에 필요한 사운드 조정
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
	void addElivator();			//엘리베이터 추가 ( 코드가 긴데 2번이상 쓰므로 함수로 따로뺌)  //작성자 : 강병민
	void MonSterAI();			//몬스터 AI
	void MonSterEvent();		//몬스터 이벤트 시작 판정함

	c2FScene();
	~c2FScene();
};

