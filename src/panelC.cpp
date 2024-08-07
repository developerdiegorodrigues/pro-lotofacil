#include "resource.h"

#define ListView01_Style WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER

HWND hListView_Pc;
//-------------------------------------------------->>
void panel_c_wm_create(HWND hwnd) {
	LV_COLUMN lvCol;
	HFONT hFont;
	
	hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Consolas");
	
	for (INT inc=BUTTON_01_C; inc<=BUTTON_06_C; inc++) {
		if (!(CreateWindowEx(
			WS_EX_WINDOWEDGE, "Button", 0,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hwnd, (HMENU) MAKEINTRESOURCE(inc), hInstance, 0
		))) error((LPSTR) "Erro: CreateWindowEx Buttons PanelC!\t", true);
	}
	
	if (!(hListView_Pc = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysListView32", 0,
		ListView01_Style,
		0, 0, 0, 0, hwnd, (HMENU) LISTVIEW_01_C, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysListView01 PanelC!\t", true);
	
	SetDlgItemText(hwnd, BUTTON_01_C, "Gerar Total");
	SetDlgItemText(hwnd, BUTTON_02_C, "Pausar");
	SetDlgItemText(hwnd, BUTTON_03_C, "Cancelar");
	SetDlgItemText(hwnd, BUTTON_04_C, "Rodar");
	SetDlgItemText(hwnd, BUTTON_05_C, "Pausar");
	SetDlgItemText(hwnd, BUTTON_06_C, "Cancelar");
	
	ListView_SetExtendedListViewStyle(hListView_Pc, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	ZeroMemory(&lvCol, sizeof(lvCol));
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_CENTER;
	lvCol.cx = 270;
	lvCol.pszText = (LPSTR) "Resultado";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView_Pc, 0, &lvCol);
	
	EnableWindow(GetDlgItem(hwnd, BUTTON_02_C), false);
	EnableWindow(GetDlgItem(hwnd, BUTTON_03_C), false);
	EnableWindow(GetDlgItem(hwnd, BUTTON_05_C), false);
	EnableWindow(GetDlgItem(hwnd, BUTTON_06_C), false);
	
	for (INT inc=BUTTON_01_C; inc<=BUTTON_06_C; inc++)
		SendDlgItemMessage(hwnd, inc, WM_SETFONT, (WPARAM) GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	
	SendMessage(hListView_Pc, WM_SETFONT, (WPARAM) hFont, MAKELPARAM(TRUE, 0));
}
//-------------------------------------------------->>
void panel_c_wm_size(HWND hwnd) {
	RECT rc;
	FLOAT fTh, fTv, mod;
	
	GetClientRect(hwnd, &rc);
	fTh = rc.right / 10;
	fTv = rc.bottom / 10;
	
	MoveWindow(GetDlgItem(hwnd, BUTTON_01_C), fTh*0.70, fTv*0.50, fTh*8.60, fTv*0.90, TRUE);
	MoveWindow(GetDlgItem(hwnd, BUTTON_02_C), fTh*0.70, fTv*1.50, fTh*4.20, fTv*0.70, TRUE);
	MoveWindow(GetDlgItem(hwnd, BUTTON_03_C), fTh*5.10, fTv*1.50, fTh*4.20, fTv*0.70, TRUE);
	
	MoveWindow(GetDlgItem(hwnd, BUTTON_04_C), fTh*0.70, fTv*2.50, fTh*8.60, fTv*0.70, TRUE);
	MoveWindow(GetDlgItem(hwnd, BUTTON_05_C), fTh*0.70, fTv*3.30, fTh*4.20, fTv*0.70, TRUE);
	MoveWindow(GetDlgItem(hwnd, BUTTON_06_C), fTh*5.10, fTv*3.30, fTh*4.20, fTv*0.70, TRUE);
	
	MoveWindow(GetDlgItem(hwnd, LISTVIEW_01_C), fTh*0.70, fTv*4.30, fTh*8.60, fTv*5.30, TRUE);
}
//-------------------------------------------------->>
void panel_c_wm_command(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	CHAR cTexto[11];
	
	switch (LOWORD(wParam)) {
		case BUTTON_01_C:
			if (general_available_disk(hwnd, 150)) break;
			panel_c_gerate_total(START, hwnd);
			break;
		
		case BUTTON_02_C:
			GetDlgItemText(hwnd, BUTTON_02_C, cTexto, 10);
			(!strcmp(cTexto, "Pausar")) ? SetDlgItemText(hwnd, BUTTON_02_C, "Continuar"): SetDlgItemText(hwnd, BUTTON_02_C, "Pausar");
			break;
		
		case BUTTON_03_C:
			panel_c_gerate_total(FINALIZE, hwnd);
			ListView_DeleteAllItems(hListView_ext_c);
			SetDlgItemText(hwnd, BUTTON_03_C, "Cancelado");
			show_message((LPSTR) "Cancelado", 2);
			break;
		
		case BUTTON_04_C:
			if (general_available_disk(hwnd, 155)) break;
			panel_c_run(START, hwnd);
			break;
		
		case BUTTON_05_C:
			GetDlgItemText(hwnd, BUTTON_05_C, cTexto, 10);
			(!strcmp(cTexto, "Pausar")) ? SetDlgItemText(hwnd, BUTTON_05_C, "Continuar"): SetDlgItemText(hwnd, BUTTON_05_C, "Pausar");
			break;
		
		case BUTTON_06_C:
			panel_c_run(FINALIZE, hwnd);
			ListView_DeleteAllItems(hListView_ext_e);
			SetDlgItemText(hwnd, BUTTON_06_C, "Cancelado");
			show_message((LPSTR) "Cancelado", 2);
			break;
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelCProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			panel_c_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			panel_c_wm_command(hwnd, wParam, lParam);
			break;
		
		case WM_PAINT:
			PAINTSTRUCT PaintStruct;
			HDC hdcWindow;
			hdcWindow = BeginPaint(hwnd, &PaintStruct);
			general_wm_paint(hwnd, hdcWindow);
			EndPaint(hwnd, &PaintStruct);
			break;
		
		case WM_TIMER:
			CHAR cTexto[11];
			if (!intMainTimerId) {
				if (wParam == TIMER_TOTAL_ID) {
					GetDlgItemText(hwnd, BUTTON_03_C, cTexto, 10);
					if (!strcmp(cTexto, "Cancelado")) {
						KillTimer(hwnd, TIMER_TOTAL_ID);
						break;
					}
					
					GetDlgItemText(hwnd, BUTTON_02_C, cTexto, 10);
					if (!strcmp(cTexto, "Pausar")) {
						KillTimer(hwnd, TIMER_TOTAL_ID);
						panel_c_gerate_total(EXECUTE, hwnd);
					}
				} else if (wParam == TIMER_EXEC_ID) {
					GetDlgItemText(hwnd, BUTTON_06_C, cTexto, 10);
					if (!strcmp(cTexto, "Cancelado")) {
						KillTimer(hwnd, TIMER_EXEC_ID);
						break;
					}
					
					GetDlgItemText(hwnd, BUTTON_05_C, cTexto, 10);
					if (!strcmp(cTexto, "Pausar")) {
						KillTimer(hwnd, TIMER_EXEC_ID);
						panel_c_run(EXECUTE, hwnd);
					}
				} else if (wParam == TIMER_SUMMARIZE_ID) {
					KillTimer(hwnd, TIMER_SUMMARIZE_ID);
					panel_c_resume(EXECUTE, hwnd);
				}
			}
			break;
		
		case WM_SIZE:
			panel_c_wm_size(hwnd);
			break;
		
		case WM_LBUTTONDBLCLK:
			(PathFileExists(DATA_RESULT)) ?
				panel_c_resume(START, hwnd):
				show_message((LPSTR)"Arquivo não encontrado", 3);
			break;
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





