#pragma once

class cMtlTex;
class cMapRender
{
private:
	LPD3DXMESH					m_pMapMesh;				// �� �Ž�
	std::vector<cMtlTex*>		m_vecMtlTex;			// �ؽ�,���׸���
	std::vector<ST_SHADER>		gpLightingShader;		// ���̴�����ü	
	D3DXVECTOR4					gWorldLightPosition;	// ���� ��ġ
	D3DXVECTOR4					gLightColor;			// �� �÷�
private:
	std::vector<D3DXVECTOR3>	m_vecSurface;			// �����̽� STL
public:
	void Setup(char* fileName, char* surFace, D3DXVECTOR3 Position, D3DXVECTOR3 sPosition, D3DXVECTOR3 lightPosition,float Scale);
	void Update();
	void Render(D3DXVECTOR3 _gWorldCameraPosition,float lightRange);
	bool GetHeight(IN float x, OUT float& y, IN float z);
	void Load(char* szSurface, D3DXVECTOR3 Position);
	cMapRender();
	~cMapRender();
};