#include "resource.h"

#define ListView01_Style WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER
//-------------------------------------------------->>
void ext_f_wm_create(HWND hwnd) {
	HWND hListView;
	HFONT hFont;
	LV_COLUMN lvCol;
	LV_ITEM lvItem;
	char cTexto[15];
	
	hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Tahoma");
	
	for (INT inc=STATIC_01_F; inc<=STATIC_02_F; inc++) {
		if (!(CreateWindowEx(
			WS_EX_WINDOWEDGE, "Static", 0,
			WS_CHILD | WS_VISIBLE | SS_GRAYFRAME,
			0, 0, 0, 0, hwnd, (HMENU) MAKEINTRESOURCE(inc), hInstance, 0
		))) error((LPSTR) "Erro: CreateWindowEx Statics ExtF!\t", true);
	}
	
	if (!(hListView = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysListView32", 0,
		ListView01_Style,
		0, 0, 0, 0, hwnd, (HMENU) LISTVIEW_01_D_EXTF, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysListView01 ExtF!\t", true);
	
	for (INT inc=CHECKBOX_01_D_EXTF; inc<=CHECKBOX_50_D_EXTF; inc++) {
		if (!(CreateWindowEx(
			WS_EX_WINDOWEDGE, "Button", 0,
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_CENTER | BS_PUSHLIKE,
			0, 0, 0, 0, hwnd, (HMENU) MAKEINTRESOURCE(inc), hInstance, 0
		))) error((LPSTR) "Erro: CreateWindowEx CheckBoxes ExtF!\t", true);
	}
	
	for (INT iControle=CHECKBOX_01_D_EXTF, inc=1; iControle<=CHECKBOX_25_D_EXTF; iControle++, inc++) {
		(inc < 10) ? wsprintf(cTexto, "0%d", inc): wsprintf(cTexto, "%d", inc);
		SetDlgItemText(hwnd, iControle, cTexto);
	}
	
	for (INT iControle=CHECKBOX_26_D_EXTF, inc=1; iControle<=CHECKBOX_50_D_EXTF; iControle++, inc++) {
		(inc < 10) ? wsprintf(cTexto, "0%d", inc): wsprintf(cTexto, "%d", inc);
		SetDlgItemText(hwnd, iControle, cTexto);
	}
	
	ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	ListView_SetTextColor(hListView, COLORREF(RGB(45, 45, 45)));
	
	ZeroMemory(&lvCol, sizeof(lvCol));
	lvCol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.pszText = (LPSTR) "Pré-Configurados";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView, 0, &lvCol);
	
	ZeroMemory(&lvItem, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = (LPSTR) "Nenhum";
	ListView_InsertItem(hListView, &lvItem);
	lvItem.iItem++;
	
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = (LPSTR) "[7:8] [B7] [43332] [-5] (994c)";
	ListView_InsertItem(hListView, &lvItem);
	lvItem.iItem++;
	
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = (LPSTR) "[-6] [+6] (715c)";
	ListView_InsertItem(hListView, &lvItem);
	lvItem.iItem++;
	
	for (INT inc=LISTVIEW_01_D_EXTF; inc<=CHECKBOX_50_D_EXTF; inc++)
		SendDlgItemMessage(hwnd, inc, WM_SETFONT, (WPARAM) hFont, MAKELPARAM(TRUE, 0));
}
//-------------------------------------------------->>
void ext_f_wm_command(HWND hwnd, WPARAM wParam) {
	if (wParam == MESSAGE_BLOCK) {
		for (int inc=LISTVIEW_01_D_EXTF; inc<=CHECKBOX_50_D_EXTF; inc++) EnableWindow(GetDlgItem(hwnd, inc), false);
		return;
	}
	
	if (wParam == MESSAGE_UNBLOCK) {
		for (int inc=LISTVIEW_01_D_EXTF; inc<=CHECKBOX_50_D_EXTF; inc++) EnableWindow(GetDlgItem(hwnd, inc), true);
		return;
	}
	
	if (LOWORD(wParam) >= CHECKBOX_01_D_EXTF && LOWORD(wParam) <= CHECKBOX_25_D_EXTF) {
		CheckDlgButton(hExtF, LOWORD(wParam) + 25, BST_UNCHECKED);
	} else if (LOWORD(wParam) >= CHECKBOX_26_D_EXTF && LOWORD(wParam) <= CHECKBOX_50_D_EXTF) {
		CheckDlgButton(hExtF, LOWORD(wParam) - 25, BST_UNCHECKED);
	}
	
	SetFocus(hwnd);
}
//-------------------------------------------------->>
void ext_f_wm_notify(WPARAM wParam, LPARAM lParam) {
	if (((int) wParam == LISTVIEW_01_D_EXTF)) {
		HWND hListView;
		DWORD dwStatus;
		UINT uCode, uVKey;
		INT iItem, iMax;
		
		hListView = ((NMHDR*)lParam)->hwndFrom;
		uCode = ((NMHDR*)lParam)->code;
		uVKey = ((LV_KEYDOWN*)lParam)->wVKey;
		iMax = ListView_GetItemCount(hListView);
		
		if ((uCode != NM_DBLCLK) && ((uCode != LVN_KEYDOWN))) return;
		if ((uCode == LVN_KEYDOWN) && (uVKey != VK_RETURN)) return;
		
		if (uCode == NM_DBLCLK) {
			iItem = ((NMLISTVIEW*) lParam)->iItem;
		} else if (uCode == LVN_KEYDOWN) {
			for (int inc=0; inc<iMax; inc++) {
				dwStatus = ListView_GetItemState(hListView, inc, LVIS_SELECTED);
				if (dwStatus == LVIS_SELECTED) {
					iItem = inc;
					break;
				}
			}
		}
		
		for (int inc=CHECKBOX_01_D_EXTD; inc<=CHECKBOX_39_D_EXTD; inc++) CheckDlgButton(hExtD, inc, BST_UNCHECKED);
		for (int inc=CHECKBOX_01_D_EXTF; inc<=CHECKBOX_50_D_EXTF; inc++) CheckDlgButton(hExtF, inc, BST_UNCHECKED);
		
		switch (iItem) {
			case 0:
				show_message((LPSTR) "Limpo", 3);
				break;
				
			case 1:
				for (int inc=CHECKBOX_01_D_EXTD; inc<=CHECKBOX_39_D_EXTD; inc++) CheckDlgButton(hExtD, inc, BST_CHECKED);
				CheckDlgButton(hExtD, CHECKBOX_06_D_EXTD, BST_UNCHECKED);
				CheckDlgButton(hExtD, CHECKBOX_18_D_EXTD, BST_UNCHECKED);
				CheckDlgButton(hExtD, CHECKBOX_23_D_EXTD, BST_UNCHECKED);
				CheckDlgButton(hExtF, CHECKBOX_03_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_07_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_14_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_19_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_22_D_EXTF, BST_CHECKED);
				break;
				
			case 2:
				CheckDlgButton(hExtF, CHECKBOX_03_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_06_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_12_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_16_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_17_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_23_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_35_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_38_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_39_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_40_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_44_D_EXTF, BST_CHECKED);
				CheckDlgButton(hExtF, CHECKBOX_49_D_EXTF, BST_CHECKED);
				break;
		}
	}
}
//-------------------------------------------------->>
void ext_f_wm_size(HWND hwnd) {
	RECT rc;
	FLOAT fTh, fTv, fLargura, fAltGeral, fModHoriz, fPosIniHoriz, fEspHoriz, fPosIniVert, fEspVert;
	
	GetClientRect(hwnd, &rc);
	
	fTh = rc.right / 20;
	fTv = rc.bottom / 11;
	
	fAltGeral = fTv*1.75;
	
	fModHoriz	= fTh*0.50;
	fPosIniHoriz= fTh*0.20 + fModHoriz;
	fEspHoriz	= fTh*1.35;
	fPosIniVert	= fTv*1.20;
	fEspVert	= fTv*1.85;
	fLargura	= fTh*1.30;
	
	MoveWindow(GetDlgItem(hwnd, STATIC_01_F),
		fPosIniHoriz - 5.00,
		fPosIniVert - 5.00,
		fLargura + fEspHoriz*4 + 10.00,
		fAltGeral + fEspVert*4 + 10.00,
		TRUE
	);
	
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_01_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_02_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_03_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_04_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_05_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_06_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_07_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_08_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_09_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_10_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_11_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_12_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_13_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_14_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_15_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_16_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_17_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_18_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_19_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_20_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_21_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_22_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_23_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_24_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_25_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	
	fModHoriz	= fTh*8.00;
	fPosIniHoriz= fTh*0.20 + fModHoriz;
	fEspHoriz	= fTh*1.35;
	fPosIniVert	= fTv*1.20;
	fEspVert	= fTv*1.85;
	fLargura	= fTh*1.30;
	
	MoveWindow(GetDlgItem(hwnd, STATIC_02_F),
		fPosIniHoriz - 5.00,
		fPosIniVert - 5.00,
		fLargura + fEspHoriz*4 + 10.00,
		fAltGeral + fEspVert*4 + 10.00,
		TRUE
	);
	
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_26_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_27_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_28_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_29_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_30_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_31_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_32_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_33_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_34_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_35_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_36_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_37_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_38_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_39_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_40_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_41_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_42_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_43_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_44_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_45_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_46_D_EXTF), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_47_D_EXTF), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_48_D_EXTF), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_49_D_EXTF), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_50_D_EXTF), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*4, fLargura, fAltGeral, TRUE);
	
	ShowWindow(GetDlgItem(hwnd, LISTVIEW_01_D_EXTF), SW_HIDE);
	MoveWindow(GetDlgItem(hwnd, LISTVIEW_01_D_EXTF), rc.right-fTh*4.70-5, rc.top+5, fTh*4.70, rc.bottom-10, TRUE);
	ListView_SetColumnWidth(GetDlgItem(hwnd, LISTVIEW_01_D_EXTF), 0, fTh*4.70);
	ShowWindow(GetDlgItem(hwnd, LISTVIEW_01_D_EXTF), SW_NORMAL);
}
//-------------------------------------------------->>
void ext_f_wm_lbuttondblclk(HWND hwnd) {
	static int iControle = 0;
	
	if (!IsWindowEnabled(GetDlgItem(hwndPanelC, BUTTON_04_C))) return;
	
	for (INT id=CHECKBOX_01_D_EXTF; id<=CHECKBOX_50_D_EXTF; id++) CheckDlgButton(hwnd, id, BST_UNCHECKED);
	
	switch (iControle) {
		case 0:
			for (INT id=CHECKBOX_01_D_EXTF; id<=CHECKBOX_25_D_EXTF; id++) CheckDlgButton(hwnd, id, BST_CHECKED);
			iControle++;
			break;
			
		case 1:
			for (INT id=CHECKBOX_26_D_EXTF; id<=CHECKBOX_50_D_EXTF; id++) CheckDlgButton(hwnd, id, BST_CHECKED);
			iControle++;
			break;
			
		case 2:
			iControle=0;
			break;
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelDExtProcF(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			ext_f_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			ext_f_wm_command(hwnd, wParam);
			break;
		
		case WM_NOTIFY:
			ext_f_wm_notify(wParam, lParam);
			break;
		
		case WM_SIZE:
			ext_f_wm_size(hwnd);
			break;
		
		case WM_LBUTTONDBLCLK:
			ext_f_wm_lbuttondblclk(hwnd);
			break;
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





