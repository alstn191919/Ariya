#include "StdAfx.h"
#include "cCrtController.h"
#include "cMapRender.h"

cCrtController::cCrtController(void)
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 1)
	, m_fSpeed(0.3f)
	, m_fAngleX(0.0f)
	, m_isRight(false)

{
}


cCrtController::~cCrtController(void)
{
}

void cCrtController::Setup()
{

}

void cCrtController::Update(cMapRender* pMap /*= NULL*/)
{
	D3DXMATRIXA16 matRx, matRy, mat;
	D3DXMatrixRotationY(&matRx, m_fAngleX);
	//D3DXMatrixRotationX(&matRy, m_fAngleY);
	//D3DXMatrixRotationAxis(&matRy, &m_vDirection, m_fAngleY);
	D3DXVECTOR3 vPosition = m_vPosition;

	mat = matRx;
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, -1), &mat);

	D3DXVECTOR3 tempDirection = m_vDirection;

	if (GetKeyState('A') & 0x8000)
	{
		D3DXVec3TransformNormal(&tempDirection, &D3DXVECTOR3(1, 0, 0), &mat);
		vPosition = m_vPosition + (tempDirection * (m_fSpeed - 0.2f));
	}
	if (GetKeyState('D') & 0x8000)
	{
		D3DXVec3TransformNormal(&tempDirection, &D3DXVECTOR3(-1, 0, 0), &mat);
		vPosition = m_vPosition + (tempDirection * (m_fSpeed - 0.2f));
	}
	if (GetKeyState('S') & 0x8000)
	{
		if (GetKeyState('A') & 0x8000)
		{
			D3DXVec3TransformNormal(&tempDirection, &D3DXVECTOR3(1, 0, 1), &mat);
			vPosition = m_vPosition + (tempDirection * (m_fSpeed - 0.2f));
		}
		else if (GetKeyState('D') & 0x8000)
		{
			D3DXVec3TransformNormal(&tempDirection, &D3DXVECTOR3(-1, 0, 1), &mat);
			vPosition = m_vPosition + (tempDirection * (m_fSpeed - 0.2f));
		}
		else
		{
			vPosition = m_vPosition - (m_vDirection * (m_fSpeed - 0.2f));
		}

	}
	if (GetKeyState('W') & 0x8000)
	{
		if (GetKeyState('A') & 0x8000)
		{
			D3DXVec3TransformNormal(&tempDirection, &D3DXVECTOR3(1, 0, -1), &mat);
			vPosition = m_vPosition + (tempDirection * (m_fSpeed - 0.2f));
		}
		else if (GetKeyState('D') & 0x8000)
		{
			D3DXVec3TransformNormal(&tempDirection, &D3DXVECTOR3(-1, 0, -1), &mat);
			vPosition = m_vPosition + (tempDirection * (m_fSpeed - 0.2f));
		}
		else
		{
			vPosition = m_vPosition + (m_vDirection * (m_fSpeed - 0.1f));
		}
	}

	if (pMap)
	{
		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
			m_vPosition = vPosition;
	}
	else
	{
		m_vPosition = vPosition;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = mat * matT;
}