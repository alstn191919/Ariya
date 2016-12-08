#pragma once

struct ST_SHADER
{
	LPD3DXEFFECT Shader;		// ���̴�
	D3DXVECTOR4 Position;		// ���̴� ��ġ

	ST_SHADER() { Shader = NULL; Position = D3DXVECTOR4(0, 0, 0, 1); }
	ST_SHADER(D3DXVECTOR3 Pos)
	{ 
		Shader = NULL;
		Position = D3DXVECTOR4(Pos.x, Pos.y, Pos.z, 1);
	}
};

class cMtlTex;

#define Mapsize	1.0f			//�� ��ü ũ�� ����
#define MapPositionY -127.5f	//�� ���� Y��
#define MapPositionX 0.0f		//�� ���� X��
#define MapPositionZ 0.0f		//�� ���� Z��

#define SurPositionX 1.0f
#define SurPositionY 1.0f
#define SurPositionZ 1.0f
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
	void Setup();
	void Update();
	void Render(D3DXVECTOR3 _gWorldCameraPosition);
	bool GetHeight(IN float x, OUT float& y, IN float z);
	void Load(char* szSurface);
	cMapRender();
	~cMapRender();
};

