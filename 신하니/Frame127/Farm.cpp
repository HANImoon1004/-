#include "stdafx.h"
#include "Farm.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "BasicBlock.h"
CFarm::CFarm()
{
}


CFarm::~CFarm()
{
	Release();
}

void CFarm::Initialize(void)
{
	Insert_Bmp();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Map_Farm.bmp", L"Map_Farm"); //�տ� /�� �ٿ����ؿ�^^!03.07
	CScrollMgr::Get_Instance()->Set_ScLock_Pos(1280 << 1, 1040 << 1);

	//CTileMgr::Get_Instance()->Load_Tile();
	Load_File();
	CObj*		pObj = nullptr;

	pObj = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pObj);

	CTileMgr::Get_Instance()->Load_Tile();

	float fOffsetX = TILECX * 7.5f;
	float fOffsetY = TILECY * 14.5f;

	float fDistance = TILECX * 4.f;

	float fX = 0.f;
	float fY = 0.f;

	for (int iY = 0; iY < 8; ++iY)
	{
		for (int iX = 0; iX < 13; ++iX)
		{
			fX = fOffsetX + fDistance * iX + (rand() % 3) *  TILECX;
			fY = fOffsetY + fDistance * iY + (rand() % 3) *  TILECX;
	
		}
	}
	
	CTileMgr::Get_Instance()->Initialize();

}

int CFarm::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();

	return 0;
}

void CFarm::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	CTileMgr::Get_Instance()->Late_Update();

}

void CFarm::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Map_Farm");

	//BitBlt(hDC,
	//	iScrollX,//ȭ�鿡 ǥ���� X��ǥ //0308���⼭ ������ 
	//	iScrollY, //ȭ�鿡 ǥ���� Y��ǥ
	//	1280,//ȭ�鿡 ǥ���� ���α���
	//	1040, //ȭ�鿡 ǥ���� ���α���
	//	hMemDC,//��Ʈ���� �׷��� �ִ� �޸� DC
	//	0,//��Ʈ�ʿ��� ���縦 ������ X��ǥ
	//	0, //��Ʈ�ʿ��� ���縦 ������ Y��ǥ
	//	SRCCOPY);

	StretchBlt(hDC, iScrollX, iScrollY,
		SCROLL_LOCKX, SCROLL_LOCKY,
		hMemDC, 0, 0,
		1280, 1040, SRCCOPY);

	//StretchBlt(hDC, iScrollX, iScrollY, WINCX, WINCY, hMemDC, 0, 0, 1280, 1040, SRCCOPY);
	//2,3���� : ��ȭ�� ������ �׸�����
	//4,5���� : ��ȭ�� ����
	//7,8���� : ������ �����ðŴ�(���� ũ��)
	//9,10���� : ������ ���� ����(���� ũ��)
	CObjMgr::Get_Instance()->Render(hDC);
	CTileMgr::Get_Instance()->Render(hDC);


}

void CFarm::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CTileMgr::Get_Instance()->Destroy_Instance();

}

void CFarm::Insert_Bmp(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/hoeDirt.bmp", L"HoeTile");
	// �÷��̾�
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/outdoorsTileSheet.bmp", L"TileSheet");*/
}

void CFarm::Load_File(void)
{
	HANDLE hFile = CreateFile(L"../Data/Save2.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD dwByte = 0;
	FILEOBJ tFileObj{};

	while (true)
	{
		ReadFile(hFile, &tFileObj, sizeof(FILEOBJ), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		if (tFileObj.eID == OBJ_BLOCK)
		{
			if (tFileObj.eBlockType == BASIC_BLOCK)
			{
				CObj* pBlock = nullptr;
				pBlock = CAbstractFactory<CBasicBlock>::Create(tFileObj.tInfo.fX, tFileObj.tInfo.fY);
				pBlock->Set_Size(fabs(tFileObj.tInfo.fCX), fabs(tFileObj.tInfo.fCY));
				dynamic_cast<CBlock*>(pBlock)->Set_Type(BASIC_BLOCK);
				CObjMgr::Get_Instance()->AddObject(OBJ_BLOCK, pBlock);
			}
		}		
	}
	CloseHandle(hFile);
//	MessageBox(g_hWnd, _T("Load ����"), _T("�Ϸ�"), MB_OK);

}

void CFarm::Key_Input(void)
{
}
