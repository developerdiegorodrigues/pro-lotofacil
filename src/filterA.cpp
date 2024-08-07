#include "resource.h"

//-------------------------------------------------->>
void ext_d_wm_create(HWND hwnd) {
	char cTexto[15];
	HFONT hFont;
	
	hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Tahoma");
	
	for (INT inc=STATIC_02_D_EXTD; inc<=STATIC_04_D_EXTD; inc++) {
		if (!(CreateWindowEx(
			WS_EX_WINDOWEDGE, "Static", 0,
			WS_CHILD | WS_VISIBLE | SS_GRAYFRAME,
			0, 0, 0, 0, hwnd, (HMENU) MAKEINTRESOURCE(inc), hInstance, 0
		))) error((LPSTR) "Erro: CreateWindowEx Statics ExtD!\t", true);
	}
	
	for (INT inc=CHECKBOX_01_D_EXTD; inc<=CHECKBOX_39_D_EXTD; inc++) {
		if (!(CreateWindowEx(
			WS_EX_WINDOWEDGE, "Button", 0,
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_CENTER | BS_PUSHLIKE,
			0, 0, 0, 0, hwnd, (HMENU) MAKEINTRESOURCE(inc), hInstance, 0
		))) error((LPSTR) "Erro: CreateWindowEx CheckBoxes ExtD!\t", true);
	}
	
	for (INT iControle=CHECKBOX_01_D_EXTD, inc=3, dec=12; iControle<=CHECKBOX_11_D_EXTD; iControle++, inc++, dec--) {
		if (dec < 10)
			(inc < 10) ? wsprintf(cTexto, "0%d : 0%d", dec, inc): wsprintf(cTexto, "0%d : %d", dec, inc);
		else
			(inc < 10) ? wsprintf(cTexto, "%d : 0%d", dec, inc): wsprintf(cTexto, "%d : %d", dec, inc);
		SetDlgItemText(hwnd, iControle, cTexto);
	}
	
	for (INT iControle=CHECKBOX_12_D_EXTD, inc=1; iControle<=CHECKBOX_21_D_EXTD; iControle++, inc++) {
		(inc < 10) ? wsprintf(cTexto, "B 0%d", inc): wsprintf(cTexto, "B %d", inc);
		SetDlgItemText(hwnd, iControle, cTexto);
	}
	
	for (INT iControle=CHECKBOX_22_D_EXTD, comp=0; iControle<=CHECKBOX_39_D_EXTD; iControle++, comp++) {
		switch (comp) {
			case 0: SetDlgItemText(hwnd, iControle, "33333"); break;
			case 1: SetDlgItemText(hwnd, iControle, "43332"); break;
			case 2: SetDlgItemText(hwnd, iControle, "44322"); break;
			case 3: SetDlgItemText(hwnd, iControle, "44331"); break;
			case 4: SetDlgItemText(hwnd, iControle, "44421"); break;
			case 5: SetDlgItemText(hwnd, iControle, "44430"); break;
			case 6: SetDlgItemText(hwnd, iControle, "53322"); break;
			case 7: SetDlgItemText(hwnd, iControle, "53331"); break;
			case 8: SetDlgItemText(hwnd, iControle, "54222"); break;
			case 9: SetDlgItemText(hwnd, iControle, "54321"); break;
			case 10: SetDlgItemText(hwnd, iControle, "54330"); break;
			case 11: SetDlgItemText(hwnd, iControle, "54411"); break;
			case 12: SetDlgItemText(hwnd, iControle, "54420"); break;
			case 13: SetDlgItemText(hwnd, iControle, "55221"); break;
			case 14: SetDlgItemText(hwnd, iControle, "55311"); break;
			case 15: SetDlgItemText(hwnd, iControle, "55320"); break;
			case 16: SetDlgItemText(hwnd, iControle, "55410"); break;
			case 17: SetDlgItemText(hwnd, iControle, "55500"); break;
		}
	}
	
	for (INT inc=CHECKBOX_01_D_EXTD; inc<=CHECKBOX_39_D_EXTD; inc++)
		SendDlgItemMessage(hwnd, inc, WM_SETFONT, (WPARAM) hFont, MAKELPARAM(TRUE, 0));
}
//-------------------------------------------------->>
void ext_d_wm_command(HWND hwnd, WPARAM wParam) {
	if (wParam == MESSAGE_BLOCK) {
		for (int inc=CHECKBOX_01_D_EXTD; inc<=CHECKBOX_39_D_EXTD; inc++) EnableWindow(GetDlgItem(hwnd, inc), false);
		return;
	}
	
	if (wParam == MESSAGE_UNBLOCK) {
		for (int inc=CHECKBOX_01_D_EXTD; inc<=CHECKBOX_39_D_EXTD; inc++) EnableWindow(GetDlgItem(hwnd, inc), true);
		return;
	}
	
	SetFocus(hwnd);
}
//-------------------------------------------------->>
void ext_d_wm_size(HWND hwnd) {
	RECT rc;
	FLOAT fTh, fTv, fLargura, fAltGeral, fModHoriz, fPosIniHoriz, fEspHoriz, fPosIniVert, fEspVert;
	
	GetClientRect(hwnd, &rc);
	
	fTh = rc.right / 20;
	fTv = rc.bottom / 10;
	
	fAltGeral = fTv*1.65;
	fModHoriz	= fTh*0.50;
	fPosIniHoriz= fTh*0.20 + fModHoriz;
	fEspHoriz	= fTh*1.85;
	fPosIniVert	= fTv*1.50;
	fEspVert	= fTv*1.75;
	fLargura	= fTh*1.80;
	
	MoveWindow(
		GetDlgItem(hwnd, STATIC_02_D_EXTD),
		fPosIniHoriz - 5.00,
		fPosIniVert - 5.00,
		fLargura + fEspHoriz*2 + 10.00,
		fAltGeral + fEspVert*3 + 10.00,
		TRUE
	);
	
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_01_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_02_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_03_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_04_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_05_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_06_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_07_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_08_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_09_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_10_D_EXTD), fPosIniHoriz+fEspHoriz*0.5, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_11_D_EXTD), fPosIniHoriz+fEspHoriz*1.5, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	
	fModHoriz	= fTh*7.00;
	fPosIniHoriz= fTh*0.20 + fModHoriz;
	fEspHoriz	= fTh*1.45;
	fLargura	= fTh*1.40;
	
	MoveWindow(GetDlgItem(hwnd, STATIC_03_D_EXTD),
	fPosIniHoriz - 5.00,
	fPosIniVert - 5.00,
	fLargura + fEspHoriz*2 + 10.00,
	fAltGeral + fEspVert*3 + 10.00,
	TRUE);
	
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_12_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_13_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_14_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_15_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_16_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_17_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_18_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_19_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_20_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_21_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	
	fModHoriz	= fTh*12.30;
	fPosIniHoriz= fTh*0.20 + fModHoriz;
	fEspHoriz	= fTh*1.45;
	fLargura	= fTh*1.40;
	
	MoveWindow(GetDlgItem(hwnd, STATIC_04_D_EXTD),
	fPosIniHoriz - 5.00,
	fPosIniVert - 5.00,
	fLargura + fEspHoriz*4 + 10.00,
	fAltGeral + fEspVert*3 + 10.00,
	TRUE);
	
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_22_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_23_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_24_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_25_D_EXTD), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_26_D_EXTD), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*0, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_27_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_28_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_29_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_30_D_EXTD), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_31_D_EXTD), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*1, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_32_D_EXTD), fPosIniHoriz+fEspHoriz*0, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_33_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_34_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_35_D_EXTD), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_36_D_EXTD), fPosIniHoriz+fEspHoriz*4, fPosIniVert+fEspVert*2, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_37_D_EXTD), fPosIniHoriz+fEspHoriz*1, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_38_D_EXTD), fPosIniHoriz+fEspHoriz*2, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	MoveWindow(GetDlgItem(hwnd, CHECKBOX_39_D_EXTD), fPosIniHoriz+fEspHoriz*3, fPosIniVert+fEspVert*3, fLargura, fAltGeral, TRUE);
	
}
//-------------------------------------------------->>
void ext_d_wm_lbuttondblclk(HWND hwnd, LPARAM lParam) {
	static int iControle = 0;
	
	if (!IsWindowEnabled(GetDlgItem(hwndPanelC, BUTTON_04_C))) return;
	
	for (INT id=CHECKBOX_01_D_EXTD; id<=CHECKBOX_39_D_EXTD; id++) CheckDlgButton(hwnd, id, BST_UNCHECKED);
	
	switch (iControle) {
		case 0:
			for (INT id=CHECKBOX_01_D_EXTD; id<=CHECKBOX_11_D_EXTD; id++) CheckDlgButton(hwnd, id, BST_CHECKED);
			iControle++;
			break;
			
		case 1:
			for (INT id=CHECKBOX_12_D_EXTD; id<=CHECKBOX_21_D_EXTD; id++) CheckDlgButton(hwnd, id, BST_CHECKED);
			iControle++;
			break;
			
		case 2:
			for (INT id=CHECKBOX_22_D_EXTD; id<=CHECKBOX_39_D_EXTD; id++) CheckDlgButton(hwnd, id, BST_CHECKED);
			iControle++;
			break;
			
		case 3:
			iControle=0;
			break;
	}
}
//-------------------------------------------------->>
void ext_d_wm_rbuttondblclk(HWND hwnd, LPARAM lParam) {
	static int iControle = 0;
	
	if (!IsWindowEnabled(GetDlgItem(hwndPanelC, BUTTON_04_C))) return;
	
	switch (iControle) {
		case 0:
			for (INT id=CHECKBOX_01_D_EXTD; id<=CHECKBOX_11_D_EXTD; id++) CheckDlgButton(hwnd, id, BST_CHECKED);
			iControle++;
			break;
			
		case 1:
			for (INT id=CHECKBOX_12_D_EXTD; id<=CHECKBOX_21_D_EXTD; id++) CheckDlgButton(hwnd, id, BST_CHECKED);
			iControle++;
			break;
			
		case 2:
			for (INT id=CHECKBOX_22_D_EXTD; id<=CHECKBOX_39_D_EXTD; id++) CheckDlgButton(hwnd, id, BST_CHECKED);
			iControle++;
			break;
			
		case 3:
			for (INT id=CHECKBOX_01_D_EXTD; id<=CHECKBOX_39_D_EXTD; id++) CheckDlgButton(hwnd, id, BST_UNCHECKED);
			iControle=0;
			break;
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelDExtProcD(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			ext_d_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			ext_d_wm_command(hwnd, wParam);
			break;
		
		case WM_SIZE:
			ext_d_wm_size(hwnd);
			break;
		
		case WM_LBUTTONDBLCLK:
			ext_d_wm_lbuttondblclk(hwnd, lParam);
			break;
		
		case WM_RBUTTONDBLCLK:
			ext_d_wm_rbuttondblclk(hwnd, lParam);
			break;
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





