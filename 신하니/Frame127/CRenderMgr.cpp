#include "stdafx.h"
#include "CRenderMgr.h"
#include "BmpMgr.h"

CRenderMgr* CRenderMgr::m_pInstance = nullptr;

CRenderMgr::CRenderMgr()
{
}

CRenderMgr::~CRenderMgr()
{
	Release();
}

void CRenderMgr::Release()
{
	
}

void CRenderMgr::Render_Obj(HDC hDC, CObj* const& pObj)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(pObj->Get_ImgKey());

	//HDC hAlphaDC = CBmpMgr::Get_Instance()->Find_Image(L"Alpha");

	GdiTransparentBlt(hDC,
		pObj->Get_Info().fX,
		pObj->Get_Info().fY,
		int(pObj->Get_Info().fCX),
		int(pObj->Get_Info().fCY),
		hMemDC,
		pObj->Get_Draw().iCX * pObj->Get_Draw().iX,
		pObj->Get_Draw().iCY * pObj->Get_Draw().iY,
		pObj->Get_Draw().iCX,
		pObj->Get_Draw().iCY,
		RGB(255,255,255));
}
