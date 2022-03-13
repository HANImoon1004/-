#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "SampleTile.h"
#include "ObjMgr.h"
#include "Player.h"
#include "HoeTile.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Picking_Tile(POINT pt, int iDrawID, int iOption)
{
	int	x = pt.x / TILECX;
	int	y = pt.y / TILECY;

	int	iIndex = y * TILEX + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);
}

void CTileMgr::Picking_SampleTile(POINT pt, int iDrawIDX, int iDrawIDY)
{
	//픽한 애의 DRAWID 받았어
	//또 마우스 클릭해! 그리고 거기 좌표 구해서 그 타일의 DRAWID 설정해

	POINT m_pt;
	GetCursorPos(&m_pt);

	int x = m_pt.x / TILECX;
	int y = m_pt.y / TILECY;

	int iIndex = y * TILEX + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex) //이 부분 뭘까!
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawIDX(iDrawIDX);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawIDY(iDrawIDY);



	//int iDrawIDX = dynamic_cast<SampleTile*>(m_vecSample[x * 3 + y])->Get_DrawIDX(); //마우스가 있는 곳의 타일 정보 가져옴
	//int iDrawIDY = dynamic_cast<SampleTile*>(m_vecSample[x * 3 + y])->Get_DrawIDY(); 

	//가져와서 그 타일을 어떻게 할거야~~~~~~~
	//마우스를 클릭하면 그 타일 정보로 적용되게
}

void CTileMgr::Paste_Tile(POINT pt, int iDrawIDX, int iDrawIDY)
{
	//Tile을 SampleTile로 . . . Tile  이미지 샘플타일 똑같이 넣고 생성할 때 iDrawIDX랑 y둘다 넣어서 생성하고
	//Tile 이미지의 idx idy 를 바꾼다
	//타일의 위치 정보 


}

void CTileMgr::Save_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int		iDrawID = 0, iOption = 0;
	DWORD	dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(iter)->Get_Option();

		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CTileMgr::Load_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Save2.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	INFO	tInfo{};
	int		iDrawID = 0, iOption = 0;
	DWORD	dwByte = 0;

	Release();		// 기존에 있던 타일 정보를 소멸하고 불러들이는 데이터로 재생성하기 위함

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pObj)->Set_Option(iOption);

		m_vecTile.push_back(pObj);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"Load", L"성공", MB_OK);
}

void CTileMgr::Initialize(void)
{
	/*for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = (float)(TILECX * j) + (TILECX >> 1);
			float fY = (float)(TILECY * i) + (TILECY >> 1);

			CObj*	pObj = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pObj);
		}
	}*/

	for (int i = 0; i < TILEY; ++i) //세로
	{
		for (int j = 0; j < TILEX; ++j) //가로
		{
			float fX = (float)(TILECX * j) + (TILECX >> 1); //타일의 중점X
			float fY = (float)(TILECY * i) + (TILECY >> 1); //타일의 중점Y

			CObj* pObj = CAbstractFactory<CTile>::Create(fX, fY, j, i); //중점 넣어서 타일 생성
			m_vecTile.push_back(pObj);
		}
	}

	for (int i = 0; i < 3; ++i) //샘플 세로
	{
		for (int j = 0; j < 3; ++j)
		{
			float fX = (float)(TILECX * 12 + TILECX * j) + (TILECX >> 1); //샘플타일 중점X 550부터
			float fY = (float)(TILECY * 8 + TILECY * i) + (TILECY >> 1);

			CObj* pObj = CAbstractFactory<SampleTile>::Create(fX, fY, j, i); //iDrawID까지 지정해서 생성
			m_vecSample.push_back(pObj);
		}
	}


	if (GetAsyncKeyState('E'))
	{
		int iX = int((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX) / TILECX) * TILECX;
		int iY = int((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY) / TILECX) * TILECX;

		switch (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Dir())
		{
		case CPlayer::PLAYERSTATE::IDLE_RIGHT:
			iX += TILECX;
			break;

		case CPlayer::PLAYERSTATE::IDLE_LEFT:
			iX -= TILECX;
			break;

		case CPlayer::PLAYERSTATE::IDLE_UP:
			iY -= TILECX;
			break;

		case CPlayer::PLAYERSTATE::IDLE:
			iY += TILECX;
			break;
		}
		CObj* pObj = CAbstractFactory<HoeTile>::Create(iX, iY);
		m_vecHoe.push_back(pObj);
	}
}

void CTileMgr::Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Update();

	for (auto& iter : m_vecSample)
		iter->Update();

	for (auto& iter : m_vecHoe)
		iter->Update();

	if (GetAsyncKeyState('E'))
	{
		int iX = int((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX) / TILECX) * TILECX;
		int iY = int((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY) / TILECX) * TILECX;

		switch (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Dir())
		{
		case CPlayer::PLAYERSTATE::IDLE_RIGHT:
			iX += TILECX;
			break;

		case CPlayer::PLAYERSTATE::IDLE_LEFT:
			iX -= TILECX;
			break;

		case CPlayer::PLAYERSTATE::IDLE_UP:
			iY -= TILECX;
			break;

		case CPlayer::PLAYERSTATE::IDLE:
			iY += TILECX;
			break;
		}
		CObj* pObj = CAbstractFactory<HoeTile>::Create(iX, iY);
		m_vecHoe.push_back(pObj);
	}
}

void CTileMgr::Late_Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();

	for (auto& iter : m_vecSample)
		iter->Late_Update();

	for (auto& iter : m_vecHoe)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{ //필요한 부분만 표시하게끔 한다. 
	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	int	iCullEndX = iCullX + (WINCX / TILECX) + 2;
	int	iCullEndY = iCullY + (WINCY / TILECY) + 2;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int	iIndex = i * TILECX + j;

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}

	/*for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int iIndex = i * 3 + j;

			if (0 > iIndex || m_vecSample.size() <= (size_t)iIndex)
				continue;

			m_vecSample[iIndex]->Render(hDC);
		}
	}*/

	for (auto& iter : m_vecSample)
		iter->Render(hDC);


	for (auto& iter : m_vecHoe)
		iter->Render(hDC);
}

void CTileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();

	for_each(m_vecSample.begin(), m_vecSample.end(), CDeleteObj());
	m_vecSample.clear();

	for_each(m_vecHoe.begin(), m_vecHoe.end(), CDeleteObj());
	m_vecHoe.clear();
}
