#pragma once

#include "Include.h"

class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	void		Initialize();
	void		Update();
	void		Render();
	void		Release();
public:
	void	Tile_Change(const D3DXVECTOR3& vPos, const BYTE& byDrawID);

private:
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool	Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);
	int		Get_TileIdx(const D3DXVECTOR3& vPos);
private:
	vector<TILE*>		m_vecTile;
};

