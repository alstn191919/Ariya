#pragma once

class cMapRender;

class cCrtController
{
private:
	bool                  m_isRight;
	float                  m_fSpeed;
	SYNTHESIZE(float, m_fAngleX, fAngleX);
	SYNTHESIZE(float, m_fAngleY, fAngleY);

	D3DXVECTOR3               m_vPosition;
	D3DXMATRIXA16            m_matWorld;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDirection, Direction);
public:
	cCrtController(void);
	~cCrtController(void);

	void Setup();
	void Update(cMapRender* pMap , cOBB * poBB);

	void SetSpeed(float f)
	{
		m_fSpeed = f;
	}

	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}

	void SetPosition(D3DXVECTOR3* v)
	{
		m_vPosition = *v;
	}

	D3DXMATRIXA16* GetWorldTM()
	{
		return &m_matWorld;
	}

};