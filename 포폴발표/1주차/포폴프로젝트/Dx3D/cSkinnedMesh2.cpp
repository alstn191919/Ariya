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
, gpShadowRenderTarget(NULL)
, gpShadowDepthStencil(NULL)
, gpApplyShadowShader(NULL)
, gpCreateShadowShader(NULL)
, vLightPosition(0, 0, 0)
{
	D3DXMatrixIdentity(&m_wolrd);
}

cSkinnedMesh2::~cSkinnedMesh2(void)
{
	SAFE_DELETE(m_Obb);


	SAFE_RELEASE(m_pAnimController);
	SAFE_RELEASE(gpShadowDepthStencil);
	SAFE_RELEASE(gpShadowRenderTarget);
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
	//Render(m_pRootBone);
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
	

	D3DXMatrixTranslation(&mat, p.x, p.y, p.z);

	if (m_eObjType == Eledoor)
	{
		D3DXMatrixRotationY(&matR,-D3DX_PI/2.0f);
	}

	D3DXMatrixIdentity(&m_wolrd);

	m_wolrd = matS * matR * mat *m_wolrd;



}

void cSkinnedMesh2::SetWolrd(D3DXVECTOR3 p, D3DXVECTOR3 size , float Angle)
{
	D3DXMATRIXA16 mat, matS, matR;

	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, size.x, size.y, size.z);



	D3DXMatrixTranslation(&mat, p.x, p.y, p.z);


	D3DXMatrixRotationY(&matR, Angle);
	


	D3DXMatrixIdentity(&m_wolrd);


	m_wolrd = matS * matR * mat *m_wolrd;






}

void cSkinnedMesh2::ObjRender()
{
	if (m_eObjType == door)
	{	

		D3DXMATRIXA16 matRX, matRY, mat , matOBB;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matOBB);

		mat._43 = -3.5;
		
		D3DXMatrixRotationY(&matRX, -m_fAngleX);
		D3DXMatrixRotationX(&matRY, -m_fAngleY);

		mat = ( mat  *  matRX * matRY);


		D3DXMatrixRotationY(&matRX, -m_fAngleX);
		D3DXMatrixRotationX(&matRY, -m_fAngleY);

		matOBB = (matOBB  *  matRX * matRY);
		

		mat = mat * m_wolrd;
		matOBB = matOBB * m_wolrd;
		D3DXVECTOR3 tempP;

		
		//tempP.x = matOBB._41 + 4;
		//tempP.y = matOBB._42 + 3;
		tempP.x = matOBB._41;
		tempP.y = matOBB._42;
		tempP.z = matOBB._43;
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		//m_sSphre.vCenter= tempP;
		D3DXMATRIXA16 a = m_Obb->GetmatWorldTM();
		m_Obb->Update(&matOBB);
		if (!m_pRootBone) return;
		ShaderRender(m_pRootBone, vLightPosition, mat);
	}
	else
	{
		if (!m_pRootBone) return;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_wolrd);
		if (m_Obb)m_Obb->Update(&m_wolrd);
		ShaderRender(m_pRootBone, vLightPosition,m_wolrd);
	}
	if (!m_pRootBone) return;
	//Render(m_pRootBone);
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
	mat._43 = pogi.z-0.5;

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



	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	if (m_pRootBone == NULL) return;
	Render(m_pRootBone);
}

void cSkinnedMesh2::ShaderInit()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	gpApplyShadowShader = g_pLightShaderManager->Getshader("./shader/ApplyShadow.fx");
	gpCreateShadowShader = g_pLightShaderManager->Getshader("./shader/CreateShadow.fx");
	// 렌더타깃을 만든다.
	const int shadowMapSize = 1024;
	if (FAILED(g_pD3DDevice->CreateTexture(rc.right, rc.bottom,
		1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F,
		D3DPOOL_DEFAULT, &gpShadowRenderTarget, NULL)))
	{
		assert("렌더타깃 생성실패", false);
	}

	// 그림자 맵과 동일한 크기의 깊이버퍼도 만들어줘야 한다.
	if (FAILED(g_pD3DDevice->CreateDepthStencilSurface(shadowMapSize, shadowMapSize,
		D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, TRUE,
		&gpShadowDepthStencil, NULL)))
	{
		assert("깊이버퍼 생성실패", false);
	}
}

