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
	, m_wasteRoomStop(false)
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
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
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
			if (time % 8 == 0) {

				if (step == 1)step = 2;
				else if(step == 2)step = 1;
			}
			if (time > 600) step = 3;
			switch (step)
				{
				case 0:
					ObjectManager->getObject(5)->SetisOpen(false);
					g_pSoundManager->Play("close door");
					g_pSoundManager->SetSpeed("slam door", 1.05f);
					step = 1;
					break;
				case 1:
					ObjectManager->getObject(5)->SetAngleX(-1.5);
					g_pSoundManager->SetVolume("rain", 5.0f);
					g_pSoundManager->Stop("open door");
					g_pSoundManager->SetVolume("slam door", 9.0f);
					g_pSoundManager->Play("slam door", DSBPLAY_LOOPING);

					break;
				case 2:
					ObjectManager->getObject(5)->SetAngleX(-D3DX_PI / 2.0 - EPSILON);
					break;
				case 3:
					ObjectManager->getObject(5)->SetisOpen(true);
					ObjectManager->getObject(7)->SetisOpen(true);
					ObjectManager->getObject(10)->SetisOpen(true);
					g_pSoundManager->Stop("slam door");
					g_pSoundManager->SetSpeed("open door", 0.9f);
					g_pSoundManager->Play("open door");
					g_pSoundManager->SetSpeedToOrig("open door");
					g_pSoundManager->SetSpeedToOrig("slam door");
					ObjectManager->SetWasteRoomStop(true);
					break;

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
				g_pSoundManager->Play("chain effect");
				g_pSoundManager->SetVolume("chain effect", 20.0f);
				ObjectManager->getObject(4)->SetWolrd(D3DXVECTOR3(32.0, 2, -40), D3DXVECTOR3(0.4, 0.4, 0.4),-D3DX_PI/6);
				step = 1;
				break;
			case 1:
				
				break;
			case 2:
				ObjectManager->getObject(5)->SetAngleX(-D3DX_PI / 2.0 - EPSILON);
				break;
			case 3:
				g_pSoundManager->Stop("chain effect");
				ObjectManager->getObject(5)->SetisOpen(true);
				ObjectManager->getObject(7)->SetisOpen(true);
				ObjectManager->getObject(10)->SetisOpen(true);


			}



		}
	};



	cEvent * _event;
	_event = new 화장실;

	m_Event["화장실"] = _event;

	_event = new 계단옆;
	m_Event["계단옆"] = _event;
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

void cObejctManager::add3FEvent()
{
	class 펄럭펄럭휠체어 : public cEvent
	{
		float speed;
		float Position;
		int randomX;
		int randomY;
		POINT temp;
		D3DXMATRIXA16 matT;
		//-35.5, -13.11, -81.01f
	public:
		펄럭펄럭휠체어()
		{
			_switch = false;
			speed = -0.70f;
			Position = -62.f;

			RECT rc;
			GetClientRect(g_hWnd, &rc);
			randomX = (rc.right - rc.left) / 2;
			randomY = (rc.bottom - rc.top) / 2;

			obb = new cOBB;
			obb->Setup(D3DXVECTOR3(-2, -2, -2), D3DXVECTOR3(2, 2, 2));
			D3DXMatrixTranslation(&matT, -35.5, -13.11, -81.01f);
		};
		~펄럭펄럭휠체어(){};


		void update()
		{
			obb->Update(&matT);
			if (obb->IsCollision(obb, ObjectManager->GettargetObb()))
			{
				_switch = true;
			}

			if (_switch)
			{
				Position += speed;
				ObjectManager->getObject(17)->SetWolrd(D3DXVECTOR3(-52.f, -14.91f, Position), D3DXVECTOR3(0.4f, 0.4f, 0.4f));
				EVENT();

			}
		}
		void EVENT()
		{
			if (Position <= -92.f)
			{
				CRT_Nervous = true;
				g_pSoundManager->SetSpeed("crash", 6.0f);
				g_pSoundManager->Play("crash");

				ObjectManager->getObject(17)->SetAngleX(0);

				Position = -92.f;
				ObjectManager->getObject(17)->SetWolrd(D3DXVECTOR3(-52.f, -14.91, Position), D3DXVECTOR3(0.4f, 0.4f, 0.4f));

				_switch = false;
			}

		}
	};

	class 공튕기기 :public cEvent
	{
		float gravity;
		float time;
		float Downspeed;
		float Upvalue;
		float Upspeed;
		float height;
		float BallPosition;
		bool IsDown;
		D3DXMATRIXA16 matT;

		//obb 위치
		//-3.5, -13.11,-81.41
	public:
		공튕기기()
		{
			obb = new cOBB;
			obb->Setup(D3DXVECTOR3(-2, -2, -2), D3DXVECTOR3(2, 2, 2));
			_switch = false;
			gravity = 1.4f;
			Downspeed = 0.f;
			Upspeed = 0.22f;
			Upvalue = 0.02f;
			height = -10.91f;
			BallPosition = -10.91f;
			IsDown = true;
			D3DXMatrixTranslation(&matT, -4.0, -15.11, -81.41);

		};

		~공튕기기(){};

		void update()
		{
			obb->Update(&matT);
			if (obb->IsCollision(obb, ObjectManager->GettargetObb()))
			{
				g_pSoundManager->SetSpeed("bounce ball", 1.05f);
				g_pSoundManager->Play("bounce ball", DSBPLAY_LOOPING);
				CRT_Nervous = true;
				_switch = true;
			}
			if (_switch)
			{
				EVENT();
			}
		}
		void EVENT()
		{


			if (IsDown)
			{
				height -= Downspeed;
				Downspeed += 0.01f;
				if (height <= -16.11f)
				{
					Downspeed = 0.f;
					IsDown = false;
					BallPosition -= gravity;
				}
			}
			else
			{
				height += Upspeed;
				Upspeed -= 0.005f;
				if (Upspeed < 0 || height >= BallPosition)
				{
					IsDown = true;
					Upspeed = 0.22f;
					Upspeed -= Upvalue;
					Upvalue += 0.02f;
				}
			}
			if (BallPosition <= -16.11f)
			{
				BallPosition = -16.11;
				height = -16.11f;
				ObjectManager->getObject(18)->SetWolrd(D3DXVECTOR3(-13.7f, BallPosition, -83.f), D3DXVECTOR3(1.2f, 1.2f, 1.2f));
				_switch = false;
				g_pSoundManager->Stop("bounce ball");
				g_pSoundManager->SetSpeedToOrig("bounce ball");
			}
			ObjectManager->getObject(18)->SetWolrd(D3DXVECTOR3(-13.7f, height, -83.f), D3DXVECTOR3(1.2f, 1.2f, 1.2f));
		}
	};


	cEvent * _event;

	_event = new 펄럭펄럭휠체어;
	m_Event["펄럭펄럭휠체어"] = _event;

	_event = new 공튕기기;
	m_Event["공튕기기"] = _event;

	
}
