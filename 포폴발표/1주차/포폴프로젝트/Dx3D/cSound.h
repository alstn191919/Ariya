#include "stdafx.h"

#define DSVOLUME_TO_DB(Volume)  ((DWORD)(-30*(100-Volume))) // 볼륨 조정 매크로.
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

	void Load(LPSTR FileName);					// 사운드 로드
	void Play(DWORD dwFlags = 0);			// 사운드 재생
	void Stop();											// 사운드 정지
	void SetVolume(LONG lVolume = 100);	 // 볼륨 설정
	void SetPan(LONG lPan = 0);					// 패닝 설정

	DWORD GetBufferStatus();

	int Release();

};