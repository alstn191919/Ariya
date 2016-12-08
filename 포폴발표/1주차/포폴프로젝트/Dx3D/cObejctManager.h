#pragma once
#define ObjectManager cObejctManager::GetInstance()

#include "cSkinnedMesh2.h"



class cObejctManager
{
private:
	SINGLETONE(cObejctManager);
private:
	std::vector<cSkinnedMesh2*> object;			//오브젝트
	SYNTHESIZE(int, m_select_index, select_index);								//선택된 오브젝트 인덱스
	//int m_select_index;
//	D3DXVECTOR3	camera;					//카메라 위치
		
public:
	


	
	void ADDobject(std::string sFolder, std::string sFile , D3DXVECTOR3 Pogi , float size);				//일단 오브젝트 추가
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, float size, ST_SPHERE _Sphre, OBJ_TYPE _objtype , std::string _Text);	//상호작용 오브젝트 추가

	void Update();

	void Render();
	
	bool isPinked();
	void SetSelect();
	void SetNonSelect() { m_select_index = NonSlect; }			//셀렉트 초기화
	void Destroy();

	OBJ_TYPE getPinkedObjType();
	std::string getText();

	void SetCameraPogition(D3DXVECTOR3 p);
	void SetMouseAngle(float x, float y);

	float getAngleX();
	float getAngleY();
	
	
};

