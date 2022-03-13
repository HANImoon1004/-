#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "ScrewBullet.h"
#include "Shield.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 1000.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 5.f;

	m_fDiagonal = 100.f;
	m_fJumpPower = 20.f;
	m_fJumpTime = 0.f;
	m_bJump = false;

	m_pFrameKey = L"Player_DOWN";
	m_eCurState=IDLE;
	m_ePreState=IDLE;
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameAnimation = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eGroup = RENDER_GAMEOBJECT;


	//파일 추가
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Success.wav", SOUND_EFFECT, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Temp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Body.bmp", L"Player_Body");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Hand.bmp", L"Player_Hand");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Hand2.bmp", L"Player_Hand2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/HairStyle.bmp", L"HairStyle");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/HairStyles_01.bmp", L"HairStyles_01");
	/*CBmpMgr::Get_Instance()->Insert_Bmp(TOP_IMG_LOC, TOP_IMG_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(BOT_IMG_LOC, BOT_IMG_KEY);
	CBmpMgr::Get_Instance()->Insert_Bmp(HAT_IMG_LOC, HAT_IMG_KEY);*/

	m_pImgKey = L"Player_Body";
	m_pHand00Key = L"Player_Hand";
	m_pHand01Key = L"Player_Hand";
	m_pHairKey = L"HairStyle";
	
}

int CPlayer::Update(void)
{
	Key_Input();

	//Jump();
	Offset();
	
	Move_Frame();
	Update_Rect();
	
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	// 중점 x에서 lineto를 하기 위해 포신의 끝 x좌표를 구하기 위해 cos 비례식을 활용하는 예
	// api에서 제공하는 삼각함수들을 각도값으로 라디안 값을 요구한다.
	
	//m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f)));
	//m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f)));

	Animation_Change();
}

void CPlayer::Render(HDC hDC)
{
	m_tInfo.iRX = int(m_tInfo.fCX);
	m_tInfo.iRY = int(m_tInfo.iRX * 2.f);

	//m_tDrawInfo.iCX = m_tInfo.fCX;
	//m_tDrawInfo.iCY = m_tInfo.fCY;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	
	HDC	hBodyDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_Body");

	//StretchBlt(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, 16, 32, hBodyDC, m_tFrame.iFrameStart * int(m_tInfo.fCX), m_tFrame.iFrameAnimation * int(m_tInfo.fCY), (int)m_tInfo.fCX, (int)m_tInfo.fCY, DSTINVERT);
		GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,							
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX+40,									
		(int)m_tInfo.fCY+50,
		hBodyDC,			// 현재 그리고자하는 비트맵 이미지 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),				// 7,8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),				// 7,8인자 : 비트맵을 출력할 시작 좌표int(m_tFrame.iFrameStart * m_tInfo.fCX),				// 7,8인자 : 비트맵을 출력할 시작 좌표
		(int)m_tInfo.fCX,	// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거하고자 하는 색상
	//}
	//GdiTransparentBlt(hDC,
	//	m_tRect.left + iScrollX,							
	//	m_tRect.top + iScrollY,
	//	(int)m_tInfo.fCX,									
	//	(int)m_tInfo.fCY,
	//	hBodyDC,			// 현재 그리고자하는 비트맵 이미지 DC
	//	m_tFrame.iFrameStart * int(m_tInfo.fCX),				// 7,8인자 : 비트맵을 출력할 시작 좌표
	//	m_tFrame.iFrameAnimation * int(m_tInfo.fCY),				// 7,8인자 : 비트맵을 출력할 시작 좌표int(m_tFrame.iFrameStart * m_tInfo.fCX),				// 7,8인자 : 비트맵을 출력할 시작 좌표
	//	(int)m_tInfo.fCX,	// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
	//	(int)m_tInfo.fCY,
	//	RGB(255, 255, 255));	// 제거하고자 하는 색상

	HDC	hHairDC = CBmpMgr::Get_Instance()->Find_Image(L"HairStyle");

	//switch (m_eCurState)
	//{
	//case IDLE:
	//	GdiTransparentBlt(hDC,
	//		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
	//		(int)m_tInfo.fCX + 30, (int)m_tInfo.fCY + 40,
	//		hHairDC, 4 * int(m_tInfo.fCX), 0 * int(m_tInfo.fCY),
	//		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//		RGB(255, 255, 255));	// 제거하고자 하는 색상
	//	break;

	//case WALK_RIGHT: IDLE_RIGHT : ATTACK:
	//	GdiTransparentBlt(hDC,
	//		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
	//		(int)m_tInfo.fCX + 30, (int)m_tInfo.fCY + 40,
	//		hHairDC, 4 * int(m_tInfo.fCX), 1 * int(m_tInfo.fCY),
	//		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//		RGB(255, 255, 255));	// 제거하고자 하는 색상
	//	break;

	//case IDLE_UP : WALK_UP :
	//	GdiTransparentBlt(hDC,
	//		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
	//		(int)m_tInfo.fCX + 30, (int)m_tInfo.fCY + 40,
	//		hHairDC, 4 * int(m_tInfo.fCX), 2 * int(m_tInfo.fCY),
	//		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//		RGB(255, 255, 255));	// 제거하고자 하는 색상
	//	break;

	//	
	//default:
	//	GdiTransparentBlt(hDC,
	//		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
	//		(int)m_tInfo.fCX + 30, (int)m_tInfo.fCY + 40,
	//		hHairDC, 4 * int(m_tInfo.fCX), 0 * int(m_tInfo.fCY),
	//		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//		RGB(255, 255, 255));	// 제거하고자 하는 색상

	//}
	//
	HDC	hHandDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_Hand");

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX+40,
		(int)m_tInfo.fCY+50,
		hHandDC,			// 현재 그리고자하는 비트맵 이미지 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),				// 7,8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),				// 7,8인자 : 비트맵을 출력할 시작 좌표int(m_tFrame.iFrameStart * m_tInfo.fCX),				// 7,8인자 : 비트맵을 출력할 시작 좌표
		(int)m_tInfo.fCX,	// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거하고자 하는 색상



}

