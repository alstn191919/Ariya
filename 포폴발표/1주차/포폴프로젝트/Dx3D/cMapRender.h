#pragma once

class cMtlTex;

class cMapRender
{
private:
	LPD3DXMESH					m_pMapMesh;				// �� �Ž�
	std::vector<cMtlTex*>		m_vecMtlTex;			// �ؽ�,���׸���
	std::vector<ST_SHADER>		gpLightingShader;		// ���̴�����ü	
	D3DXVECTOR3					gWorldLightPosition;	// ���� ��ġ
	D3DXVECTOR4					gLightColor;			// �� �÷�
private://���̴�
	LPDIRECT3DTEXTURE9			gpShadowRenderTarget;
	LPDIRECT3DSURFACE9			gpShadowDepthStencil;
	LPD3DXEFFECT				gpApplyShadowShader;
	LPD3DXEFFECT				gpCreateShadowShader;
private:
	LPD3DXFONT					gpFont;
	LPD3DXSPRITE				LogoSprite;				//����׿�
	std::vector<D3DXVECTOR3>	m_vecSurface;			// �����̽� STL
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