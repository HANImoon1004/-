#pragma once

#include "Include.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "Shield.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);	// ������ �ʱ�ȭ�� ���� ����� �Լ�
	void		Update(void);		// �� �����Ӹ��� �����͸� �����ϴ� �Լ�
	void		Late_Update(void);	// ������Ʈ ������ ���� �ڿ� ȣ���Ͽ� �ϼ��� ��ü���� ������ �����ϰų� ���� ��ü ���¸� ǥ���ϱ� ���� ���� �Լ�
	void		Render(void);		// �� �����Ӹ��� ����ϴ� �Լ�
	void		Release(void);		// �����Ҵ��� �޸𸮸� �����ϴ� �Լ�

private:
	HDC			m_DC;
	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
};

// 1. ���α׷� ���� �� �ΰ� ȭ���� ���
// 2. ���͸� �Է��ϸ� ���������� �̵��ϴ� ���� �����ϱ�



