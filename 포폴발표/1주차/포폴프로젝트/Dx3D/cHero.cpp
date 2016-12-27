#include "stdafx.h"
#include "cHero.h"
#include "cSkinnedMesh.h"

cHero::cHero(char* szDirectory, char* szFilename)
	: m_pSkinnedMesh(NULL)
	, m_enumState(CRT_STATE::CRT_IDLE)
	, m_enumDirection(ENUM_DIRECTION::DR_NONE)
	, m_enumPrevState(m_enumState)
	, m_enumPrevDirection(m_enumDirection)
	//, m_isInteract(false)
	, m_enumInteraction(CRT_INTERACTION::ACTION_NONE)
{
	m_pSkinnedMesh = new cSkinnedMesh(szDirectory, szFilename);

	//바운딩 박스 설정
	m_Min = D3DXVECTOR3(-1, 0, -1);
	m_Max = D3DXVECTOR3(1, 3, 1);
	m_pSkinnedMesh->SetMin(m_Min);
	m_pSkinnedMesh->SetMax(m_Max);

	SetAnimationIndex(CRT_ANIMLIST::ANIM_IDLE);
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
		m_Max = D3DXVECTOR3(1, 0, 1);

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
	else if (m_enumState == CRT_STATE::CRT_JUMPOVER)
	{
		m_Min = D3DXVECTOR3(-1, 2, -1);
		m_Max = D3DXVECTOR3(1, 3, 1);

		m_pSkinnedMesh->GetPosition();
	}

	m_enumPrevState = m_enumState;
	m_enumPrevDirection = m_enumDirection;

	//메시 바운딩박스 설정
	m_pSkinnedMesh->SetMin(m_Min);
	m_pSkinnedMesh->SetMax(m_Max);

	m_pSkinnedMesh->UpdateAndRender(pmat);
}

void cHero::SetAnimationCrawl()
{
	if (m_enumState != m_enumPrevState)
	{
		//기본 상태
		SetAnimationIndex(ANIM_STAY_CRAWL);
	}

	if (m_enumPrevDirection == m_enumDirection)
	{
		return;
	}

	//입력에 따른 처리
	//캐릭터 모델링에 머리 없는 게 보여서 stay로 통일
	//if (m_enumDirection == ENUM_DIRECTION::DR_NONE)
	//{
	//	SetAnimationIndex(ANIM_STAY_CRAWL);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_FORWARD || DR_LEFT || DR_RIGHT)
	//{
	//	SetAnimationIndex(ANIM_FORDWALK_CRAWL);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_BACKWARD)
	//{
	//	SetAnimationIndex(ANIM_BACKWALK_CRAWL);
	//}
}

