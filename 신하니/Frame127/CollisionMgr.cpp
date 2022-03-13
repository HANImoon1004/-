#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};	

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				DestIter->Set_Dead();
				SourIter->Set_Dead();
			}
		}
	}

}


void CCollisionMgr::Collision_Sphere(list<CObj*> Dest, list<CObj*> Sour)
{
	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (Check_Sphere(DestIter, SourIter))
			{
				DestIter->Set_Dead();
				SourIter->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{

	float	fWidth  = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float* pfX, float* pfY)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fRadiusX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if (fRadiusX > fWidth && fRadiusY > fHeight)
	{
		*pfX = fRadiusX - fWidth;
		*pfY = fRadiusY - fHeight;

		return true;
	}

	return false;
}
void CCollisionMgr::Collision_RectEx(list<CObj*> Dest, list<CObj*> Sour)
{
	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(DestIter ,SourIter, &fX, &fY))
			{
				/*DestIter->Set_Dead();
				SourIter->Set_Dead();*/

				// 상, 하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (DestIter->Get_Info().fY < SourIter->Get_Info().fY)
					{
						DestIter->Set_PosY(-fY);
					}
					// 하 충돌
					else
					{
						DestIter->Set_PosY(fY);
					}
				}

				// 좌, 우 충돌
				else
				{
					// 좌 충돌
					if (DestIter->Get_Info().fX < SourIter->Get_Info().fX)
					{
						DestIter->Set_PosX(-fX);
					}
					// 우 충돌
					else
					{
						DestIter->Set_PosX(fX);
					}
				}
			}
		}
	}
}
