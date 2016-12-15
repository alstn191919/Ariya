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

	std::vector<cSkinnedMesh2*> object;			//������Ʈ
	SYNTHESIZE(int, m_select_index, select_index);								//���õ� ������Ʈ �ε���
	SYNTHESIZE(bool, b_Collision, Collision);
	//int m_select_index;
//	D3DXVECTOR3	camera;					//ī�޶� ��ġ

		
public:
	


	
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, D3DXVECTOR3 Min, D3DXVECTOR3 Max);				//�ϴ� ������Ʈ �߰�
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text);	//��ȣ�ۿ� ������Ʈ �߰�
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text, D3DXVECTOR3 Min, D3DXVECTOR3 Max , float Angle);	//��ȣ �ۿ� + obb + �����̼� Ÿ��

	void Update();

	void Render();
	
	bool isPinked();
	int getIndex();												//��ŷ�ε������� �����ɴϴ�.	void SetSelect();
	void SetSelect();
	void SetNonSelect() { m_select_index = NonSlect; }			//����Ʈ �ʱ�ȭ	
	void Destroy();

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
	
	
};

