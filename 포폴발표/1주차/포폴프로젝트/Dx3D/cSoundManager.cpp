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
	cSound* data;
	if (m_mapSound.empty())
	{
		assert("map is empty");
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
		assert("map is empty");
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

void cSoundManager::SetVolume(LPSTR szFileName, long lVolume)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		assert("map is empty");
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
		assert("map is empty");
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

void cSoundManager::AddSound(LPSTR szFileName)
{
	cSound* sound = new cSound;
	sound->Load(szFileName);
	m_mapSound.insert(std::make_pair(szFileName, sound));
}

void cSoundManager::AddSound(LPSTR szFileName, cSound * pSound)
{
	m_mapSound.insert(std::make_pair(szFileName, pSound));
}

bool cSoundManager::GetState(LPSTR szFileName)
{
	cSound* data;
	if (m_mapSound.empty())
	{
		assert("map is empty");
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
