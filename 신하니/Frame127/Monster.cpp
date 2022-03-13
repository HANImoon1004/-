#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"


CMonster::CMonster()
{
	ZeroMemory(m_tPoint, sizeof(m_tPoint));
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Plg.bmp",	 L"Rotation");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Reset.bmp",	 L"Reset");

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 200.f;

	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_pFrameKey = L"Monster";

	m_fSpeed = 3.f;

	m_eGroup = RENDER_GAMEOBJECT;	

}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	float	fDiagonal = sqrtf((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) + (m_tInfo.fCY / 2.f) * (m_tInfo.fCY / 2.f));

	//�� ���
	m_tPoint[0].x = long((m_tInfo.fCX / 2.f) + cosf((m_fAngle + 135.f) * (PI / 180.f)) * fDiagonal);
	m_tPoint[0].y = long((m_tInfo.fCY / 2.f) - sinf((m_fAngle + 135.f) * (PI / 180.f)) * fDiagonal);

	//�� ���
	m_tPoint[1].x = long((m_tInfo.fCX / 2.f) + cosf((m_fAngle + 45.f) * (PI / 180.f)) * fDiagonal);
	m_tPoint[1].y = long((m_tInfo.fCY / 2.f) - sinf((m_fAngle + 45.f) * (PI / 180.f)) * fDiagonal);

	//�� �ϴ�
	m_tPoint[2].x = long((m_tInfo.fCX / 2.f) + cosf((m_fAngle + 225.f) * (PI / 180.f)) * fDiagonal);
	m_tPoint[2].y = long((m_tInfo.fCY / 2.f) - sinf((m_fAngle + 225.f) * (PI / 180.f)) * fDiagonal);
	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		m_fAngle -= 5.f;

	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	
}

void CMonster::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC	hRotaionDC = CBmpMgr::Get_Instance()->Find_Image(L"Rotation");
	HDC	hResetDC = CBmpMgr::Get_Instance()->Find_Image(L"Reset");

	PlgBlt(hRotaionDC,		// ȸ�� ��ų �̹����� ��� �׸� ���ΰ�
		m_tPoint,			// �׸��� �׸� �簢�� ��ǥ ����Ʈ �迭�� �̸�(������ �� ���, �� ���, �� �ϴ�)
		hMemDC,				// ��� �ִ� �̹����� ȸ����Ų �̹��� DC�� �׸� ���ΰ�
		0,					// 4,5 ���� : �׸��� �׸� �̹����� X,Y ���� ��ǥ
		0,
		(int)m_tInfo.fCX,	// 6,7 ���� : �̹����� ����, ���� ����
		(int)m_tInfo.fCY,
		NULL,
		NULL,
		NULL);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hRotaionDC,				// ���� ���� ���� ���� ȸ���� ����� �̹��� DC�� �־��ְ� ����
		m_tFrame.iFrameStart * int(m_tInfo.fCX),			
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),		
		(int)m_tInfo.fCX,	
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	

	BitBlt(hRotaionDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hResetDC, 0, 0, SRCCOPY);
}

void CMonster::Release(void)
{
	
}
