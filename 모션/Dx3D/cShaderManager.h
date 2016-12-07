#pragma once

#define g_pLightShaderManager cShaderManager::GetInstance()

class cShaderManager
{
private:
	SINGLETONE(cShaderManager);
private:
	std::map<std::string, LPD3DXEFFECT> gpLightingShader;
public:
	LPD3DXEFFECT Getshader(const char* filename);
	LPD3DXEFFECT Getshader(std::string sPath);
	void Destroy();
};

