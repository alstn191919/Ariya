#include "stdafx.h"
#include "cObejctManager.h"
#include "cRay.h"
#include "cCamera.h"
#include "cOBB.h"

float closeSpeed = 0.0167f;
float eleLeft = 60.35f;
float eleRight = 62.95f;

cObejctManager::cObejctManager()
	:m_select_index(NonSlect)
	, b_Collision(false)
	
{
	Event1();
	EventDefinitions();

}


cObejctManager::~cObejctManager()
{

}



void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, D3DXVECTOR3 Min, D3DXVECTOR3 Max, float Angle)
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	newobject->SetWolrd(Pogi, size, Angle);

	newobject->SetInter(false);

	cOBB * obb;

	obb = new cOBB;

	obb->Setup(Min, Max);

	newobject->SetObb(obb);

	object.push_back(newobject);

	//SAFE_DELETE(newobject);
}
										  //������            ���ϸ�          ��ġ          ������     ��(�浹��)   ������Ʈ Ÿ��  ����ؽ�Ʈ(door , switch�� �Ҵ��������) , item
void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text = NULL)
{									
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	newobject->SetWolrd(Pogi, size);

	newobject->m_sSphre = _Sphre;

	newobject->SetInter(true);

	newobject->SetObjType(_objtype);

	if(_Text.size())newobject->SetText(_Text);

	object.push_back(newobject);

	//SAFE_DELETE(newobject);
}


void cObejctManager::ADDobject(std::string sFolder,
	std::string sFile,
	D3DXVECTOR3 Pogi, 
	D3DXVECTOR3 size,
	ST_SPHERE _Sphre,
	OBJ_TYPE _objtype, 
	std::string _Text, 
	D3DXVECTOR3 Min, 
	D3DXVECTOR3 Max ,
	float Angle, D3DXVECTOR3* _LightPositon)
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	if (Angle)
	newobject->SetWolrd(Pogi, size, Angle);
	else newobject->SetWolrd(Pogi, size);
	newobject->m_sSphre = _Sphre;

	newobject->SetInter(true);
	if (_LightPositon)
	{
		newobject->SetLightPositon(*_LightPositon);
	}
	newobject->SetObjType(_objtype);

	if (_Text.size())newobject->SetText(_Text);

	cOBB * obb;

	obb = new cOBB;

	obb->Setup(Min, Max);

	newobject->SetObb(obb);

	object.push_back(newobject);
}

void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, OBJ_TYPE _objtype, float Angle)	//obb�浹���ϴ°�
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	if (Angle)
		newobject->SetWolrd(Pogi, size, Angle);
	else newobject->SetWolrd(Pogi, size);

	newobject->SetInter(true);

	newobject->SetObjType(_objtype);

	object.push_back(newobject);
}
void cObejctManager::Update()
{
	//Ray�� Ŭ���̾�Ʈ �߰����� ���
	RECT rc;
	POINT pt;
	//ClientToScreen(g_hWnd, &pt);
	GetClientRect(g_hWnd, &rc);
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	int index;


	std::map<std::string, cEvent *>::iterator it;
	for (it=m_Event.begin(); it != m_Event.end(); it++)
	{
		m_Event[it->first]->update();
		
		//it->second->update();
	}
	cRay r = cRay::RayAtWorldSpace(pt.x, pt.y);
	for (size_t i = 0; i < object.size(); ++i)
	{
		if (object[i]->GetInter())
		{
			object[i]->m_sSphre.isPicked = r.IsPicked(object[i]->m_sSphre);
			if ((index = getIndex() )!= NonSlect)
			{
				if (GetAsyncKeyState('E') & 1)		//����׿����� ���� �����ϰ� �߽��ϴ� ���߿� �̺�Ʈ �ſ��� �ش� �ε��� �� ó�����ִ°ɷ� ����
				{
					if (object[index]->GetObjType() == OBJ_TYPE::door)
					{
						if (object[index]->GetisOpen())	object[index]->SetisOpen(false);
						else object[index]->SetisOpen(true);
					}

				}
			}


		}
		
	}


	
	if (object.size() > 1)
	{
		////������ �ݰ� 
		if (object[0]->GetisOpen() == true)
		{
			object[2]->SetWolrd(D3DXVECTOR3(eleLeft, -17, -105.5f), D3DXVECTOR3(26.0f, 27.0f, 26.0f));
			eleLeft -= closeSpeed;
			object[3]->SetWolrd(D3DXVECTOR3(eleRight, -17, -105.5f), D3DXVECTOR3(26.0f, 27.0f, 26.0f));
			eleRight += closeSpeed;

			if (eleRight > 64.95f && eleLeft < 58.35f)
			{
				eleRight = 64.95f;
				eleLeft = 58.35f;
			}
		}
		else if (object[0]->GetisOpen() == false)
		{
			object[2]->SetWolrd(D3DXVECTOR3(eleLeft, -17, -105.5f), D3DXVECTOR3(26.0f, 27.0f, 26.0f));
			eleLeft += closeSpeed;
			object[3]->SetWolrd(D3DXVECTOR3(eleRight, -17, -105.5f), D3DXVECTOR3(26.0f, 27.0f, 26.0f));
			eleRight -= closeSpeed;

			if (eleRight <= 62.95f && eleLeft >= 60.35f)
			{
				eleRight = 62.95f;
				eleLeft = 60.35f;
			}
		}

	}


	if (m_select_index != NonSlect && object[m_select_index]->GetObjType()==OBJ_TYPE::item)
	{
		object[m_select_index]->m_sSphre.isPicked = true;
	}

}



