#include "StdAfx.h"
#include "cMtlTex.h"


cMtlTex::cMtlTex(void)
	: m_pTexture(NULL)
	, m_pTextureN(0)
	, m_pTextureS(0)
	, m_dwAttrID(0)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}


cMtlTex::~cMtlTex(void)
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTextureS);
	SAFE_RELEASE(m_pTextureS);
}