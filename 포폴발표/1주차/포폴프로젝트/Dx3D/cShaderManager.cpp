#include "stdafx.h"
#include "cShaderManager.h"

cShaderManager::cShaderManager()
{
}

cShaderManager::~cShaderManager()
{
}

LPD3DXEFFECT cShaderManager::Getshader(const char* szPath)
{
	return Getshader(std::string(szPath));
}

LPD3DXEFFECT cShaderManager::Getshader(std::string szPath)
{
	if (gpLightingShader.find(szPath) == gpLightingShader.end())
	{
		LPD3DXEFFECT ret = NULL;
		LPD3DXBUFFER pError = NULL;
		DWORD dwShaderFlags = 0;

#if _DEBUG
		dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

		D3DXCreateEffectFromFile(g_pD3DDevice, szPath.c_str(),
			NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

		if (!ret && pError)
		{
			int size = pError->GetBufferSize();
			void *ack = pError->GetBufferPointer();

			if (ack)
			{
				char* str = new char[size];
				sprintf_s(str, size,(const char*)ack);
				OutputDebugString(str);
				delete[] str;
			}
		}
		gpLightingShader[szPath] = ret;
	}
	return gpLightingShader[szPath];
}
void cShaderManager::Destroy()
{

}