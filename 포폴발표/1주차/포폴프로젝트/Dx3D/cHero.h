#pragma once
class cSkinnedMesh;

//주인공 클래스
//maingame 클래스에서 키입력을 받아 변경하는 방식
//오브젝트에서 입력을 받아 사용하고 싶을 때에는 외부에서 m_enumInteraction을 변경합니다.
//메소드는 SetInteraction(CRT_INTERACTION interaction)

class cHero
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
	cSkinnedMesh*					m_pSkinnedMesh;
	CRT_STATE							m_enumState;					//캐릭터 상태
	ENUM_DIRECTION				m_enumDirection;				//키보드 방향

	CRT_STATE						m_enumPrevState;			//캐릭터 이전 상태
	ENUM_DIRECTION				m_enumPrevDirection;		//키보드 이전 방향

															//bool										m_isInteract;						//상호작용 여부
	CRT_INTERACTION				m_enumInteraction;			//상호작용

															//바운딩 박스용
	D3DXVECTOR3						m_Min;
	D3DXVECTOR3						m_Max;

public:
	cHero(char* szDirectory, char* szFilename);
	~cHero();

	void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);

	void SetAnimationCrawl();
	void SetAnimationIdle();
	void SetAnimationWalk();
	void SetAnimationRun();
	void SetAnimationJump();

	bool IsCrawl();

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
};

/*
15.뛰기: 0 25
14.제자리점프 : 2208 2238
13.아이템 줍기 : 3501 3531
12.장애물 넘어가기(스페이스) : 3532 3562
11. 뛰면서 문열기(E) : 10832 10862
10. 미션실패모션 : 6576 6614
8. 잡히는 모션 : 6752 6903
8. (앉은상태에서)일어서기 : 1065 1095
7. 뛰면서 장애물 넘어가기(스페이스) : 9255 9280
6. 제자리 : 11996 12086
5.걷기(앞) : 854 883
4.걷기(뒤) : 884 913
3.걷기(왼) : 914 944
2.(앉은 상태에서)걸어가기(앞) : 975 1004
1.(앉은 상태에서)걸어가기(뒤) : 945 974
0.(앉은 상태에서)제자리 : 1096 1186
*/