#pragma once

#include "cAllocateHierarchy2.h"

class cSkinnedMesh2
{
private:
	ST_BONE2*					m_pRootBone;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXMATRIXA16				m_wolrd;
	//SYNTHESIZE(ST_SPHERE, m_sSphre, Sphre);
	SYNTHESIZE(BOOL, m_bInter, Inter);
	SYNTHESIZE(OBJ_TYPE, m_eObjType, ObjType);

	SYNTHESIZE(float,m_fAngleX,AngleX);
	SYNTHESIZE(float,m_fAngleY,AngleY);
	SYNTHESIZE(std::string, M_sText, Text);		//도어 , 스위치 형식 오브젝트는 항상 값을 셋팅해줘야합니다.

	
	
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
	void SetWolrd(D3DXVECTOR3 p, float size);

	D3DXVECTOR3 GetMin()
	{
		return D3DXVECTOR3(2, 0, 2);
	}
	D3DXVECTOR3 GetMax()
	{
		return D3DXVECTOR3(2, 5, 2);
	}
private:
	void Render(ST_BONE2* pBone);
	void Update(ST_BONE2* pBone, D3DXMATRIX* pParent);
	void UpdateSkinnedMesh(ST_BONE2* pBone);
	void SetupBoneMatrixPtrs(ST_BONE2* pBone);
	
};

