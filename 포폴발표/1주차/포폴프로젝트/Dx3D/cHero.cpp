#include "stdafx.h"
#include "cHero.h"
#include "cSkinnedMesh.h"

cHero::cHero(char* szDirectory, char* szFilename)
	: m_pSkinnedMesh(NULL)
	, m_enumState(CRT_STATE::CRT_IDLE)
	, m_enumDirection(ENUM_DIRECTION::DR_FORWARD)
{
	m_pSkinnedMesh = new cSkinnedMesh(szDirectory, szFilename);

	//바운딩 박스 설정
	m_pSkinnedMesh->SetMin(D3DXVECTOR3(-1, 0, -1));
	m_pSkinnedMesh->SetMax(D3DXVECTOR3(1, 3, 1));
}

cHero::~cHero()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cHero::UpdateAndRender(D3DXMATRIXA16 * pmat)
{
	//기어갈 때 바운딩 박스 변경
	if (m_enumState == CRT_STATE::CRT_CRAWL)
	{
		m_pSkinnedMesh->SetMin(D3DXVECTOR3(-1, 0, -1));
		m_pSkinnedMesh->SetMax(D3DXVECTOR3(1, 1, 1));
	}

	m_pSkinnedMesh->UpdateAndRender(pmat);
}

void cHero::SetAnimationIndex(int nIndex)
{
	m_pSkinnedMesh->SetAnimationIndex(nIndex);
}

void cHero::SetPosition(D3DXVECTOR3 v)
{
	m_pSkinnedMesh->SetPosition(v);
}

void cHero::SetState(CRT_STATE chrtState)
{
	m_enumState = chrtState;
}

void cHero::SetDirection(ENUM_DIRECTION direction)
{
	m_enumDirection = direction;
}

/*		GET		*/

cSkinnedMesh * cHero::GetMesh()
{
	return m_pSkinnedMesh;
}

D3DXVECTOR3 cHero::GetPosition()
{
	return m_pSkinnedMesh->GetPosition();
}

ST_SPHERE * cHero::GetBoundingSphere()
{
	return m_pSkinnedMesh->GetBoundingSphere();
}
