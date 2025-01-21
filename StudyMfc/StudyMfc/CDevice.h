#pragma once
#include "Include.h"

class CDevice
{
	DECLARE_SINGLETON(CDevice)  //싱글톤 만드는 법
public:
	CDevice();
	~CDevice();
public:
	LPDIRECT3DDEVICE9			Get_Device() { return m_pDevice; }
	LPD3DXSPRITE				Get_Sprite() { return m_pSprite; }

public:
	HRESULT		Init_Device();

	void		Render_Begin();
	void		Render_End(HWND hWnd = nullptr);

	void		Release();

private:
	void		Set_Parameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9			m_pSDK;		// 1번에 해당하는 객체
	LPDIRECT3DDEVICE9	m_pDevice;	// 3번에 해당하는 객체

	LPD3DXSPRITE		m_pSprite;	// 2d 이미지를 출력하기 위한 용도
};