void cSkinnedMesh2::ShaderRender(ST_BONE2* pBone, D3DXVECTOR3 _gWorldCameraPosition, D3DXMATRIX _gBoneWorld)
{
	if (!pBone) return;
	ST_BONE_MESH2* pBoneMesh = (ST_BONE_MESH2*)pBone->pMeshContainer;

	// 광원-뷰 행렬을 만든다.
	D3DXMATRIXA16 matLightView;
	{
		D3DXVECTOR3 dir = D3DXVECTOR3(_gBoneWorld._41, _gBoneWorld._42, _gBoneWorld._43);
		D3DXVECTOR3 vRight;
		D3DXVECTOR3 vLookAt = dir - vLightPosition;
		D3DXVECTOR3 vEyePt(vLightPosition.x, vLightPosition.y, vLightPosition.z);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&vRight, &vUpVec, &vLookAt);
		D3DXVec3Cross(&vUpVec, &vLookAt, &vRight);
		D3DXMatrixLookAtLH(&matLightView, &vEyePt, &vLookAt, &vUpVec);
	}
	//g_pD3DDevice->GetTransform(D3DTS_VIEW, &matLightView);
	// 광원-투영 행렬을 만든다.
	D3DXMATRIXA16 matLightProjection;
	{
		D3DXMatrixPerspectiveFovLH(&matLightProjection, D3DX_PI / 4.0f, 1, 1, 1000);
	}

	// 뷰/투영행렬을 만든다.
	D3DXMATRIXA16 matViewProjection;
	{
		// 뷰 행렬을 만든다.
		D3DXMATRIXA16 matView;
		D3DXMATRIXA16 matProjection;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
		D3DXMatrixMultiply(&matViewProjection, &matView, &matProjection);
	}

	// 현재 하드웨어 벡버퍼와 깊이버퍼
	LPDIRECT3DSURFACE9 pHWBackBuffer = NULL;
	LPDIRECT3DSURFACE9 pHWDepthStencilBuffer = NULL;
	g_pD3DDevice->GetRenderTarget(0, &pHWBackBuffer);
	g_pD3DDevice->GetDepthStencilSurface(&pHWDepthStencilBuffer);

	// 그림자 맵의 렌더타깃과 깊이버퍼를 사용한다.
	LPDIRECT3DSURFACE9 pShadowSurface = NULL;
	if (SUCCEEDED(gpShadowRenderTarget->GetSurfaceLevel(0, &pShadowSurface)))
	{
		g_pD3DDevice->SetRenderTarget(0, pShadowSurface);
		pShadowSurface->Release();
		pShadowSurface = NULL;
	}
	g_pD3DDevice->SetDepthStencilSurface(gpShadowDepthStencil);

	// 저번 프레임에 그렸던 그림자 정보를 지움
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		0xFFFFFFFF,
		1.0f, 0);

	D3DXMATRIXA16 matView, matProjection;
	D3DXMATRIXA16 matWorldView, matWorldViewProjection;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
	D3DXMatrixMultiply(&matWorldView, &_gBoneWorld, &matView);
	D3DXMatrixMultiply(&matWorldViewProjection, &matWorldView, &matProjection);

	// 그림자 만들기 쉐이더 전역변수들을 설정
	gpCreateShadowShader->SetMatrix("gWorldMatrix", &_gBoneWorld);
	gpCreateShadowShader->SetMatrix("gLightViewMatrix", &matLightView);
	gpCreateShadowShader->SetMatrix("gLightProjectionMatrix", &matLightProjection);

	while (pBoneMesh)
	{
		for (size_t j = 0; j < pBoneMesh->vecMtlTex.size(); ++j)
		{
			UINT numPasses = 0;
			gpCreateShadowShader->Begin(&numPasses, NULL);
			{
				for (UINT i = 0; i < numPasses; ++i)
				{
					gpCreateShadowShader->BeginPass(i);
					{
						pBoneMesh->pWorkMesh->DrawSubset(j);
					}
					gpCreateShadowShader->EndPass();
				}
			}
			gpCreateShadowShader->End();
		}
		pBoneMesh = (ST_BONE_MESH2*)pBoneMesh->pNextMeshContainer;
	}

	//////////////////////////////
	// 2. 그림자 입히기
	//////////////////////////////

	// 하드웨어 백버퍼/깊이버퍼를 사용한다.
	g_pD3DDevice->SetRenderTarget(0, pHWBackBuffer);
	g_pD3DDevice->SetDepthStencilSurface(pHWDepthStencilBuffer);

	pHWBackBuffer->Release();
	pHWBackBuffer = NULL;
	pHWDepthStencilBuffer->Release();
	pHWDepthStencilBuffer = NULL;


	// 그림자 입히기 쉐이더 전역변수들을 설정
	gpApplyShadowShader->SetMatrix("gViewProjectionMatrix", &matViewProjection);
	gpApplyShadowShader->SetMatrix("gLightViewMatrix", &matLightView);
	gpApplyShadowShader->SetMatrix("gLightProjectionMatrix", &matLightProjection);
	gpApplyShadowShader->SetMatrix("gWorldMatrix", &_gBoneWorld);
	gpApplyShadowShader->SetMatrix("gWorldViewProjectionMatrix", &matWorldViewProjection);

	gpApplyShadowShader->SetVector("gWorldLightPosition", &D3DXVECTOR4(vLightPosition, 1));
	gpApplyShadowShader->SetVector("gObjectColor", &D3DXVECTOR4(1, 1, 1, 1));
	gpApplyShadowShader->SetVector("gWorldCameraPosition", &D3DXVECTOR4(_gWorldCameraPosition, 1));

	gpApplyShadowShader->SetTexture("ShadowMap_Tex", gpShadowRenderTarget);

	gpApplyShadowShader->SetFloat("gRange", 200.0f); // 빛 범위 설정
	gpApplyShadowShader->SetFloat("gAlphaBlend", 2.0f); // 빛 세기 알파값


	pBoneMesh = (ST_BONE_MESH2*)pBone->pMeshContainer;

	while (pBoneMesh)
	{
		for (size_t j = 0; j < pBoneMesh->vecMtlTex.size(); ++j)
		{
			gpApplyShadowShader->SetTexture("DiffuseMap_Tex", pBoneMesh->vecMtlTex[j]->GetTexture());
			//gpApplyShadowShader->SetTexture("SpecularMap_Tex", pBoneMesh->vecMtlTex[j]->GetTexture());
			//gpApplyShadowShader->SetTexture("NormalMap_Tex", pBoneMesh->vecMtlTex[j]->GetTexture());
			UINT numPasses = 0;
			gpApplyShadowShader->Begin(&numPasses, NULL);
			{
				for (UINT i = 0; i < numPasses; ++i)
				{
					gpApplyShadowShader->BeginPass(i);
					{
						pBoneMesh->pWorkMesh->DrawSubset(j);
					}
					gpApplyShadowShader->EndPass();
				}
			}
			gpApplyShadowShader->End();
		}
		pBoneMesh = (ST_BONE_MESH2*)pBoneMesh->pNextMeshContainer;
	}

	if (pBone->pFrameFirstChild)
	{
		ShaderRender((ST_BONE2*)pBone->pFrameFirstChild, vLightPosition, _gBoneWorld);
	}
	
	if (pBone->pFrameSibling)
	{
		ShaderRender((ST_BONE2*)pBone->pFrameSibling, vLightPosition, _gBoneWorld);
	}
}