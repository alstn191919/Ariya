#include "StdAfx.h"
#include "cSkinnedMesh2.h"
#include "cMtlTex.h"

cSkinnedMesh2::cSkinnedMesh2(void)
	: m_pRootBone(NULL)
	, m_pAnimController(NULL)
	, m_fAngleX(-D3DX_PI / 2.0f + EPSILON)  //3.14/2
	, m_fAngleY(0.0)
	, m_Obb(NULL)
	, b_isOpen(false)
{
	D3DXMatrixIdentity(&m_wolrd);
}

cSkinnedMesh2::~cSkinnedMesh2(void)
{
	SAFE_RELEASE(m_pAnimController);

	cAllocateHierarchy2 alloc;
	D3DXFrameDestroy(m_pRootBone, &alloc);
}

void cSkinnedMesh2::Load( std::string sFolder, std::string sFile )
{
	std::string sFullPath = sFolder + "/" + sFile;
	cAllocateHierarchy2 alloc;
	alloc.SetFolder(sFolder);

	D3DXLoadMeshHierarchyFromX(
		sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&alloc,
		NULL,
		(LPD3DXFRAME*)&m_pRootBone,
		&m_pAnimController);

	assert(m_pRootBone && "뿌리가 없어요!");

	if(m_pRootBone)
		SetupBoneMatrixPtrs(m_pRootBone);
}

void cSkinnedMesh2::Update(ST_BONE2* pBone, D3DXMATRIX* pParent)
{
	if(pParent)
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * *pParent;
	}
	else
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;
	}

	if (pBone->pFrameFirstChild)
	{
		Update((ST_BONE2*)pBone->pFrameFirstChild, &pBone->CombinedTransformationMatrix);
	}

	if (pBone->pFrameSibling)
	{
		Update((ST_BONE2*)pBone->pFrameSibling, pParent);
	}
}

void cSkinnedMesh2::Update()
{
	if (m_pRootBone == NULL)
		return;
	
	m_pAnimController->AdvanceTime(g_pTimeManager->GetDeltaTime(), NULL);

	Update(m_pRootBone, NULL);
	UpdateSkinnedMesh(m_pRootBone);
}

