#pragma once
#include "Obj.h"
class CBlock :
	public CObj
{
public:
	CBlock();
	CBlock(INFO _tInfo);
	virtual ~CBlock();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

	BLOCK_TYPE Get_Type(void) { return m_eType; }
	void Set_Type(BLOCK_TYPE _BlockType) { m_eType = _BlockType; }

protected:
	BLOCK_TYPE		m_eType;
};

