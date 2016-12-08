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

class iMap;
class cHeightMap;
class cMtlTex;

#define Mapsize	1.0f			//�� ��ü ũ�� ����
#define MapPositionY -127.5f	//�� ���� Y��
#define MapPositionX 0.0f		//�� ���� X��
#define MapPositionZ 0.0f		//�� ���� Z��

class cMapRender
{
private:
	LPD3DXMESH					m_pMapMesh;				// �� �Ž�
	std::vector<cMtlTex*>		m_vecMtlTex;			// �ؽ�,���׸���
	std::vector<ST_SHADER>		gpLightingShader;		// ���̴�����ü	
	D3DXVECTOR4					gWorldLightPosition;	// ���� ��ġ
	D3DXVECTOR4					gLightColor;			// �� �÷�
public:
	void Setup();
	void Update();
	void Render(D3DXVECTOR3 _gWorldCameraPosition);


	cMapRender();
	~cMapRender();
};

