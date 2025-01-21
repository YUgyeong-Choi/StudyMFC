#include "pch.h"
#include "CMultiTexture.h"
#include "CDevice.h"

CMultiTexture::CMultiTexture()
{
}

CMultiTexture::~CMultiTexture()
{
    Release();
}

const TEXINFO* CMultiTexture::Get_Texture(const TCHAR* pStateKey,
    const int& iCnt)
{
    auto        iter = find_if(m_MapMultiTex.begin(), m_MapMultiTex.end(), [&](auto& MyPair)->bool
        {
            if (pStateKey == MyPair.first)
                return true;

            return false;
        });

    if (iter == m_MapMultiTex.end())
        return nullptr;


    return iter->second[iCnt];
}

HRESULT CMultiTexture::Insert_Texture(const TCHAR* pFilePath, const TCHAR* pStateKey, const int& iCnt)
{

    // 경로를 의미는 길이는 절대 520byte를 넘어서면 안된다.
    TCHAR       szFullPath[MAX_PATH] = L"";


    for (int i = 0; i < iCnt; ++i)
    {
        swprintf_s(szFullPath, pFilePath, i);

        TEXINFO* pTexInfo = new TEXINFO;
        ZeroMemory(pTexInfo, sizeof(TEXINFO));

        // D3DXGetImageInfoFromFile : 지정한 이미지 파일에 관한 정보를 얻어와 구조체에 기록하는 함수
        if (FAILED(D3DXGetImageInfoFromFile(szFullPath, &(pTexInfo->tImgInfo))))
        {
            Safe_Delete(pTexInfo);
            AfxMessageBox(szFullPath);
            return E_FAIL;
        }

        if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(),
            szFullPath,
            pTexInfo->tImgInfo.Width,
            pTexInfo->tImgInfo.Height,
            pTexInfo->tImgInfo.MipLevels,
            0,  // USAGE : 텍스처의 사용 방식(0 일반적인 텍스처, D3DUSAGE_RENDERTARGET : 화면 그리기 텍스처)
            pTexInfo->tImgInfo.Format,
            D3DPOOL_MANAGED,
            D3DX_DEFAULT,
            D3DX_DEFAULT,
            0,              // 0을 넣어주면 컬러키 무효화
            nullptr,        // 이미지 정보 기록
            nullptr,        // 팔레트 이미지에 대한 처리
            &(pTexInfo->pTexture))))
        {
            Safe_Delete(pTexInfo);
            AfxMessageBox(L"D3DXCreateTextureFromFileEx Failed");
            return E_FAIL;
        }


        m_MapMultiTex[pStateKey].push_back(pTexInfo);
    }

    return S_OK;
}

void CMultiTexture::Release()
{
    for_each(m_MapMultiTex.begin(), m_MapMultiTex.end(), [](auto& MyPair)
    {
        for_each(MyPair.second.begin(), MyPair.second.end(),Safe_Delete<TEXINFO*>);
        MyPair.second.clear();
    });

    m_MapMultiTex.clear();
}

