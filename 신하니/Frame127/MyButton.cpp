#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 74;
	m_tInfo.fCY = 58;

	m_eGroup = RENDER_UI;
}

int CMyButton::Update(void)
{	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!(lstrcmp(L"Start", m_pFrameKey)))
				CSceneMgr::Get_Instance()->Set_Scene(SC_FARM);

			else if (!(lstrcmp(L"Edit", m_pFrameKey)))
				CSceneMgr::Get_Instance()->Set_Scene(SC_EDIT);

			else if (!(lstrcmp(L"Exit", m_pFrameKey)))
				DestroyWindow(g_hWnd);

			return;
		}

		m_iDrawID = 1;
	}

	else
		m_iDrawID = 0;

}

void CMyButton::Render(HDC hDC)
{
	TCHAR szComName[255]; //hani 컴퓨터, 유저 이름
	TCHAR szUserName[255];
	TCHAR str[255];
	DWORD len;
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(g_hWnd, &ps);
	len = 255;
	GetComputerName(szComName, &len);
	len = 255;
	GetUserName(szUserName, &len);

	TextOut(hDC, 300, 300, szComName, NULL);


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,
		m_tRect.left ,		
		m_tRect.top,
		(int)m_tInfo.fCX,	
		(int)m_tInfo.fCY,
		hMemDC,				
		0,
		(int)m_tInfo.fCY * m_iDrawID,
		(int)m_tInfo.fCX,		
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));

		//HDC	hEditDC = CBmpMgr::Get_Instance()->Find_Image(L"Edit");

		//GdiTransparentBlt(hDC,
		//	m_tRect.left,
		//	m_tRect.top,
		//	(int)m_tInfo.fCX,
		//	(int)m_tInfo.fCY,
		//	hEditDC,
		//	(int)m_tInfo.fCX*1,
		//	(int)m_tInfo.fCY * m_iDrawID,
		//	(int)m_tInfo.fCX,
		//	(int)m_tInfo.fCY,
		//	RGB(255, 255, 255));

		//HDC	hExitDC = CBmpMgr::Get_Instance()->Find_Image(L"Exit");

		//GdiTransparentBlt(hDC,
		//	m_tRect.left,
		//	m_tRect.top,
		//	(int)m_tInfo.fCX,
		//	(int)m_tInfo.fCY,
		//	hExitDC,
		//	(int)m_tInfo.fCX * 2,
		//	(int)m_tInfo.fCY * m_iDrawID,
		//	(int)m_tInfo.fCX,
		//	(int)m_tInfo.fCY,
		//	RGB(255, 255, 255));
}

void CMyButton::Release(void)
{
	
}
