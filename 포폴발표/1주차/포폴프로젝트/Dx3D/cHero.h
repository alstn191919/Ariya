#pragma once
class cSkinnedMesh;

//���ΰ� Ŭ����
//maingame Ŭ�������� Ű�Է��� �޾� �����ϴ� ���
//������Ʈ���� �Է��� �޾� ����ϰ� ���� ������ �ܺο��� m_enumInteraction�� �����մϴ�.
//�޼ҵ�� SetInteraction(CRT_INTERACTION interaction)

class cHero
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
	cSkinnedMesh*					m_pSkinnedMesh;
	CRT_STATE							m_enumState;					//ĳ���� ����
	ENUM_DIRECTION				m_enumDirection;				//Ű���� ����

	CRT_STATE						m_enumPrevState;			//ĳ���� ���� ����
	ENUM_DIRECTION				m_enumPrevDirection;		//Ű���� ���� ����

															//bool										m_isInteract;						//��ȣ�ۿ� ����
	CRT_INTERACTION				m_enumInteraction;			//��ȣ�ۿ�

															//�ٿ�� �ڽ���
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
15.�ٱ�: 0 25
14.���ڸ����� : 2208 2238
13.������ �ݱ� : 3501 3531
12.��ֹ� �Ѿ��(�����̽�) : 3532 3562
11. �ٸ鼭 ������(E) : 10832 10862
10. �̼ǽ��и�� : 6576 6614
8. ������ ��� : 6752 6903
8. (�������¿���)�Ͼ�� : 1065 1095
7. �ٸ鼭 ��ֹ� �Ѿ��(�����̽�) : 9255 9280
6. ���ڸ� : 11996 12086
5.�ȱ�(��) : 854 883
4.�ȱ�(��) : 884 913
3.�ȱ�(��) : 914 944
2.(���� ���¿���)�ɾ��(��) : 975 1004
1.(���� ���¿���)�ɾ��(��) : 945 974
0.(���� ���¿���)���ڸ� : 1096 1186
*/