#pragma once


#define		WINCX		800
#define		WINCY		600
#define		PI			3.14f
#define		PURE		= 0 

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		VK_MAX			0xff


#define		SAFE_DELETE(p)	if(p) { delete p; p = nullptr;}

#define		TILECX			50
#define		TILECY			50 //0308 hani 64

#define		TILEX			50 //0308 hani 30/20 이거 16/12로 하면 딱 화면 맞는 갯수밖에 생성 안돼서 스크롤이 안됨
#define		TILEY			50

#define		CENTERED(fCX)		(WINCX - fCX)*0.5; //03.07 hani 

extern HWND		g_hWnd;

//typedef unsigned int        UINT;

// 선언과 동시에 초기화 불가능, 먼저 선언된 전역변수와 자료형, 변수명까지 일치하는 상태에서만 사용 가능