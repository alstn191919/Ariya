#include "stdafx.h"
#include "cFrostumCulling.h"

cFrostumCulling::cFrostumCulling() : _isUpdate(true)
{
}

cFrostumCulling::~cFrostumCulling()
{
	
}

void cFrostumCulling::Setup()
{
	D3DXPLANE _Plane;
	D3DXPlaneFromPoints(&_Plane, &VecInvers(D3DXVECTOR3(-1, 1, -1+1)), &VecInvers(D3DXVECTOR3(1, -1, -1+1)), &VecInvers(D3DXVECTOR3(-1, -1, -1+1)));
	v_Plane.push_back(_Plane);									
	D3DXPlaneFromPoints(&_Plane, &VecInvers(D3DXVECTOR3(1, 1, -1+1)), &VecInvers(D3DXVECTOR3(1, 1,   0+1)), &VecInvers(D3DXVECTOR3(1, -1,  -1+1)));
	v_Plane.push_back(_Plane);									
	D3DXPlaneFromPoints(&_Plane, &VecInvers(D3DXVECTOR3(-1, 1 , 0+1)), &VecInvers(D3DXVECTOR3(1, -1,  0+1)), &VecInvers(D3DXVECTOR3(1, 1,    0+1)));
	v_Plane.push_back(_Plane);									
	D3DXPlaneFromPoints(&_Plane, &VecInvers(D3DXVECTOR3(-1, 1,  0+1)), &VecInvers(D3DXVECTOR3(-1, 1, -1+1)), &VecInvers(D3DXVECTOR3(-1, -1, -1+1)));
	v_Plane.push_back(_Plane);									
	D3DXPlaneFromPoints(&_Plane, &VecInvers(D3DXVECTOR3(-1, 1, -1+1)), &VecInvers(D3DXVECTOR3(-1, 1,  0+1)), &VecInvers(D3DXVECTOR3(1, 1,    0+1)));
	v_Plane.push_back(_Plane);									
	D3DXPlaneFromPoints(&_Plane, &VecInvers(D3DXVECTOR3(-1, -1,-1+1)), &VecInvers(D3DXVECTOR3(1, -1, -1+1)), &VecInvers(D3DXVECTOR3(1, -1,   0+1)));
	v_Plane.push_back(_Plane);
}

void cFrostumCulling::Update()
{
	if (_isUpdate)
	{
		D3DXPlaneFromPoints(&v_Plane[0], &VecInvers(D3DXVECTOR3(-1, 1, -1 + 1)), &VecInvers(D3DXVECTOR3(1, -1, -1 + 1)), &VecInvers(D3DXVECTOR3(-1, -1, -1 + 1)));
		D3DXPlaneFromPoints(&v_Plane[1], &VecInvers(D3DXVECTOR3(1, 1, -1 + 1)), &VecInvers(D3DXVECTOR3(1, 1, 0 + 1)), &VecInvers(D3DXVECTOR3(1, -1, -1 + 1)));
		D3DXPlaneFromPoints(&v_Plane[2], &VecInvers(D3DXVECTOR3(-1, 1, 0 + 1)), &VecInvers(D3DXVECTOR3(1, -1, 0 + 1)), &VecInvers(D3DXVECTOR3(1, 1, 0 + 1)));
		D3DXPlaneFromPoints(&v_Plane[3], &VecInvers(D3DXVECTOR3(-1, 1, 0 + 1)), &VecInvers(D3DXVECTOR3(-1, 1, -1 + 1)), &VecInvers(D3DXVECTOR3(-1, -1, -1 + 1)));
		D3DXPlaneFromPoints(&v_Plane[4], &VecInvers(D3DXVECTOR3(-1, 1, -1 + 1)), &VecInvers(D3DXVECTOR3(-1, 1, 0 + 1)), &VecInvers(D3DXVECTOR3(1, 1, 0 + 1)));
		D3DXPlaneFromPoints(&v_Plane[5], &VecInvers(D3DXVECTOR3(-1, -1, -1 + 1)), &VecInvers(D3DXVECTOR3(1, -1, -1 + 1)), &VecInvers(D3DXVECTOR3(1, -1, 0 + 1)));
	}
}
bool cFrostumCulling::PositionCulling(D3DXVECTOR3 _ShpereCenter)
{
	for (size_t i = 0; i < v_Plane.size(); i++)
	{
		float _Distance = D3DXPlaneDotCoord(&v_Plane[i], &_ShpereCenter);
		if (_Distance > 0)
		{
			return false;
		}
	}
			return true;
}
D3DXVECTOR3 cFrostumCulling:: VecInvers(D3DXVECTOR3 _Vec)
{
	D3DXVECTOR3 Inverse;
	D3DXMATRIXA16 _ProjM, _ViewM, _Projinverse, _Viewinverse;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &_ProjM);
	D3DXMatrixInverse(&_Projinverse, 0, &_ProjM);

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &_ViewM);
	D3DXMatrixInverse(&_Viewinverse, 0, &_ViewM);

	D3DXVec3TransformCoord(&Inverse, &_Vec, &(_Projinverse * _Viewinverse));

	return Inverse;
}