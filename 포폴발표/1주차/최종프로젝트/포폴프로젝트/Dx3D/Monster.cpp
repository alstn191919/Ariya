#include "stdafx.h"
#include "Monster.h"
#include "cSkinnedMesh.h"


Monster::Monster(char* szDirectory, char* szFilename)
	: m_pSkinnedMesh(NULL)
	, m_enumState(CRT_STATE::CRT_IDLE)
	, m_enumDirection(ENUM_DIRECTION::DR_NONE)
	, m_enumPrevState(m_enumState)
	, m_enumPrevDirection(m_enumDirection)
	, i_Phase(NonPhase)
	, b_swich_1(false)
	, b_swich_2(false)
	, m_fSpeed(0.2f)
	//, m_isInteract(false)
	, m_enumInteraction(CRT_INTERACTION::ACTION_NONE)
{
	m_pSkinnedMesh = new cSkinnedMesh(szDirectory, szFilename);

	//바운딩 박스 설정
	D3DXVECTOR3	m_Min = D3DXVECTOR3(-100, -100, -100);
	D3DXVECTOR3	m_Max = D3DXVECTOR3(100, 100, 100);
	m_pSkinnedMesh->SetMin(m_Min);
	m_pSkinnedMesh->SetMax(m_Max);

	m_Direction = D3DXVECTOR3(0, 0, 1);
	SetAnimationIndex(4);

	m_Obb = new cOBB;
	m_Obb->Setup(m_Min, m_Max);
}


Monster::~Monster()
{
	SAFE_DELETE(m_pSkinnedMesh);
}


void Monster::UpdateAndRender(D3DXMATRIXA16 * pmat)
{
	//캐릭터 상태에 따른 바운딩박스, 애니메이션 변화
	if (m_enumState == CRT_STATE::CRT_CRAWL)					//기어가기
	{


		//애니메이션 세팅: ENUM_DIRECTION에 따라 바꿉니다.
		SetAnimationCrawl();
	}
	else if (m_enumState == CRT_STATE::CRT_IDLE)				//기본
	{


		SetAnimationIdle();
	}
	else if (m_enumState == CRT_STATE::CRT_WALK)					//걷기
	{


		SetAnimationWalk();
	}
	else if (m_enumState == CRT_STATE::CRT_RUN)					//뛰기
	{


		SetAnimationRun();
	}
	else if (m_enumState == CRT_STATE::CRT_JUMPOVER)
	{

	}

	m_enumPrevState = m_enumState;
	m_enumPrevDirection = m_enumDirection;

	//메시 바운딩박스 설정

	m_Obb->Update(pmat);
	m_pSkinnedMesh->UpdateAndRender(pmat);

	if (GetAsyncKeyState(VK_F1) & 1)
	{
		m_Obb->DebugRender(D3DCOLOR_XRGB(255, 0, 0));
	}
}

