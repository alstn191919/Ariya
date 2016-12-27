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

	std::vector<cSkinnedMesh2*> object;			//������Ʈ
	SYNTHESIZE(int, m_select_index, select_index);								//���õ� ������Ʈ �ε���
	SYNTHESIZE(bool, b_Collision, Collision);
	SYNTHESIZE(D3DXVECTOR3, m_targetPosition, targetPosition);

private: //�ø�
	D3DXVECTOR3		m_aProjVertex[8];
	D3DXPLANE		m_aPlane[6];
public:

	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, D3DXVECTOR3 Min, D3DXVECTOR3 Max, float Angle, D3DXVECTOR3 _LightPositon);				//�ϴ� ������Ʈ �߰�
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text, D3DXVECTOR3 _LightPositon);	//��ȣ�ۿ� ������Ʈ �߰�
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text, D3DXVECTOR3 Min, D3DXVECTOR3 Max, float Angle, D3DXVECTOR3 _LightPositon);	//��ȣ �ۿ� + obb + �����̼� Ÿ��
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, OBJ_TYPE _objtype, float Angle, D3DXVECTOR3 _LightPositon);	//obb�浹���ϴ°�
	void Update();

	void Render();

	bool isPinked();
	int getIndex();												//��ŷ�ε������� �����ɴϴ�.	void SetSelect();
	void SetSelect();
	void SetNonSelect() { m_select_index = NonSlect; }			//����Ʈ �ʱ�ȭ	
	void Destroy();
	void DestroyObject(){
		//	for (int i = 0; i < object.size(); i++)object[i]->~cSkinnedMesh2();
		object.clear();
		m_Event.clear();
	}
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

	bool Culling(cSkinnedMesh2* _object);
	void CullingUpdate();
};