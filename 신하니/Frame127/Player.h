#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	enum PLAYERSTATE { IDLE, IDLE_RIGHT, IDLE_LEFT, IDLE_UP, WALK_DOWN, WALK_RIGHT,  WALK_LEFT, 
		WALK_UP, ATTACK, HIT, DEAD, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Set_Bullet(list<CObj*>* pBullet){ m_pBullet = pBullet;	}
	void		Set_Shield(list<CObj*>* pShield) { m_pShield = pShield; }
	PLAYERSTATE Get_Dir() { return m_eCurState; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void	Late_Update(void)	override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Key_Input(void);
	//void	Jump(void);
	void	Offset(void);
	CObj*	CreateBullet(float _fAngle);
	CObj*	CreateShield();
	void	Animation_Change(void);

private:
	list<CObj*>*			m_pBullet = nullptr;
	list<CObj*>*			m_pShield = nullptr;
	POINT					m_tPosin;


	bool					m_bJump; // 점프 상태 확인
	float					m_fJumpPower; 
	float					m_fJumpTime;

	PLAYERSTATE				m_ePreState;
	PLAYERSTATE				m_eCurState;

private:
	TCHAR*		m_pImgKey;
	
	TCHAR*		m_pHand00Key;
	TCHAR*		m_pHand01Key;
	
	TCHAR*		m_pHairKey;
	
	TCHAR*		m_pHeadKey;
	TCHAR*		m_pTopKey;
	TCHAR*		m_pBottomKey;
	TCHAR*		m_pShoesKey;

	bool		m_bRenverse;

	tagBodyInfo	m_tBody;
	tagHairInfo m_tHair;
	tagHandsInfo m_tHands;
	tagShirtInfo m_tShirt;
};

