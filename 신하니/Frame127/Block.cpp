#include "stdafx.h"
#include "Block.h"
#include "ScrollMgr.h"

CBlock::CBlock()
{
}

CBlock::CBlock(INFO _tInfo)
{
}


CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
}

int CBlock::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlock::Late_Update(void)
{
}

void CBlock::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScLockY();
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	// 블록 색깔 회색으로 지정
	HBRUSH hBrush2 = CreateSolidBrush(RGB(73, 73, 73));
	//HBRUSH hBrush2 = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH oldBrush2 = (HBRUSH)SelectObject(hDC, hBrush2);
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
	SelectObject(hDC, oldBrush2);
	DeleteObject(hBrush2);
}

void CBlock::Release(void)
{
}
