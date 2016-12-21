#include "stdafx.h"

#define DSVOLUME_TO_DB(Volume)  ((DWORD)(-30*(100-Volume))) // ���� ���� ��ũ��.
class cSound
{
private:
	int m_nRate;
	int m_nSize;

	DSBUFFERDESC					m_DSBufDesc;
	WAVEFORMATEX				m_WaveFmtX;

	LPDIRECTSOUND				m_pDS;
	LPDIRECTSOUNDBUFFER m_pDSBuffer;

	SYNTHESIZE(bool, m_isPlay, State);

private:
	int LoadWAV(char *FileName, int Flags);

	int ReadMMIO(HMMIO hmmioIn, MMCKINFO* pckInRIFF, LPWAVEFORMATEX* lplpwfxInfo);
	int OpenWaveFile(LPSTR FileName, HMMIO* phmmioIn, LPWAVEFORMATEX* lplpwfxInfo, MMCKINFO* pckInRIFF);
	int DescendIntoChunk(HMMIO* phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF);
	int ReadWaveFile(HMMIO hmmioIn, UINT cbRead, BYTE* pbDest, MMCKINFO* pckIn, UINT* cbActualRead);

public:
	cSound();
	~cSound();

	void Load(LPSTR FileName);					// ���� �ε�
	void Play(DWORD dwFlags = 0);			// ���� ���
	void Stop();											// ���� ����
	void SetVolume(LONG lVolume = 100);	 // ���� ����
	void SetPan(LONG lPan = 0);					// �д� ����

	DWORD GetBufferStatus();

	int Release();

};