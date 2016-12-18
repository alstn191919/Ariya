#pragma once
#include "stdafx.h"

#define g_pSoundManager cSoundManager::GetInstance()

class cSound;
class cSoundManager
{
private:
	SINGLETONE(cSoundManager);

private:
	std::map<LPSTR, cSound*> m_mapSound;
	std::vector<LPSTR> m_vecSoundIndex;

public:
	void Play(LPSTR szFileName, DWORD flag = 0);
	void Stop(LPSTR szFileName);
	void SetVolume(LPSTR szFileName, long lVolume);
	void SetPan(LPSTR szFileName, long lPan);
	void AddSound(LPSTR szFileName);
	void AddSound(LPSTR szFileName, cSound* pSound);
	bool GetState(LPSTR szFileName);

	void Destroy();

};

