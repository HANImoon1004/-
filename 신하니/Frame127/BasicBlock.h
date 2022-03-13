#pragma once
#include "Block.h"
class CBasicBlock :
	public CBlock
{
public:
	CBasicBlock();
	virtual ~CBasicBlock();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;
};

