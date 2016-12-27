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

	//절두체
	int n = 0;
	m_aProjVertex[n++] = D3DXVECTOR3(-1, 1, 0);
	m_aProjVertex[n++] = D3DXVECTOR3(1, 1, 0);
	m_aProjVertex[n++] = D3DXVECTOR3(1, -1, 0);
	m_aProjVertex[n++] = D3DXVECTOR3(-1, -1, 0);
	m_aProjVertex[n++] = D3DXVECTOR3(-1, 1, 1);
	m_aProjVertex[n++] = D3DXVECTOR3(1, 1, 1);
	m_aProjVertex[n++] = D3DXVECTOR3(1, -1, 1);
	m_aProjVertex[n++] = D3DXVECTOR3(-1, -1, 1);
	//

}


cObejctManager::~cObejctManager()
{

}



void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, D3DXVECTOR3 Min, D3DXVECTOR3 Max, float Angle, D3DXVECTOR3 _LightPositon)
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	newobject->SetLightPositon(_LightPositon);

	newobject->SetWolrd(Pogi, size, Angle);

	newobject->SetInter(false);

	cOBB * obb;

	obb = new cOBB;

	obb->Setup(Min, Max);

	newobject->SetObb(obb);

	object.push_back(newobject);

	//SAFE_DELETE(newobject);
}
										  //폴더명            파일명          위치          사이즈     구(충돌용)   오브젝트 타입  출력텍스트(door , switch는 할당해줘야함) , item
void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text , D3DXVECTOR3 _LightPositon)
{									
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	newobject->SetWolrd(Pogi, size);

	newobject->m_sSphre = _Sphre;

	newobject->SetInter(true);

	newobject->SetLightPositon(_LightPositon);


	newobject->SetObjType(_objtype);

	if(_Text.size())newobject->SetText(_Text);

	object.push_back(newobject);

	//SAFE_DELETE(newobject);
}


void cObejctManager::ADDobject(std::string sFolder,std::string sFile,D3DXVECTOR3 Pogi, D3DXVECTOR3 size,ST_SPHERE _Sphre,OBJ_TYPE _objtype, std::string _Text, D3DXVECTOR3 Min, D3DXVECTOR3 Max ,float Angle, D3DXVECTOR3 _LightPositon)
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	if (Angle)
	newobject->SetWolrd(Pogi, size, Angle);
	else newobject->SetWolrd(Pogi, size);
	newobject->m_sSphre = _Sphre;

	newobject->SetInter(true);

	newobject->SetLightPositon(_LightPositon);

	newobject->SetObjType(_objtype);

	if (_Text.size())newobject->SetText(_Text);

	cOBB * obb;

	obb = new cOBB;

	obb->Setup(Min, Max);

	newobject->SetObb(obb);

	object.push_back(newobject);
}

void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, OBJ_TYPE _objtype, float Angle, D3DXVECTOR3 _LightPositon)	//obb충돌안하는거
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	if (Angle)
		newobject->SetWolrd(Pogi, size, Angle);
	else newobject->SetWolrd(Pogi, size);

	newobject->SetInter(true);

	newobject->SetLightPositon(_LightPositon);

	newobject->SetObjType(_objtype);

	object.push_back(newobject);
}
void cObejctManager::Update()
{
	//Ray를 클라이언트 중간에서 쏘기
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
				if (GetAsyncKeyState('E') & 1)		//디버그용으로 열닫 조절하게 했습니다 나중에 이벤트 신에서 해당 인덱스 만 처리해주는걸로 수정
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
		////문열고 닫고 
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
	CullingUpdate();
}



