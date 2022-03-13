#include "stdafx.h"
#include "BasicBlock.h"
#include "ScrollMgr.h"

CBasicBlock::CBasicBlock()
{
}


CBasicBlock::~CBasicBlock()
{
}

void CBasicBlock::Initialize(void)
{
}

int CBasicBlock::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBasicBlock::Late_Update(void)
{
}

void CBasicBlock::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	// 블록 색깔 회색으로 지정
	HBRUSH hBrush2 = CreateSolidBrush(RGB(73, 73, 73));
	//HBRUSH hBrush2 = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH oldBrush2 = (HBRUSH)SelectObject(hDC, hBrush2);
	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	SelectObject(hDC, oldBrush2);
	DeleteObject(hBrush2);
}

void CBasicBlock::Release(void)
{
}
