#include "resource.h"

//-------------------------------------------------->>
void sec_wm_create(HWND hwnd) {
	RECT rd;
	GetWindowRect(GetDesktopWindow(), &rd);
	MoveWindow(hwnd, rd.right/2 - 100, rd.bottom/2 - 60, 200, 120, TRUE);
}
//-------------------------------------------------->>
void sec_wm_paint(HWND hwnd) {
	PAINTSTRUCT PaintStruct;
	HFONT hFontA, hFontB, hFontC;
	HDC hdcWindow;
	RECT rc;
	
	hdcWindow = BeginPaint(hwnd, &PaintStruct);
	
	hFontA = CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Verdana");
	hFontB = CreateFont(23, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Candara");
	hFontC = CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Verdana");
	
	SetBkMode(hdcWindow, TRANSPARENT);
	
	SetTextColor(hdcWindow, BLACK_BRUSH);
	SelectObject(hdcWindow, hFontA);
	SetRect(&rc, 0, 10, 200, 120);
	DrawText(hdcWindow, PROJECT_TITLE, -1, &rc, DT_TOP | DT_CENTER | DT_SINGLELINE);
	
	SetTextColor(hdcWindow, BLACK_BRUSH);
	SelectObject(hdcWindow, hFontB);
	SetRect(&rc, 0, 0, 200, 110);
	DrawText(hdcWindow, "... Carregando ...", -1, &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	
	SetTextColor(hdcWindow, RGB(100, 100, 100));
	SelectObject(hdcWindow, hFontC);
	SetRect(&rc, 0, 0, 200, 100);
	DrawText(hdcWindow, AUTHOR, -1, &rc, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
	
	EndPaint(hwnd, &PaintStruct);
	DeleteObject(hFontA);
	DeleteObject(hFontB);
	DeleteObject(hFontC);
}
//-------------------------------------------------->>
LRESULT CALLBACK SecProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			sec_wm_create(hwnd);
			break;
		
		case WM_PAINT:
			sec_wm_paint(hwnd);
			break;
		
		case WM_CLOSE:
			return 0;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





