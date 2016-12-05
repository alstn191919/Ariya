#pragma once
#define MaxTri 131072
class cHeightMap
{
private:
	std::vector<ST_PNT_VERTEX> v_vertex;
	LPD3DXMESH _Mesh;
	LPDIRECT3DTEXTURE9 pTexture;
	D3DMATERIAL9 _mtl;
public:
	cHeightMap();
	~cHeightMap();

	void load(const char* _Filename, const char* _imgFilename);
	void Setup();
	float PositionHeight(D3DXVECTOR3 _pV);
	void Update();
	void Render();
};

