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
	void Destroy();
	void Release(LPSTR szFileName);

	void AddSound(LPSTR szFileName, LPSTR szPath);
	void AddSound(LPSTR szFileName, LPSTR szPath, D3DXVECTOR3 vPosition);
	void AddSound(LPSTR szFileName, cSound* pSound);

	
	/* GET */
	D3DXVECTOR3 GetPosition(LPSTR szFileName);
	bool GetState(LPSTR szFileName);
	bool	IsNear(LPSTR szFileName, D3DXVECTOR3 vCRTPosition, float fGap);					//ĳ���� �������� ���� �������� �������� Gap ���� �ִ��� Ȯ��

	/* SET */
	void SetPosition(LPSTR szFileName, D3DXVECTOR3 vPosition);
	void SetVolume(LPSTR szFileName, long lVolume);
	void SetPan(LPSTR szFileName, long lPan);
	void SetVolumeAndPan(LPSTR szFileName, D3DXVECTOR3 vCRTPosition);
	void SetSpeed(LPSTR szFileName, float fMul);
	void SetSpeedToOrig(LPSTR szFileName);
	void SetGameSound(long gSound);			//���� ��ü ���� ����

};

