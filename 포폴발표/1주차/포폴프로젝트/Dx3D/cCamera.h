#pragma once
class cCamera
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vEye, vEye);
	SYNTHESIZE(D3DXVECTOR3, m_vLookAt, vLookat);

	D3DXVECTOR3            m_vUp;
	D3DXMATRIXA16         m_matView;
	D3DXMATRIXA16         m_matProj;
	POINT               m_ptPrevMouse;
	bool               m_isLButtonDown;
	bool				m_LockupMouse;
	SYNTHESIZE(float, m_fAngleX, fAngleX);
	SYNTHESIZE(float, m_fAngleY, fAngleY);
	float             m_fTempX;
	float             m_fTempY;
	//HCURSOR temp;
	POINT temp;
	float               m_fDistance;

	//오브젝트 용
	bool               m_isLButtonOBJDown;
	POINT               m_ptOBJPrevMouse;
	float               m_fAngleX_obj;
	float               m_fAngleY_obj;
	bool				isPlay;
	bool				isOpen;
	float				startTime;
public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	void Update(D3DXVECTOR3* pTarget, D3DXVECTOR3* pDirection, bool IsCrawl = NULL);


	D3DXMATRIXA16* GetViewMatrix();
	D3DXMATRIXA16* GetProjMatrix();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};