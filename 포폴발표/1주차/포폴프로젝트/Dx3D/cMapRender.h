#pragma once

struct ST_SHADER
{
	LPD3DXEFFECT Shader;		// 쉐이더
	D3DXVECTOR4 Position;		// 쉐이더 위치

	ST_SHADER() { Shader = NULL; Position = D3DXVECTOR4(0, 0, 0, 1); }
	ST_SHADER(D3DXVECTOR3 Pos)
	{ 
		Shader = NULL;
		Position = D3DXVECTOR4(Pos.x, Pos.y, Pos.z, 1);
	}
};

class cMtlTex;

#define Mapsize	1.0f			//맵 전체 크기 비율

#define MapPositionX 2.0f		//맵 위지 X
#define MapPositionY -126.5f	//맵 위지 Y
#define MapPositionZ 9.0f		//맵 위지 Z

#define SurPositionX 15.0f		//서페이스맵 위지 X
#define SurPositionY -126.5f	//서페이스맵 위지 Y
#define SurPositionZ 7.0f		//서페이스맵 위지 Z
class cMapRender
{
private:
	LPD3DXMESH					m_pMapMesh;				// 맵 매쉬
	std::vector<cMtlTex*>		m_vecMtlTex;			// 텍스,메테리얼
	std::vector<ST_SHADER>		gpLightingShader;		// 쉐이더구조체	
	D3DXVECTOR4					gWorldLightPosition;	// 빛의 위치
	D3DXVECTOR4					gLightColor;			// 빛 컬러
private:
	std::vector<D3DXVECTOR3>	m_vecSurface;			// 서페이스 STL
public:
	void Setup();
	void Update();
	void Render(D3DXVECTOR3 _gWorldCameraPosition);
	bool GetHeight(IN float x, OUT float& y, IN float z);
	void Load(char* szSurface);
	cMapRender();
	~cMapRender();
};

