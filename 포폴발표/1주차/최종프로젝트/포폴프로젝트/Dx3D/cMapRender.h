#pragma once

class cMtlTex;

class cMapRender
{
private:
	LPD3DXMESH					m_pMapMesh;				// 맵 매쉬
	std::vector<cMtlTex*>		m_vecMtlTex;			// 텍스,메테리얼
	D3DXVECTOR3					gWorldLightPosition;	// 빛의 위치
	D3DXVECTOR4					gLightColor;			// 빛 컬러
private://깊이버퍼
	LPDIRECT3DTEXTURE9			gpShadowRenderTarget;
	LPDIRECT3DSURFACE9			gpShadowDepthStencil;
	LPDIRECT3DTEXTURE9			gpBackShadowRenderTarget;
	LPDIRECT3DSURFACE9			gpBackShadowDepthStencil;
private://셰이더
	LPD3DXEFFECT				gpApplyShadowShader;
	LPD3DXEFFECT				gpCreateShadowShader;
	LPD3DXEFFECT				gpBackCreateShadowShader;
private:
	LPD3DXFONT					gpFont;
	LPD3DXSPRITE				LogoSprite;				//디버그용
	std::vector<D3DXVECTOR3>	m_vecSurface;			// 서페이스 STL
public:
	void Setup(char* fileName, char* surFace, D3DXVECTOR3 Position, D3DXVECTOR3 sPosition, float Scale);
	void Update();
	void Render(D3DXVECTOR4* _gWorldLightPosition, D3DXVECTOR4* _gWorldLightDir, D3DXVECTOR3 _gWorldCameraPosition, float lightRange, float* lightPower);
	bool GetHeight(IN float x, OUT float& y, IN float z);
	void Shadowinit(char* ApplyShaderFilename, char* CreateShaderFilename, char* BackCreateShaderFilename);
private:
	void Load(char* szSurface, D3DXVECTOR3 Position);
	void FrontDebugRender();
	void BackDebugRender();

	void shaderRender(D3DXVECTOR4* _gWorldLightPosition, D3DXVECTOR4* _gWorldLightDir, D3DXVECTOR3 _gWorldCameraPosition, float lightRange, float* lightPower);
public:
	cMapRender();
	~cMapRender();
};