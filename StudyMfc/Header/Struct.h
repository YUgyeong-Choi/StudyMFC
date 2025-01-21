#pragma once

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // 컴 객체 (텍스처를 다루기 위한 COM 인터페이스 타입)

	D3DXIMAGE_INFO			tImgInfo;	// 구조체

}TEXINFO;