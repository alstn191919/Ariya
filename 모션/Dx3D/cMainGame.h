#pragma once

class cCamera;
class cGrid;
class cCrtController;
class cSkinnedMesh;
class cHeightMap;
class cMapRender;

#define RADIUS 0.3f
#define charsize 0.02f

class cMainGame
{
private:
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCrtController*				m_pController;
	cSkinnedMesh*				m_pZealot;
	cMapRender*					m_pMap;
private:
	bool						_isRuning;
	D3DXMATRIXA16				_zMat;
	DWORD						FrameCnt;
	float						TimeElapsed;
	float						FPS;
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Getfps(float deltaTime);
	void SetLight();
};

