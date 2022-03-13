// Frame127.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Frame127.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND	g_hWnd;


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance); // ������ â ��Ÿ���� �����ϴ� ��Ÿ��

BOOL                InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,		// ���� ����Ǿ��� �ν��Ͻ� �ڵ��� �Ѿ�´�. ���� ��� NULL
                     _In_ LPWSTR    lpCmdLine,				// TSTR : �����ڵ�, �ƽ�Ű�ڵ� ��� ȣȯ�ϴ� ������ TCHAR�� ���� STRING Ŭ������ �ǹ�, LP : �����͸� ����, LPTSTR : ���ڿ� �����͸� �ǹ�
                     _In_ int       nCmdShow)				// ��°� ���õ� �޼��� �Ű� ����		
{		
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAME127, szWindowClass, MAX_LOADSTRING);
    
	MyRegisterClass(hInstance);		// ���� ������(â)�� ����� ���� ������(â)�� ���� ������ ����ϴ� �Լ�

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAME127));

    MSG msg;
	msg.message = WM_NULL;


	CMainGame		MainGame;

	MainGame.Initialize();


    // �⺻ �޽��� �����Դϴ�.
   /* while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))		// �޴� ����� ����Ű�� ����� �۵��ϵ��� �˻��ϴ� �Լ�
        {
            TranslateMessage(&msg);		// Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ���ִ� �Լ�
            DispatchMessage(&msg);		// �ý��� �޼��� ť���� ���� �޼����� wndproc�� �����ϴ� �Լ�
        }
    }*/


	// GetTickCount() �Լ� : �ü���� �����ϱ� ������ �ķ� �帥 �ð��� ���� ���·� ��ȯ, �뷫 1 / 1000(�и� ������)

	DWORD	dwOldTime = GetTickCount();
	
	while (true)
	{
		// PM_REMOVE : �޽����� �о�Ȱ� ���ÿ� �޽��� ť���� ����
		// PM_NOREMOVE : �޽��� ť�� �޽����� �����ϴ� ���� �ľ�, �޽����� �о������ GetMessage�� �ٽ� ȣ������� ��
		
		// PeekMessage�� ����ϴ� ���� : ���ŷ ���¿� ������ ����. �о�� �޼����� ���� ��� false�� ����

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))		// �޴� ����� ����Ű�� ����� �۵��ϵ��� �˻��ϴ� �Լ�
			{
				TranslateMessage(&msg);		// Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ���ִ� �Լ�
				DispatchMessage(&msg);		// �ý��� �޼��� ť���� ���� �޼����� wndproc�� �����ϴ� �Լ�
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   RECT	rc{ 0, 0, WINCX, WINCY };

   // ���� â ������ = rc + �⺻ ������ â ��Ÿ�� + �޴��� ũ�� ��� ����
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, 
	   szTitle, 
	   WS_OVERLAPPEDWINDOW, // �⺻���� �ش��ϴ� ������ â ��Ÿ�Ϸ� ����
	   CW_USEDEFAULT, 0,	// ����ϰ����ϴ� â�� left, top ��ǥ
	   rc.right - rc.left, 
	   rc.bottom - rc.top,	// ����ϰ����ϴ� â�� ����, ���� ����
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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// �Լ� ȣ��Ծ�
//list<RECT>		BulletList;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//static	RECT	rc{ 100, 100, 200, 200 };

    switch (message)
    {
#pragma region 1���� ������ �ڵ�
		/*case WM_CREATE:		// ���� â�� ������ �� �߻��ϴ� �޼���

		SetTimer(hWnd, 0, 0, 0);	// Ÿ�̸Ӹ� ��ġ
		// 2���� : Ÿ�̸��� id ��ȣ, ���� ���� Ÿ�̸Ӱ� ������ �� �ֱ� ������ ��ȣ�� �ʿ�
		// 3���� : Ÿ�̸� �ֱ�, 0�� ��������� �⺻ ������ 1000�� 1���̴�.
		// 4���� : 0(null)�� ��� ������ �ֱ��� WM_TIMER �޼����� �߻���Ŵ

		break;

		case WM_TIMER:
		InvalidateRect(hWnd, 0, TRUE);

		// ������ â ���� ���� �Լ�
		// �� �Լ��� wm_paint �޽����� �߻�

		// 2���� : â �ȿ��� ���Ž�ų ����, ����(null�� ��� ��ü ����)
		// 3���� : true�� ��� �׷��� ���� �ʴ� �κе� ����, false �� ��� ���� �׸��� �κи� ����
		break;

		case WM_PAINT:
		{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

		// �簢�� �׸��� �Լ�
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

#pragma endregion 1���� ������ �ڵ�
	
		
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
