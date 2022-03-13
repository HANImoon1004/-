#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");

	// MCI(Meia Control Interface) : 멀티 미디어 장치를 재생하고 리소스 파일을 기록하기 위한 인터페이스
	// 오디오 및 비디오 제어 장치

	// MCIWndCreate : 멀티미디어 재생하기 위한 윈도우 창 생성 함수
	// 1. 부모의 핸들
	// 2. mci 윈도우를 사용하는 인스턴스 핸들
	// 3. 윈도우 모양설정 : WS_CHILD 자식의 형태, WS_VISIBLE 윈도우를 만들자 마자 화면에 출력한다. MCIWNDF_NOPLAYBAR 플레이 바 생성 안함
	// 4. 재생할 파일의 경로 전달
	//m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Video/Wildlife.wmv");

	//// 동영상을 재생할 크기를 설정
	//// 설정하지 않을 경우 원래 크기대로 출력
	//MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	//MCIWndPlay(m_hVideo);
}

int CLogo::Update(void)
{
	
	return 0;
}

void CLogo::Late_Update(void)
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo) ||		
		CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);
		return;
	}
}

void CLogo::Render(HDC hDC)
{
	/*HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	BitBlt(hDC,		
		0,			
		0,
		WINCX,		
		WINCY,
		hMemDC,		
		0,			
		0,
		SRCCOPY);*/
}

void CLogo::Release(void)
{
	MCIWndClose(m_hVideo);
}
