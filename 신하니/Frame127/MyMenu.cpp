#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CMyMenu::CMyMenu()
{
}

CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	m_Title.Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Start2.bmp", L"Start2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Exit.bmp", L"Exit");


	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");*/

	//CSoundMgr::Get_Instance()->PlaySound(L"Success.wav", SOUND_EFFECT, g_fSound); //0308 hani


	CObj* pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(300.f, 400.f);
	pObj->Set_FrameKey(L"Start2");
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(500.f, 400.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

	//CObj* pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f);
	//pObj->Set_FrameKey(L"Start");
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

	//pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f);
	//pObj->Set_FrameKey(L"Edit");
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

	//pObj = CAbstractFactory<CMyButton>::Create(600.f, 400.f);
	//pObj->Set_FrameKey(L"Exit");
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

}

int CMyMenu::Update(void)
{
	m_Title.Update();
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu"); //�޴� ����̹���
	//
	//BitBlt(hDC,
	//	0,
	//	0,
	//	WINCX,
	//	WINCY,
	//	hMemDC,
	//	0,
	//	0,
	//	SRCCOPY);

	StretchBlt(

		hDC, 0, 0, // �׸����� �ϴ� ���� ��ǥ

		WINCX, WINCY, // ����� �̹����� �ʺ�, ����

		hMemDC, 0, 0, // ������ �̹����� �������� ��ǥ, �̹����� �ڸ��� ���

		640, 400, //���� �̹��� ������

		SRCCOPY

	);

	CObjMgr::Get_Instance()->Render(hDC);

	m_Title.Render(hDC);
}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);
}
