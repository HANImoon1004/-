// Frame127.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Frame127.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance); // 윈도우 창 스타일을 지정하는 스타일

BOOL                InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,		// 전에 실행되었던 인스턴스 핸들이 넘어온다. 없을 경우 NULL
                     _In_ LPWSTR    lpCmdLine,				// TSTR : 유니코드, 아스키코드 모두 호환하는 윈도우 TCHAR로 만든 STRING 클래스를 의미, LP : 포인터를 뜻함, LPTSTR : 문자열 포인터를 의미
                     _In_ int       nCmdShow)				// 출력과 관련된 메세지 매개 변수		
{		
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAME127, szWindowClass, MAX_LOADSTRING);
    
	MyRegisterClass(hInstance);		// 현재 윈도우(창)을 만들기 위해 윈도우(창)에 대한 설정을 기록하는 함수

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAME127));

    MSG msg;
	msg.message = WM_NULL;


	CMainGame		MainGame;

	MainGame.Initialize();


    // 기본 메시지 루프입니다.
   /* while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))		// 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
        {
            TranslateMessage(&msg);		// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 해주는 함수
            DispatchMessage(&msg);		// 시스템 메세지 큐에서 꺼낸 메세지를 wndproc로 전달하는 함수
        }
    }*/


	// GetTickCount() 함수 : 운영체제가 구동하기 시작한 후로 흐른 시간을 정수 형태로 반환, 대략 1 / 1000(밀리 세컨드)

	DWORD	dwOldTime = GetTickCount();
	
	while (true)
	{
		// PM_REMOVE : 메시지를 읽어옴과 동시에 메시지 큐에서 제거
		// PM_NOREMOVE : 메시지 큐에 메시지가 존재하는 지만 파악, 메시지를 읽어오려면 GetMessage를 다시 호출해줘야 함
		
		// PeekMessage를 사용하는 이유 : 블로킹 상태에 빠지질 않음. 읽어올 메세지가 없을 경우 false를 리턴

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))		// 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
			{
				TranslateMessage(&msg);		// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 해주는 함수
				DispatchMessage(&msg);		// 시스템 메세지 큐에서 꺼낸 메세지를 wndproc로 전달하는 함수
			}
		}

		else
		{
			if (dwOldTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();

				dwOldTime = GetTickCount();
			}		
		}		
	}

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAME127));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; // MAKEINTRESOURCEW(IDC_FRAME127);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT	rc{ 0, 0, WINCX, WINCY };

   // 최종 창 사이즈 = rc + 기본 윈도우 창 스타일 + 메뉴바 크기 고려 여부
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, 
	   szTitle, 
	   WS_OVERLAPPEDWINDOW, // 기본값에 해당하는 윈도우 창 스타일로 생성
	   CW_USEDEFAULT, 0,	// 출력하고자하는 창의 left, top 좌표
	   rc.right - rc.left, 
	   rc.bottom - rc.top,	// 출력하고자하는 창의 가로, 세로 길이
	   nullptr, 
	   nullptr, 
	   hInstance,
	   nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 함수 호출규약
//list<RECT>		BulletList;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//static	RECT	rc{ 100, 100, 200, 200 };

    switch (message)
    {
#pragma region 1일차 복습용 코드
		/*case WM_CREATE:		// 최초 창이 생성될 때 발생하는 메세지

		SetTimer(hWnd, 0, 0, 0);	// 타이머를 설치
		// 2인자 : 타이머의 id 번호, 여러 개의 타이머가 존재할 수 있기 때문에 번호가 필요
		// 3인자 : 타이머 주기, 0을 집어넣으면 기본 값으로 1000당 1초이다.
		// 4인자 : 0(null)인 경우 설정한 주기대로 WM_TIMER 메세지를 발생시킴

		break;

		case WM_TIMER:
		InvalidateRect(hWnd, 0, TRUE);

		// 윈도우 창 정보 갱신 함수
		// 이 함수가 wm_paint 메시지가 발생

		// 2인자 : 창 안에서 갱신시킬 영역, 범위(null인 경우 전체 영역)
		// 3인자 : true인 경우 그려져 있지 않는 부분도 갱신, false 인 경우 새로 그리는 부분만 갱신
		break;

		case WM_PAINT:
		{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

		// 사각형 그리기 함수
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		for (auto& iter : BulletList)
		{
		Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

		iter.top -= 10;
		iter.bottom -= 10;
		}


		EndPaint(hWnd, &ps);
		}
		break;
		
		case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;

		case VK_LEFT:

			rc.left -= 10;
			rc.right -= 10;

			break;

		case VK_RIGHT:

			rc.left += 10;
			rc.right += 10;

			break;

		case VK_UP:
			rc.top -= 10;
			rc.bottom -= 10;
			break;

		case VK_DOWN:
			rc.top += 10;
			rc.bottom += 10;
			break;

		case VK_SPACE:
			BulletList.push_back(rc);
			break;

		}
		break;
		
		*/

#pragma endregion 1일차 복습용 코드
	
		
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;	

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(g_hWnd);
			break;		
		}
		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
