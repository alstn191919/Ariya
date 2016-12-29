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
		ANIM_STAY_CRAWL = 0,			//앉아서 제자리
		ANIM_BACKWALK_CRAWL,		//앉아서 뒷걸음
		ANIM_FORDWALK_CRAWL,		//앉아서 앞으로
		ANIM_LEFTWALK,		//좌로 걸음
		ANIM_BACKWALK,		//뒤로 걸음
		ANIM_FORDWALK,		//앞으로 걸음
		ANIM_IDLE,					//제자리
		ANIM_JUMPOVER_FAST,	//뛰면서 장애물 넘기
		ANIM_STANDUP,			//(앉아있다가) 일어나기
		ANIM_CATCH,				//잡히기
		ANIM_MISSIONFAILED,	//미션실패
		ANIM_OPEN_FAST,		//뛰면서 문열기
		ANIM_JUMPOVER,		//장애물 넘기
		ANIM_GRAB,				//아이템 줍기
		ANIM_JUMP,				//제자리 점프
		ANIM_RUN,					//뛰기
		ANIM_NONE
	};

private:
	cSkinnedMesh*				m_pSkinnedMesh;
	
	CRT_STATE					m_enumState;					//캐릭터 상태
	ENUM_DIRECTION				m_enumDirection;				//키보드 방향

	CRT_STATE					m_enumPrevState;			//캐릭터 이전 상태
	ENUM_DIRECTION				m_enumPrevDirection;		//키보드 이전 방향

	//bool										m_isInteract;						//상호작용 여부
	CRT_INTERACTION				m_enumInteraction;			//상호작용


	SYNTHESIZE(cOBB*, m_Obb, Obb);				//obb
	SYNTHESIZE(D3DXVECTOR3, m_Direction, Direction);
	SYNTHESIZE(Tag_Phase, i_Phase, Phase);				//몬스터 이벤트 페이즈
	SYNTHESIZE(BOOL, b_swich_1, swich_1);				//이벤트 시작(플레이어가 막다른길에 도착했을시 플레이가 돌아갈거)
	SYNTHESIZE(BOOL, b_swich_2, swich_2);				//이벤트 시작2(스위치 1의 ON 상태를 판정하고 돌아가는길에 특정 포인트를 지나가면 ON이 됨
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

