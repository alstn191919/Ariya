#include "stdafx.h"
#include "cHeightMap.h"

cHeightMap::cHeightMap() :_Mesh(NULL)
{

}
cHeightMap::~cHeightMap()
{
	SAFE_RELEASE(_Mesh);
	SAFE_RELEASE(pTexture);
}

void cHeightMap::load(const char* _Filename, const char* _imgFilename)
{
	D3DXCreateTextureFromFile(g_pD3DDevice, _imgFilename, &pTexture);
	FILE* _fp = NULL;
	fopen_s(&_fp, _Filename, "rb");
	unsigned char szBuff;
	int x = 0;
	int z = 256;
	int Count = 0;
	float TectureX = 0;
	float TectureY = 0;
	while (!feof(_fp))
	{
		szBuff = fgetc(_fp);
		ST_PNT_VERTEX Vertex(
			D3DXVECTOR3(x, (int)szBuff / 5 - 15, z),
			D3DXVECTOR3(0, 1, 0), 
			D3DXVECTOR2(TectureX / 256, TectureY/256));
		v_vertex.push_back(Vertex);
		if (x == 256)
		{
			x = 0;
			z--;
			TectureX = 0;
			TectureY++;
		}
		else
		{
			x++;
			TectureX++;
		}
	}
	fclose(_fp);
	v_vertex.pop_back();
	D3DXVECTOR3 v_Normal;
	for (int i = 0; i < (int)v_vertex.size(); i++)
	{
		if (i == 0)
		{
			D3DXVec3Cross(&v_Normal, &(v_vertex[i + 1].p - v_vertex[i].p), &v_vertex[i + 257].p);
			D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
		}
		else if (i < 256)
		{
			D3DXVec3Cross(&v_Normal, &(v_vertex[i + 1].p - v_vertex[i - 1].p), &(v_vertex[i + 257].p - v_vertex[i].p));
			D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
		}
		else if (i == 256)
		{
			D3DXVec3Cross(&v_Normal, &(v_vertex[i].p - v_vertex[i - 1].p), &(v_vertex[i + 257].p - v_vertex[i].p));
			D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
		}
		else if (i % 257 == 0)
		{
			if (i + 257 >= v_vertex.size())
			{
				D3DXVec3Cross(&v_Normal, &(v_vertex[i + 1].p - v_vertex[i].p), &(v_vertex[i].p - v_vertex[i - 257].p));
				D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
			}
			else
			{
				D3DXVec3Cross(&v_Normal, &(v_vertex[i + 1].p - v_vertex[i].p), &(v_vertex[i + 257].p - v_vertex[i - 257].p));
				D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
			}

		}
		else if (i % 256 == 0)
		{
			if (i + 256 > v_vertex.size())
			{
				D3DXVec3Cross(&v_Normal, &(v_vertex[i].p - v_vertex[i - 1].p), &(v_vertex[i].p - v_vertex[i - 257].p));
				D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
			}
			else
			{
				D3DXVec3Cross(&v_Normal, &(v_vertex[i].p - v_vertex[i - 1].p), &(v_vertex[i + 257].p - v_vertex[i - 257].p));
				D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
			}
		}
		else if (i + 257 > v_vertex.size())
		{
			D3DXVec3Cross(&v_Normal, &(v_vertex[i + 1].p - v_vertex[i - 1].p), &(v_vertex[i].p - v_vertex[i - 257].p));
			D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
		}
		else
		{
			D3DXVec3Cross(&v_Normal, &(v_vertex[i + 1].p - v_vertex[i - 1].p), &(v_vertex[i + 257].p - v_vertex[i - 257].p));
			D3DXVec3Normalize(&v_vertex[i].n, &v_Normal);
		}
	}
}
void cHeightMap:: Setup()
{
	D3DCOLORVALUE Color;
	Color.a = 1.0f; Color.g = 1.0f; Color.b = 1.0f; Color.a = 1.0f;
	_mtl.Ambient = Color;
	_mtl.Diffuse = Color;
	Color.a = 0.0f; Color.g = 0.0f; Color.b = 0.0f; Color.a = 0.0f;
	_mtl.Specular = Color;
	_mtl.Power = 3.0f;

	D3DXCreateMeshFVF(
		MaxTri,
		v_vertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&_Mesh);



	ST_PNT_VERTEX* VertexBuffer = NULL;
	_Mesh->LockVertexBuffer(0, (LPVOID*)&VertexBuffer);
	memcpy(VertexBuffer, &v_vertex[0], v_vertex.size() * sizeof(ST_PNT_VERTEX));
	_Mesh->UnlockVertexBuffer();

	DWORD* IndexBuffer = NULL;
	int _inDexX = 0;
	int _inDexZ = 1;
	_Mesh->LockIndexBuffer(0, (LPVOID*)&IndexBuffer);

	for (size_t i = 0; i < MaxTri*3; i += 6)
	{
		IndexBuffer[i + 2]	   = _inDexX + (257 * (_inDexZ - 1));
		IndexBuffer[i + 1] = _inDexX + (257 * _inDexZ);
		IndexBuffer[i] = _inDexX + 1 + (257 * (_inDexZ - 1));

		IndexBuffer[i + 5] = _inDexX + (257 * _inDexZ);
		IndexBuffer[i + 4] = _inDexX + 1 + (257 * _inDexZ);
		IndexBuffer[i + 3] = _inDexX + 1 + (257 * (_inDexZ - 1));

		if (_inDexX == 255)
		{
			_inDexX = 0;
			_inDexZ++;
		}
		else
		{
			_inDexX++;
		}
	}

	_Mesh->UnlockIndexBuffer();

	DWORD* ATT = NULL;
	_Mesh->LockAttributeBuffer(0, &ATT);
	for (int i = 0; i < MaxTri; i++)
	{
		ATT[i] = 0;
	}
	_Mesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(MaxTri*3);
	_Mesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		NULL,
		NULL,
		NULL);
}
void cHeightMap:: Update()
{

}

