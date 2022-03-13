#pragma once
#include "Obj.h"
class CRenderMgr
{
private:
	CRenderMgr();
	virtual ~CRenderMgr();

public:
	static	CRenderMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CRenderMgr;
			
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	void Release();

public:
	void Render_Obj(HDC hDC, CObj* const& pObj);

private:
		static CRenderMgr* m_pInstance;
};

