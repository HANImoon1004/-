#pragma once
#include "Obj.h"
class CGUI :
    public CObj
{
public:
    CGUI();
    virtual ~CGUI();

public:
    // CObj��(��) ���� ��ӵ�
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;

protected:
    float m_fZorder;
};

