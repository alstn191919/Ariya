#pragma once
class cSkinnedMesh;

class cHero
{
private:
	enum CRT_ANIMLIST
	{
		CRT_ANIM_STAY_CRAWL = 0,			//앉아서 제자리
		CRT_ANIM_BACKWALK_CRAWL,		//앉아서 뒷걸음
		CRT_ANIM_FORDWALK_CRAWL,		//앉아서 앞으로
		CRT_ANIM_LEFTWALK,		//좌로 걸음
		CRT_ANIM_BACKWALK,		//뒤로 걸음
		CRT_ANIM_FORDWALK,		//앞으로 걸음
		CRT_ANIM_IDLE,					//제자리
		CRT_ANIM_JUMPOVER_FAST,	//뛰면서 장애물 넘기
		CRT_ANIM_STANDUP,			//(앉아있다가) 일어나기
		CRT_ANIM_CATCH,				//잡히기
		CRT_ANIM_MISSIONFAILED,	//미션실패
		CRT_ANIM_OPEN_FAST,		//뛰면서 문열기
		CRT_ANIM_JUMPOVER,		//장애물 넘기
		CRT_ANIM_GRAB,				//아이템 줍기
		CRT_ANIM_JUMP,				//제자리 점프
		CRT_ANIM_RUN,					//뛰기
		CRT_ANIM_NONE
	};

private:
	cSkinnedMesh*						m_pSkinnedMesh;
	CRT_STATE							m_enumState;
	ENUM_DIRECTION				m_enumDirection;
	D3DXVECTOR3					m_Min;
	D3DXVECTOR3					m_Max;

public:
	cHero(char* szDirectory, char* szFilename);
	~cHero();

	void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);

	/*		SET		*/
	void SetAnimationIndex(int nIndex);
	void SetPosition(D3DXVECTOR3 v);
	void SetState(CRT_STATE chrtState);
	void SetDirection(ENUM_DIRECTION direction);


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