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
	, m_LockupMouse(false)
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

	GetClientRect(g_hWnd, &rc);
	m_ptPrevMouse.x = (rc.right - rc.left) / 2;
	m_ptPrevMouse.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(g_hWnd, &m_ptPrevMouse);
	SetCursorPos(m_ptPrevMouse.x, m_ptPrevMouse.y);
}

void cCamera::Update(D3DXVECTOR3* pTarget, D3DXVECTOR3* pDirection,bool IsCrawl)
{
	//마우스 가두기
	if (m_LockupMouse)
		SetCursor(NULL);

	D3DXMATRIXA16 matRX, matRY, matT, mat;
	D3DXMatrixRotationX(&matRX, m_fAngleX);
	D3DXMatrixRotationY(&matRY, m_fAngleY);

	mat = matRX * matRY;

	D3DXVECTOR3 templook;
	D3DXVec3TransformNormal(&templook, &D3DXVECTOR3(0, 0, -1), &mat);

	//D3DXVec3TransformNormal(&m_vLookAt, &D3DXVECTOR3(0, 0, 1), &mat);


	//D3DXVec3TransformCoord(&m_vEye, &m_vEye, &mat);


	if (pTarget)
	{
		if (IsCrawl)
		{
			pTarget->y += 2.5f;
			pTarget->x -= sinf(m_fAngleY);
			pTarget->z -= cosf(m_fAngleY);
			m_vEye = *pTarget;
			
		}
		else
		{
			pTarget->y += 3.5f;
			m_vEye = *pTarget;
		}

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

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//마우스 가두기
	if (GetAsyncKeyState(VK_CONTROL) & 1)
	{
		if (m_LockupMouse) m_LockupMouse = false;
		else m_LockupMouse = true;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
	{
		ObjectManager->SetNonSelect();

	}
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{

		GetCursorPos(&temp);
		m_fTempX = m_fAngleX;
		m_fTempY = m_fAngleY;
	}
	switch (message)
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

		//오브젝트  선택 되어있을시 해당 오브젝트의 앵글값을 계속 받아옴
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
		if (m_isLButtonOBJDown)
		{
			SetCursorPos(temp.x, temp.y);
		}

		m_isLButtonDown = false;
		m_isLButtonOBJDown = false;
		if (ObjectManager->getPinkedObjType() == door)ObjectManager->SetNonSelect();
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (!m_isLButtonOBJDown && ObjectManager->Getselect_index() == NonSlect)
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			if (m_LockupMouse)
			{
				RECT rc;
				GetClientRect(g_hWnd, &rc);
				if (pt.x >= rc.right - 200 || pt.x <= rc.left + 200)
				{
					pt.x = (rc.right - rc.left) / 2;
					m_ptPrevMouse = pt;
					ClientToScreen(g_hWnd, &pt);
					SetCursorPos(pt.x, pt.y);
					break;
				}
				else if (pt.y >= rc.bottom - 100 || pt.y <= rc.top + 100)
				{
					pt.y = (rc.bottom - rc.top) / 2;
					m_ptPrevMouse = pt;
					ClientToScreen(g_hWnd, &pt);
					SetCursorPos(pt.x, pt.y);
					break;
				}
				int nDeltaX = pt.x - m_ptPrevMouse.x;
				int nDeltaY = pt.y - m_ptPrevMouse.y;

				m_fAngleX += -nDeltaY * 0.01f;
				if (m_fAngleX > D3DX_PI / 1.5f - EPSILON)
				{
					m_fAngleX = D3DX_PI / 1.5f - EPSILON;
				}
				if (m_fAngleX < -D3DX_PI / 1.5f + EPSILON)
				{
					m_fAngleX = -D3DX_PI / 1.5f + EPSILON;
				}
				m_fAngleY += nDeltaX * 0.01f;


				m_ptPrevMouse = pt;
			}
		}

			if (m_isLButtonOBJDown)
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);

				int nDeltaX = pt.x - m_ptOBJPrevMouse.x;
				int nDeltaY = pt.y - m_ptOBJPrevMouse.y;

				m_fAngleX_obj += nDeltaY * 0.01f;

				if (ObjectManager->getPinkedObjType() == OBJ_TYPE::door)
				{
					if (ObjectManager->getOpen())
					{
						if (m_fAngleX_obj > -1.5)
							m_fAngleX_obj = -1.5;

						if (m_fAngleX_obj < -D3DX_PI - EPSILON)
							m_fAngleX_obj = -D3DX_PI - EPSILON;
					}
					else
					{
						if (m_fAngleX_obj > -1.5)
							m_fAngleX_obj = -1.5;

						if (m_fAngleX_obj < -D3DX_PI / 2.0 - EPSILON)
							m_fAngleX_obj = -D3DX_PI / 2.0 - EPSILON;

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