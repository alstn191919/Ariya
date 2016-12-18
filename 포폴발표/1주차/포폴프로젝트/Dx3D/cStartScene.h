#pragma once
#include "cUIButton.h"

class cMapRender;
class cCamera;
class cCrtController;
class cUIButton;
class iUIButtonDelegate;

enum ButtonState
{
	Button_NULL,
	Button_MAIN,
	Button_START,
	Button_END
};

class cStartScene : iUIButtonDelegate
{
private:
	cMapRender*			pMap;
	cCamera*			pCamera;
	cCrtController*		m_pController;
	LPD3DXSPRITE		LogoSprite;
	LPDIRECT3DTEXTURE9	Texture;
	cUIButton*			Button;
	D3DXVECTOR3			CameraPosition;
	D3DXVECTOR3			CameraDirection;;
	ST_SIZE				_imgSize;
	ButtonState			State;

private:
	virtual void OnClick(cUIButton* pSender);
public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	
	cStartScene();
	~cStartScene();
	
};

