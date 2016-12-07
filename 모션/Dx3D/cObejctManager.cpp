#include "stdafx.h"
#include "cObejctManager.h"
#include "cRay.h"
#include "cCamera.h"


cObejctManager::cObejctManager()
	:m_select_index(NonSlect)
{
}


cObejctManager::~cObejctManager()
{

}



void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi,  float size)
{
	cSkinnedMesh2* newobject;

	newobject = new cSkinnedMesh2;

	newobject->Load(sFolder, sFile);

	newobject->SetWolrd(Pogi, size);

	newobject->SetInter(false);

	object.push_back(newobject);

	//SAFE_DELETE(newobject);
}
										  //폴더명            파일명          위치          사이즈     구(충돌용)   오브젝트 타입  출력텍스트(door , switch는 할당해줘야함) , item
void cObejctManager::ADDobject(std::string sFolder, std::string sFile, D3DXVECTOR3 Pogi, float size, ST_SPHERE _Sphre, OBJ_TYPE _objtype, std::string _Text=NULL)	
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



void cObejctManager::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	cRay r = cRay::RayAtWorldSpace(pt.x, pt.y);
	for (size_t i = 0; i < object.size(); ++i)
	{
		if (object[i]->GetInter())
		{
			object[i]->m_sSphre.isPicked = r.IsPicked(object[i]->m_sSphre);
			//m_sleect_index = i;
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