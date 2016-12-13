#include "stdafx.h"
#include "cSceneManager.h"
#include "cStartScene.h"
#include "c2FScene.h"

cSceneManager::cSceneManager() :eMenu(Scene_NULL)
, pStartScene(NULL)
, p2FScene(NULL)
{

}

cSceneManager::~cSceneManager()
{

}

void cSceneManager::Update()
{
	switch (eMenu)
	{
		case Scene_NULL:
		{
						   assert("���� �ʱ�ȭ�� �����Դϴ�.", false);
						   break;
		}
		case Scene_Main:
		{
						   if (pStartScene)
				   {
							   pStartScene->Update();
				   }
				   break;
		}
		case Scene_2F:
		{
					if (p2FScene)
				   {
						p2FScene->Update();
				   }
				   break;
		}
		case Scene_3F:
		{
						 break;
		}
		case Scene_End:
		{
						 break;
		}
		default:
		{
				   assert("�߸��� enum��", false);
				   break;
		}
	}
}
void cSceneManager::Render()
{
	switch (eMenu)
	{
		case Scene_NULL:
		{
			assert("���� �ʱ�ȭ�� �����Դϴ�.", false);
			break;
		}
		case Scene_Main:
		{
						   if (pStartScene)
			{
							   pStartScene->Render();
			}
			break;
		}
		case Scene_2F:
		{
			 if (p2FScene)
			 {
				 p2FScene->Render();
			 }
			 break;
		}
		case Scene_3F:
		{
						 break;
		}
		case Scene_End:
		{
						  break;
		}
		default:
		{
			assert("�߸��� enum��", false);
			break;
		}
	}
}
//�� ���� �Լ�
void cSceneManager::ChangeScene(SceneMenu Scene)
{
	eMenu = Scene;
	switch (eMenu)
	{
		case Scene_NULL:
		{
			assert("���� �ʱ�ȭ�� �����Դϴ�.", false);
			break;
		}
		case Scene_Main:
		{
						   pStartScene = new cStartScene;
						   pStartScene->Setup();
			 break;
		}
		case Scene_2F:
		{
			 p2FScene = new c2FScene;
			 p2FScene->Setup();
			 break;
		}
		case Scene_3F:
		{
						 break;
		}
		case Scene_End:
		{
						 break;
		}
		default:
		{
			 assert("�߸��� enum��", false);
			 break;
		}
	}
}

void cSceneManager:: WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (eMenu)
	{
	case Scene_NULL:
	{
					   assert("���� �ʱ�ȭ�� �����Դϴ�.", false);
					   break;
	}
	case Scene_Main:
	{
					   pStartScene->WndProc(hWnd, message, wParam, lParam);
					   break;
	}
	case Scene_2F:
	{
					 p2FScene->WndProc(hWnd, message, wParam, lParam);
					 break;
	}
	case Scene_3F:
	{
					 break;
	}
	case Scene_End:
	{
					  break;
	}
	default:
	{
			   assert("�߸��� enum��", false);
			   break;
	}
	}
}

void cSceneManager::Destroy()
{
	SAFE_DELETE(p2FScene);
	SAFE_DELETE(pStartScene);
}