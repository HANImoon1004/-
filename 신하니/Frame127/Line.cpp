#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}

CLine::CLine(LINEINFO & tInfo)
	: m_tInfo(tInfo)
{
}


CLine::CLine(LINEPOS& tLPoint, LINEPOS& tRPoint)
	: m_tInfo(tLPoint, tRPoint)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	MoveToEx(hDC, (int)m_tInfo.tLeftPoint.fX + iScrollX, (int)m_tInfo.tLeftPoint.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRightPoint.fX + iScrollX, (int)m_tInfo.tRightPoint.fY);
}
