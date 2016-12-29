#pragma once
#include "cOBB.h"


	enum Tag_Phase
	{
		stand_by,
		Phase1,
		Phase2,
		Phase3,
		Phase4,
		EndPhase,
		NonPhase
	};

class Monster
{
private:
	enum CRT_ANIMLIST
	{
		ANIM_STAY_CRAWL = 0,			//�ɾƼ� ���ڸ�
		ANIM_BACKWALK_CRAWL,		//�ɾƼ� �ް���
		ANIM_FORDWALK_CRAWL,		//�ɾƼ� ������
		ANIM_LEFTWALK,		//�·� ����
		ANIM_BACKWALK,		//�ڷ� ����
		ANIM_FORDWALK,		//������ ����
		ANIM_IDLE,					//���ڸ�
		ANIM_JUMPOVER_FAST,	//�ٸ鼭 ��ֹ� �ѱ�
		ANIM_STANDUP,			//(�ɾ��ִٰ�) �Ͼ��
		ANIM_CATCH,				//������
		ANIM_MISSIONFAILED,	//�̼ǽ���
		ANIM_OPEN_FAST,		//�ٸ鼭 ������
		ANIM_JUMPOVER,		//��ֹ� �ѱ�
		ANIM_GRAB,				//������ �ݱ�
		ANIM_JUMP,				//���ڸ� ����
		ANIM_RUN,					//�ٱ�
		ANIM_NONE
	};

private:
	cSkinnedMesh*				m_pSkinnedMesh;
	
	CRT_STATE					m_enumState;					//ĳ���� ����
	ENUM_DIRECTION				m_enumDirection;				//Ű���� ����

	CRT_STATE					m_enumPrevState;			//ĳ���� ���� ����
	ENUM_DIRECTION				m_enumPrevDirection;		//Ű���� ���� ����

	//bool										m_isInteract;						//��ȣ�ۿ� ����
	CRT_INTERACTION				m_enumInteraction;			//��ȣ�ۿ�


	SYNTHESIZE(cOBB*, m_Obb, Obb);				//obb
	SYNTHESIZE(D3DXVECTOR3, m_Direction, Direction);
	SYNTHESIZE(Tag_Phase, i_Phase, Phase);				//���� �̺�Ʈ ������
	SYNTHESIZE(BOOL, b_swich_1, swich_1);				//�̺�Ʈ ����(�÷��̾ ���ٸ��濡 ���������� �÷��̰� ���ư���)
	SYNTHESIZE(BOOL, b_swich_2, swich_2);				//�̺�Ʈ ����2(����ġ 1�� ON ���¸� �����ϰ� ���ư��±濡 Ư�� ����Ʈ�� �������� ON�� ��
	SYNTHESIZE(float, m_fSpeed, Speed);
	//D3DXVECTOR3						m_Direction;

public:
	void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);

	void SetAnimationCrawl();
	void SetAnimationIdle();
	void SetAnimationWalk();
	void SetAnimationRun();
	void SetAnimationJump();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/*		SET		*/
	void SetAnimationIndex(int nIndex);
	void SetPosition(D3DXVECTOR3 v);
	void SetState(CRT_STATE chrtState);
	void SetDirection(ENUM_DIRECTION direction);
	void SetInteraction(CRT_INTERACTION interaction);


	/*		GET		*/
	cSkinnedMesh* GetMesh();
	D3DXVECTOR3 GetPosition();
	ST_SPHERE* GetBoundingSphere();


public:
	Monster(char* szDirectory, char* szFilename);
	~Monster();
};

