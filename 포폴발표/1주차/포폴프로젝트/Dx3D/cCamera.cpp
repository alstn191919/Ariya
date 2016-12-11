#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
	: m_vEye(0, 0, 10)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_isLButtonDown(false)
	, m_isLButtonOBJDown(false)
	, m_fAngleX(0.0f)
	, m_fAngleY(0.0f)
	, m_fDistance(10.0f)
{
}

cCamera::~cCamera(void)
{
}

void cCamera::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);
	
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 1000);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

}

void cCamera::Update(D3DXVECTOR3* pTarget, D3DXVECTOR3* pDirection)
{

	//SetCursor(NULL);

	D3DXMATRIXA16 matRX, matRY, matT, mat;
	D3DXMatrixRotationX(&matRX, m_fAngleX);
	D3DXMatrixRotationY(&matRY, m_fAngleY);

	mat = matRX * matRY;

	D3DXVECTOR3 templook;
	D3DXVec3TransformNormal(&templook, &D3DXVECTOR3(0, 0, 1), &mat);

	//D3DXVec3TransformNormal(&m_vLookAt, &D3DXVECTOR3(0, 0, 1), &mat);


	//D3DXVec3TransformCoord(&m_vEye, &m_vEye, &mat);


	if (pTarget)
	{
		pTarget->y += 4.0f;
		m_vEye = *pTarget;
		m_vLookAt = *pTarget + *pDirection + templook;
	}

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);



}

D3DXMATRIXA16* cCamera::GetViewMatrix()
{
	return &m_matView;
}

D3DXMATRIXA16* cCamera::GetProjMatrix()
{
	return &m_matProj;
}

void cCamera::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		ObjectManager->SetNonSelect();

	}
	switch(message)
	{
	case WM_LBUTTONDOWN:
		{
			m_isLButtonDown = true;
			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);

			if (ObjectManager->isPinked())
			{
				m_ptOBJPrevMouse.x = LOWORD(lParam);
				m_ptOBJPrevMouse.y = HIWORD(lParam);
				m_isLButtonDown = false;
				m_isLButtonOBJDown = true;


				if (ObjectManager->Getselect_index() == NonSlect && ObjectManager->getPinkedObjType() == OBJ_TYPE::item || ObjectManager->getPinkedObjType() == OBJ_TYPE::door)
				{
					ObjectManager->SetSelect();
					//else
					//{
					//	m_isLButtonOBJDown = false;
					//	//ObjectManager->SetNonSelect();
					//}
					m_fAngleX_obj = ObjectManager->getAngleX();
					m_fAngleY_obj = ObjectManager->getAngleY();



					break;
				}
			}


			if (ObjectManager->Getselect_index() != NonSlect)
			{
				m_ptOBJPrevMouse.x = LOWORD(lParam);
				m_ptOBJPrevMouse.y = HIWORD(lParam);
				m_isLButtonDown = false;
				m_isLButtonOBJDown = true;

				m_fAngleX_obj = ObjectManager->getAngleX();
				m_fAngleY_obj = ObjectManager->getAngleY();
			}

		}
		break;
	case WM_LBUTTONUP:
		{
			m_isLButtonDown = false;
			m_isLButtonOBJDown = false;
			if (ObjectManager->getPinkedObjType() == door)ObjectManager->SetNonSelect();
		}
		break;
	case WM_MOUSEMOVE:
	{
		//if(m_isLButtonDown)
			//{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			m_fAngleX = pt.y * -0.015f;

			if(m_fAngleX > -D3DX_PI * 0.4f - EPSILON)
			   m_fAngleX = -D3DX_PI * 0.4f - EPSILON;

			if (m_fAngleX <= -D3DX_PI * 1.6f + EPSILON)
				m_fAngleX = -D3DX_PI * 1.6f + EPSILON;

			m_fAngleY = pt.x* 0.015f;

			//커서 다시 중간에 돌려놓기
			if ((m_fAngleY > D3DX_PI * 4.4f) || (m_fAngleY < D3DX_PI / 2.2f ))
			{
				RECT rc;
				GetClientRect(g_hWnd, &rc);
				pt.x = (rc.right - rc.left) / 2;
				ClientToScreen(g_hWnd, &pt);
				SetCursorPos(pt.x, pt.y);
			}

			if (m_isLButtonOBJDown)
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);

				int nDeltaX = pt.x - m_ptOBJPrevMouse.x;
				int nDeltaY = pt.y - m_ptOBJPrevMouse.y;

				m_fAngleX_obj += nDeltaY * 0.01f;
				
				if (ObjectManager->getPinkedObjType()==OBJ_TYPE::door)
				{
					if (ObjectManager->getOpen())
					{
						if (m_fAngleX_obj > D3DX_PI / 2.0f - EPSILON)
							m_fAngleX_obj = D3DX_PI / 2.0f - EPSILON;

						if (m_fAngleX_obj < -D3DX_PI / 2.0f + EPSILON)
							m_fAngleX_obj = -D3DX_PI / 2.0f + EPSILON;
					}
					else
					{
						if (m_fAngleX_obj > -1.5)
							m_fAngleX_obj = -1.5;

						if (-D3DX_PI / 2.0f + EPSILON)
							-D3DX_PI / 2.0f + EPSILON;
					}
				}
				else
				{
					if (m_fAngleX > D3DX_PI / 2.0f - EPSILON)
						m_fAngleX = D3DX_PI / 2.0f - EPSILON;

					if (m_fAngleX < -D3DX_PI / 2.0f + EPSILON)
						m_fAngleX = -D3DX_PI / 2.0f + EPSILON;
				}

				m_fAngleY_obj += nDeltaX * 0.01f;


				ObjectManager->SetMouseAngle(m_fAngleX_obj, m_fAngleY_obj);
				m_ptOBJPrevMouse = pt;
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			int n = GET_WHEEL_DELTA_WPARAM(wParam);
			m_fDistance -= n / 100.f;
		}
		break;
	}
}