void Monster::SetAnimationCrawl()
{
	//if (m_enumState != m_enumPrevState)
	//{
	//	//기본 상태
	//	SetAnimationIndex(ANIM_STAY_CRAWL);
	//}

	//if (m_enumPrevDirection == m_enumDirection)
	//{
	//	return;
	//}

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

void Monster::SetAnimationIdle()
{
	//if (m_enumState != m_enumPrevState)
	//{
	//	//기본 상태
	//	SetAnimationIndex(ANIM_IDLE);
	//}

	////상호작용의 처리
	//if (m_enumInteraction != CRT_INTERACTION::ACTION_NONE)
	//{
	//	if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
	//	{
	//		SetAnimationIndex(ANIM_OPEN_FAST);
	//		return;
	//	}
	//	else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
	//	{
	//		SetAnimationIndex(ANIM_JUMPOVER);
	//		return;
	//	}
	//	else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
	//	{
	//		SetAnimationIndex(ANIM_CATCH);
	//		return;
	//	}
	//}

	////입력에 따른 처리
	//if (m_enumPrevDirection == m_enumDirection)
	//{
	//	return;
	//}
	//if (m_enumDirection == ENUM_DIRECTION::DR_NONE)
	//{
	//	SetAnimationIndex(ANIM_IDLE);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_FORWARD)
	//{
	//	SetAnimationIndex(ANIM_FORDWALK);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_BACKWARD)
	//{
	//	SetAnimationIndex(ANIM_BACKWALK);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_LEFT || DR_RIGHT)
	//{
	//	SetAnimationIndex(ANIM_LEFTWALK);
	//}
}

void Monster::SetAnimationWalk()
{
	//if (m_enumState != m_enumPrevState)
	//{
	//	//기본 상태
	//	SetAnimationIndex(ANIM_FORDWALK);
	//}

	////상호작용의 처리
	//if (m_enumInteraction != CRT_INTERACTION::ACTION_NONE)
	//{
	//	if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
	//	{
	//		SetAnimationIndex(ANIM_OPEN_FAST);
	//		return;
	//	}
	//	else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
	//	{
	//		SetAnimationIndex(ANIM_JUMPOVER);
	//		return;
	//	}
	//	else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
	//	{
	//		SetAnimationIndex(ANIM_CATCH);
	//		return;
	//	}
	//}

	////입력에 따른 처리
	//if (m_enumPrevDirection == m_enumDirection)
	//{
	//	return;
	//}
	//if (m_enumDirection == ENUM_DIRECTION::DR_NONE)
	//{
	//	SetAnimationIndex(ANIM_FORDWALK);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_FORWARD)
	//{
	//	SetAnimationIndex(ANIM_FORDWALK);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_BACKWARD)
	//{
	//	SetAnimationIndex(ANIM_BACKWALK);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_LEFT || DR_RIGHT)
	//{
	//	SetAnimationIndex(ANIM_LEFTWALK);
	//}
}

void Monster::SetAnimationRun()
{
	//if (m_enumState != m_enumPrevState)
	//{
	//	//기본 상태
	//	SetAnimationIndex(ANIM_RUN);
	//}

	////상호작용의 처리
	//if (m_enumInteraction != CRT_INTERACTION::ACTION_NONE)
	//{
	//	if (m_enumInteraction == CRT_INTERACTION::ACTION_DOOR)
	//	{
	//		SetAnimationIndex(ANIM_OPEN_FAST);
	//		return;
	//	}
	//	else if (m_enumInteraction == CRT_INTERACTION::ACTION_DESK)
	//	{
	//		SetAnimationIndex(ANIM_JUMPOVER_FAST);
	//		return;
	//	}
	//	else if (m_enumInteraction == CRT_INTERACTION::ACTION_CATCH)
	//	{
	//		SetAnimationIndex(ANIM_CATCH);
	//		return;
	//	}
	//}

	////입력에 따른 처리
	//if (m_enumPrevDirection == m_enumDirection)
	//{
	//	return;
	//}
	//if (m_enumDirection == ENUM_DIRECTION::DR_NONE)
	//{
	//	SetAnimationIndex(ANIM_RUN);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_FORWARD)
	//{
	//	SetAnimationIndex(ANIM_FORDWALK);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_BACKWARD)
	//{
	//	SetAnimationIndex(ANIM_BACKWALK);
	//}
	//else if (m_enumDirection == ENUM_DIRECTION::DR_LEFT || DR_RIGHT)
	//{
	//	SetAnimationIndex(ANIM_LEFTWALK);
	//}
}

void Monster::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//switch (message)
	//{
	//case WM_KEYDOWN:
	//{
	//	switch (wParam)
	//	{
	//	case 'C':
	//	{
	//		m_enumState = CRT_STATE::CRT_CRAWL;
	//		break;
	//	}
	//	case  'R':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_CRAWL)
	//			m_enumState = CRT_STATE::CRT_RUN;
	//		break;
	//	}

	//	case 'W':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_RUN && m_enumState != CRT_STATE::CRT_CRAWL)
	//		{
	//			m_enumState = CRT_STATE::CRT_WALK;
	//		}
	//		//방향 설정 : 정면
	//		m_enumDirection = ENUM_DIRECTION::DR_FORWARD;
	//		break;
	//	}
	//	case 'S':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_RUN&& m_enumState != CRT_STATE::CRT_CRAWL)
	//		{
	//			m_enumState = CRT_STATE::CRT_WALK;
	//		}
	//		m_enumDirection = ENUM_DIRECTION::DR_BACKWARD;
	//		break;
	//	}
	//	case 'A':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_RUN&& m_enumState != CRT_STATE::CRT_CRAWL)
	//		{
	//			m_enumState = CRT_STATE::CRT_WALK;
	//		}
	//		m_enumDirection = ENUM_DIRECTION::DR_LEFT;
	//		break;
	//	}
	//	case 'D':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_RUN&& m_enumState != CRT_STATE::CRT_CRAWL)
	//		{
	//			m_enumState = CRT_STATE::CRT_WALK;
	//		}
	//		m_enumDirection = ENUM_DIRECTION::DR_RIGHT;
	//		break;
	//	}
	//	case VK_SPACE:
	//	{
	//		//	m_enumInteraction == CRT_INTERACTION::ACTION_DOOR;

	//		m_enumState = CRT_STATE::CRT_JUMPOVER;
	//		SetAnimationIndex(ANIM_JUMP);

	//	}
	//	}
	//}//case WM_KEYDOWN:
	//break;

	//case WM_KEYUP:
	//{
	//	switch (wParam)
	//	{
	//	case 'C':
	//	{
	//		m_enumState = CRT_STATE::CRT_IDLE;
	//		break;
	//	}
	//	case  'R':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_CRAWL)
	//			m_enumState = CRT_STATE::CRT_WALK;
	//		break;
	//	}
	//	case 'W':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_CRAWL)
	//			m_enumState = CRT_STATE::CRT_IDLE;

	//		m_enumDirection = ENUM_DIRECTION::DR_NONE;
	//		break;
	//	}
	//	case 'S':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_CRAWL)
	//			m_enumState = CRT_STATE::CRT_IDLE;

	//		m_enumDirection = ENUM_DIRECTION::DR_NONE;
	//		break;
	//	}
	//	case 'A':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_CRAWL)
	//			m_enumState = CRT_STATE::CRT_IDLE;

	//		m_enumDirection = ENUM_DIRECTION::DR_NONE;
	//		break;
	//	}
	//	case 'D':
	//	{
	//		if (m_enumState != CRT_STATE::CRT_CRAWL)
	//			m_enumState = CRT_STATE::CRT_IDLE;

	//		m_enumDirection = ENUM_DIRECTION::DR_NONE;
	//		break;
	//	}
	//	}
	//}//case WM_KEYUP:
	//break;
	//}
}

void Monster::SetAnimationIndex(int nIndex)
{
	m_pSkinnedMesh->SetAnimationIndex(nIndex);
}

void Monster::SetPosition(D3DXVECTOR3 v)
{
	m_pSkinnedMesh->SetPosition(v);
}

void Monster::SetState(CRT_STATE chrtState)
{
	m_enumState = chrtState;
}

void Monster::SetDirection(ENUM_DIRECTION direction)
{
	m_enumDirection = direction;
}

void Monster::SetInteraction(CRT_INTERACTION interaction)
{
	//m_isInteract = true;
	m_enumInteraction = interaction;
}

/*		GET		*/

cSkinnedMesh * Monster::GetMesh()
{
	return m_pSkinnedMesh;
}

D3DXVECTOR3 Monster::GetPosition()
{
	return m_pSkinnedMesh->GetPosition();
}

ST_SPHERE * Monster::GetBoundingSphere()
{
	return m_pSkinnedMesh->GetBoundingSphere();
}