void cObejctManager::Render()
{
	if (object.size() > 1)
	{
		for (int i = 0; i < 4; i++)
		{
			object[i]->ObjRender();
		}
		for (int i = 4; i < object.size(); i++)
		{
			if (Culling(object[i]))
			{
				object[i]->ObjRender();
			}
			if (GetAsyncKeyState(VK_F1) & 0x8001)
			{
				if (object[i]->GetObb())
				{

					object[i]->GetObb()->DebugRender(D3DCOLOR_XRGB(255, 0, 0));
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < object.size(); i++)
		{
			if (Culling(object[i]))
			{
				object[i]->ObjRender();
			}
			if (GetAsyncKeyState(VK_F1) & 0x8001)
			{
				if (object[i]->GetObb())
				{

					object[i]->GetObb()->DebugRender(D3DCOLOR_XRGB(255, 0, 0));
				}
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

bool cObejctManager::isPinked()		//카메라 처리용입니다.
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
	object.clear();
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



void cObejctManager::evt()//이벤트 사용예제
{
	

	class bac:public cEvent
	{
		virtual void EVENT(){assert(false && "얍얍");}

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
		virtual void EVENT(){ assert(false && "2번컨테이너"); }

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
		virtual void EVENT(){ assert(false && "asd클라스"); }

	};



	test = new asd;


	test->obb = obb2;


	test->_switch = true;
	std::string a = "이벤트";
	
	m_Event.insert(std::pair<std::string, cEvent *> (a, test));

	class 유지현 :public cEvent
	{
		virtual void EVENT(){ assert(false && "유지현클라스"); }

	};


	test = new 유지현;

	test->obb = obb2;

	test->_switch = true;

	m_Event["유지현"] = test;




}


void cObejctManager::Event1()
{

	//printf("qqqqqqqq");



	class 이벤트1 :public cEvent
	{
		void update(){
			if (ObjectManager->Getselect_index() == 6)
			{
				ObjectManager->getObject(5)->SetisOpen(true);
			}
		}
	};

	cEvent * _event;
	_event = new 이벤트1;


	m_Event["이벤트1"] = _event;
}

void cObejctManager::EventDefinitions()
{
	class 화장실 :public cEvent
	{
		int step;//이벤트 스텝
		int time;		//시간
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



	class 계단옆 :public cEvent
	{
		int step;//이벤트 스텝
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


	class 펄럭펄럭휠체어 :public cEvent
	{
		float speed;
		float Position;
		int randomX;
		int randomY;
		int _time;
		POINT temp;

		void update()
		{
			_time++;
			if (ObjectManager->GettargetPosition().x >= -38.f && ObjectManager->GettargetPosition().y <= -13.f)
			{
				srand((unsigned int)time(NULL));

				_switch = true;
				speed = -0.35f;
				Position = -62.f;
				_time = 0;
				RECT rc;
				GetClientRect(g_hWnd, &rc);
				randomX = (rc.right - rc.left) / 2;
				randomY = (rc.bottom - rc.top) / 2;

			}
			if (_switch)
			{
				Position += speed;
				EVENT();
			}
		}
		void EVENT()
		{
			ObjectManager->getObject(16)->SetWolrd(D3DXVECTOR3(-52.f, -14.91, Position), D3DXVECTOR3(0.4f, 0.4f, 0.4f));
			if (Position <= -92.f)
			{
				//벽에 부딪혔음 화면 흔들리고 쿵!하는 소리 나야함

				ObjectManager->getObject(16)->SetAngleX(D3DX_PI / 2);
				ObjectManager->getObject(16)->SetAngleY(D3DX_PI / 2);

				Position = -92.f;
				ObjectManager->getObject(16)->SetWolrd(D3DXVECTOR3(-52.f, -14.91, Position), D3DXVECTOR3(0.4f, 0.4f, 0.4f));

				_switch = false;
			}
		}
	};


	cEvent * _event;
	_event = new 화장실;

	m_Event["화장실"] = _event;

	_event = new 계단옆;
	m_Event["계단옆"] = _event;

	_event = new 펄럭펄럭휠체어;
	m_Event["펄럭펄럭휠체어"] = _event;

}
void cObejctManager::setIndexOpen(bool _isOpen)
{
	object[0]->SetisOpen(_isOpen);
}

bool cObejctManager:: Culling(cSkinnedMesh2* _object)
{
	for (int i = 0; i < 6; ++i)
	{
		
		if (D3DXPlaneDotCoord(&m_aPlane[i], &D3DXVECTOR3(_object->GetWolrd()->_41, _object->GetWolrd()->_42, _object->GetWolrd()->_43)) > 3.0f)
			return false;
	}
	return true;
}

void cObejctManager::CullingUpdate()
{
	D3DXMATRIXA16 matView, matInvView, matProj, matInvProj, mat;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvProj, 0, &matProj);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	mat = matInvProj * matInvView;

	D3DXVECTOR3 aFrustumVertex[8];
	for (int i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&aFrustumVertex[i], &m_aProjVertex[i], &mat);
	}

	int n = 0;
	D3DXPlaneFromPoints(&m_aPlane[n++],
		&aFrustumVertex[0],
		&aFrustumVertex[1],
		&aFrustumVertex[2]);

	D3DXPlaneFromPoints(&m_aPlane[n++],
		&aFrustumVertex[5],
		&aFrustumVertex[4],
		&aFrustumVertex[7]);

	D3DXPlaneFromPoints(&m_aPlane[n++],
		&aFrustumVertex[4],
		&aFrustumVertex[0],
		&aFrustumVertex[3]);

	D3DXPlaneFromPoints(&m_aPlane[n++],
		&aFrustumVertex[1],
		&aFrustumVertex[5],
		&aFrustumVertex[6]);

	D3DXPlaneFromPoints(&m_aPlane[n++],
		&aFrustumVertex[4],
		&aFrustumVertex[5],
		&aFrustumVertex[0]);

	D3DXPlaneFromPoints(&m_aPlane[n++],
		&aFrustumVertex[3],
		&aFrustumVertex[2],
		&aFrustumVertex[6]);
}