void cHero::SetAnimationIdle()
{
	if (m_enumState != m_enumPrevState)
	{
		//기본 상태
		SetAnimationIndex(ANIM_IDLE);
	}

	//상호작용의 처리
	if (m_enumInteraction != CRT_INTERACTION::ACTION_NONE)
	{
		if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
		{
			SetAnimationIndex(ANIM_OPEN_FAST);
			return;
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
		{
			SetAnimationIndex(ANIM_JUMPOVER);
			return;
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
		{
			SetAnimationIndex(ANIM_CATCH);
			return;
		}
	}

	//입력에 따른 처리
	if (m_enumPrevDirection == m_enumDirection)
	{
		return;
	}
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

void cHero::SetAnimationWalk()
{
	if (m_enumState != m_enumPrevState)
	{
		//기본 상태
		SetAnimationIndex(ANIM_FORDWALK);
	}

	//상호작용의 처리
	if (m_enumInteraction != CRT_INTERACTION::ACTION_NONE)
	{
		if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
		{
			SetAnimationIndex(ANIM_OPEN_FAST);
			return;
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
		{
			SetAnimationIndex(ANIM_JUMPOVER);
			return;
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
		{
			SetAnimationIndex(ANIM_CATCH);
			return;
		}
	}

	//입력에 따른 처리
	if (m_enumPrevDirection == m_enumDirection)
	{
		return;
	}
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

void cHero::SetAnimationRun()
{
	if (m_enumState != m_enumPrevState)
	{
		//기본 상태
		SetAnimationIndex(ANIM_RUN);
	}

	//상호작용의 처리
	if (m_enumInteraction != CRT_INTERACTION::ACTION_NONE)
	{
		if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
		{
			SetAnimationIndex(ANIM_OPEN_FAST);
			return;
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
		{
			SetAnimationIndex(ANIM_JUMPOVER_FAST);
			return;
		}
		else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
		{
			SetAnimationIndex(ANIM_CATCH);
			return;
		}
	}

	//입력에 따른 처리
	if (m_enumPrevDirection == m_enumDirection)
	{
		return;
	}
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

bool cHero::IsCrawl()
{
	if (m_enumState == CRT_STATE::CRT_CRAWL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void cHero::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'C':
		{
			m_enumState = CRT_STATE::CRT_CRAWL;
			break;
		}
		case  'R':
		{
			if (m_enumState != CRT_STATE::CRT_CRAWL)
				m_enumState = CRT_STATE::CRT_RUN;
			break;
		}

		case 'W':
		{
			if (m_enumState != CRT_STATE::CRT_RUN && m_enumState != CRT_STATE::CRT_CRAWL)
			{
				m_enumState = CRT_STATE::CRT_WALK;
			}
			//방향 설정 : 정면
			m_enumDirection = ENUM_DIRECTION::DR_FORWARD;
			break;
		}
		case 'S':
		{
			if (m_enumState != CRT_STATE::CRT_RUN&& m_enumState != CRT_STATE::CRT_CRAWL)
			{
				m_enumState = CRT_STATE::CRT_WALK;
			}
			m_enumDirection = ENUM_DIRECTION::DR_BACKWARD;
			break;
		}
		case 'A':
		{
			if (m_enumState != CRT_STATE::CRT_RUN&& m_enumState != CRT_STATE::CRT_CRAWL)
			{
				m_enumState = CRT_STATE::CRT_WALK;
			}
			m_enumDirection = ENUM_DIRECTION::DR_LEFT;
			break;
		}
		case 'D':
		{
			if (m_enumState != CRT_STATE::CRT_RUN&& m_enumState != CRT_STATE::CRT_CRAWL)
			{
				m_enumState = CRT_STATE::CRT_WALK;
			}
			m_enumDirection = ENUM_DIRECTION::DR_RIGHT;
			break;
		}
		}
	}//case WM_KEYDOWN:
	break;

	case WM_KEYUP:
	{
		switch (wParam)
		{
		case 'C':
		{
			m_enumState = CRT_STATE::CRT_IDLE;
			break;
		}
		case  'R':
		{
			if (m_enumState != CRT_STATE::CRT_CRAWL)
				m_enumState = CRT_STATE::CRT_WALK;
			break;
		}
		case 'W':
		{
			if (m_enumState != CRT_STATE::CRT_CRAWL)
				m_enumState = CRT_STATE::CRT_IDLE;

			m_enumDirection = ENUM_DIRECTION::DR_NONE;
			break;
		}
		case 'S':
		{
			if (m_enumState != CRT_STATE::CRT_CRAWL)
				m_enumState = CRT_STATE::CRT_IDLE;

			m_enumDirection = ENUM_DIRECTION::DR_NONE;
			break;
		}
		case 'A':
		{
			if (m_enumState != CRT_STATE::CRT_CRAWL)
				m_enumState = CRT_STATE::CRT_IDLE;

			m_enumDirection = ENUM_DIRECTION::DR_NONE;
			break;
		}
		case 'D':
		{
			if (m_enumState != CRT_STATE::CRT_CRAWL)
				m_enumState = CRT_STATE::CRT_IDLE;

			m_enumDirection = ENUM_DIRECTION::DR_NONE;
			break;
		}
		case VK_SPACE:
		{
			//	m_enumInteraction == CRT_INTERACTION::ACTION_DOOR;

				m_enumState = CRT_STATE::CRT_JUMPOVER;
				SetAnimationIndex(ANIM_JUMP);
			
		}
		}
	}//case WM_KEYUP:
	break;
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

void cHero::SetInteraction(CRT_INTERACTION interaction)
{
	//m_isInteract = true;
	m_enumInteraction = interaction;
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
