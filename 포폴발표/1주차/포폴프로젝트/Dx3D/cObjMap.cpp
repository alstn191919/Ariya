#include "StdAfx.h"
#include "cObjMap.h"
#include "cGroup.h"
#include "cObjLoader.h"

cObjMap::cObjMap(void)
{
}


cObjMap::~cObjMap(void)
{
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}
}

void cObjMap::Load( char* szMap, char* szSurface, D3DXMATRIXA16* pmat /*= NULL*/ )
{
	cObjLoader l;
	l.Load(szMap, m_vecGroup, pmat);
	if (szSurface == NULL) return;
	std::vector<D3DXVECTOR3>	vecV;

	FILE* fp = NULL;

	fopen_s(&fp, szSurface, "r");

	while(!feof(fp))
	{
		char szBuf[1024] = {'\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;

		if (szBuf[0] == '#') 
		{
			continue;
		}
		else if(szBuf[0] == 'm')
		{
		}
		else if(szBuf[0] == 'u')
		{
		}
		else if(szBuf[0] == 'g')
		{
		}
		else if(szBuf[0] == 'v')
		{
			if(szBuf[1] == 't')
			{
			}
			else if(szBuf[1] == 'n')
			{
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szBuf[0] == 'f')
		{
			int aIndex[3];
			sscanf_s(szBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; ++i)
			{
				D3DXVECTOR3 p = vecV[aIndex[i] - 1];
				if(pmat)
				{
					D3DXVec3TransformCoord(&p, &p, pmat);
				}
				m_vecSurface.push_back(p);
			}
		}
	}

	fclose(fp);
}

void cObjMap::Render()
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}

bool cObjMap::GetHeight( IN float x, OUT float& y, IN float z )
{
	D3DXVECTOR3 vRayPos(x, y + 5, z);
	D3DXVECTOR3 vRayDir( 0,-1, 0);
	float u, v, d;
	for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecSurface[i];
		D3DXVECTOR3 v1 = m_vecSurface[i + 1];
		D3DXVECTOR3 v2 = m_vecSurface[i + 2];
		if(D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			y = (y + 5) - d;
			return true;
		}
	}
	y = 0;
	return false;
}

