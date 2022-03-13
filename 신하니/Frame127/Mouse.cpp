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

	GetCursorPos(&pt);		// ���� ���콺�� ��ġ ������ ������ �Լ�
	ScreenToClient(g_hWnd, &pt);	// ��ũ�� ������ ���콺 ��ǥ�� �츮�� ������ ������ â ��ǥ�� �������ִ� �Լ�

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
