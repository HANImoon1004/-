#pragma once
#include "Scene.h"
class CFarm :
	public CScene
{
public:
	CFarm();
	virtual ~CFarm();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void Insert_Bmp(void);
	void Load_File(void);
private:
	void		Key_Input(void);
};

