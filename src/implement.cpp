#include "resource.h"

INT longNumExtG[16];

#define ListView01_Style WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER
//-------------------------------------------------->>
void ext_g_wm_create(HWND hwnd) {
	HWND hListView;
	LV_COLUMN lvCol;
	HFONT hFont;
	
	ZeroMemory(&longNumExtG, sizeof(longNumExtG));
	
	hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Consolas");
	
	for (int inc=BUTTON_01_D_EXTG; inc <=BUTTON_05_D_EXTG; inc++) {
		if (!(CreateWindowEx(
			WS_EX_WINDOWEDGE, "Button", 0,
			(inc == BUTTON_04_D_EXTG) ?
				WS_CHILD | WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | BS_CENTER:
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hwnd, (HMENU) MAKEINTRESOURCE(inc), hInstance, 0
		))) error((LPSTR) "Erro: CreateWindowEx Buttons ExtG!\t", true);
	}
	
	for (int inc=EDIT_01_D_EXTG; inc<=EDIT_14_D_EXTG; inc++) {
		if (!(CreateWindowEx(
			WS_EX_CLIENTEDGE, "Edit", 0,
			(inc == EDIT_09_D_EXTG) ?
				WS_CHILD | WS_VISIBLE | ES_CENTER | ES_AUTOVSCROLL | ES_MULTILINE:
				WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
			0, 0, 0, 0, hwnd, (HMENU) MAKEINTRESOURCE(inc), hInstance, 0
		))) error((LPSTR) "Erro: CreateWindowEx Edits ExtG!\t", true);
	}
	
	if (!(hListView = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysListView32",
		0, ListView01_Style,
		0, 0, 0, 0, hwnd, (HMENU) LISTVIEW_01_D_EXTG, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysListView01 ExtG!\t", true);
	
	for (int inc=EDIT_10_D_EXTG; inc<=EDIT_14_D_EXTG; inc++)
		SetWindowLong(GetDlgItem(hwnd, inc), GWL_STYLE, WS_CHILD | WS_VISIBLE| ES_CENTER);
	
	EnableWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTG), false);
	EnableWindow(GetDlgItem(hwnd, BUTTON_03_D_EXTG), false);
	
	for (INT inc=EDIT_01_D_EXTG; inc<=EDIT_08_D_EXTG; inc++)
		SendDlgItemMessage(hwnd, inc, EM_LIMITTEXT, 3, 0);
	
	SendDlgItemMessage(hwnd, EDIT_09_D_EXTG, EM_LIMITTEXT, 44, 0);
	SendDlgItemMessage(hwnd, EDIT_10_D_EXTG, EM_LIMITTEXT, 5, 0);
	SendDlgItemMessage(hwnd, EDIT_11_D_EXTG, EM_LIMITTEXT, 5, 0);
	SendDlgItemMessage(hwnd, EDIT_12_D_EXTG, EM_LIMITTEXT, 6, 0);
	SendDlgItemMessage(hwnd, EDIT_13_D_EXTG, EM_LIMITTEXT, 8, 0);
	SendDlgItemMessage(hwnd, EDIT_14_D_EXTG, EM_LIMITTEXT, 11, 0);
	
	ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	SetDlgItemText(hwnd, BUTTON_01_D_EXTG, "Salvar Cartelas");
	SetDlgItemText(hwnd, BUTTON_02_D_EXTG, "Pausar");
	SetDlgItemText(hwnd, BUTTON_03_D_EXTG, "Cancelar");
	SetDlgItemText(hwnd, BUTTON_05_D_EXTG, "Conferir");
	
	ZeroMemory(&lvCol, sizeof(lvCol));
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvCol.fmt = LVCFMT_CENTER;
	
	lvCol.cx = 100;
	lvCol.pszText = (LPSTR) "Dados Cruzados";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView, 0, &lvCol);
	
	lvCol.cx = 80;
	lvCol.pszText = (LPSTR) "Quant";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView, 1, &lvCol);
	
	lvCol.cx = 80;
	lvCol.pszText = (LPSTR) "%";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView, 2, &lvCol);
	
	for (INT inc=BUTTON_01_D_EXTG; inc<=EDIT_14_D_EXTG; inc++)
		SendDlgItemMessage(hwnd, inc, WM_SETFONT, (WPARAM) GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	
	SendMessage(hListView, WM_SETFONT, (WPARAM) hFont, MAKELPARAM(TRUE, 0));
	
	ext_g_fill(hwnd);
}
//-------------------------------------------------->>
void ext_g_fill(HWND hwnd) {
	SetDlgItemText(hwnd, EDIT_01_D_EXTG, "37");
	SetDlgItemText(hwnd, EDIT_02_D_EXTG, "14");
	SetDlgItemText(hwnd, EDIT_03_D_EXTG, "48");
	SetDlgItemText(hwnd, EDIT_04_D_EXTG, "84");
	SetDlgItemText(hwnd, EDIT_05_D_EXTG, "9");
	SetDlgItemText(hwnd, EDIT_06_D_EXTG, "17");
	SetDlgItemText(hwnd, EDIT_07_D_EXTG, "38");
	SetDlgItemText(hwnd, EDIT_08_D_EXTG, "277");
	SetDlgItemText(hwnd, EDIT_10_D_EXTG, "4.0");
	SetDlgItemText(hwnd, EDIT_11_D_EXTG, "8.0");
	SetDlgItemText(hwnd, EDIT_12_D_EXTG, "20.0");
	SetDlgItemText(hwnd, EDIT_13_D_EXTG, "1500.0");
	SetDlgItemText(hwnd, EDIT_14_D_EXTG, "1500000.0");
}
//-------------------------------------------------->>
void ext_g_wm_command(HWND hwnd, WPARAM wParam) {
	char cTexto[11];
	
	if (wParam == MESSAGE_BLOCK) {
		for (int inc=BUTTON_01_D_EXTG; inc<=EDIT_14_D_EXTG; inc++) EnableWindow(GetDlgItem(hwnd, inc), false);
		return;
	}
	
	if (wParam == MESSAGE_UNBLOCK) {
		for (int inc=BUTTON_01_D_EXTG; inc<=EDIT_14_D_EXTG; inc++) EnableWindow(GetDlgItem(hwnd, inc), true);
		return;
	}
	
	switch (LOWORD(wParam)) {
		case BUTTON_01_D_EXTG:
			ext_g_save_card(START, hwnd);
			break;
			
		case BUTTON_02_D_EXTG:
			GetDlgItemText(hwnd, BUTTON_02_D_EXTG, cTexto, 10);
			(!strcmp(cTexto, "Pausar")) ? SetDlgItemText(hwnd, BUTTON_02_D_EXTG, "Continuar"): SetDlgItemText(hwnd, BUTTON_02_D_EXTG, "Pausar");
			break;
			
		case BUTTON_03_D_EXTG:
			ext_g_save_card(FINALIZE, hwnd);
			SetDlgItemText(hwnd, BUTTON_03_D_EXTG, "Cancelado");
			show_message((LPSTR)"Cancelado", 2);
			break;
			
		case BUTTON_04_D_EXTG:
			if (IsDlgButtonChecked(hExtG, BUTTON_04_D_EXTG))
				show_message((LPSTR)"Essa opção muda o ângulo das casas", 3);
			SetFocus(hwnd);
			break;
			
		case BUTTON_05_D_EXTG:
			ext_g_analyze(hwnd);
			break;
	}
	
	if (HIWORD(wParam) == EN_SETFOCUS) {
		switch (LOWORD(wParam)) {
			case EDIT_01_D_EXTG:
				show_message((LPSTR)"Posição inicial fHorizontal", 3);
				break;
				
			case EDIT_02_D_EXTG:
				show_message((LPSTR)"Tamanho fHorizontal", 3);
				break;
				
			case EDIT_03_D_EXTG:
				show_message((LPSTR)"Espaçamento fHorizontal", 3);
				break;
				
			case EDIT_04_D_EXTG:
				show_message((LPSTR)"Posição inicial fVertical", 3);
				break;
				
			case EDIT_05_D_EXTG:
				show_message((LPSTR)"Tamanho fVertical", 3);
				break;
				
			case EDIT_06_D_EXTG:
				show_message((LPSTR)"Espaçamento fVertical", 3);
				break;
				
			case EDIT_07_D_EXTG:
				show_message((LPSTR)"PIH Ultimo quadro", 3);
				break;
				
			case EDIT_08_D_EXTG:
				show_message((LPSTR)"PIV Ultimo quadro", 3);
				break;
				
			case EDIT_09_D_EXTG:
				show_message((LPSTR)"15 números para conferência", 3);
				break;
				
			case EDIT_10_D_EXTG:
				show_message((LPSTR)"Valor para 11 números", 3);
				break;
				
			case EDIT_11_D_EXTG:
				show_message((LPSTR)"Valor para 12 números", 3);
				break;
				
			case EDIT_12_D_EXTG:
				show_message((LPSTR)"Valor para 13 números", 3);
				break;
				
			case EDIT_13_D_EXTG:
				show_message((LPSTR)"Valor para 14 números", 3);
				break;
				
			case EDIT_14_D_EXTG:
				show_message((LPSTR)"Valor para 15 números", 3);
				break;
		}
	}
}
//-------------------------------------------------->>
void ext_g_wm_size(HWND hwnd) {
	RECT rc;
	FLOAT fTh, fTv, modHoriz;
	
	GetClientRect(hwnd, &rc);
	
	fTh = rc.right / 20;
	fTv = rc.bottom / 10;
	
	modHoriz = fTh*0.2;
	MoveWindow(GetDlgItem(hwnd, BUTTON_01_D_EXTG), fTh*0.20+modHoriz, fTv*0.50, fTh*3.10, fTv*1.80, TRUE);
	MoveWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTG), fTh*0.20+modHoriz, fTv*2.50, fTh*1.50, fTv*1.80, TRUE);
	MoveWindow(GetDlgItem(hwnd, BUTTON_03_D_EXTG), fTh*1.80+modHoriz, fTv*2.50, fTh*1.50, fTv*1.80, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_01_D_EXTG), fTh*0.20+modHoriz, fTv*4.60, fTh*1.00, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_02_D_EXTG), fTh*1.25+modHoriz, fTv*4.60, fTh*1.00, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_03_D_EXTG), fTh*2.30+modHoriz, fTv*4.60, fTh*1.00, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_04_D_EXTG), fTh*0.20+modHoriz, fTv*6.30, fTh*1.00, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_05_D_EXTG), fTh*1.25+modHoriz, fTv*6.30, fTh*1.00, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_06_D_EXTG), fTh*2.30+modHoriz, fTv*6.30, fTh*1.00, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_07_D_EXTG), fTh*0.20+modHoriz, fTv*8.00, fTh*1.00, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_08_D_EXTG), fTh*1.25+modHoriz, fTv*8.00, fTh*1.00, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, BUTTON_04_D_EXTG), fTh*2.30+modHoriz, fTv*8.00, fTh*1.00, fTv*1.60, TRUE);
	
	modHoriz = fTh*3.7;
	MoveWindow(GetDlgItem(hwnd, BUTTON_05_D_EXTG), fTh*0.20+modHoriz, fTv*0.50, fTh*3.10, fTv*1.80, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_09_D_EXTG), fTh*0.20+modHoriz, fTv*2.50, fTh*3.10, fTv*1.80, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_10_D_EXTG), fTh*0.20+modHoriz, fTv*4.60, fTh*1.54, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_11_D_EXTG), fTh*1.76+modHoriz, fTv*4.60, fTh*1.54, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_12_D_EXTG), fTh*0.20+modHoriz, fTv*6.30, fTh*1.54, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_13_D_EXTG), fTh*1.76+modHoriz, fTv*6.30, fTh*1.54, fTv*1.60, TRUE);
	MoveWindow(GetDlgItem(hwnd, EDIT_14_D_EXTG), fTh*0.20+modHoriz, fTv*8.00, fTh*3.10, fTv*1.60, TRUE);
	
	ShowWindow(GetDlgItem(hwnd, LISTVIEW_01_D_EXTG), SW_HIDE);
	MoveWindow(GetDlgItem(hwnd, LISTVIEW_01_D_EXTG), rc.right-fTh*12.50-5, rc.top+5, fTh*12.50, rc.bottom-10, TRUE);
	ListView_SetColumnWidth(GetDlgItem(hwnd, LISTVIEW_01_D_EXTG), 0, fTh*12.50-180);
	ShowWindow(GetDlgItem(hwnd, LISTVIEW_01_D_EXTG), SW_NORMAL);
}
//-------------------------------------------------->>
void ext_g_analyze(HWND hwnd) {
	CHAR cTexto[47], cConverter[3], cFormatar[55];
	INT iNum[15], iPosAtual, iLinha, iQuantidade, iControle;
	BOOL bAlternar;
	
	iLinha = iControle = 0;
	bAlternar = false;
	
	ZeroMemory(&cTexto, sizeof(cTexto));
	ZeroMemory(&iNum, sizeof(iNum));
	ZeroMemory(&longNumExtG, sizeof(longNumExtG));
	
	iQuantidade = GetDlgItemText(hwnd, EDIT_09_D_EXTG, cTexto, 45);
	
	if (strlen(cTexto) == 0) {
		show_message((LPSTR)"Caixa de texto vazia", 3);
		show_message((LPSTR)"Abortar", 2);
		return;
	}
	
	cTexto[iQuantidade] = ' ';
	cTexto[iQuantidade+1] = 0;
	
	for (int inc=0; cTexto[inc]; inc++) {
		if ((cTexto[inc] >= (int)'0') && (cTexto[inc] <= (int)'9')) {
			if (bAlternar == false) {
				bAlternar = true;
				iPosAtual = 0;
				ZeroMemory(&cConverter, sizeof(cConverter));
			}
			
			if (bAlternar == true) {
				cConverter[iPosAtual] = cTexto[inc];
				iPosAtual++;
				
				if (iPosAtual > 2) {
					show_message((LPSTR)"Os números inseridos são inválidos", 3);
					show_message((LPSTR)"Abortar", 2);
					return;
				}
				
				cConverter[iPosAtual] = 0;
			}
		} else {
			if (bAlternar == true) {
				bAlternar = false;
				
				iNum[iLinha] = atoi(cConverter);
				iLinha++;
				
				if (iLinha > 15) {
					show_message((LPSTR)"Quantidade superior à 15 números", 3);
					show_message((LPSTR)"Abortar", 2);
					return;
				}
			}
		}
	}
	
	if (iLinha < 15) {
		show_message((LPSTR)"Quantidade inferior à 15 números", 3);
		show_message((LPSTR)"Abortar", 2);
		return;
	}
	
	for (int inc=0; inc<15; inc++) {
		if (iNum[inc] == 0) {
			show_message((LPSTR)"O número zero não é válido", 3);
			show_message((LPSTR)"Abortar", 2);
			return;
		}
	}
	
	for (int inc=0; inc<15; inc++) {
		if (iNum[inc] > 25) {
			wsprintf(cFormatar, "Números maiores que 25 não são válidos: [%d]", iNum[inc]);
			show_message((LPSTR)cFormatar, 3);
			show_message((LPSTR)"Abortar", 2);
			return;
		}
	}
	
	for (int inc=0; inc<15; inc++) {
		for (int imp=0; imp<15; imp++) {
			if ((iNum[inc] == iNum[imp]) && (inc != imp)) {
				wsprintf(cFormatar, "Números repitidos: [%d %d]", iNum[inc], iNum[imp]);
				show_message((LPSTR)cFormatar, 3);
				show_message((LPSTR)"Abortar", 2);
				return;
			}
		}
	}
	
	for (int imp=1; imp<=25; imp++) {
		for (int inc=0; inc<15; inc++) {
			if (iNum[inc] == imp) {
				longNumExtG[iControle] = imp;
				iControle++;
				break;
			}
		}
	}
	
	longNumExtG[15] = 1;
	PostMessage(hwndPanelB, WM_COMMAND, MESSAGE_B, 0);
	
	panel_c_check(START, hwnd);
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelDExtProcG(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			ext_g_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			ext_g_wm_command(hwnd, wParam);
			break;
		
		case WM_SIZE:
			ext_g_wm_size(hwnd);
			break;
		
		case WM_TIMER:
			CHAR cTexto[11];
			if (!intMainTimerId) {
				if (wParam == TIMER_GENERATE_IMAGE_ID) {
					GetDlgItemText(hwnd, BUTTON_03_D_EXTG, cTexto, 10);
					if (!strcmp(cTexto, "Cancelado")) {
						KillTimer(hwnd, TIMER_GENERATE_IMAGE_ID);
						break;
					}
					
					GetDlgItemText(hwnd, BUTTON_02_D_EXTG, cTexto, 10);
					if (!strcmp(cTexto, "Pausar")) {
						KillTimer(hwnd, TIMER_GENERATE_IMAGE_ID);
						ext_g_save_card(EXECUTE, hwnd);
					}
				} else if (wParam == TIMER_CHECK_ID) {
					KillTimer(hwnd, TIMER_CHECK_ID);
					panel_c_check(EXECUTE, hwnd);
				}
			}
			break;
		
		case WM_LBUTTONDBLCLK:
			if (!IsWindowEnabled(GetDlgItem(hwnd, BUTTON_05_D_EXTG))) break;
			show_message((LPSTR)"Valores padrão", 3);
			ext_g_fill(hwnd);
			break;
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





