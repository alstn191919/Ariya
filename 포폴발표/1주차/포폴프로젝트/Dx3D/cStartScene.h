#pragma once

class cMapRender;
class cCamera;
class cCrtController;
class cGrid;

class cStartScene
{
private:
	cMapRender*			pMap;
	cCamera*			pCamera;
	cCrtController*		m_pController;
	cGrid*						m_pGrid;

private:

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	cStartScene();
	~cStartScene();
	
};

