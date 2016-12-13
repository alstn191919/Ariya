#pragma once

enum SceneMenu
{
	Scene_NULL,
	Scene_Main,
	Scene_2F,
	Scene_3F,
	Scene_End
};

class cStartScene;
class c2FScene;

#define g_pSceneManager cSceneManager::GetInstance()

class cSceneManager
{
private:
	SINGLETONE(cSceneManager);
private:
	cStartScene*	pStartScene;
	c2FScene*		p2FScene;
private:
	SceneMenu		eMenu;
public:
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void ChangeScene(SceneMenu Scene);
	void Destroy();
};

