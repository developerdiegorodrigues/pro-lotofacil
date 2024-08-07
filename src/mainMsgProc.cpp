#include "resource.h"

HBRUSH hBrushButton;
HBITMAP hPrimary, hSecond, hTertiary, hQuaternay;
HWND hwndPanelA, hwndPanelB, hwndPanelC, hwndPanelD, hwndPaleta;
INT intMainTimerId;
//-------------------------------------------------->>
void error(LPSTR lpTexto, INT iOpt) {
	if (!hwndMain) hwndMain = GetForegroundWindow();
	MessageBox(hwndMain, lpTexto, " (--_) Erro ", MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_TOPMOST);
	if (iOpt) ExitProcess(0);
}
//-------------------------------------------------->>
void show_message(LPSTR lpTexto, INT iLocal) {
	switch (iLocal) {
		case 1:
			SetDlgItemText(hwndMain, STATUS_BAR_01, lpTexto);
			SetTimer(hwndMain, TIMER_MESSAGE_ID1, 10000, NULL);
			break;
		
		case 2:
			SetDlgItemText(hwndMain, STATUS_BAR_02, lpTexto);
			SetTimer(hwndMain, TIMER_MESSAGE_ID2, 6000, NULL);
			break;
		
		case 3:
			SetDlgItemText(hwndMain, STATUS_BAR_03, lpTexto);
			SetTimer(hwndMain, TIMER_MESSAGE_ID3, 6000, NULL);
			break;
	}
}
//-------------------------------------------------->>
void wm_create(HWND hwnd) {
	RECT rect;
	HICON hIcon;
	HFONT hFont;
	
	hPrimary = LoadBitmap(hInstance, "FIRST");
	hSecond = LoadBitmap(hInstance, "SECOND");
	hTertiary = LoadBitmap(hInstance, "TERTIARY");
	hQuaternay = LoadBitmap(hInstance, "QUATERNARY");
	
	if (!hPrimary || !hSecond || !hTertiary || !hQuaternay) error((LPSTR) "Erro: LoadBitmaps!\t", true);
	
	if (!(hIcon = LoadIcon(hInstance, "icone"))) error((LPSTR) "Erro: LoadIcon!\t", true);
	
	hBrushButton = (HBRUSH) GetStockObject(WHITE_BRUSH);
	hFont = CreateFont(18, 0, 0, 0, 550, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Calibri");
	
	GetWindowRect(GetDesktopWindow(), &rect);
	MoveWindow(
		hwndMain, rect.right/2 - MAIN_WINDOW_WIDTH/2,
		rect.bottom/2 - MAIN_WINDOW_HEIGHT/2,
		MAIN_WINDOW_WIDTH,
		MAIN_WINDOW_HEIGHT,
		TRUE
	);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, MIN_CLASS_NAME, 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwndMain, (HMENU) OBJ_ID_MIN, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Min!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, MAX_CLASS_NAME, 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwndMain, (HMENU) OBJ_ID_MAX, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Max!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, CLOSE_CLASS_NAME, 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwndMain, (HMENU) OBJ_ID_FEC, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Fec!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Static", 0,
		WS_CHILD | WS_VISIBLE | SS_ICON | SS_NOTIFY,
		EDGE_WIDTH, EDGE_WIDTH, 0, 0, hwndMain, (HMENU) STATIC_ICON, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx StaticIcon!\t", true);
	
	if (!(hwndPanelA = CreateWindowEx(
		WS_EX_WINDOWEDGE, PAINEL_A_CLASS_NAME, 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwndMain, (HMENU) PANEL_A, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx PanelA!\t", true);
	
	if (!(hwndPanelB = CreateWindowEx(
		WS_EX_WINDOWEDGE, PAINEL_B_CLASS_NAME, 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwndMain, (HMENU) PANEL_B, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx PanelB!\t", true);
	
	if (!(hwndPanelC = CreateWindowEx(
		WS_EX_WINDOWEDGE, PAINEL_C_CLASS_NAME, 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwndMain, (HMENU) PANEL_C, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx PanelC!\t", true);
	
	if (!(hwndPanelD = CreateWindowEx(
		WS_EX_WINDOWEDGE, PAINEL_D_CLASS_NAME, 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwndMain, (HMENU) PANEL_D, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx PanelD!\t", true);
	
	if (!(hwndPaleta = CreateWindowEx(
		WS_EX_WINDOWEDGE | WS_EX_TOPMOST, PLT_CLASS_NAME, "Paleta",
		WS_POPUPWINDOW,
		0, 0, 0, 0, 0, 0, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Plt!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "msctls_progress32", 0,
		WS_CHILD,
		0, 0, 0, 0, hwnd, (HMENU) PROGRESS_01, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Progress!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_STATICEDGE, "Edit", 0,
		WS_CHILD | WS_VISIBLE | ES_CENTER | ES_READONLY,
		0, 0, 0, 0, hwnd, (HMENU) STATUS_BAR_01, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx BS01!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_STATICEDGE, "Edit", 0,
		WS_CHILD | WS_VISIBLE | ES_CENTER | ES_READONLY,
		0, 0, 0, 0, hwnd, (HMENU) STATUS_BAR_02, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx BS02!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_STATICEDGE, "Edit", 0,
		WS_CHILD | WS_VISIBLE | ES_CENTER | ES_READONLY,
		0, 0, 0, 0, hwnd, (HMENU) STATUS_BAR_03, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx BS03!\t", true);
	
	SendDlgItemMessage(hwndMain, STATIC_ICON, STM_SETIMAGE, IMAGE_ICON , (LPARAM) hIcon);
	SendDlgItemMessage(hwnd, PROGRESS_01, PBM_SETSTEP, 1, 0);
	
	for (INT imp=STATUS_BAR_01; imp<=STATUS_BAR_03; imp++)
		SendDlgItemMessage(hwnd, imp, WM_SETFONT, (WPARAM) hFont, MAKELPARAM(TRUE, 0));
	
	show_message((LPSTR)"Bem vindo!", 1);
	SetDlgItemText(hwndMain, STATUS_BAR_02, "(,--)");
	SetDlgItemText(hwndMain, STATUS_BAR_03, "(--,)");
	
	DeleteObject(hIcon);
	ShowWindow(hwndMain, SW_SHOWNORMAL);
}
//-------------------------------------------------->>
void wm_size() {
	RECT rc;
	FLOAT fHoriz, fVert;
	
	GetClientRect(hwndMain, &rc);
	
	fHoriz = rc.right;
	fVert = rc.bottom;
	
	MoveWindow(GetDlgItem(hwndMain, OBJ_ID_MIN), fHoriz-150, 10, 40, 20, TRUE);
	MoveWindow(GetDlgItem(hwndMain, OBJ_ID_MAX), fHoriz-100, 10, 40, 20, TRUE);
	MoveWindow(GetDlgItem(hwndMain, OBJ_ID_FEC), fHoriz-50, 10, 40, 20, TRUE);
	
	MoveWindow(hwndPanelA, 15, 50, (fHoriz/4), (fVert/5)*2.80, TRUE);
	MoveWindow(hwndPanelB, fHoriz/2-(fHoriz/4)+20, 50, (fHoriz/4)*2-40, (fVert/5)*2.80, TRUE);
	MoveWindow(hwndPanelC, fHoriz-(fHoriz/4)-15, 50, (fHoriz/4), (fVert/5)*2.80, TRUE);
	MoveWindow(hwndPanelD, 15, fVert-(fVert/5)*2.20+55, fHoriz-30, (fVert/5)*2.20-90, TRUE);
	
	MoveWindow(GetDlgItem(hwndMain, STATUS_BAR_01), EDGE_WIDTH+1, fVert-EDGE_WIDTH-23, (fHoriz/4), 22, TRUE);
	MoveWindow(GetDlgItem(hwndMain, STATUS_BAR_02), (fHoriz/4)+10, fVert-EDGE_WIDTH-23, (fHoriz/4)-12, 22, TRUE);
	MoveWindow(GetDlgItem(hwndMain, STATUS_BAR_03), (fHoriz/4)*2, fVert-EDGE_WIDTH-23, (fHoriz/4)*2-EDGE_WIDTH-1, 22, TRUE);
	
	MoveWindow(GetDlgItem(hwndMain, PROGRESS_01), 50, 7, fHoriz/20*6, 30, TRUE);
}
//-------------------------------------------------->>
void wm_command(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	switch (LOWORD(wParam)) {
		case STATIC_ICON:
			show_message((LPSTR)AUTHOR, 3);
			break;
	}
}
//-------------------------------------------------->>
void wm_timer(WPARAM wParam) {
	if (wParam == TIMER_MESSAGE_ID1) {
		KillTimer(hwndMain, wParam);
		SetDlgItemText(hwndMain, STATUS_BAR_01, "ProLoto v1.0");
		return;
	}
	
	if (wParam == TIMER_MESSAGE_ID2) {
		KillTimer(hwndMain, wParam);
		SetDlgItemText(hwndMain, STATUS_BAR_02, "(,--)");
		return;
	}
	
	if (wParam == TIMER_MESSAGE_ID3) {
		KillTimer(hwndMain, wParam);
		SetDlgItemText(hwndMain, STATUS_BAR_03, AUTHOR);
		return;
	}
	
	to_size(EXECUTE, 0, 0, wParam);
}
//-------------------------------------------------->>
void to_size(INT iMode, INT iHoriz, INT iVert, WPARAM wParam) {
	RECT rc, rw, rd;
	
	static INT iDifx;
	static INT iDify;
	static INT iDifLeft;
	static INT iDifRight;
	static INT iDifTop;
	static INT iDifBottom;
	static INT iPosRigth;
	static INT iPosBottom;
	
	if (iMode == START) {
		GetClientRect(hwndMain, &rc);
		GetWindowRect(hwndMain, &rw);
		GetWindowRect(GetDesktopWindow(), &rd);
		
		iDifx = iHoriz;
		iDify = iVert;
		
		iDifLeft	= iDifx - rc.left;
		iDifRight	= iDifx - rc.right;
		iDifTop		= iDify - rc.top;
		iDifBottom	= iDify - rc.bottom;
		
		iPosRigth = rd.right - rw.left - rc.right;
		iPosBottom = rd.bottom - rw.top - rc.bottom;
		
		if ((iDifx > RESIZE_BORDER) && (iDifx < rc.right - RESIZE_BORDER) && (iDify > RESIZE_BORDER) && (iDify < rc.bottom - RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_MOVE_ID, TIMER_MOVE_ELAPSE, NULL);
		
		else if ((iDifx < RESIZE_BORDER) && (iDify > RESIZE_BORDER) && (iDify < rc.bottom - RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_LEFT_ID, TIMER_RESIZE_ELAPSE, NULL);
		
		else if ((iDifx > rc.right - RESIZE_BORDER) && (iDify > RESIZE_BORDER) && (iDify < rc.bottom - RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_RIGHT_ID, TIMER_MOVE_ELAPSE, NULL);
		
		else if ((iDifx > RESIZE_BORDER) && (iDifx < rc.right - RESIZE_BORDER) && (iDify < RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_TOP_ID, TIMER_RESIZE_ELAPSE, NULL);
		
		else if ((iDifx > RESIZE_BORDER) && (iDifx < rc.right - RESIZE_BORDER) && (iDify > rc.bottom - RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_BOTTOM_ID, TIMER_MOVE_ELAPSE, NULL);
		
		else if ((iDifx < RESIZE_BORDER) && (iDify < RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_DIAG_A_ID, TIMER_RESIZE_ELAPSE, NULL);
		
		else if ((iDifx > rc.right - RESIZE_BORDER) && (iDify < RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_DIAG_B_ID, TIMER_RESIZE_ELAPSE, NULL);
		
		else if ((iDifx < RESIZE_BORDER) && (iDify > rc.bottom - RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_DIAG_C_ID, TIMER_RESIZE_ELAPSE, NULL);
		
		else if ((iDifx > rc.right - RESIZE_BORDER) && (iDify > rc.bottom - RESIZE_BORDER))
			SetTimer(hwndMain, TIMER_DIAG_D_ID, TIMER_MOVE_ELAPSE, NULL);
		
		return;
	}
	
	if (iMode == EXECUTE) {
		POINT point;
		INT iAuxPri, iAuxSec;
		
		intMainTimerId = wParam;
		
		GetCursorPos(&point);
		GetClientRect(hwndMain, &rc);
		GetWindowRect(hwndMain, &rw);
		GetWindowRect(GetDesktopWindow(), &rd);
		
		if (rc.right < MAIN_WINDOW_MINIMUM_WIDTH || rc.bottom < MAIN_WINDOW_MAXIMUM_WIDTH) {
			KillTimer(hwndMain, intMainTimerId);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, GetMessageExtraInfo());
			MoveWindow(hwndMain, (rd.right/2)-(MAIN_WINDOW_MINIMUM_WIDTH/2), (rd.bottom/2)-(MAIN_WINDOW_MAXIMUM_WIDTH/2), MAIN_WINDOW_MINIMUM_WIDTH, MAIN_WINDOW_MAXIMUM_WIDTH, TRUE);
			InvalidateRect(hwndMain, &rc, TRUE);
			return;
		}
		
		if ((!GetAsyncKeyState(VK_LBUTTON))) {
			KillTimer(hwndMain, intMainTimerId);
			intMainTimerId = 0;
			return;
		}
		
		switch (intMainTimerId) {
			case TIMER_MOVE_ID:
				if ((rw.left == point.x - iDifx) && (rw.top == point.y - iDify)) return;
				MoveWindow(hwndMain, point.x-iDifx, point.y-iDify, rc.right, rc.bottom, TRUE);
				return;
			
			case TIMER_LEFT_ID:
				if ((rw.left == point.x - iDifLeft)) return;
				iAuxPri = rd.right - rw.left - iPosRigth;
				if ((iAuxPri) > MAIN_WINDOW_MINIMUM_WIDTH)
					MoveWindow(hwndMain, point.x-iDifLeft, rw.top, iAuxPri, rc.bottom, TRUE);
				else return;
				break;
			
			case TIMER_RIGHT_ID:
				iAuxPri = point.x - rw.left - iDifRight;
				if ((rc.right == iAuxPri)) return;
				if ((iAuxPri) > MAIN_WINDOW_MINIMUM_WIDTH)
					MoveWindow(hwndMain, rw.left, rw.top, iAuxPri, rc.bottom, TRUE);
				else return;
				break;
			
			case TIMER_TOP_ID:
				if ((rw.top == point.y - iDifTop)) return;
				iAuxPri = rd.bottom - rw.top-iPosBottom;
				if ((iAuxPri) > MAIN_WINDOW_MAXIMUM_WIDTH)
					MoveWindow(hwndMain, rw.left, point.y-iDifTop, rc.right, iAuxPri, TRUE);
				else return;
				break;
			
			case TIMER_BOTTOM_ID:
				iAuxPri = point.y - rw.top - iDifBottom;
				if ((rc.bottom == iAuxPri)) return;
				if ((iAuxPri) > MAIN_WINDOW_MAXIMUM_WIDTH)
					MoveWindow(hwndMain, rw.left, rw.top, rc.right, iAuxPri, TRUE);
				else return;
				break;
			
			case TIMER_DIAG_A_ID:
				if ((rw.left == point.x-iDifx) && (rw.top == point.y-iDify)) return;
				iAuxPri = rd.right - rw.left - iPosRigth;
				iAuxSec = rd.bottom - rw.top - iPosBottom;
				if ((iAuxPri) > MAIN_WINDOW_MINIMUM_WIDTH && (iAuxSec) > MAIN_WINDOW_MAXIMUM_WIDTH)
					MoveWindow(hwndMain, point.x-iDifx, point.y-iDify, iAuxPri, iAuxSec, TRUE);
				else return;
				break;
			
			case TIMER_DIAG_B_ID:
				iAuxPri = point.x-rw.left - iDifRight;
				iAuxSec = rd.bottom - rw.top-iPosBottom;
				if ((rw.top == point.y-iDifTop) && (rc.right == iAuxPri)) return;
				if ((iAuxPri) > MAIN_WINDOW_MINIMUM_WIDTH && (iAuxSec) > MAIN_WINDOW_MAXIMUM_WIDTH)
					MoveWindow(hwndMain, rw.left, point.y-iDifTop, iAuxPri, iAuxSec, TRUE);
				else return;
				break;
			
			case TIMER_DIAG_C_ID:
				iAuxPri = rd.right - rw.left - iPosRigth;
				iAuxSec = point.y - rw.top - iDifBottom;
				if ((rw.left == point.x-iDifLeft) && (rc.bottom == iAuxSec)) return;
				if ((iAuxPri) > MAIN_WINDOW_MINIMUM_WIDTH && (iAuxSec) > MAIN_WINDOW_MAXIMUM_WIDTH)
					MoveWindow(hwndMain, point.x-iDifLeft, rw.top, iAuxPri, iAuxSec, TRUE);
				else return;
				break;
			
			case TIMER_DIAG_D_ID:
				iAuxPri = point.x - rw.left - iDifRight;
				iAuxSec = point.y - rw.top - iDifBottom;
				if ((rc.right == iAuxPri) && (rc.bottom == iAuxSec)) return;
				if ((iAuxPri) > MAIN_WINDOW_MINIMUM_WIDTH && (iAuxSec) > MAIN_WINDOW_MAXIMUM_WIDTH)
					MoveWindow(hwndMain, rw.left, rw.top, iAuxPri, iAuxSec, TRUE);
				else return;
				break;
		}
		
		InvalidateRect(hwndMain, &rc, TRUE);
		return;
	}
}
//-------------------------------------------------->>
void wm_paint() {
	PAINTSTRUCT PaintStruct;
	HDC hdc;
	RECT rect, rc;
	CHAR titulo[] = PROJECT_TITLE;
	
	static HBRUSH hBrushA, hBrushB;
	static HFONT hFont;
	
	if (!hFont) {
		hFont = CreateFont(25, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Verdana");
		hBrushA = CreateSolidBrush(COLOR_MAIN_TITLE_BAR);
		hBrushB = CreateSolidBrush(COLOR_MAIN_BORDER);
	}
	
	GetClientRect(hwndMain, &rc);
	hdc = BeginPaint(hwndMain, &PaintStruct);
	
	SetRect(&rect, 0, 0, rc.right, TITLE_BAR_HEIGHT);
	FillRect(hdc, &rect, hBrushA);
	
	for (int x=0, y=0; x<=EDGE_WIDTH; x++, y++) {
		SetRect(&rect, x, x, rc.right-y, rc.bottom-y);
		FrameRect(hdc, &rect, hBrushB);
	}
	
	SelectObject(hdc, hFont);
	SetTextColor(hdc, COLOR_MAIN_TITLE);
	SetBkMode(hdc, TRANSPARENT);
	SetRect(&rect, 0, 0, rc.right, TITLE_BAR_HEIGHT / 4*3);
	DrawText(hdc, titulo, -1, &rect, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
	
	EndPaint(hwndMain, &PaintStruct);
}
//-------------------------------------------------->>
/*
	// DEBUG
	static int iDebug = 0;
	char cDebug[100];
	iDebug++;
	wsprintf(cDebug, "cont: %d", iDebug);
	SetWindowText(hwndMain, cDebug);
	// SetDlgItemText(hwndMain, STATUS_BAR_01, cDebug);
*/





