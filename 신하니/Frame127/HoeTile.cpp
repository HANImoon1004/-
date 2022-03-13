#include "stdafx.h"
#include "HoeTile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

HoeTile::HoeTile()
{
}

HoeTile::~HoeTile()
{
	Release();
}

void HoeTile::Initialize(void)
{
	m_iOption = 0;
	m_iDrawID = 0;

	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
}

int HoeTile::Update(void)
{
	Update_Rect();


	return OBJ_NOEVENT;
}

void HoeTile::Late_Update(void)
{
}

void HoeTile::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"HoeTile");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		TILECX,
		TILECY,
		hMemDC,
		TILECX * m_iDrawID,
		TILECY * m_iOption,
		SRCCOPY);
}

void HoeTile::Release(void)
{
}
