#pragma once

#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{
public:
	enum eFontType
	{
		E_FT_NORMAL,
		E_FT_QUEST,
		E_FT_CHATTING,
	};

private:
	std::map<eFontType, LPD3DXFONT> m_mapFont;

private:
	SINGLETONE(cFontManager);

public:
	LPD3DXFONT GetFont(eFontType e);
	void Destory();
};

