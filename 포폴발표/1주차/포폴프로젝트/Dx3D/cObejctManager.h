#pragma once
#define ObjectManager cObejctManager::GetInstance()

#include "cSkinnedMesh2.h"
#include "cSkinnedMesh.h"
#include "cEvent.h"



class cObejctManager
{
private:
	SINGLETONE(cObejctManager);
private:

	std::vector<cSkinnedMesh2*> object;			//오브젝트
	SYNTHESIZE(int, m_select_index, select_index);								//선택된 오브젝트 인덱스
	SYNTHESIZE(bool, b_Collision, Collision);

	
		
public:
		
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, D3DXVECTOR3 Min, D3DXVECTOR3 Max);				//일단 오브젝트 추가
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text);	//상호작용 오브젝트 추가
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text, D3DXVECTOR3 Min, D3DXVECTOR3 Max , float Angle);	//상호 작용 + obb + 로테이션 타입

	void Update();

	void Render();
	
	bool isPinked();
	int getIndex();												//픽킹인덱스값을 가져옵니다.	void SetSelect();
	void SetSelect();
	void SetNonSelect() { m_select_index = NonSlect; }			//셀렉트 초기화	
	void Destroy();
	void evt();

	OBJ_TYPE getPinkedObjType();
	std::string getText();

	void SetCameraPogition(D3DXVECTOR3 p);
	void SetMouseAngle(float x, float y);

	float getAngleX();
	float getAngleY();

	bool getOpen();
	bool getIndexOpen(int _index);
	void setIndexOpen(bool _isOpen);
	bool IsCollision(cOBB * player);

	cSkinnedMesh2* getObject(int index){ return object[index]; }


	void Event1();
	void EventDefinitions();

	std::vector<cEvent *>v_Event;
	std::map<std::string, cEvent *>m_Event;
};

