#pragma once

class cMtlTex;
class cGroup;

class cObjLoader
{
private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;

public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN char* szPath, OUT std::vector<cGroup*>& vecGroup, IN D3DXMATRIXA16* pmat = NULL);
	LPD3DXMESH Load(IN char* szPath, 
		OUT std::vector<cMtlTex*>& vecMtlTex,
		IN D3DXMATRIXA16* pmat = NULL);

private:
	void LoadMtlLib(char* szPath);
	void LoadMtlLib(char* szPath, OUT std::vector<cMtlTex*>& vecMtlTex);
};

