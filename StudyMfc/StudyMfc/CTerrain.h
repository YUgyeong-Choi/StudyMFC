#pragma once

#include "Include.h"
#include "CDevice.h"

class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	void		Initialize();
	void		Update();
	void		Render(CDevice* _device);
	void		Release();
	void		ChangeTile(int x, int y);
private:
	vector<TILE*>		m_vecTile;
};

