#pragma once
#include"cUIButton.h"
class cUIImageView;
class cUI :public iUIButtonDelegate
{
private:

	cUIObject*					m_pUI;				//OBJ_TYPE::item UI
	cUIObject*					m_pUI_IN;
	LPD3DXSPRITE				m_pSprite;

public:
	void Setup();
	void Render();

	virtual void OnClick(cUIButton* pSender) override;

	cUI();
	~cUI();
};

