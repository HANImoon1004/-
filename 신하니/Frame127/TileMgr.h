#pragma once

#include "Tile.h"


class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void		Picking_Tile(POINT pt, int iDrawID, int iOption);
	void		Picking_SampleTile(POINT pt, int iDrawIDX, int iDrawIDY);
	void		Paste_Tile(POINT pt, int iDrawIDX, int iDrawIDY);

	CObj*	Get_SampleTile(int x, int y) { return m_vecSample[x + y]; }
	CObj*	Get_Tile(int x, int y) { return m_vecTile[x + y]; }

	void		Save_Tile(void);
	void		Load_Tile(void);

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	static	CTileMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CTileMgr;
		}

		return m_pInstance;
	}
	static	void		Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CTileMgr*			m_pInstance;
	vector<CObj*>				m_vecTile;
	vector<CObj*>				m_vecSample;
	vector<CObj*>				m_vecHoe;

};

