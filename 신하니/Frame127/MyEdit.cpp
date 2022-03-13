#include "stdafx.h"
#include "MyEdit.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"


CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/outdoorsTileSheet.bmp", L"SampleTile");

	CTileMgr::Get_Instance()->Initialize();
}

int CMyEdit::Update(void)
{
	Key_Input();
	CTileMgr::Get_Instance()->Update();

	return 0;
}

void CMyEdit::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	CTileMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release(void)
{
	CTileMgr::Get_Instance()->Destroy_Instance();
}

void CMyEdit::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		//CTileMgr::Get_Instance()->Picking_Tile(pt, 1, 0); //0310 hani

		int x = (pt.x -600)/ TILECX;
		int y = (pt.y - 400) / TILECY;

		//마우스가 있는 곳의 타일 정보 내놔 TileMgr이 갖고올 수 있어... TileMgr 
		//int iDrawIDX = dynamic_cast<SampleTile*>(m_vecSample[x * 3 + y])->Get_DrawIDX(); //마우스가 있는 곳의 타일 정보 가져옴
		//int iDrawIDY = dynamic_cast<SampleTile*>(m_vecSample[x * 3 + y])->Get_DrawIDY();

		int iDrawIDX = CTileMgr::Get_Instance()->Get_SampleTile(x, y*3)->Get_DrawIDX();
		int iDrawIDY = CTileMgr::Get_Instance()->Get_SampleTile(x, y*3)->Get_DrawIDY();

		if (CKeyMgr::Get_Instance()->Key_DdoDown(VK_LBUTTON)) //안되네 . . . 
		{
			CTileMgr::Get_Instance()->Picking_SampleTile(pt, iDrawIDX, iDrawIDY);
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		CTileMgr::Get_Instance()->Save_Tile();

/*
	if (CKeyMgr::Get_Instance()->Key_Down('L'))
		CTileMgr::Get_Instance()->Load_Tile();*/

}
