#include "StdAfx.h"
#include "cAllocateHierarchy2.h"
#include "cMtlTex.h"

cAllocateHierarchy2::cAllocateHierarchy2(void)
{
}

cAllocateHierarchy2::~cAllocateHierarchy2(void)
{
}

STDMETHODIMP cAllocateHierarchy2::CreateFrame(
	THIS_ LPCSTR Name,
	LPD3DXFRAME *ppNewFrame )
{
	ST_BONE2* pBone = new ST_BONE2;
	// TODO : �̸��� �������ּ���.
	pBone->Name = NULL;
	if(Name)
	{
		pBone->Name = new char[strlen(Name) + 1];
		strcpy(pBone->Name, Name);
	}
	
	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);
	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	pBone->pFrameFirstChild = NULL;
	pBone->pFrameSibling = NULL;
	pBone->pMeshContainer = NULL;

	*ppNewFrame = pBone;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy2::CreateMeshContainer( 
	THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData, 
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials, 
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer )
{
	ST_BONE_MESH2* pBoneMesh = new ST_BONE_MESH2;

	assert(pMeshData->Type == D3DXMESHTYPE_MESH);
	
	pBoneMesh->MeshData.pMesh = NULL;

	SAFE_ADD_REF(pMeshData->pMesh);

	// step 1. pSkinInfo ����
	pBoneMesh->pSkinInfo = NULL;
	if(pSkinInfo)
	{
		SAFE_ADD_REF(pSkinInfo);
		pBoneMesh->pSkinInfo = pSkinInfo;
	}
	pBoneMesh->pOrigMesh = pMeshData->pMesh;

	// step 2. ���� �޽� ����
	pBoneMesh->pOrigMesh->CloneMeshFVF(
		pBoneMesh->pOrigMesh->GetOptions(),
		pBoneMesh->pOrigMesh->GetFVF(),
		g_pD3DDevice,
		&pBoneMesh->pWorkMesh);

	pBoneMesh->Name = NULL;
	pBoneMesh->NumMaterials = NumMaterials;
	pBoneMesh->pAdjacency = NULL;
	pBoneMesh->pEffects = NULL;
	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		cMtlTex* pMtlTex = new cMtlTex;
		pMtlTex->SetMtl(pMaterials[i].MatD3D);
		std::string sFullPath = m_sFolder + "/" + std::string(pMaterials[i].pTextureFilename);
		pMtlTex->SetTexture(g_pTextureManager->GetTexture(sFullPath));
		pBoneMesh->vecMtlTex.push_back(pMtlTex);
	}
	pBoneMesh->pNextMeshContainer = NULL;

	// step 3. pSkinInfo->GetNumBones()�� ����
	// ������� ��ġ�� ��� ���� ���� ��Ʈ���� ���� ����
	// ppBoneMatrixPtrs, pBoneOffsetMatrices, pCurrentBoneMatrices�� �����Ҵ�
	if (pSkinInfo)
	{
		DWORD dwNumBones = pSkinInfo->GetNumBones();
		pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
		pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];
		pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];

		// step 4. ���� �Ҵ�� pBoneOffsetMatrices ��Ʈ������ �� ����.
		// pSkinInfo->GetBoneOffsetMatrix(i)
		for (DWORD i = 0; i < dwNumBones; ++i)
		{
			LPD3DXMATRIX pmat = pSkinInfo->GetBoneOffsetMatrix(i);
			pBoneMesh->pBoneOffsetMatrices[i] = *pmat;
		}
	}

	*ppNewMeshContainer = pBoneMesh;
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy2::DestroyFrame( 
	THIS_ LPD3DXFRAME pFrameToFree )
{
	// TODO : ���� �� �սô�.
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	SAFE_DELETE(pFrameToFree);
	
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy2::DestroyMeshContainer( 
	THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	// TODO : ���� �� �սô�.
	ST_BONE_MESH2* pBoneMesh = (ST_BONE_MESH2*)pMeshContainerToFree;
	
	SAFE_RELEASE(pBoneMesh->pOrigMesh);
	SAFE_RELEASE(pBoneMesh->pWorkMesh);

	for each(auto p in pBoneMesh->vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
	pBoneMesh->vecMtlTex.clear();
	SAFE_RELEASE(pBoneMesh->pSkinInfo);
	
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->pCurrentBoneMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);

	SAFE_DELETE(pMeshContainerToFree);

	return S_OK;
}
