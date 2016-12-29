#include "stdafx.h"

#define DSVOLUME_TO_DB(Volume)  ((DWORD)(-30*(100-Volume))) // 볼륨 조정 매크로.
class cSound
{
private:
	DWORD m_dwFreq, m_dwOrigFreq;
	int m_nRate;
	int m_nSize;

	DSBUFFERDESC					m_DSBufDesc;
	WAVEFORMATEX				m_WaveFmtX;

	LPDIRECTSOUND					m_pDS;
	LPDIRECTSOUNDBUFFER    m_pDSBuffer;

	SYNTHESIZE_PASS_BY_REF(LPSTR, m_szPath, Path);
	SYNTHESIZE(bool, m_isPlay, State);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);							//맵에서의 포지션

private:
	int LoadWAV(char *FileName, int Flags);

	int ReadMMIO(HMMIO hmmioIn, MMCKINFO* pckInRIFF, LPWAVEFORMATEX* lplpwfxInfo);
	int OpenWaveFile(LPSTR FileName, HMMIO* phmmioIn, LPWAVEFORMATEX* lplpwfxInfo, MMCKINFO* pckInRIFF);
	int DescendIntoChunk(HMMIO* phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF);
	int ReadWaveFile(HMMIO hmmioIn, UINT cbRead, BYTE* pbDest, MMCKINFO* pckIn, UINT* cbActualRead);

public:
	cSound();
	~cSound();

	void Load(LPSTR FileName, LPSTR szPath = NULL);					// 사운드 로드
	void Play(DWORD dwFlags = 0);									// 사운드 재생
	void Stop();																	// 사운드 정지

	int Release();

	/* SET */
	void SetVolume(LONG lVolume = 10);							// 볼륨 설정
	void SetVolume(D3DXVECTOR3 vCRTPosition);
	void SetPan(LONG lPan);												// 패닝 설정 
	void SetPan(D3DXVECTOR3 vCRTPosition);
	void SetSpeed(float fMul);												// 재생 속도 설정
	void SetSpeedToOrig();

	/* GET */
	DWORD GetBufferStatus();

	DWORD GetCurPlayPosition();


};