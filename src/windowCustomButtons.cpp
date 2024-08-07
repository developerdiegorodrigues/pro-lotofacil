#include "resource.h"

extern INT intMainTimerId;
BOOL bWindowStatus = false;
BOOL bObjStatus = false;
//-------------------------------------------------->>
void obj_wm_mousemove(HWND hwnd, INT obj) {
	RECT rc;
	HBRUSH hBrush;
	
	bObjStatus = true;
	GetClientRect(hwnd, &rc);
	
	switch (obj) {
		case 1:
			hBrush = CreateSolidBrush(COLOR_MIN_ACTIVE);
			break;
		
		case 2:
			hBrush = CreateSolidBrush(COLOR_MAX_ACTIVE);
			break;
		
		case 3:
			hBrush = CreateSolidBrush(COLOR_CLOSE_ACTIVE);
			break;
	}
	
	FillRect(GetDC(hwnd), &rc, hBrush);
	DeleteObject(hBrush);
	SetTimer(hwnd, TIMER_OBJ_ID, TIMER_OBJ_ELAPSE, NULL);
}
//-------------------------------------------------->>
void obj_wm_timer(HWND hwnd, WPARAM wParam) {
	POINT point;
	RECT rw, rc;
	
	GetCursorPos(&point);
	GetWindowRect(hwnd, &rw);
	GetClientRect(hwnd, &rc);
	
	if (point.x < rw.left || point.x > rw.right || point.y < rw.top || point.y > rw.bottom) {
		InvalidateRect(hwnd, &rc, TRUE);
		KillTimer(hwnd, wParam);
		bObjStatus = false;
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK MinProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_MOUSEMOVE:
			if (!bObjStatus)
				if (!intMainTimerId) obj_wm_mousemove(hwnd, 1);
			break;
		
		case WM_TIMER:
			obj_wm_timer(hwnd, wParam);
			break;
		
		case WM_LBUTTONUP:
			CloseWindow(hwndMain);
			break;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>
LRESULT CALLBACK MaxProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_MOUSEMOVE:
			if (!bObjStatus)
				if (!intMainTimerId) obj_wm_mousemove(hwnd, 2);
			break;
		
		case WM_TIMER:
			obj_wm_timer(hwnd, wParam);
			break;
		
		case WM_LBUTTONUP: {
			static RECT rcSave, rwSave;
			INT iMetricCx, iMetricCy, iMetricCaption;
			RECT rc;
			
			iMetricCx = GetSystemMetrics(SM_CXFULLSCREEN);
			iMetricCy = GetSystemMetrics(SM_CYFULLSCREEN);
			iMetricCaption = GetSystemMetrics(SM_CYCAPTION);
			
			GetClientRect(hwndMain, &rc);
			
			if (!bWindowStatus) {
				bWindowStatus = true;
				GetClientRect(hwndMain, &rcSave);
				GetWindowRect(hwndMain, &rwSave);
				MoveWindow(hwndMain, 0, 0, iMetricCx, iMetricCy + iMetricCaption, TRUE);
				InvalidateRect(hwndMain, 0, true);
			} else {
				bWindowStatus = false;
				MoveWindow(hwndMain, rwSave.left, rwSave.top, rcSave.right, rcSave.bottom, TRUE);
				InvalidateRect(hwndMain, 0, true);
			}
			
			InvalidateRect(hwndMain, &rc, TRUE);
			break;
		}
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>
LRESULT CALLBACK CloseProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_MOUSEMOVE:
			if (!bObjStatus)
				if (!intMainTimerId) obj_wm_mousemove(hwnd, 3);
			break;
		
		case WM_TIMER:
			obj_wm_timer(hwnd, wParam);
			break;
		
		case WM_LBUTTONUP:
			DestroyWindow(hwndMain);
			break;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





