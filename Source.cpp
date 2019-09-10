//Headers
#include<Windows.h>
#include"Header.h"

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Win Main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdLine, int cmdShow)

{
	// variable declaration
	WNDCLASSEX wndClass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("MyApp");

	//Code
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE (MYICON));
	wndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE (100));

	// Register the class
	RegisterClassEx(&wndClass);

	// Create window
	hwnd = CreateWindow(szAppName, TEXT("My Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, cmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap;
	HDC hdc;
	HGDIOBJ hgd;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bitmap;
	HDC hmdc;
	//code
	switch (iMsg) 

	{

	case WM_CREATE:

		hBitmap = LoadBitmap(GetModuleHandle(NULL),MAKEINTATOM (MYBITMAP) );
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);

		hdc = BeginPaint(hwnd, &ps);
		hmdc = CreateCompatibleDC(NULL);
		SelectObject(hmdc, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		StretchBlt(hdc, rc.left | rc.top, rc.left | rc.top, rc.right | rc.top, rc.bottom | rc.right, hmdc, rc.left | rc.top, rc.left | rc.top, rc.right | rc.top, rc.bottom | rc.right, SRCCOPY );
		DeleteObject(hmdc);
		EndPaint(hwnd, &ps);
		break;

	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}