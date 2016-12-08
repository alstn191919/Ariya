#pragma once

#include "cAllocateHierarchy2.h"
#include "cOBB.h"
class cSkinnedMesh2
{
private:
	ST_BONE2*					m_pRootBone;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXMATRIXA16				m_wolrd;
	//SYNTHESIZE(ST_SPHERE, m_sSphre, Sphre);
	SYNTHESIZE(BOOL, m_bInter, Inter);					//��ȣ�浹 ���� OBJ�ΰ�?
	SYNTHESIZE(OBJ_TYPE, m_eObjType, ObjType);

	SYNTHESIZE(float,m_fAngleX,AngleX);			//ȸ���� �����ޱ�
	SYNTHESIZE(float,m_fAngleY,AngleY);			//ȸ���� �����ޱ�
	SYNTHESIZE(std::string, M_sText, Text);		//���� , ����ġ ���� ������Ʈ�� �׻� ���� ����������մϴ�.
	SYNTHESIZE(cOBB*, m_Obb, Obb);				//obb
	SYNTHESIZE(bool, b_isOpen, isOpen);			//���������� üũ

	
	
public:
	cSkinnedMesh2(void);
	~cSkinnedMesh2(void);

	ST_SPHERE m_sSphre;

	void Load(std::string sFolder, std::string sFile);
	void Update();
	void Render();
	void ObjRender();
	void ObjVIEWRender();
	void ObjEvent();
	void SetAnimationIndex(int n);
	void SetWolrd(D3DXVECTOR3 p, float size  );
	D3DXMATRIXA16 * GetWolrd(){ return &m_wolrd; }

private:
	void Render(ST_BONE2* pBone);
	void Update(ST_BONE2* pBone, D3DXMATRIX* pParent);
	void UpdateSkinnedMesh(ST_BONE2* pBone);
	void SetupBoneMatrixPtrs(ST_BONE2* pBone);
	
};