void CPlayer::Release(void)
{
	
}

void CPlayer::Key_Input(void)
{
	float		fY = 0.f;

	if (GetAsyncKeyState('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"Player_LEFT";
		m_eCurState = WALK_LEFT;
	}

	else if (GetAsyncKeyState('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_RIGHT";
		m_eCurState = WALK_RIGHT;
	}

	else if (GetAsyncKeyState('W'))
	{
		m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_UP";
		m_eCurState = WALK_UP;
	}
	else if (GetAsyncKeyState('S'))
	{
		m_tInfo.fY += m_fSpeed;
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = WALK_DOWN;
	}

	else if (GetAsyncKeyState('E'))
	{
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = ATTACK;
	}

	else if (GetAsyncKeyState('R'))
	{
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = HIT;
	}

	/*else if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
	}*/

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Success.wav", SOUND_EFFECT, g_fSound);
		return;
	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		g_fSound -= 0.1f;

		if (g_fSound < 0.f)
			g_fSound = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		g_fSound += 0.1f;

		if (g_fSound > 1.f)
			g_fSound = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fSound);
	}

	
	else
		m_eCurState = IDLE;

}


void CPlayer::Offset(void)
{
	int iOffsetLeft = 300;
	int iOffsetRight = WINCX - iOffsetLeft;

	int iOffsetTop = 300;
	int iOffsetBottom = WINCY - iOffsetTop;

	// 좌우
	if (iOffsetLeft > CScrollMgr::Get_Instance()->Get_ScrollX() + m_tInfo.fX)
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffsetLeft - int(m_tInfo.fX));
	if (iOffsetRight < CScrollMgr::Get_Instance()->Get_ScrollX() + int(m_tInfo.fX))
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffsetRight - int(m_tInfo.fX));

	// 상하 
	if (iOffsetTop > CScrollMgr::Get_Instance()->Get_ScrollY() + m_tInfo.fY)
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffsetTop - int(m_tInfo.fY));
	if (iOffsetBottom < CScrollMgr::Get_Instance()->Get_ScrollY() + m_tInfo.fY)
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffsetBottom - int(m_tInfo.fY));

	CScrollMgr::Get_Instance()->Scroll_Lock();

	//int		iOffSetMaxX = (WINCX >> 1) + 200; //0308 hani 주석
	//int		iOffSetMinX = (WINCX >> 1) - 200;

	//int		iOffSetMaxY = (WINCY >> 1) + 200;
	//int		iOffSetMinY = (WINCY >> 1) - 200;

	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	//if (iOffSetMaxX > m_tInfo.fX + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	//if(iOffSetMinX < m_tInfo.fX + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//if (iOffSetMinY > m_tInfo.fY + iScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	//if (iOffSetMaxY < m_tInfo.fY + iScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

CObj* CPlayer::CreateBullet(float _fAngle)
{
	CObj*	 pBullet = CAbstractFactory<CGuideBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y);
	pBullet->Set_Angle(_fAngle);

	return pBullet;
}

CObj* CPlayer::CreateShield()
{
	CObj*		pShield = CAbstractFactory<CShield>::Create();

	pShield->Set_Target(this);

	return pShield;
}

void CPlayer::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tBody.tFrame;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();

			break;

		case WALK_DOWN:	
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case WALK_UP:
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameAnimation = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameAnimation = 8;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameAnimation = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
		
			break;
		}

		m_ePreState = m_eCurState;
	}

}
