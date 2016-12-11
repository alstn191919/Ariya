#pragma once
class cSkinnedMesh;

class cHero
{
private:
	enum CRT_ANIMLIST
	{
		CRT_ANIM_STAY_CRAWL = 0,			//�ɾƼ� ���ڸ�
		CRT_ANIM_BACKWALK_CRAWL,		//�ɾƼ� �ް���
		CRT_ANIM_FORDWALK_CRAWL,		//�ɾƼ� ������
		CRT_ANIM_LEFTWALK,		//�·� ����
		CRT_ANIM_BACKWALK,		//�ڷ� ����
		CRT_ANIM_FORDWALK,		//������ ����
		CRT_ANIM_IDLE,					//���ڸ�
		CRT_ANIM_JUMPOVER_FAST,	//�ٸ鼭 ��ֹ� �ѱ�
		CRT_ANIM_STANDUP,			//(�ɾ��ִٰ�) �Ͼ��
		CRT_ANIM_CATCH,				//������
		CRT_ANIM_MISSIONFAILED,	//�̼ǽ���
		CRT_ANIM_OPEN_FAST,		//�ٸ鼭 ������
		CRT_ANIM_JUMPOVER,		//��ֹ� �ѱ�
		CRT_ANIM_GRAB,				//������ �ݱ�
		CRT_ANIM_JUMP,				//���ڸ� ����
		CRT_ANIM_RUN,					//�ٱ�
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