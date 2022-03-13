#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> Dest, list<CObj*> Sour);
	static void	Collision_RectEx(list<CObj*> Dest, list<CObj*> Sour);
	static void	Collision_Sphere(list<CObj*> Dest, list<CObj*> Sour);
	static bool Check_Sphere(CObj* pDest, CObj* pSour);
	static bool	Check_Rect(CObj* pDest, CObj* pSour, float* pfX, float* pfY);
};

