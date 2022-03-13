#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_iOption = 0;
	m_iDrawID = 0;

	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
}

int CTile::Update(void)
{

	Update_Rect();


	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{

}

void CTile::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,			
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		TILECX,					
		TILECY,
		hMemDC,					
		TILECX * m_iDrawID,		
		0,
		SRCCOPY);

	//HDC hSheetDC = CBmpMgr::Get_Instance()->Find_Image(L"TileSheet");

	//BitBlt(hDC,
	//	m_tRect.left + iScrollX,
	//	m_tRect.top + iScrollY,
	//	TILECX,
	//	TILECY,
	//	hSheetDC,
	//	TILECX * m_iDrawID, //Ω√¿€ x¡¬«• 
	//	0,
	//	SRCCOPY);
}

void CTile::Release(void)
{

}
