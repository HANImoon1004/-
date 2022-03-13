#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO&			Get_Info(void) const {	return m_tInfo;	}
	const RECT&			Get_Rect(void) const { return m_tRect;  }
	void				Set_Dead() { m_bDead = true; }
	bool				Get_Dead(void) { return m_bDead; }

	void		Set_Pos(float _fX, float _fY) 
	{ 
		m_tInfo.fX = _fX; 
		m_tInfo.fY = _fY;
	}
	void		Set_Direction(DIRECTION eDir)	{	m_eDir = eDir;	}
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void		Set_Size(float _fCX, float _fCY) { m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY; }

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void		Set_FrameKey(TCHAR* _FrameKey) { m_pFrameKey = _FrameKey; }

	void		Set_DrawIDX(int _iDrawIDX) { m_iDrawIDX = _iDrawIDX; }
	void		Set_DrawIDY(int _iDrawIDY) { m_iDrawIDY = _iDrawIDY; }

	int			Get_DrawIDX() { return m_iDrawIDX; }
	int			Get_DrawIDY() { return m_iDrawIDY; }

	const RENDERID		Get_GroupID(void)const { return m_eGroup; }
	const	DRAW&				Get_Draw() const { return m_tDraw; }
	const TCHAR*			Get_ImgKey() const { return m_pImgKey; }
public:
	virtual		void	Initialize(void)	PURE;
	virtual		int	    Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);

protected:
	INFO				m_tInfo;
	RECT				m_tRect;
	FRAME				m_tFrame;
	DRAW				m_tDraw;

	float				m_fSpeed;
	bool				m_bDead;
	DIRECTION			m_eDir = DIR_END;
	float				m_fAngle;
	float				m_fDiagonal;

	CObj*				m_pTarget;

	TCHAR*				m_pFrameKey = L"";
	TCHAR*				m_pImgKey = L"";
	RENDERID			m_eGroup;

	int				m_iDrawIDX;
	int				m_iDrawIDY; //0310 hani 

	static		float	g_fSound;

};

