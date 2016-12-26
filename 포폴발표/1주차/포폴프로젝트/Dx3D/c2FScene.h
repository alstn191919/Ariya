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
	cOBB*						m_pObbObj;
	
	D3DMATERIAL9				m_TextMtl;
	std::vector<ID3DXMesh*>		m_vecText;
	float						m_fPassedActionTime;
	float						m_fActionTime;
	bool						m_b1stFloor;
	bool						m_bisClicked;
	bool						m_Change;
	cUI *						m_pUI;

private:
	bool						m_isCrtRunning;
	bool						m_isCrtCrawling;
	D3DXMATRIXA16				_zMat;
	cSkinnedMesh2*				m_pSkinnedMesh;
	LPD3DXSPRITE				m_pSprite;
	cUIObject*					m_pUIRoot;
	cUITextView*				 pTextView;


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

	c2FScene();
	~c2FScene();
};

