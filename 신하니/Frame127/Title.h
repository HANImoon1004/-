#pragma once
#include "Obj.h"
class CTitle :
    public CObj
{
public:
    CTitle();
    virtual ~CTitle();

public:

public:
    virtual void Initialize() override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

};

