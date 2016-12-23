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

public:
	void Play(LPSTR szFileName, DWORD flag = 0);
	void Stop(LPSTR szFileName);
	void SetVolume(LPSTR szFileName, D3DXVECTOR3 vCRTPosition);
	void SetVolume(LPSTR szFileName, long lVolume);
	void SetPan(LPSTR szFileName, long lPan);
	void AddSound(LPSTR szFileName, LPSTR szPath);
	void AddSound(LPSTR szFileName, LPSTR szPath, D3DXVECTOR3 vPosition);
	void AddSound(LPSTR szFileName, LPSTR szPath, D3DXVECTOR3 vPosition, SOUND_MAP mPos);
	void AddSound(LPSTR szFileName, cSound* pSound);
	void SetPosition(LPSTR szFileName, D3DXVECTOR3 vPosition);
	D3DXVECTOR3 GetPosition(LPSTR szFileName);

	//사운드가 어느 맵에 있는지 겟(MapPosition)
	SOUND_MAP WhichMapIn(LPSTR szFileName);

	//포지션과 사운드 포지션이 같은 사운드맵에 있는지 확인
	SOUND_MAP IsInSameMap(LPSTR szFileName, D3DXVECTOR3 vCRTPosition);

	bool GetState(LPSTR szFileName);

	void Destroy();
	void Release(LPSTR szFileName);

};

