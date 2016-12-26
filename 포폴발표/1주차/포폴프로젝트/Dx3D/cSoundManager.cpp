#include "stdafx.h"
#include "cSoundManager.h"
#include "cSound.h"

cSoundManager::cSoundManager()
{
}


cSoundManager::~cSoundManager()
{
	Destroy();
}

void cSoundManager::Play(LPSTR szFileName, DWORD flag)
{
	//DSBPLAY_LOOPING : stop 때까지 반복재생
	cSound* data;
	if (m_mapSound.empty())
	{
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		data->Play(flag);
	}
	else
	{
		assert("no such music", szFileName);
	}
}

void cSoundManager::Stop(LPSTR szFileName)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		return;
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		data->Stop();
	}
	else
	{
		assert("no such music", szFileName);
	}
}

void cSoundManager::SetVolume(LPSTR szFileName, D3DXVECTOR3 vCRTPosition)
{
}

void cSoundManager::SetVolume(LPSTR szFileName, long lVolume)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		data->SetVolume(lVolume);
	}
	else
	{
		assert("no such music", szFileName);
	}
}

void cSoundManager::SetPan(LPSTR szFileName, long lPan)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		data->SetPan(lPan);
	}
	else
	{
		assert("no such music", szFileName);
	}
}

void cSoundManager::AddSound(LPSTR szFileName, LPSTR szPath)
{
	cSound* sound = new cSound;
	sound->SetPath(szPath);
	sound->Load(szFileName, szPath);
	m_mapSound.insert(std::make_pair(szFileName, sound));
}

void cSoundManager::AddSound(LPSTR szFileName, LPSTR szPath, D3DXVECTOR3 vPosition)
{
	cSound* sound = new cSound;
	sound->SetPath(szPath);
	sound->Load(szFileName, szPath);
	sound->SetPosition(vPosition);
	m_mapSound.insert(std::make_pair(szFileName, sound));
}

void cSoundManager::AddSound(LPSTR szFileName, LPSTR szPath, D3DXVECTOR3 vPosition, SOUND_MAP mPos)
{
	cSound* sound = new cSound;
	sound->SetPath(szPath);
	sound->Load(szFileName, szPath);
	sound->SetPosition(vPosition);
	sound->SetMapPosition(mPos);
	m_mapSound.insert(std::make_pair(szFileName, sound));
}

void cSoundManager::AddSound(LPSTR szFileName, cSound * pSound)
{
	m_mapSound.insert(std::make_pair(szFileName, pSound));
}

void cSoundManager::SetPosition(LPSTR szFileName, D3DXVECTOR3 vPosition)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		data->SetPosition(vPosition);
	}
	else
	{
		assert("no such music", szFileName);
	}
}

D3DXVECTOR3 cSoundManager::GetPosition(LPSTR szFileName)
{
	cSound* data;
	D3DXVECTOR3 position;
	if (m_mapSound.empty())
	{
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		return data->GetPosition();
	}
	else
	{
		assert("no such music", szFileName);
	}
}

SOUND_MAP cSoundManager::WhichMapIn(LPSTR szFileName)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		return data->GetMapPosition();
	}
	else
	{
		assert("no such music", szFileName);
	}
}

SOUND_MAP cSoundManager::IsInSameMap(LPSTR szFileName, D3DXVECTOR3 vPosition)
{
	cSound* data;
	SOUND_MAP soundP;

	if (m_mapSound.empty())
	{
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		soundP = data->GetMapPosition();
	}
	else
	{
		assert("no such music", szFileName);
	}

	for (int i = 0; i < SOUND_MAP::SM_NONE; ++i)
	{

	}

	return SOUND_MAP::SM_NONE;
}

bool cSoundManager::GetState(LPSTR szFileName)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		//assert("map is empty");
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		if (data->GetState() == SND_PLAYING)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		assert("no such music", szFileName);
	}
}

void cSoundManager::Destroy()
{
	std::map<LPSTR, cSound*>::iterator iter;
	iter = m_mapSound.begin();
	for (iter; iter != m_mapSound.end(); ++iter)
	{
		iter->second->Release();
		SAFE_DELETE(iter->second);
	}
	m_mapSound.clear();

	if (!m_mapSound.empty())
	{
		assert("map is not destroied");
	}
}

void cSoundManager::Release(LPSTR szFileName)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		//assert("map is empty");
		return;
	}

	if (data = m_mapSound.find(szFileName)->second)
	{
		data->Release();
		SAFE_DELETE(data);
		m_mapSound.erase("szFileName");
	}
	else
	{
		assert("no such music", szFileName);
	}
}
