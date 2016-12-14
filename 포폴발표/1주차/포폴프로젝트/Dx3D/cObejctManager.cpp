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
	, DoorClose(0.0f)
	, b_Collision(false)
	
{
}


cObejctManager::~cObejctManager()
{

}



void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, D3DXVECTOR3 Min, D3DXVECTOR3 Max)
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	newobject->SetWolrd(Pogi, size);

	newobject->SetInter(false);

	cOBB * obb;

	obb = new cOBB;

	obb->Setup(Min, Max);

	newobject->SetObb(obb);

	object.push_back(newobject);

	//SAFE_DELETE(newobject);
}
										  //폴더명            파일명          위치          사이즈     구(충돌용)   오브젝트 타입  출력텍스트(door , switch는 할당해줘야함) , item
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


void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, D3DXVECTOR3 size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text, D3DXVECTOR3 Min, D3DXVECTOR3 Max , float Angle)
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	if (Angle)
	newobject->SetWolrd(Pogi, size, Angle);
	else newobject->SetWolrd(Pogi, size);
	newobject->m_sSphre = _Sphre;

	newobject->SetInter(true);

	newobject->SetObjType(_objtype);

	if (_Text.size())newobject->SetText(_Text);

	cOBB * obb;

	obb = new cOBB;

	obb->Setup(Min, Max);

	newobject->SetObb(obb);

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
					//엘베 스위치 눌렀을 때 행동
					if (object[i]->GetObjType() == OBJ_TYPE::Switch)
					{
						//if (object[2]->GetisOpen())	object[2]->SetisOpen(false);
						//else object[2]->SetisOpen(true);

						//if (object[3]->GetisOpen())	object[3]->SetisOpen(false);
						//else object[3]->SetisOpen(true);

						//float closeSpeed = 0.567f;
						//float leftp = 61.6f;
						//float rightp = 64.0f;
						//
						//leftp -= closeSpeed;
						//rightp += closeSpeed;
						//
						//object[2]->SetWolrd(D3DXVECTOR3(leftp, -17, -105.5f), D3DXVECTOR3(0.06f, 0.07f, 0.06f));
						//object[3]->SetWolrd(D3DXVECTOR3(rightp, -17, -105.5f), D3DXVECTOR3(0.06f, 0.07f, 0.06f));



						//p = D3DXVECTOR3(61.6f, -17, -105.5f);
						//p = D3DXVECTOR3(64.0f, -17, -105.5f);

						//엘베 문을 열꺼야


					}


				}
			}


			//float closeSpeed = 0.567f;
			//float leftp = 61.6f;
			//float rightp = 64.0f;
			//
			//leftp -= closeSpeed;
			//rightp += closeSpeed;
			//
			//object[2]->SetWolrd(D3DXVECTOR3(leftp, -17, -105.5f), D3DXVECTOR3(0.06f, 0.07f, 0.06f));
			//object[3]->SetWolrd(D3DXVECTOR3(rightp, -17, -105.5f), D3DXVECTOR3(0.06f, 0.07f, 0.06f));
			//여기서 문ㅇㄹ자			}

			
			//m_sleect_index = i;
		}
		//엘베 스위치 눌렀을 때 행동
		if (object[0]->m_sSphre.isPicked)
		{
			if (GetAsyncKeyState('E') & 0x8000)			//디버그용으로 열닫 조절하게 했습니다 나중에 이벤트 신에서 해당 인덱스 만 처리해주는걸로 수정
			{
				if (object[i]->GetObjType() == OBJ_TYPE::Switch)
				{
					if (object[i]->GetisOpen())	object[i]->SetisOpen(false);
					else object[i]->SetisOpen(true);
				}
			}
		}
		//if (object[i]->GetObb())
		//{
		//
		//}
	}
	//문열고 닫고 
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



	if (m_select_index != NonSlect && object[m_select_index]->GetObjType()==OBJ_TYPE::item)
	{
		object[m_select_index]->m_sSphre.isPicked = true;
	}

}



void cObejctManager::Render()
{

	for (int i = 0; i < object.size(); i++)
	{
		object[i]->ObjRender();
		/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && object[i]->GetAngleX() <= 3.14 / 2)
		{
			
			DoorClose -= 0.000000000000001f;
			object[i]->SetAngleX(object[i]->GetAngleX() - DoorClose);
			if (object[i]->GetAngleX() < 3.14 / 2)
			{
				object[i]->SetAngleX(3.14 / 2);
				DoorClose = 0;
			}
		}*/

		////다음 프로젝트 여는 순간 이 if 업데이트문 지워버려!!! ☆
		//if (object[i]->GetObb())
		//{
		//	
		//	object[i]->GetObb()->Update(object[i]->GetWolrd());
		//}

		if (GetAsyncKeyState(VK_F1)&0x8001)
		{
			if (object[i]->GetObb())
			{
			//	object[i]->ObjRender();
				
				
				object[i]->GetObb()->DebugRender(D3DCOLOR_XRGB(255, 0, 0));
			}
		}
	}

	//for (int i = 0; i < object.size(); i++)
	//{
	//	if (object[i]->m_sSphre.isPicked)
	//	{
	//		object[i]->ObjVIEWRender();
	//	}
	//}

	if (m_select_index != NonSlect && object[m_select_index]->GetObjType()==item)
	{
		object[m_select_index]->ObjVIEWRender();
	}

	

}


float cObejctManager::getAngleX()
{
	/*for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
			return	object[i]->GetAngleX();
		}
	}*/

	return	object[m_select_index]->GetAngleX();
}
float cObejctManager::getAngleY()
{
	/*for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
			return object[i]->GetAngleY();
		}
	}*/

	return	object[m_select_index]->GetAngleX();
}

bool cObejctManager::isPinked()		//카메라 처리용입니다.
{
	/*int size = object.size();
	int count = 0;*/
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->m_sSphre.isPicked)
		{
			return true;
		}
		else
		{
	//		count++;
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
		else
		{
			//		없음
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
		else
		{
			//		count++;
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