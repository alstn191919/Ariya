#pragma once

class cMtlTex;

class cMapRender
{
private:
	LPD3DXMESH					m_pMapMesh;				// 맵 매쉬
	std::vector<cMtlTex*>		m_vecMtlTex;			// 텍스,메테리얼
	std::vector<ST_SHADER>		gpLightingShader;		// 쉐이더구조체	
	D3DXVECTOR3					gWorldLightPosition;	// 빛의 위치
	D3DXVECTOR4					gLightColor;			// 빛 컬러
private://셰이더
	LPDIRECT3DTEXTURE9			gpShadowRenderTarget;
	LPDIRECT3DSURFACE9			gpShadowDepthStencil;
	LPD3DXEFFECT				gpApplyShadowShader;
	LPD3DXEFFECT				gpCreateShadowShader;
private:
	LPD3DXFONT					gpFont;
	LPD3DXSPRITE				LogoSprite;				//디버그용
	std::vector<D3DXVECTOR3>	m_vecSurface;			// 서페이스 STL
public:
	void Setup(char* fileName, char* surFace, D3DXVECTOR3 Position, D3DXVECTOR3 sPosition, float Scale);
	void Update();
	void Render(D3DXVECTOR3 _gWorldLightPosition, D3DXVECTOR3 _gWorldLightDir, D3DXVECTOR3 _gWorldCameraPosition, float lightRange, float lightPower);
	bool GetHeight(IN float x, OUT float& y, IN float z);
	void Shadowinit(char* ApplyShaderFilename, char* CreateShaderFilename);
private:
	void Load(char* szSurface, D3DXVECTOR3 Position);
	void DebugRender();
	void shaderRender(D3DXVECTOR3 _gWorldLightPosition, D3DXVECTOR3 _gWorldLightDir, D3DXVECTOR3 _gWorldCameraPosition, float lightRange, float lightPower);
public:
	cMapRender();
	~cMapRender();
};