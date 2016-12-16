#pragma once

class cMtlTex;
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
	void Setup(char* fileName, char* surFace, D3DXVECTOR3 Position, D3DXVECTOR3 sPosition, D3DXVECTOR3 lightPosition,float Scale);
	void Update();
	void Render(D3DXVECTOR3 _gWorldCameraPosition,float lightRange);
	bool GetHeight(IN float x, OUT float& y, IN float z);
	void Load(char* szSurface, D3DXVECTOR3 Position);
	cMapRender();
	~cMapRender();
};