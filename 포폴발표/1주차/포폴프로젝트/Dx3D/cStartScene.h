#pragma once

class cMapRender;
class cCamera;
class cCrtController;
class cUIButton;

class cStartScene
{
private:
	cMapRender*			pMap;
	cCamera*			pCamera;
	cCrtController*		m_pController;
	LPD3DXSPRITE		LogoSprite;
	LPDIRECT3DTEXTURE9	Texture;
	cUIButton*			Button;
	ST_SIZE				_imgSize;
private:

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	cStartScene();
	~cStartScene();
	
};