void cSkinnedMesh2::Render(ST_BONE2* pBone)
{
	ST_BONE_MESH2* pBoneMesh = (ST_BONE_MESH2*)pBone->pMeshContainer;
	while(pBoneMesh)
	{
		for (size_t i = 0; i < pBoneMesh->vecMtlTex.size(); ++i)
		{
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->GetMtl());
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
			pBoneMesh->pWorkMesh->DrawSubset(i);
		}
		pBoneMesh = (ST_BONE_MESH2*)pBoneMesh->pNextMeshContainer;
	}

	if (pBone->pFrameFirstChild)
	{
		Render((ST_BONE2*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		Render((ST_BONE2*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh2::Render()
{
	if (m_pRootBone == NULL) return;
	Render(m_pRootBone);
}

void cSkinnedMesh2::SetupBoneMatrixPtrs(ST_BONE2* pBone)
{
	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
	// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
	// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
	// 찾아서 월드매트릭스를 걸어줘라.
	if (pBone && pBone->pMeshContainer)
	{
		ST_BONE_MESH2* pBoneMesh = (ST_BONE_MESH2*)pBone->pMeshContainer;
		LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
		if(pSkinInfo)
		{
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR szName = pSkinInfo->GetBoneName(i);
				ST_BONE2* p = (ST_BONE2*)D3DXFrameFind(m_pRootBone, szName);
				pBoneMesh->ppBoneMatrixPtrs[i] = &p->CombinedTransformationMatrix;
			}
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs((ST_BONE2*)pBone->pFrameFirstChild);
	}
	
	if (pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs((ST_BONE2*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh2::UpdateSkinnedMesh(ST_BONE2* pBone)
{
	// pCurrentBoneMatrices 를 계산하시오
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 

	if (pBone && pBone->pMeshContainer)
	{
		ST_BONE_MESH2* pBoneMesh = (ST_BONE_MESH2*)pBone->pMeshContainer;
		LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
		if(pSkinInfo)
		{
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				pBoneMesh->pCurrentBoneMatrices[i] = 
					pBoneMesh->pBoneOffsetMatrices[i] *
					*(pBoneMesh->ppBoneMatrixPtrs[i]);
			}

			BYTE* src = NULL;
			BYTE* dest = NULL;

			pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
			pBoneMesh->pWorkMesh->LockVertexBuffer( 0, (void**)&dest );

			//pWorkMesh을 업데이트 시켜준다.
			pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

			pBoneMesh->pWorkMesh->UnlockVertexBuffer();
			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameFirstChild)
	{
		UpdateSkinnedMesh((ST_BONE2*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		UpdateSkinnedMesh((ST_BONE2*)pBone->pFrameSibling);
	}
}

void cSkinnedMesh2::SetAnimationIndex( int n )
{
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(n, &pAnimSet);
	//m_pAnimController->SetTrackSpeed(0, -1);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	SAFE_RELEASE(pAnimSet);
}


void cSkinnedMesh2::SetWolrd(D3DXVECTOR3 p, D3DXVECTOR3 size)
{
	D3DXMATRIXA16 mat,matS,matR;
	
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, size.x, size.y, size.z);
	
	/*mat._41 = p.x;
	mat._42 = p.y;
	mat._43 = p.z;*/

	D3DXMatrixTranslation(&mat, p.x, p.y, p.z);

	if (m_eObjType == Eledoor)
	{
		D3DXMatrixRotationY(&matR,-D3DX_PI/2.0f);
	}

	D3DXMatrixIdentity(&m_wolrd);

	//m_wolrd = matS * mat *m_wolrd;

	m_wolrd = matS * matR * mat *m_wolrd;

	//

}

void cSkinnedMesh2::SetWolrd(D3DXVECTOR3 p, D3DXVECTOR3 size , float Angle)
{
	D3DXMATRIXA16 mat, matS, matR;

	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, size.x, size.y, size.z);

	/*mat._41 = p.x;
	mat._42 = p.y;
	mat._43 = p.z;*/

	D3DXMatrixTranslation(&mat, p.x, p.y, p.z);


	D3DXMatrixRotationY(&matR, Angle);
	


	D3DXMatrixIdentity(&m_wolrd);

	//m_wolrd = matS * mat *m_wolrd;

	m_wolrd = matS * matR * mat *m_wolrd;

	//




}

void cSkinnedMesh2::ObjRender()
{
	if (m_eObjType == door)
	{	

		D3DXMATRIXA16 matRX, matRY, mat , matOBB;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matOBB);

		mat._43 = -3.5;
		//matOBB._43 = -3.5;
		D3DXMatrixRotationY(&matRX, -m_fAngleX);
		D3DXMatrixRotationZ(&matRY, -m_fAngleY);

		mat = ( mat  *  matRX * matRY);


		D3DXMatrixRotationY(&matRX, -m_fAngleX);
		D3DXMatrixRotationZ(&matRY, -m_fAngleY);

		matOBB = (matOBB  *  matRX * matRY);
		//D3DXMatrixTranslation(&mat, m_wolrd._41, m_wolrd._42, m_wolrd._43);

		mat = mat * m_wolrd;
		matOBB = matOBB * m_wolrd;
		//m_wolrd = mat;
		//m_wolrd = mat* m_wolrd;
	/*	pt.vCenter = p;
		pt.vCenter.x = pt.vCenter.x + 2;
		pt.vCenter.y = pt.vCenter.y + 3;*/
		D3DXVECTOR3 tempP;

		
		tempP.x = matOBB._41 + 4;
		tempP.y = matOBB._42 + 3;
		tempP.z = matOBB._43;
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		//m_sSphre.vCenter= tempP;
		D3DXMATRIXA16 a = m_Obb->GetmatWorldTM();
		m_Obb->Update(&matOBB);
	
	}
	else
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_wolrd);
		if (m_Obb)m_Obb->Update(&m_wolrd);
	}
	

	if (m_pRootBone == NULL) return;
	Render(m_pRootBone);
}


void cSkinnedMesh2::ObjEvent()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	bool isLButtonDown = (bool)(GetKeyState(VK_LBUTTON) & 0x8000);
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{

	}
}

void cSkinnedMesh2::ObjVIEWRender(D3DXVECTOR3 pogi)
{
	
	D3DXMATRIXA16 mat;

	mat = m_wolrd;

	mat._41 = pogi.x;
	mat._42 = pogi.y;
	mat._43 = pogi.z;

	D3DXMATRIXA16 matRX, matRY, matR;
	D3DXMatrixRotationY(&matRX, m_fAngleX);
	D3DXMatrixRotationZ(&matRY, m_fAngleY);

	matR = matRX * matRY;

	mat = matR * mat;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	if (m_pRootBone == NULL) return;
	Render(m_pRootBone);
}
void cSkinnedMesh2::ObjVIEWRender()
{
	D3DXMATRIXA16 mat ,viewamat, inverview,inverProj;

	D3DXMatrixIdentity(&mat);

	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &inverProj);



	g_pD3DDevice->GetTransform(D3DTS_VIEW, &viewamat);


	D3DXMatrixInverse(&inverview, 0, &viewamat);

	D3DXMATRIXA16 matRX, matRY, matR;
		D3DXMatrixRotationY(&matRX, m_fAngleX);
		D3DXMatrixRotationZ(&matRY, m_fAngleY);

		matR = matRX * matRY;

		mat = matR * inverview;
	


		mat._42 = mat._42 + 1;
	//g_pD3DDevice->GetTransform(D3DTS_WORLD, &mat);

//	D3DXMatrixInverse(&inverview, 0, &viewamat);
	/*

	*/
	//D3DXMatrixInverse(&inverProj, 0, &inverProj);

	//mat._43 = -1;

//	viewamat._43 = -viewamat._43 + 5;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	
	if (m_pRootBone == NULL) return;
	Render(m_pRootBone);

	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &viewmat);

	
}