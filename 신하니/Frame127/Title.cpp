#include "stdafx.h"
#include "Title.h"
#include "BmpMgr.h"

CTitle::CTitle()
{
}

CTitle::~CTitle()
{
	Release();
}

void CTitle::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Title.bmp", L"Title_Logo");
	m_pImgKey = L"Title_Logo";

	m_tInfo.fCX = int(398 * 1.5f); //크기 늘림
	m_tInfo.fCY = int(187 * 1.5f);

	m_tInfo.fX = CENTERED(m_tInfo.fCX); //왼쪽 끝 위치... 중앙 정렬  어케 쉽게하죠 (WINCX-fCX)*0.5 
	m_tInfo.fY = WINCY * 0.1f; 

	m_tDraw.iCX = 398;
	m_tDraw.iCY = 187;
}


int CTitle::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CTitle::Late_Update(void)
{
}


void CTitle::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Title_Logo");
	GdiTransparentBlt(hDC, m_tInfo.fX, m_tInfo.fY, m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0,
		m_tDraw.iCX, m_tDraw.iCY, RGB(255, 255, 255));
}

void CTitle::Release()
{

}
