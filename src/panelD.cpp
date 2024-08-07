#include "resource.h"

HWND hExtA, hExtB, hExtC, hExtD, hExtE, hExtF, hExtG;
//-------------------------------------------------->>
panel_d_wm_create(HWND hwnd) {
	TC_ITEM tci;
	HWND hTabControl;
	
	if (!(hTabControl = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysTabControl32", 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwnd, (HMENU) TABCONTROL_01_D, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysTabControl PanelD!\t", true);
	
	if (!(hExtA = CreateWindowEx(
		WS_EX_WINDOWEDGE, PD_EXT_A_CLASS_NAME, 0,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwnd, (HMENU) EXT_A, hInstance, NULL
	))) error((LPSTR) "Erro: CreateWindowEx ExtA!\t", true);
	
	if (!(hExtB = CreateWindowEx(
		WS_EX_WINDOWEDGE, PD_EXT_B_CLASS_NAME, 0,
		WS_CHILD,
		0, 0, 0, 0, hwnd, (HMENU) EXT_B, hInstance, NULL
	))) error((LPSTR) "Erro: CreateWindowEx ExtB!\t", true);
	
	if (!(hExtC = CreateWindowEx(
		WS_EX_WINDOWEDGE, PD_EXT_C_CLASS_NAME, 0,
		WS_CHILD,
		0, 0, 0, 0, hwnd, (HMENU) EXT_C, hInstance, NULL
	))) error((LPSTR) "Erro: CreateWindowEx ExtC!\t", true);
	
	if (!(hExtD = CreateWindowEx(
		WS_EX_WINDOWEDGE, PD_EXT_D_CLASS_NAME, 0,
		WS_CHILD | WS_BORDER,
		0, 0, 0, 0, hwnd, (HMENU) EXT_D, hInstance, NULL
	))) error((LPSTR) "Erro: CreateWindowEx ExtD!\t", true);
	
	if (!(hExtE = CreateWindowEx(
		WS_EX_WINDOWEDGE, PD_EXT_E_CLASS_NAME, 0,
		WS_CHILD,
		0, 0, 0, 0, hwnd, (HMENU) EXT_E, hInstance, NULL
	))) error((LPSTR) "Erro: CreateWindowEx ExtE!\t", true);
	
	if (!(hExtF = CreateWindowEx(
		WS_EX_WINDOWEDGE, PD_EXT_F_CLASS_NAME, 0,
		WS_CHILD | WS_BORDER,
		0, 0, 0, 0, hwnd, (HMENU) EXT_F, hInstance, NULL
	))) error((LPSTR) "Erro: CreateWindowEx ExtF!\t", true);
	
	if (!(hExtG = CreateWindowEx(
		WS_EX_WINDOWEDGE, PD_EXT_G_CLASS_NAME, 0,
		WS_CHILD | WS_BORDER,
		0, 0, 0, 0, hwnd, (HMENU) EXT_G, hInstance, NULL
	))) error((LPSTR) "Erro: CreateWindowEx ExtG!\t", true);
	
	ZeroMemory(&tci, sizeof(tci));
	tci.mask = TCIF_TEXT;
	
	tci.pszText = (LPSTR)"Concursos";
	tci.cchTextMax = strlen(tci.pszText);
	TabCtrl_InsertItem(hTabControl, 0, &tci);
	
	tci.pszText = (LPSTR)"Total";
	tci.cchTextMax = strlen(tci.pszText);
	TabCtrl_InsertItem(hTabControl, 1, &tci);
	
	tci.pszText = (LPSTR)"Resultado";
	tci.cchTextMax = strlen(tci.pszText);
	TabCtrl_InsertItem(hTabControl, 2, &tci);
	
	tci.pszText = (LPSTR)"Vizualizar em Cartelas";
	tci.cchTextMax = strlen(tci.pszText);
	TabCtrl_InsertItem(hTabControl, 3, &tci);
	
	tci.pszText = (LPSTR)"Filtros 1";
	tci.cchTextMax = strlen(tci.pszText);
	TabCtrl_InsertItem(hTabControl, 4, &tci);
	
	tci.pszText = (LPSTR)"Filtros 2";
	tci.cchTextMax = strlen(tci.pszText);
	TabCtrl_InsertItem(hTabControl, 5, &tci);
	
	tci.pszText = (LPSTR)"Implemento";
	tci.cchTextMax = strlen(tci.pszText);
	TabCtrl_InsertItem(hTabControl, 6, &tci);
	
	SendMessage(hTabControl, WM_SETFONT, (WPARAM) GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}
//-------------------------------------------------->>
void panel_d_wm_notify(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	if ((wParam == TABCONTROL_01_D) && (((NMHDR*)lParam)->code == TCN_SELCHANGE)) {
		for (int comp=EXT_A; comp<=EXT_G; comp++) ShowWindow(GetDlgItem(hwnd, comp), SW_HIDE);
		
		switch (TabCtrl_GetCurSel(GetDlgItem(hwnd, TABCONTROL_01_D))) {
			case 0:
				ShowWindow(hExtA, SW_NORMAL);
				SetFocus(hExtA);
				break;
			
			case 1:
				ShowWindow(hExtC, SW_NORMAL);
				SetFocus(hExtC);
				break;
			
			case 2:
				ShowWindow(hExtE, SW_NORMAL);
				SetFocus(hExtE);
				break;
			
			case 3:
				ShowWindow(hExtB, SW_NORMAL);
				SetFocus(hExtB);
				break;
			
			case 4:
				ShowWindow(hExtD, SW_NORMAL);
				SetFocus(hExtD);
				break;
			
			case 5:
				ShowWindow(hExtF, SW_NORMAL);
				SetFocus(hExtF);
				break;
			
			case 6:
				ShowWindow(hExtG, SW_NORMAL);
				SetFocus(hExtG);
				break;
		}
	}
}
//-------------------------------------------------->>
panel_d_wm_size(HWND hwnd) {
	RECT rc;
	GetClientRect(hwnd, &rc);
	
	MoveWindow(GetDlgItem(hwnd, TABCONTROL_01_D), 15, 15, rc.right-30, rc.bottom-30, TRUE);
	MoveWindow(hExtA, 25, 45, rc.right-50, rc.bottom-70, TRUE);
	MoveWindow(hExtB, 25, 45, rc.right-50, rc.bottom-70, TRUE);
	MoveWindow(hExtC, 25, 45, rc.right-50, rc.bottom-70, TRUE);
	MoveWindow(hExtD, 25, 45, rc.right-50, rc.bottom-70, TRUE);
	MoveWindow(hExtE, 25, 45, rc.right-50, rc.bottom-70, TRUE);
	MoveWindow(hExtF, 25, 45, rc.right-50, rc.bottom-70, TRUE);
	MoveWindow(hExtG, 25, 45, rc.right-50, rc.bottom-70, TRUE);
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelDProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			panel_d_wm_create(hwnd);
			break;
		
		case WM_SIZE:
			panel_d_wm_size(hwnd);
			break;
		
		case WM_NOTIFY:
			panel_d_wm_notify(hwnd, wParam, lParam);
			break;
		
		case WM_PAINT:
			PAINTSTRUCT PaintStruct;
			HDC hdcWindow;
			hdcWindow = BeginPaint(hwnd, &PaintStruct);
			general_wm_paint(hwnd, hdcWindow);
			EndPaint(hwnd, &PaintStruct);
			break;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





