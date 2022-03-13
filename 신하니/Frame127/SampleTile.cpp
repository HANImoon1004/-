#include "stdafx.h"
#include "SampleTile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

SampleTile::SampleTile()
{
}

SampleTile::~SampleTile()
{
	Release();
}

void SampleTile::Initialize(void)
{
	m_iOption = 0;
	m_iDrawID = 0;

	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
}

int SampleTile::Update(void)
{

	Update_Rect();


	return OBJ_NOEVENT;
}

void SampleTile::Late_Update(void)
{
}

void SampleTile::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SampleTile");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		TILECX,
		TILECY,
		hMemDC,
		TILECX * m_iDrawIDX,
		TILECY * m_iDrawIDY,
		SRCCOPY);
}

void SampleTile::Release(void)
{
}
