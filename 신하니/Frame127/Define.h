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

#define		TILEX			50 //0308 hani 30/20 �̰� 16/12�� �ϸ� �� ȭ�� �´� �����ۿ� ���� �ȵż� ��ũ���� �ȵ�
#define		TILEY			50

#define		CENTERED(fCX)		(WINCX - fCX)*0.5; //03.07 hani 

extern HWND		g_hWnd;

//typedef unsigned int        UINT;

// ����� ���ÿ� �ʱ�ȭ �Ұ���, ���� ����� ���������� �ڷ���, ��������� ��ġ�ϴ� ���¿����� ��� ����