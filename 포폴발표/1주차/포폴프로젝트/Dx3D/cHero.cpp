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
	m_Min = D3DXVECTOR3(-1, 0, -1);
	m_Max = D3DXVECTOR3(1, 3, 1);
	m_pSkinnedMesh->SetMin(m_Min);
	m_pSkinnedMesh->SetMax(m_Max);
}

cHero::~cHero()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cHero::UpdateAndRender(D3DXMATRIXA16 * pmat)
{
	//캐릭터 상태에 따른 바운딩박스, 애니메이션 변화
	if (m_enumState == CRT_STATE::CRT_CRAWL)					//기어가기
	{
		//현재 임시값
		m_Min = D3DXVECTOR3(-1, 0, -1);
		m_Max = D3DXVECTOR3(1, 1, 1);

		//애니메이션 세팅: ENUM_DIRECTION에 따라 바꿉니다.
		SetAnimationCrawl();
	}
	else if (m_enumState == CRT_STATE::CRT_IDLE)				//기본
	{
		m_Min = D3DXVECTOR3(-1, 0, -1);
		m_Max = D3DXVECTOR3(1, 3, 1);

		SetAnimationIdle();
	}
	else if (m_enumState == CRT_STATE::CRT_WALK)					//걷기
	{
		m_Min = D3DXVECTOR3(-1, 0, -1);
		m_Max = D3DXVECTOR3(1, 3, 1);

		SetAnimationWalk();
	}
	else if (m_enumState == CRT_STATE::CRT_RUN)					//뛰기
	{
		m_Min = D3DXVECTOR3(-1, 0, -1);
		m_Max = D3DXVECTOR3(1, 3, 1);

		SetAnimationRun();
	}

	//메시 바운딩박스 설정
	m_pSkinnedMesh->SetMin(m_Min);
	m_pSkinnedMesh->SetMax(m_Max);

	m_pSkinnedMesh->UpdateAndRender(pmat);
}

void cHero::SetAnimationCrawl()
{
	//기본 상태
	SetAnimationIndex(ANIM_STAY_CRAWL);

	//입력에 따른 처리
	if (m_enumDirection == ENUM_DIRECTION::DR_NONE)
	{
		SetAnimationIndex(ANIM_STAY_CRAWL);
	}
	else if (m_enumDirection == ENUM_DIRECTION::DR_FORWARD || DR_LEFT || DR_RIGHT)
	{
		SetAnimationIndex(ANIM_FORDWALK_CRAWL);
	}
	else if (m_enumDirection == ENUM_DIRECTION::DR_BACKWARD)
	{
		SetAnimationIndex(ANIM_BACKWALK_CRAWL);
	}
}

void cHero::SetAnimationIdle()
{
	//기본 상태
	SetAnimationIndex(ANIM_IDLE);

	if (m_isInteract)	//상호작용의 처리
	{
		if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
		{
			SetAnimationIndex(ANIM_OPEN_FAST);
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
		{
			SetAnimationIndex(ANIM_JUMPOVER_FAST);
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
		{
			SetAnimationIndex(ANIM_CATCH);
		}
	}
	else	//입력에 따른 처리
	{
		if (m_enumDirection == ENUM_DIRECTION::DR_NONE)
		{
			SetAnimationIndex(ANIM_IDLE);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_FORWARD)
		{
			SetAnimationIndex(ANIM_FORDWALK);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_BACKWARD)
		{
			SetAnimationIndex(ANIM_BACKWALK);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_LEFT || DR_RIGHT)
		{
			SetAnimationIndex(ANIM_LEFTWALK);
		}
	}
}

void cHero::SetAnimationWalk()
{
	SetAnimationIndex(ANIM_FORDWALK);

	if (m_isInteract)	//상호작용의 처리
	{
		if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
		{
			SetAnimationIndex(ANIM_OPEN_FAST);
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
		{
			SetAnimationIndex(ANIM_JUMPOVER);
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
		{
			SetAnimationIndex(ANIM_CATCH);
		}
	}
	else	//입력에 따른 처리
	{
		if (m_enumDirection == ENUM_DIRECTION::DR_NONE)
		{
			SetAnimationIndex(ANIM_FORDWALK);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_FORWARD)
		{
			SetAnimationIndex(ANIM_FORDWALK);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_BACKWARD)
		{
			SetAnimationIndex(ANIM_BACKWALK);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_LEFT || DR_RIGHT)
		{
			SetAnimationIndex(ANIM_LEFTWALK);
		}
	}
}

void cHero::SetAnimationRun()
{
	SetAnimationIndex(ANIM_RUN);

	if (m_isInteract)	//상호작용의 처리
	{
		if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
		{
			SetAnimationIndex(ANIM_OPEN_FAST);
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
		{
			SetAnimationIndex(ANIM_JUMPOVER_FAST);
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
		{
			SetAnimationIndex(ANIM_CATCH);
		}
	}
	else	//입력에 따른 처리
	{
		if (m_enumDirection == ENUM_DIRECTION::DR_NONE)
		{
			SetAnimationIndex(ANIM_RUN);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_FORWARD)
		{
			SetAnimationIndex(ANIM_FORDWALK);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_BACKWARD)
		{
			SetAnimationIndex(ANIM_BACKWALK);
		}
		else if (m_enumDirection == ENUM_DIRECTION::DR_LEFT || DR_RIGHT)
		{
			SetAnimationIndex(ANIM_LEFTWALK);
		}
	}
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
