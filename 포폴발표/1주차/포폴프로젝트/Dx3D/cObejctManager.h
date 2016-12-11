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
	//int m_select_index;
//	D3DXVECTOR3	camera;					//ī�޶� ��ġ

		
public:
	


	
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, D3DXVECTOR3 Min, D3DXVECTOR3 Max);				//�ϴ� ������Ʈ �߰�
	void ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text);	//��ȣ�ۿ� ������Ʈ �߰�


	void Update();

	void Render();
	
	bool isPinked();
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
	


	bool IsCollision(cOBB * player);
	
	
};

