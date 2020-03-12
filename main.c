// 7 SEGMENT COUNTER PROJECT
// by Ozgur GUNES
// mail: gunes.ozgr@gmail.com

// file name: main.c

#include "Counter.h"

int posX = 15;
int posY = 15;

const UINT timerID_1 = 1;
UINT timerDelay = 1000;

UINT counter = 0;

LRESULT CALLBACK WndProc(	HWND hwnd,
				UINT Message,
				WPARAM wParam,
				LPARAM lParam)
{
	switch(Message) {

		case WM_CREATE:

			hbmSgmBlue = LoadBitmap(Wnd_hInst, "SGM_BLUE_BMP");

			hbmSgmMask0 = LoadBitmap(Wnd_hInst, "SGM_MASK0_BMP");
			hbmSgmMask1 = LoadBitmap(Wnd_hInst, "SGM_MASK1_BMP");
			hbmSgmMask2 = LoadBitmap(Wnd_hInst, "SGM_MASK2_BMP");
			hbmSgmMask3 = LoadBitmap(Wnd_hInst, "SGM_MASK3_BMP");
			hbmSgmMask4 = LoadBitmap(Wnd_hInst, "SGM_MASK4_BMP");
			hbmSgmMask5 = LoadBitmap(Wnd_hInst, "SGM_MASK5_BMP");
			hbmSgmMask6 = LoadBitmap(Wnd_hInst, "SGM_MASK6_BMP");
			hbmSgmMask7 = LoadBitmap(Wnd_hInst, "SGM_MASK7_BMP");
			hbmSgmMask8 = LoadBitmap(Wnd_hInst, "SGM_MASK8_BMP");
			hbmSgmMask9 = LoadBitmap(Wnd_hInst, "SGM_MASK9_BMP");

			if(	!hbmSgmBlue
				|| !hbmSgmMask0
				|| !hbmSgmMask1
				|| !hbmSgmMask2
				|| !hbmSgmMask3
				|| !hbmSgmMask4
				|| !hbmSgmMask5
				|| !hbmSgmMask6
				|| !hbmSgmMask7
				|| !hbmSgmMask8
				|| !hbmSgmMask9 ) {

				MessageBox(	hwnd,
						"Load of resources failed.",
						"Error",
						MB_OK | MB_ICONEXCLAMATION );
				return -1;
			}

			GetObject(hbmSgmMask0, sizeof(bm0), &bm0);
			SetTimer(hwnd, timerID_1, timerDelay, NULL);

			break;

		case WM_PAINT:

			if(	hbmSgmBlue
				&& hbmSgmMask0
				&& hbmSgmMask1
				&& hbmSgmMask2
				&& hbmSgmMask3
				&& hbmSgmMask4
				&& hbmSgmMask5
				&& hbmSgmMask6
				&& hbmSgmMask7
				&& hbmSgmMask8
				&& hbmSgmMask9 ) {

				PAINTSTRUCT ps;
            			HDC hdcWindow;
            			hdcWindow = BeginPaint(hwnd, &ps);

				DrawDigit(hdcWindow, 3, posX, posY);

				EndPaint(hwnd, &ps);
			}

			break;

		case WM_TIMER:

			UpdateDigit(hwnd, posX, posY, (counter%10));
			counter++;
			break;

		case WM_DESTROY:

			KillTimer(hwnd, timerID_1);

			DeleteObject(hbmSgmBlue);
			DeleteObject(hbmSgmMask0);
			DeleteObject(hbmSgmMask1);
			DeleteObject(hbmSgmMask2);
			DeleteObject(hbmSgmMask3);
			DeleteObject(hbmSgmMask4);
			DeleteObject(hbmSgmMask5);
			DeleteObject(hbmSgmMask6);
			DeleteObject(hbmSgmMask7);
			DeleteObject(hbmSgmMask8);
			DeleteObject(hbmSgmMask9);

			PostQuitMessage(0);
			break;

		default: return DefWindowProc(hwnd, Message, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(	HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPSTR lpCmdLine,
			int nCmdShow )
{
	WNDCLASSEX WndClass;
	HWND Hwnd;
	MSG Msg;

	Wnd_hInst = hInstance;

	WndClass.cbSize        = sizeof(WNDCLASSEX);
	WndClass.style         = 0;
	WndClass.lpfnWndProc   = WndProc;
	WndClass.cbClsExtra    = 0;
	WndClass.cbWndExtra    = 0;
	WndClass.hInstance     = Wnd_hInst;
	WndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = Wnd_bg;
	WndClass.lpszMenuName  = NULL;
	WndClass.lpszClassName = Wnd_szClassName;
	WndClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass)) {

		MessageBox(0, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
		return 0;
	}

	Hwnd = CreateWindowEx(	WS_EX_CLIENTEDGE,
				Wnd_szClassName,
				"Counter",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				320, 240,
				NULL, NULL, Wnd_hInst, NULL);

	if(Hwnd == NULL) {
      
		MessageBox(	0,
				"Window Creation Failed!",
				"Error!",
				MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
		return 0;
	}

	ShowWindow(Hwnd, nCmdShow);
	UpdateWindow(Hwnd);

	while(GetMessage(&Msg, NULL, 0, 0)) {
      
	TranslateMessage(&Msg);
	DispatchMessage(&Msg);
	}

	return Msg.wParam;
}