#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
}

int CMouse::Update(void)
{
	POINT	pt{};

	GetCursorPos(&pt);		// 현재 마우스의 위치 정보를 얻어오는 함수
	ScreenToClient(g_hWnd, &pt);	// 스크린 상태의 마우스 좌표를 우리가 생성한 윈도우 창 좌표로 변경해주는 함수

	m_tInfo.fX = float(pt.x);
	m_tInfo.fY = float(pt.y);

	Update_Rect();
	ShowCursor(false);

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
	
}

void CMouse::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release(void)
{
	
}
