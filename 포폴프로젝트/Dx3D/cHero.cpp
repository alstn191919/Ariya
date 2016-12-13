#include "stdafx.h"
#include "cHero.h"
#include "cSkinnedMesh.h"

cHero::cHero(char* szDirectory, char* szFilename)
	: m_pSkinnedMesh(NULL)
	, m_enumState(CRT_STATE::CRT_IDLE)
	, m_enumDirection(ENUM_DIRECTION::DR_FORWARD)
{
	m_pSkinnedMesh = new cSkinnedMesh(szDirectory, szFilename);

	//�ٿ�� �ڽ� ����
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
	//ĳ���� ���¿� ���� �ٿ���ڽ�, �ִϸ��̼� ��ȭ
	if (m_enumState == CRT_STATE::CRT_CRAWL)					//����
	{
		//���� �ӽð�
		m_Min = D3DXVECTOR3(-1, 0, -1);
		m_Max = D3DXVECTOR3(1, 1, 1);

		//�ִϸ��̼� ����: ENUM_DIRECTION�� ���� �ٲߴϴ�.
		SetAnimationCrawl();
	}
	else if (m_enumState == CRT_STATE::CRT_IDLE)				//�⺻
	{
		m_Min = D3DXVECTOR3(-1, 0, -1);
		m_Max = D3DXVECTOR3(1, 3, 1);

		SetAnimationIdle();
	}
	else if (m_enumState == CRT_STATE::CRT_WALK)					//�ȱ�
	{
		m_Min = D3DXVECTOR3(-1, 0, -1);
		m_Max = D3DXVECTOR3(1, 3, 1);

		SetAnimationWalk();
	}
	else if (m_enumState == CRT_STATE::CRT_RUN)					//�ٱ�
	{
		m_Min = D3DXVECTOR3(-1, 0, -1);
		m_Max = D3DXVECTOR3(1, 3, 1);

		SetAnimationRun();
	}

	//�޽� �ٿ���ڽ� ����
	m_pSkinnedMesh->SetMin(m_Min);
	m_pSkinnedMesh->SetMax(m_Max);

	m_pSkinnedMesh->UpdateAndRender(pmat);
}

void cHero::SetAnimationCrawl()
{
	//�⺻ ����
	SetAnimationIndex(ANIM_STAY_CRAWL);

	//�Է¿� ���� ó��
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
	//�⺻ ����
	SetAnimationIndex(ANIM_IDLE);

	if (m_isInteract)	//��ȣ�ۿ��� ó��
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
	else	//�Է¿� ���� ó��
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

	if (m_isInteract)	//��ȣ�ۿ��� ó��
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
	else	//�Է¿� ���� ó��
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

	if (m_isInteract)	//��ȣ�ۿ��� ó��
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
	else	//�Է¿� ���� ó��
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
