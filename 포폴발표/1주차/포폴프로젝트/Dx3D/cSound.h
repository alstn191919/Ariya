#include "stdafx.h"

#define DSVOLUME_TO_DB(Volume)  ((DWORD)(-30*(100-Volume))) // ���� ���� ��ũ��.
class cSound
{
private:
	int m_nRate;
	int m_nSize;

	DSBUFFERDESC					m_DSBufDesc;
	WAVEFORMATEX				m_WaveFmtX;

	LPDIRECTSOUND					m_pDS;
	LPDIRECTSOUNDBUFFER    m_pDSBuffer;

	SYNTHESIZE_PASS_BY_REF(LPSTR, m_szPath, Path);
	SYNTHESIZE(bool, m_isPlay, State);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);							//�÷��̾� �þ߿����� position. �þ� ���� ���
	SYNTHESIZE(SOUND_MAP, m_vMapPosition, MapPosition);					//��� SOUND_MAP�� �����ϴ���

private:
	int LoadWAV(char *FileName, int Flags);

	int ReadMMIO(HMMIO hmmioIn, MMCKINFO* pckInRIFF, LPWAVEFORMATEX* lplpwfxInfo);
	int OpenWaveFile(LPSTR FileName, HMMIO* phmmioIn, LPWAVEFORMATEX* lplpwfxInfo, MMCKINFO* pckInRIFF);
	int DescendIntoChunk(HMMIO* phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF);
	int ReadWaveFile(HMMIO hmmioIn, UINT cbRead, BYTE* pbDest, MMCKINFO* pckIn, UINT* cbActualRead);

public:
	cSound();
	~cSound();

	void Load(LPSTR FileName, LPSTR szPath = NULL);					// ���� �ε�
	void Play(DWORD dwFlags = 0);									// ���� ���
	void Stop();																	// ���� ����
	void SetVolume(LONG lVolume = 10);							// ���� ����
	void SetVolume(D3DXVECTOR3 vCRTPosition);
	void SetPan(LONG lPan);												// �д� ���� 
	void SetPan(D3DXVECTOR3 vCRTPosition);

	DWORD GetBufferStatus();

	DWORD GetCurPlayPosition();

	int Release();

};