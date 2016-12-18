#include "stdafx.h"
#include "cSound.h"
//////////////////////
// ���� ���� ����. //
/////////////////////

cSound::cSound()
{ };

cSound::~cSound()
{};

void cSound::Load(LPSTR FileName)
{
	// DirectSound ��ü ����
	DirectSoundCreate(NULL, &m_pDS, NULL);

	// DirectSound�� ���� ���� ����
	m_pDS->SetCooperativeLevel(g_hWnd, DSSCL_NORMAL);

	// WAV ���� �ε� �� DirectSoundBuffer ����
	LoadWAV(FileName, DSBCAPS_STATIC | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME);
}

void cSound::Play(DWORD dwFlags)
{
	//DSBPLAY_LOOPING : stop ������ �ݺ����

	m_pDSBuffer->SetCurrentPosition(0);
	if (FAILED(m_pDSBuffer->Play(0, 0, dwFlags)))
	{
		assert("���� ��� ����");
	}
	m_isPlay = SND_PLAYING; // ���� ������ ���� - "�÷��� ��".
}

void cSound::Stop()
{
	if (FAILED(m_pDSBuffer->Stop()))
	{
		assert("���� ���� ����");
	}
	m_isPlay = SND_STOPPED; // ���� ������ ���� - "�÷��� ��".
}

void cSound::SetVolume(LONG lVolume)
{
	if (FAILED(m_pDSBuffer->SetVolume(DSVOLUME_TO_DB(lVolume))))
	{
		assert("���� ���� ����");
	}
}

void cSound::SetPan(LONG lPan)
{
	if (FAILED(m_pDSBuffer->SetPan(lPan)))
	{
		assert("�� ���� ����");
	}
}

DWORD cSound::GetBufferStatus()
{
	DWORD Status;
	m_pDSBuffer->GetStatus(&Status);

	return Status;
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
	//���� ����� ����
	BYTE*   WholeSndBuff;
	LPVOID  PrimarySndBuff = NULL;
	LPVOID  SecondarySndBuff = NULL;
	DWORD   PrimaryLength, SecondaryLength; // ������ ����
	UINT                         cbWavSize;
	LPWAVEFORMATEX   lpwfmtx;

	OpenWaveFile(FileName, &hWAV, &lpwfmtx, &Parent);
	DescendIntoChunk(&hWAV, &Child, &Parent);

	ZeroMemory(&m_DSBufDesc, sizeof(m_DSBufDesc));
	m_DSBufDesc.dwSize = sizeof(m_DSBufDesc);
	m_DSBufDesc.dwFlags = Flags | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
	m_DSBufDesc.dwBufferBytes = Child.cksize;
	m_DSBufDesc.lpwfxFormat = lpwfmtx;

	//���� ���� ����
	m_pDS->CreateSoundBuffer(&m_DSBufDesc, &m_pDSBuffer, NULL);

	m_nSize = Child.cksize;
	m_isPlay = SND_STOPPED;

	WholeSndBuff = new BYTE[m_nSize];

	ReadWaveFile(hWAV, m_nSize, WholeSndBuff, &Child, &cbWavSize);

	// ���� ���� ��
	m_pDSBuffer->Lock(0, m_DSBufDesc.dwBufferBytes,
		(LPVOID*)&PrimarySndBuff, &PrimaryLength,
		&SecondarySndBuff, &SecondaryLength, 0L);

	memcpy(PrimarySndBuff, WholeSndBuff, PrimaryLength);
	memcpy(SecondarySndBuff, (WholeSndBuff + PrimaryLength), SecondaryLength);

	//���� ���� �� ����
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
		assert("�������� �ʴ� ���� ����. WAV�� �ƴմϴ�.");
	}

	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK);
	ckIn.cksize < (LONG)sizeof(pcmwf);

	mmioRead(hmmioIn, (HPSTR)&pcmwf, sizeof(pcmwf)) != sizeof(pcmwf);
	if (pcmwf.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		if (NULL == (*lplpwfxInfo = new WAVEFORMATEX))
		{
			assert("WAVEFORMATEX �ʱ�ȭ ����. PCM�� �ƴմϴ�.");
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
		assert("���� �Ľ� ����");
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
		assert("Descend into Chunk ����");
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
		assert("MMIOINFO �б� ����");
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