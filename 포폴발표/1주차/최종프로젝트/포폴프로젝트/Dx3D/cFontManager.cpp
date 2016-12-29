#include "StdAfx.h"
#include "cFontManager.h"

cFontManager::cFontManager()
{

}

cFontManager::~cFontManager()
{

}

LPD3DXFONT cFontManager::GetFont( eFontType e )
{
	if (m_mapFont.find(e) != m_mapFont.end())
		return m_mapFont[e];

	if (e == E_FT_NORMAL)
	{
		D3DXFONT_DESC fd;
		ZeroMemory(&fd,sizeof(D3DXFONT_DESC));
		fd.Height			= 25;
		fd.Width			= 12;
		fd.Weight			= FW_NORMAL;
		fd.Italic			= false;
		fd.CharSet			= DEFAULT_CHARSET;
		fd.OutputPrecision  = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily   = FF_DONTCARE;
		//AddFontResource("umberto.ttf");
		strcpy_s(fd.FaceName, "궁서체");	//글꼴 스타일
		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
	}
	return m_mapFont[e];
}

void cFontManager::Destory()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
}
