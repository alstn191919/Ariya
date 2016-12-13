#pragma once
#define ObjectManager cObejctManager::GetInstance()

#include "cSkinnedMesh2.h"
#include "cSkinnedMesh.h"



class cObejctManager
{
private:
	SINGLETONE(cObejctManager);
private:

	float DoorClose;

	std::vector<cSkinnedMesh2*> object;			//오브젝트
	SYNTHESIZE(int, m_select_index, select_index);								//선택된 오브젝트 인덱스
	SYNTHESIZE(bool, b_Collision, Collision);
	//int m_select_index;
//	D3DXVECTOR3	camera;					//카메라 위치

		
public:
	


	
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, OBJ_TYPE _objtype, D3DXVECTOR3 Min, D3DXVECTOR3 Max);				//일단 오브젝트 추가
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text);	//상호작용 오브젝트 추가
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text, D3DXVECTOR3 Min, D3DXVECTOR3 Max);	//상호작용 OBB추가타입

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

	bool getOpen();
	


	bool IsCollision(cOBB * player);
	
	
};