void cObejctManager::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->ObjRender();
	

		if (GetAsyncKeyState(VK_F1)&0x8001)
		{
			if (object[i]->GetObb())
			{
			//	object[i]->ObjRender();
				
				
				object[i]->GetObb()->DebugRender(D3DCOLOR_XRGB(255, 0, 0));
			}
		}
	}



	if (m_select_index != NonSlect && object[m_select_index]->GetObjType()==item)
	{
	//	object[m_select_index]->ObjVIEWRender();
	}

	

}


float cObejctManager::getAngleX()
{
	return	object[m_select_index]->GetAngleX();
}
float cObejctManager::getAngleY()
{
	return	object[m_select_index]->GetAngleX();
}

bool cObejctManager::isPinked()		//ī�޶� ó�����Դϴ�.
{

	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
			return true;
		}

	}

	return false;
}

int cObejctManager::getIndex()
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
			return i;
		}
	}
	return NonSlect;
}


void cObejctManager::SetSelect()
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
			m_select_index = i;
		}
	}

	return;
}


std::string cObejctManager::getText()
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
		return 	object[i]->GetText();
		}
	}
}


void  cObejctManager::Destroy()
{
	for each(auto it in object)
	{
		SAFE_DELETE(it);
	}	
}


void cObejctManager::SetMouseAngle(float x, float y)
{
	if (m_select_index != NonSlect && object[m_select_index]->GetObjType()==item)
	{
		object[m_select_index]->SetAngleY(y);
		object[m_select_index]->SetAngleX(x);
	}
	else
	{
		for (int i = 0; i < object.size(); i++)
		{
			if (object[i]->m_sSphre.isPicked)
			{
				if (object[i]->GetObjType() == door)
				{
					object[i]->SetAngleX(x);
					object[i]->SetAngleX(x);
				}
			}
		}
	}	
}


OBJ_TYPE cObejctManager::getPinkedObjType()
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
			return object[i]->GetObjType();
		}
	}
}



bool cObejctManager::IsCollision(cOBB * player)
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->GetObb())
		{
			if (cOBB::IsCollision(player, object[i]->GetObb()))
				return true;
		}
	}
	return false;
}


bool cObejctManager::getOpen()
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
			return object[i]->GetisOpen();
		}
	}
	return false;
}


bool cObejctManager::getIndexOpen(int _index)
{
	return object[_index]->GetisOpen();
}



