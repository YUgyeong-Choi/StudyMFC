#include "pch.h"
#include "CTerrain.h"
#include "CTextureMgr.h"

CTerrain::CTerrain()
{
	m_vecTile.reserve(TILEX * TILEY);
}

CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::Initialize()
{

	for (int i = 0; i < TILEX; ++i) {
		for (int j = 0; j < TILEY; ++j) {
			TILE* newTile = new TILE;
			newTile->vPos = D3DXVECTOR3((float)TILECX * j, (float)TILECY * i, 0.f);   // 기본 값으로 초기화
			newTile->vSize = D3DXVECTOR2((float)TILECX, (float)TILECY);         // 기본 값으로 초기화
			newTile->byOption = 0;  // 옵션 초기화
			newTile->byDrawID = 7;
			m_vecTile.push_back(newTile);


			TILE* newTile2 = new TILE;
			newTile2->vPos = D3DXVECTOR3((float)TILECX * j + (TILECX*0.5), (float)TILECY * i + (TILECY * 0.5), 0.f);   // 기본 값으로 초기화
			newTile2->vSize = D3DXVECTOR2((float)TILECX, (float)TILECY);         // 기본 값으로 초기화
			newTile2->byOption = 0;  // 옵션 초기화
			newTile2->byDrawID = 7;
			m_vecTile.push_back(newTile2);
		}
	}
}

void CTerrain::Update()
{
}

void CTerrain::Render(CDevice* _device)
{
	D3DXMATRIX	matWorld, matScale, matRotZ, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(45.f));

	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", 7);
	float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXVECTOR3	vTemp{ fCenterX, fCenterY, 0.f };

	for (size_t i = 0; i < m_vecTile.size(); ++i) {
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x, m_vecTile[i]->vPos.y, 0.f);
		matWorld = matScale * matTrans;
		_device->Get_Sprite()->SetTransform(&matWorld);
		_device->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &vTemp, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		TCHAR	szBuf[MIN_STR] = L"";
		int	iNumber = 1000;
		swprintf_s(szBuf, L"%d,%d", (int)m_vecTile[i]->vPos.x, (int)m_vecTile[i]->vPos.y);
		RECT rect = { -400, -300, 400, 300 };
		_device->Get_Font()->DrawTextW(_device->Get_Sprite(),
			szBuf,		// 출력할 문자열
			lstrlen(szBuf),  // 문자열 버퍼의 크기
			&rect,	// 출력할 렉트 위치
			DT_CENTER | DT_VCENTER,			// 정렬 기준(옵션)
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CTerrain::Release()
{
	for (size_t i = 0; i < m_vecTile.size(); ++i) {
		Safe_Delete<TILE*>(m_vecTile[i]);
	}
}
