#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }

	int			Get_DrawID() { return m_iDrawID; }
	int			Get_Option() { return m_iOption; }

public:
	virtual void Initialize(void) override;

	virtual int Update(void) override;

	virtual void Late_Update(void) override;

	virtual void Render(HDC hDC) override;

	virtual void Release(void) override;

private:
	int			m_iDrawID;
	int			m_iOption;
};

