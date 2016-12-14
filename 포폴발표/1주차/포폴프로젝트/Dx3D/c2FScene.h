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
	std::vector<ID3DXMesh*>		m_vecText;
	float						m_fPassedActionTime;
	float						m_fActionTime;

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
	void SetUITest();
	c2FScene();
	~c2FScene();
};

