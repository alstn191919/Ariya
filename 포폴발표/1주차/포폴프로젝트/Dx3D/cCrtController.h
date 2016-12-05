#pragma once

class iMap;

class cCrtController
{
private:
	bool						m_isRight;
	float						m_fSpeed;
	SYNTHESIZE(float, m_fAngleX, fAngleX);

	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDirection, Direction);
public:
	cCrtController(void);
	~cCrtController(void);

	void Setup();
	void Update(iMap* pMap = NULL);
	
	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}
	
	D3DXMATRIXA16* GetWorldTM()
	{
		return &m_matWorld;
	}

};