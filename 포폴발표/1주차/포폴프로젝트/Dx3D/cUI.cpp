#include "stdafx.h"
#include "cUI.h"
#include "cUIObject.h"
#include "cUIImageView.h"
#include "cUITextView.h"


cUI::cUI()
{
}


cUI::~cUI()
{
}




void cUI::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIImageView* pImageView = new cUIImageView;
	D3DXIMAGE_INFO stImageInfo;
	

	ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetSpriteTexture(
		//"./UI2/panel-info.png.png",
		"./UI/UI_S.tga",
		&stImageInfo);
	pImageView->SetTexture(pTexture);
	pImageView->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	pImageView->SetLocalPos(D3DXVECTOR3(-200, 50, 0));
	m_pUI = pImageView;


	//pImageView = new cUIImageView;
	//ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	//pTexture = g_pTextureManager->GetSpriteTexture(
	//	//"./UI2/panel-info.png.png",
	//	"./UI/UI_IN.tga",
	//	&stImageInfo);
	//pImageView->SetTexture(pTexture);
	//pImageView->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	//pImageView->SetLocalPos(D3DXVECTOR3(200, 50, 0));
	//m_pUI->AddChild(pImageView);


	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cUIButton* pButton = NULL;
	pButton = new cUIButton;
	pButton->SetTexture("./UI/butten2.png",
		"./UI/butten_over2.png",
		"./UI/butten_down.jpg");
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat, rc.right/2 - 35, rc.bottom - 100, 0);
	pButton->SetWorld(mat);
	pButton->SetDelegate(this);
	pButton->SetTag(E_BUTTON1);
	pButton->AutoRelease();
	m_pUI->AddChild(pButton);




	 pImageView = new cUIImageView;


	ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	LPDIRECT3DTEXTURE9 pTexture2 = g_pTextureManager->GetSpriteTexture(
		"./UI/UI_IN.tga",
		&stImageInfo);
	pImageView->SetTexture(pTexture2);
	pImageView->SetSize(ST_SIZE(stImageInfo.Width, stImageInfo.Height));
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat, 100, 0, 0);
	pImageView->SetWorld(mat);
	//pImageView->SetLocalPos(D3DXVECTOR3(-200, 50, 0));
	m_pUI_IN = pImageView;

    pButton = NULL;
	pButton = new cUIButton;
	pButton->SetTexture("./UI/butten2.png",
		"./UI/butten_over2.png",
		"./UI/butten_down.jpg");

	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat, rc.right / 2 - 35, rc.bottom - 100, 0);
	pButton->SetWorld(mat);
	pButton->SetDelegate(this);
	pButton->SetTag(E_BUTTON1);
	pButton->AutoRelease();
	m_pUI_IN->AddChild(pButton);


	cUITextView * pTextView = new cUITextView;
	pTextView->SetText("±¸...±¸±ÞÆÑ!?");
	pTextView->SetFont(g_pFontManager->GetFont(cFontManager::E_FT_NORMAL));
//	pTextView->SetLocalPos(D3DXVECTOR3(100, 100, 0));
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat, rc.right / 2 - 35-150, rc.bottom /2-100, 0);
	pTextView->SetWorld(mat);
	pTextView->SetSize(ST_SIZE(321, 200));
	pTextView->SetDrawTextFormat(DT_CENTER | DT_TOP | DT_WORDBREAK);
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	pTextView->SetTag(E_TEXTVIEW);
	pTextView->AutoRelease();
	//	m_pUIRoot = pTextView;
	m_pUI_IN->AddChild(pTextView);

}



void cUI::Render()
{
	m_pUI->Render(m_pSprite);
	if (GetAsyncKeyState(VK_SPACE))
	{
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		m_pUI_IN->Render(m_pSprite);
		//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	}
}



void cUI::OnClick(cUIButton* pSender)
{

}