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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Map_Farm.bmp", L"Map_Farm"); //앞에 /를 붙여야해요^^!03.07
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
	//	iScrollX,//화면에 표시할 X좌표 //0308여기서 시작해 
	//	iScrollY, //화면에 표시할 Y좌표
	//	1280,//화면에 표시할 가로길이
	//	1040, //화면에 표시할 세로길이
	//	hMemDC,//비트맵이 그려져 있는 메모리 DC
	//	0,//비트맵에서 복사를 시작할 X좌표
	//	0, //비트맵에서 복사를 시작할 Y좌표
	//	SRCCOPY);

	StretchBlt(hDC, iScrollX, iScrollY,
		SCROLL_LOCKX, SCROLL_LOCKY,
		hMemDC, 0, 0,
		1280, 1040, SRCCOPY);

	//StretchBlt(hDC, iScrollX, iScrollY, WINCX, WINCY, hMemDC, 0, 0, 1280, 1040, SRCCOPY);
	//2,3인자 : 도화지 어디부터 그릴꺼니
	//4,5인자 : 도화지 길이
	//7,8인자 : 어디부터 가져올거니(원래 크기)
	//9,10인자 : 복사할 영역 길이(원래 크기)
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
	// 플레이어
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
//	MessageBox(g_hWnd, _T("Load 성공"), _T("완료"), MB_OK);

}

void CFarm::Key_Input(void)
{
}
