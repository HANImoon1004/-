#pragma once
#include "Obj.h"
class CScrewBullet :
	public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:

	POINT		m_tCenter;		// 공전을 할 중심 
	float		m_fRotAngle;	// 공전을 수행할 각도
	float		m_fRotSpeed;	// 프레임마다 각도 값을 증가시키기 위한 상수
	float		m_fRotDistance;	// 중점으로부터 거리값

	bool		m_bStart;

};

