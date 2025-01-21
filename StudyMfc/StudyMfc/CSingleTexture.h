#pragma once
#include "CTexture.h"
class CSingleTexture : public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

public:
	const TEXINFO* CSingleTexture::Get_Texture(const TCHAR* pStateKey = L"", const int& iCnt = 0)
	{
		return m_pTexInfo;
	}

public:
	HRESULT Insert_Texture(const TCHAR* pFilePath, const TCHAR* pStateKey = L"", const int& iCnt = 0) override;
	void Release() override;

private:
	TEXINFO* m_pTexInfo;
};