void cObejctManager::evt()//�̺�Ʈ ��뿹��
{
	

	class bac:public cEvent
	{
		virtual void EVENT(){assert(false && "���");}

	};

	cEvent * test;

	test = new bac;


	cOBB * obb;

	obb = new cOBB;

	obb->Setup(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1));

	test->obb = obb;


	test->_switch = false;
	

	v_Event.push_back(test);

	class atoz :public cEvent
	{
		virtual void EVENT(){ assert(false && "2�������̳�"); }

	};

	

	test = new atoz;


	cOBB * obb2;

	obb2 = new cOBB;

	obb->Setup(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1));

	test->obb = obb2;


	test->_switch = true;


	


	v_Event.push_back(test);


	class asd :public cEvent
	{
		virtual void EVENT(){ assert(false && "asdŬ��"); }

	};



	test = new asd;


	test->obb = obb2;


	test->_switch = true;
	std::string a = "�̺�Ʈ";
	
	m_Event.insert(std::pair<std::string, cEvent *> (a, test));

	class ������ :public cEvent
	{
		virtual void EVENT(){ assert(false && "������Ŭ��"); }

	};


	test = new ������;

	test->obb = obb2;

	test->_switch = true;

	m_Event["������"] = test;




}


void cObejctManager::Event1()
{

	//printf("qqqqqqqq");



	class �̺�Ʈ1 :public cEvent
	{
		void update(){
			if (ObjectManager->Getselect_index() == 6)
			{
				ObjectManager->getObject(5)->SetisOpen(true);
			}
		}
	};

	cEvent * _event;
	_event = new �̺�Ʈ1;


	m_Event["�̺�Ʈ1"] = _event;
}

void cObejctManager::EventDefinitions()
{
	class ȭ��� :public cEvent
	{
		int step;//�̺�Ʈ ����
		int time;		//�ð�
		int Stime;
		void update()
		{
			if (ObjectManager->Getselect_index() == 24)
			{
				_switch = true;
				step = 0;
				time = 0;
				Stime = 0;
			}

			if (_switch)EVENT();

		}



		void EVENT()
		{
			time++;
			if (time % 4 == 0) {

				if (step == 1)step = 2;
				else if(step == 2)step = 1;
			}
			if (time > 600) step = 3;
			switch (step)
				{
				case 0:
					ObjectManager->getObject(5)->SetisOpen(false);
					step = 1;
					break;
				case 1:
					ObjectManager->getObject(5)->SetAngleX(-1.5);
					break;
				case 2:
					ObjectManager->getObject(5)->SetAngleX(-D3DX_PI / 2.0 - EPSILON);
					break;
				case 3:
					ObjectManager->getObject(5)->SetisOpen(true);
					ObjectManager->getObject(7)->SetisOpen(true);
					ObjectManager->getObject(10)->SetisOpen(true);


				}
				
			

		}
	};



	class ��ܿ� :public cEvent
	{
		int step;//�̺�Ʈ ����
		void update()
		{
			if (ObjectManager->Getselect_index() == 23)
			{
				_switch = true;
				step = 0;
			
			}

			if (_switch)EVENT();

		}



		void EVENT()
		{

			switch (step)
			{
			case 0:
			//	ObjectManager->ADDobject()
				ObjectManager->getObject(4)->SetWolrd(D3DXVECTOR3(32.0, 2, -40), D3DXVECTOR3(0.4, 0.4, 0.4),-D3DX_PI/6);
				step = 1;
				break;
			case 1:
				
				break;
			case 2:
				ObjectManager->getObject(5)->SetAngleX(-D3DX_PI / 2.0 - EPSILON);
				break;
			case 3:
				ObjectManager->getObject(5)->SetisOpen(true);
				ObjectManager->getObject(7)->SetisOpen(true);
				ObjectManager->getObject(10)->SetisOpen(true);


			}



		}
	};



	cEvent * _event;
	_event = new ȭ���;

	m_Event["ȭ���"] = _event;

	_event = new ��ܿ�;
	m_Event["��ܿ�"] = _event;
}
void cObejctManager::setIndexOpen(bool _isOpen)
{
	object[0]->SetisOpen(_isOpen);
}