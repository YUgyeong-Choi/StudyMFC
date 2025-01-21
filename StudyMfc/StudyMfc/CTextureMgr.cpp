#include "pch.h"
#include "CTextureMgr.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}

CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEXINFO* CTextureMgr::Get_Texture(const TCHAR* pObjKey,const TCHAR* pStateKey,const int& iCnt)
{
	auto	iter = find_if(m_mapTex.begin(), m_mapTex.end(),
		[&](auto& MyPair)->bool
		{
			if (MyPair.first == pObjKey)
				return true;

			return false;
		});

	if (iter == m_mapTex.end())
		return nullptr;


	return iter->second->Get_Texture(pStateKey, iCnt);
}

HRESULT CTextureMgr::Insert_Texture(const TCHAR* pFilePath, TEXTYPE eTexture, const TCHAR* pObjKey, const TCHAR* pStateKey, const int& iCnt)
{
	auto	iter = find_if(m_mapTex.begin(), m_mapTex.end(),
		[&](auto& MyPair)->bool
		{
			if (MyPair.first == pObjKey)
				return true;

			return false;
		});

	if (iter == m_mapTex.end())
	{
		CTexture* pTexture = nullptr;

		switch (eTexture)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;

		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->Insert_Texture(pFilePath, pStateKey, iCnt)))
		{
			AfxMessageBox(pFilePath);
			return E_FAIL;
		}

		m_mapTex.insert({ pObjKey, pTexture });

	}

	return S_OK;
}

void CTextureMgr::Release()
{
	for_each(m_mapTex.begin(), m_mapTex.end(), [](auto& MyPair)
	{
		Safe_Delete<CTexture*>(MyPair.second);
	});

	m_mapTex.clear();

}
