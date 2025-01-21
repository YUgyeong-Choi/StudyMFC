#include "pch.h"
#include "CSingleTexture.h"
#include "CDevice.h"

CSingleTexture::CSingleTexture():m_pTexInfo(nullptr)
{
}

CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::Insert_Texture(const TCHAR* pFilePath, const TCHAR* pStateKey, const int& iCnt)
{
    m_pTexInfo = new TEXINFO;
    ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

    // D3DXGetImageInfoFromFile : 지정한 이미지 파일에 관한 정보를 얻어와 구조체에 기록하는 함수
    if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &(m_pTexInfo->tImgInfo))))
    {
        Safe_Delete(m_pTexInfo);
        AfxMessageBox(L"D3DXGetImageInfoFromFile Failed");
        return E_FAIL;
    }

    if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(),
        pFilePath,
        m_pTexInfo->tImgInfo.Width,
        m_pTexInfo->tImgInfo.Height,
        m_pTexInfo->tImgInfo.MipLevels, //(원본 텍스처 이미지의 여러 크기 버전들을 포함한 계층 구조)
        0,  // USAGE : 텍스처의 사용 방식(0 일반적인 텍스처, D3DUSAGE_RENDERTARGET : 화면 그리기 텍스처)
        m_pTexInfo->tImgInfo.Format,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,              // 0을 넣어주면 컬러키 무효화 (텍스처 이미지에서 특정 색을 투명한 색(알파값 0)으로 처리하는 컬러키 기능을 사용하지 않겠다는 의미)
        nullptr,        // 이미지 정보 기록
        nullptr,        // 팔레트 이미지에 대한 처리
        &(m_pTexInfo->pTexture))))
    {
        Safe_Delete(m_pTexInfo);
        AfxMessageBox(L"D3DXCreateTextureFromFileEx Failed");
        return E_FAIL;
    }

    return S_OK;
}
void CSingleTexture::Release()
{
	Safe_Release(m_pTexInfo->pTexture);
	Safe_Delete(m_pTexInfo);
}