float cHeightMap::PositionHeight(D3DXVECTOR3 _pV)
{
	if (_pV.x < 1 || _pV.z < 1 || _pV.x > 256 || _pV.z > 256)
	{
		return 0.0f;
	}
	float lx = (float)_pV.x - (int)_pV.x;
	float lz = (float)_pV.z - (int)_pV.z;
	int VerinDex = (v_vertex.size()-1) + (int)_pV.x - (257 * (int)_pV.z) - 257;
	D3DXVECTOR3 _vPos = _pV;
	D3DXVECTOR3 _v1 = v_vertex[VerinDex].p;
	D3DXVECTOR3 _v2 = v_vertex[VerinDex+1].p;
	D3DXVECTOR3 _v3 = v_vertex[VerinDex-257].p;
	D3DXVECTOR3 _v4 = v_vertex[VerinDex-257+1].p;
	D3DXVECTOR3 _fz = _v2 - _v3;

	if ((_pV.z - _fz.z) + (_pV.x - _fz.x) < 1)
	{
		D3DXVECTOR3 _xVec = _v2 - _v1;
		D3DXVECTOR3 _zVec = _v3 - _v1;
		_xVec *= lx;
		_zVec *= lz;

		return _v1.y + (_xVec + _zVec).y;
	}
	else
	{
		D3DXVECTOR3 _xVec = _v2 - _v4;
		D3DXVECTOR3 _zVec = _v3 - _v4;
		_xVec *= lx;
		_zVec *= lz;

		return _v4.y - (_xVec + _zVec).y;
	}
}

void cHeightMap::Render()
{
	g_pD3DDevice->SetMaterial(&_mtl);
	g_pD3DDevice->SetTexture(0, pTexture);
	_Mesh->DrawSubset(0);
}