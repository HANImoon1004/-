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
	void		Initialize(void);	// 데이터 초기화를 위해 만드는 함수
	void		Update(void);		// 매 프레임마다 데이터를 갱신하는 함수
	void		Late_Update(void);	// 업데이트 연산이 끝난 뒤에 호출하여 완성된 객체들의 정보를 참조하거나 각종 객체 상태를 표현하기 위해 만든 함수
	void		Render(void);		// 매 프레임마다 출력하는 함수
	void		Release(void);		// 동적할당한 메모리를 해제하는 함수

private:
	HDC			m_DC;
	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
};

// 1. 프로그램 실행 시 로고 화면을 출력
// 2. 엔터를 입력하면 스테이지로 이동하는 상태 구현하기



