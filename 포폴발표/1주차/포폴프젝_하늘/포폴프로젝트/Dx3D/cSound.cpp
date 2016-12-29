#include "stdafx.h"
#include "cSound.h"

cSound::cSound()
	: m_szPath(NULL)
	, m_vPosition(0, 0, 0)
{
	G_SOUND_VOLUME = 10.0f;
};

cSound::~cSound()
{};

void cSound::Load(LPSTR FileName, LPSTR szPath)
{
	// DirectSound 객체 생성
	DirectSoundCreate(NULL, &m_pDS, NULL);

	// DirectSound의 협력 레벨 설정
	m_pDS->SetCooperativeLevel(g_hWnd, DSSCL_NORMAL);

	char* fullPath;

	//사운드 경로 설정 여부에 따라
	if (strlen(m_szPath) != NULL)
	{
		fullPath = new char[strlen(m_szPath) + strlen(FileName)];
		ZeroMemory(fullPath, strlen(m_szPath) + strlen(FileName));
		strcpy(fullPath, szPath);
	}
	else
	{
		if (szPath == NULL)
		{
			assert("경로가 설정되지 않았습니다.");
		}
		fullPath = new char[strlen(szPath) + strlen(FileName)];
		ZeroMemory(fullPath, strlen(szPath) + strlen(FileName));
		strcpy(fullPath, szPath);
	}
	strncat(fullPath, FileName, strlen(FileName));
	char* type = ".wav";
	strncat(fullPath, type, strlen(type));

	// WAV 파일 로드 및 DirectSoundBuffer 생성
	LoadWAV(fullPath, DSBCAPS_STATIC | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY);

	m_pDSBuffer->GetFrequency(&m_dwOrigFreq);
	m_dwFreq = m_dwOrigFreq;
}

void cSound::Play(DWORD dwFlags)
{
	//DSBPLAY_LOOPING : stop 때까지 반복재생
	if (m_isPlay)
		return;

	m_pDSBuffer->SetCurrentPosition(0);
	if (FAILED(m_pDSBuffer->Play(0, 0, dwFlags)))
	{
		assert("음악 재생 실패");
	}
	m_isPlay = SND_PLAYING;
}

void cSound::Stop()
{
	if (FAILED(m_pDSBuffer->Stop()))
	{
		assert("음악 정지 실패");
	}
	m_isPlay = SND_STOPPED;
}

void cSound::SetVolume(LONG lVolume)
{
	float volume = G_SOUND_VOLUME * lVolume;
	if (volume >= 100)
		volume = 100;

	if (volume < 0)
		volume = 0;

	if (FAILED(m_pDSBuffer->SetVolume(DSVOLUME_TO_DB(volume))))
	{
		assert("볼륨 조정 실패");
	}
}

void cSound::SetVolume(D3DXVECTOR3 vCRTPosition)
{
	D3DXVECTOR3 vDist = m_vPosition - vCRTPosition;
	float distance = sqrtf(vDist.x * vDist.x + vDist.y * vDist.y + vDist.z * vDist.z);
	long volume = G_SOUND_VOLUME * fabs(10 - (distance * 0.1));

	if (FAILED(m_pDSBuffer->SetVolume(DSVOLUME_TO_DB(volume))))
	{
		assert("볼륨 조정 실패");
	}
}

void cSound::SetPan(LONG lPan)
{
	if (FAILED(m_pDSBuffer->SetPan(lPan)))
	{
		assert("팬 조정 실패");
	}
}

void cSound::SetPan(D3DXVECTOR3 vCRTPosition)
{
	//L(-10,000 ~ 10,000)R
	float distance = m_vPosition.x - vCRTPosition.x;
	long	pan;

	pan = distance * 10;
	if (pan > 10000)
		pan = 10000;
	else if (pan < -10000)
		pan = -10000;

	if (FAILED(m_pDSBuffer->SetPan(pan)))
	{
		assert("팬 조정 실패");
	}
}

void cSound::SetSpeed(float fMul)
{
	m_dwFreq *= fMul;
	if (FAILED(m_pDSBuffer->SetFrequency(m_dwFreq)))
	{
		assert("재생 속도 조정 실패");
	}
}

void cSound::SetSpeedToOrig()
{
	m_dwFreq = m_dwOrigFreq;
	if (FAILED(m_pDSBuffer->SetFrequency(m_dwFreq)))
	{
		assert("재생 속도 조정 실패");
	}
}

DWORD cSound::GetBufferStatus()
{
	DWORD Status;
	m_pDSBuffer->GetStatus(&Status);

	return Status;
}

DWORD cSound::GetCurPlayPosition()
{
	DWORD curPlayPosition;
	m_pDSBuffer->GetCurrentPosition(&curPlayPosition, NULL);

	return curPlayPosition;
}

int cSound::Release()
{
	SAFE_RELEASE(m_pDSBuffer);
	SAFE_RELEASE(m_pDS);
	return 1;
}

int cSound::LoadWAV(char *FileName, int Flags)
{
	HMMIO          hWAV;
	MMCKINFO   Child, Parent;
	//사운드 저장용 버퍼
	BYTE*   WholeSndBuff;
	LPVOID  PrimarySndBuff = NULL;
	LPVOID  SecondarySndBuff = NULL;
	DWORD   PrimaryLength, SecondaryLength; // 버퍼의 길이
	UINT                         cbWavSize;
	LPWAVEFORMATEX   lpwfmtx;

	OpenWaveFile(FileName, &hWAV, &lpwfmtx, &Parent);
	DescendIntoChunk(&hWAV, &Child, &Parent);

	ZeroMemory(&m_DSBufDesc, sizeof(m_DSBufDesc));
	m_DSBufDesc.dwSize = sizeof(m_DSBufDesc);
	m_DSBufDesc.dwFlags = Flags | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
	m_DSBufDesc.dwBufferBytes = Child.cksize;
	m_DSBufDesc.lpwfxFormat = lpwfmtx;

	//사운드 버퍼 생성
	m_pDS->CreateSoundBuffer(&m_DSBufDesc, &m_pDSBuffer, NULL);

	m_nSize = Child.cksize;
	m_isPlay = SND_STOPPED;

	WholeSndBuff = new BYTE[m_nSize];

	ReadWaveFile(hWAV, m_nSize, WholeSndBuff, &Child, &cbWavSize);

	// 사운드 버퍼 락
	m_pDSBuffer->Lock(0, m_DSBufDesc.dwBufferBytes,
		(LPVOID*)&PrimarySndBuff, &PrimaryLength,
		&SecondarySndBuff, &SecondaryLength, 0L);

	memcpy(PrimarySndBuff, WholeSndBuff, PrimaryLength);
	memcpy(SecondarySndBuff, (WholeSndBuff + PrimaryLength), SecondaryLength);

	//사운드 버퍼 락 해제
	m_pDSBuffer->Unlock(PrimarySndBuff, m_DSBufDesc.dwBufferBytes, NULL, 0);

	memcpy(&m_WaveFmtX, lpwfmtx, sizeof(WAVEFORMATEX));
	SAFE_DELETE(WholeSndBuff);

	return 1;
}

int cSound::ReadMMIO(HMMIO hmmioIn, MMCKINFO* pckInRIFF, LPWAVEFORMATEX* lplpwfxInfo)
{
	MMCKINFO        ckIn;
	PCMWAVEFORMAT   pcmwf;

	*lplpwfxInfo = NULL;
	mmioDescend(hmmioIn, pckInRIFF, NULL, 0);
	if ((pckInRIFF->ckid != FOURCC_RIFF) ||
		(pckInRIFF->fccType != mmioFOURCC('W', 'A', 'V', 'E')))
	{
		assert("지원하지 않는 파일 포맷. WAV가 아닙니다.");
	}

	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK);
	ckIn.cksize < (LONG)sizeof(pcmwf);

	mmioRead(hmmioIn, (HPSTR)&pcmwf, sizeof(pcmwf)) != sizeof(pcmwf);
	if (pcmwf.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		if (NULL == (*lplpwfxInfo = new WAVEFORMATEX))
		{
			assert("WAVEFORMATEX 초기화 실패. PCM이 아닙니다.");
		}

		memcpy(*lplpwfxInfo, &pcmwf, sizeof(pcmwf));
		(*lplpwfxInfo)->cbSize = 0;
	}
	else
	{
		WORD cbExtraBytes = 0L;
		if (mmioRead(hmmioIn, (LPSTR)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
		{
			assert("error");
		}
		*lplpwfxInfo = (LPWAVEFORMATEX)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];
		if (NULL == *lplpwfxInfo)
		{
			assert("error");
		}
		memcpy(*lplpwfxInfo, &pcmwf, sizeof(pcmwf));
		(*lplpwfxInfo)->cbSize = cbExtraBytes;
		if (mmioRead(hmmioIn,
			(LPSTR)(((BYTE*)&(*lplpwfxInfo)->cbSize) + sizeof(WORD)),
			cbExtraBytes) != cbExtraBytes)
		{
			delete *lplpwfxInfo;
			*lplpwfxInfo = NULL;
			assert("error");
		}
	}
	if (mmioAscend(hmmioIn, &ckIn, 0))
	{
		delete *lplpwfxInfo;
		*lplpwfxInfo = NULL;
		assert("error");
	}

	return 1;
}

int cSound::OpenWaveFile(LPSTR FileName, HMMIO* phmmioIn, LPWAVEFORMATEX* lplpwfxInfo, MMCKINFO* pckInRIFF)
{
	HMMIO   hmmioIn = NULL;

	hmmioIn = mmioOpen(FileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (!hmmioIn)
	{
		assert("파일 파싱 실패");
	}

	ReadMMIO(hmmioIn, pckInRIFF, lplpwfxInfo);

	*phmmioIn = hmmioIn;
	return 1;
}

int cSound::DescendIntoChunk(HMMIO* phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF)
{
	mmioSeek(*phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC), SEEK_SET);
	pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(*phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK))
	{
		assert("Descend into Chunk 실패");
	}
	return 1;
}

int cSound::ReadWaveFile(HMMIO hmmioIn, UINT cbRead,
	BYTE* pbDest, MMCKINFO* pckIn, UINT* cbActualRead)
{
	MMIOINFO mmioinfoIn;
	UINT cbDataIn = cbRead;
	*cbActualRead = 0;
	if (mmioGetInfo(hmmioIn, &mmioinfoIn, 0))
	{
		assert("MMIOINFO 읽기 실패");
	}

	if (cbDataIn > pckIn->cksize)
		cbDataIn = pckIn->cksize;
	pckIn->cksize -= cbDataIn;

	for (DWORD cnt = 0; cnt < cbDataIn; cnt++)
	{
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			if (mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ))
			{
				assert("error");
			}
			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
				assert("error");
			}
		}
		*((BYTE*)pbDest + cnt) = *((BYTE*)mmioinfoIn.pchNext);
		mmioinfoIn.pchNext++;
	}
	if (mmioSetInfo(hmmioIn, &mmioinfoIn, 0))
	{
		assert("error");
	}
	*cbActualRead = cbDataIn;
	return 1;
}