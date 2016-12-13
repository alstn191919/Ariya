#pragma once

class cMainGame
{
private:
	float		FPS;
	DWORD		FrameCnt;
	float		TimeElapsed;
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void Getfps(float deltaTime);
	void SetLight();
};

