#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount())
	, m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	
	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Set_Scene(SC_LOGO);
}

void CMainGame::Update(void)
{

	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render(void)
{
	if (SC_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	BitBlt(m_DC,			// 최종적으로 그릴 DC
		0, // 2, 3인자 : 복사받을 위치 좌표
		0,
		WINCX,	// 4,5인자 : 복사 받을 가로, 세로 길이
		WINCY,
		hBackDC,			// 현재 그리고자하는 비트맵 이미지 DC
		0,				// 7,8인자 : 비트맵을 출력할 시작 좌표
		0,
		SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hBackDC);


	// 프레임 출력
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		wsprintf(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release(void)
{
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();

	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
