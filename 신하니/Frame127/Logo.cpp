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

	// MCI(Meia Control Interface) : ��Ƽ �̵�� ��ġ�� ����ϰ� ���ҽ� ������ ����ϱ� ���� �������̽�
	// ����� �� ���� ���� ��ġ

	// MCIWndCreate : ��Ƽ�̵�� ����ϱ� ���� ������ â ���� �Լ�
	// 1. �θ��� �ڵ�
	// 2. mci �����츦 ����ϴ� �ν��Ͻ� �ڵ�
	// 3. ������ ��缳�� : WS_CHILD �ڽ��� ����, WS_VISIBLE �����츦 ������ ���� ȭ�鿡 ����Ѵ�. MCIWNDF_NOPLAYBAR �÷��� �� ���� ����
	// 4. ����� ������ ��� ����
	//m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Video/Wildlife.wmv");

	//// �������� ����� ũ�⸦ ����
	//// �������� ���� ��� ���� ũ���� ���
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
