#include "resource.h"

#define ListView01_Style WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER
//-------------------------------------------------->>
void panel_a_wm_create(HWND hwnd) {
	HWND hListView;
	LV_COLUMN lvCol;
	HFONT hFont;
	
	hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Consolas");
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Listar",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_01_A, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Button01 PanelA!\t", true);
	
	if (!(hListView = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysListView32",
		0, ListView01_Style,
		0, 0, 0, 0, hwnd, (HMENU) LISTVIEW_01_A, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysListView01 PanelA!\t", true);
	
	ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	ZeroMemory(&lvCol, sizeof(lvCol));
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvCol.fmt = LVCFMT_CENTER;
	lvCol.cx = 255;
	lvCol.pszText = (LPSTR) "Estatísticas";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView, 0, &lvCol);
	
	SendDlgItemMessage(hwnd, BUTTON_01_A, WM_SETFONT, (WPARAM) GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
	SendMessage(hListView, WM_SETFONT, (WPARAM) hFont, MAKELPARAM(TRUE, 0));
}
//-------------------------------------------------->>
void panel_a_wm_command(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	if (LOWORD(wParam) == BUTTON_01_A) {
		HWND hListView, hListViewExtG;
		LV_ITEM lvItem;
		LONG lParImpar[11], lSep[10], lLimite, lNvLimite, lContador;
		INT iCasas[15], iOrganinar[25], iApoio[5], iQuantLinha[18], iCruzado[3], iQuant, iPares, iImpares, iControle;
		CHAR cTexto[11], cFormatar[70], cConferir[70], cCasasLinha[6];
		FLOAT fPorcent, fQuociente;
		
		ZeroMemory(&lParImpar, sizeof(lParImpar));
		ZeroMemory(&lSep, sizeof(lSep));
		ZeroMemory(&iCasas, sizeof(iCasas));
		ZeroMemory(&iQuantLinha, sizeof(iQuantLinha));
		ZeroMemory(&lvItem, sizeof(lvItem));
		
		lvItem.mask = LVIF_TEXT;
		lNvLimite = lContador = 0;
		
		hListView = GetDlgItem(hwnd, LISTVIEW_01_A);
		hListViewExtG = GetDlgItem(hExtG, LISTVIEW_01_D_EXTG);
		
		lLimite = ListView_GetItemCount(hListView_ext_a);
		
		if (!lLimite) {
			show_message((LPSTR)"Número insuficiente", 3);
			return;
		}
		
		fQuociente = lLimite * 0.01;
		
		if ((ListView_GetItemCount(hListView)) > 1) {
			ListView_DeleteAllItems(hListView);
			ListView_DeleteAllItems(hListViewExtG);
		}
		
		for (long ini=0; ini<lLimite; ini++) {
			for (int inc=2; inc<17; inc++) {
				ListView_GetItemText(hListView_ext_a, ini, inc, cTexto, 10);
				iCasas[inc-2] = atoi(cTexto);
			}
			
			iPares = iImpares = 0;
			for (int inc=0; inc<15; inc++) ((iCasas[inc] % 2) > 0) ? iImpares++: iPares++;
			
			ZeroMemory(&iCruzado, sizeof(iCruzado));
			
			switch (iPares) {
				case 12: lParImpar[0]++; iCruzado[0] = iPares; break;
				case 11: lParImpar[1]++; iCruzado[0] = iPares; break;
				case 10: lParImpar[2]++; iCruzado[0] = iPares; break;
				case 9: lParImpar[3]++; iCruzado[0] = iPares; break;
				case 8: lParImpar[4]++; iCruzado[0] = iPares; break;
				case 7: lParImpar[5]++; iCruzado[0] = iPares; break;
				case 6: lParImpar[6]++; iCruzado[0] = iPares; break;
				case 5: lParImpar[7]++; iCruzado[0] = iPares; break;
				case 4: lParImpar[8]++; iCruzado[0] = iPares; break;
				case 3: lParImpar[9]++; iCruzado[0] = iPares; break;
				case 2: lParImpar[10]++; iCruzado[0] = iPares; break;
			}
			
			iQuant = 0;
			ZeroMemory(&iOrganinar, sizeof(iOrganinar));
			for (int inc=0; inc<15; inc++) iOrganinar[iCasas[inc]-1] = 1;
			for (int inc=1; inc<25; inc++) if ((iOrganinar[inc] != 0) && (iOrganinar[inc-1] != 0)) iOrganinar[inc] = 2;
			for (int inc=0; inc<25; inc++) if (iOrganinar[inc] == 1) iQuant++;
			lSep[iQuant-1]++;
			
			iCruzado[1] = iQuant;
			
			iControle = 0;
			ZeroMemory(&iApoio, sizeof(iApoio));
			ZeroMemory(&iOrganinar, sizeof(iOrganinar));
			for (int inc=0; inc<15; inc++) iOrganinar[iCasas[inc]-1] = 1;
			iApoio[0] = iOrganinar[0] + iOrganinar[1] + iOrganinar[2] + iOrganinar[3] + iOrganinar[4];
			iApoio[1] = iOrganinar[5] + iOrganinar[6] + iOrganinar[7] + iOrganinar[8] + iOrganinar[9];
			iApoio[2] = iOrganinar[10] + iOrganinar[11] + iOrganinar[12] + iOrganinar[13] + iOrganinar[14];
			iApoio[3] = iOrganinar[15] + iOrganinar[16] + iOrganinar[17] + iOrganinar[18] + iOrganinar[19];
			iApoio[4] = iOrganinar[20] + iOrganinar[21] + iOrganinar[22] + iOrganinar[23] + iOrganinar[24];
			
			ZeroMemory(&cCasasLinha, sizeof(cCasasLinha));
			wsprintf(cFormatar, "%d%d%d%d%d", iApoio[0], iApoio[1], iApoio[2], iApoio[3], iApoio[4]);
			for (int letra=53; letra>=48; letra--) {
				for (int vas=0; vas<5; vas++) {
					if (cFormatar[vas] == letra) {
						cCasasLinha[iControle] = letra;
						iControle++;
					}
				}
			}
			
			iCruzado[2] = atoi(cCasasLinha);
			
			switch (atoi(cCasasLinha)) {
				case 33333: iQuantLinha[0]++; break;
				case 43332: iQuantLinha[1]++; break;
				case 44322: iQuantLinha[2]++; break;
				case 44331: iQuantLinha[3]++; break;
				case 44421: iQuantLinha[4]++; break;
				case 44430: iQuantLinha[5]++; break;
				case 53322: iQuantLinha[6]++; break;
				case 53331: iQuantLinha[7]++; break;
				case 54222: iQuantLinha[8]++; break;
				case 54321: iQuantLinha[9]++; break;
				case 54330: iQuantLinha[10]++; break;
				case 54411: iQuantLinha[11]++; break;
				case 54420: iQuantLinha[12]++; break;
				case 55221: iQuantLinha[13]++; break;
				case 55311: iQuantLinha[14]++; break;
				case 55320: iQuantLinha[15]++; break;
				case 55410: iQuantLinha[16]++; break;
				case 55500: iQuantLinha[17]++; break;
			}
			
			lNvLimite = ListView_GetItemCount(hListViewExtG);
			lContador = -1;
			wsprintf(cFormatar, "P(%d) I(%d) | Blocos: %d | CL: %d", iCruzado[0], 15-iCruzado[0], iCruzado[1], iCruzado[2]);
			
			for (long inc=0; inc<lNvLimite; inc++) {
				ListView_GetItemText(hListViewExtG, inc, 0, cConferir, 70);
				if (!strcmp(cFormatar, cConferir)) {
					lContador = inc;
					break;
				}
			}
			
			if (lContador != -1) {
				ListView_GetItemText(hListViewExtG, lContador, 1, cConferir, 70);
				wsprintf(cFormatar, "%d", atoi(cConferir)+1);
				ListView_SetItemText(hListViewExtG, lContador, 1, (LPSTR)cFormatar);
				fPorcent = (atoi(cConferir)+1) / fQuociente;
				wsprintf(cFormatar, "(%d%%)", (int)fPorcent);
				ListView_SetItemText(hListViewExtG, lContador, 2, (LPSTR)cFormatar);
			} else {
				wsprintf(cFormatar, "P(%d) I(%d) | Blocos: %d | CL: %d", iCruzado[0], 15-iCruzado[0], iCruzado[1], iCruzado[2]);
				lvItem.pszText = (LPSTR) cFormatar;
				ListView_InsertItem(hListViewExtG, &lvItem);
				ListView_SetItemText(hListViewExtG, lvItem.iItem, 1, (LPSTR)"1");
				ListView_SetItemText(hListViewExtG, lvItem.iItem, 2, (LPSTR)"(~0%)");
				lvItem.iItem++;
			}
		}
		
		lvItem.iItem = 0;
		lvItem.pszText = (LPSTR) "••• PAR MAX 12 - IMPAR MAX 13";
		ListView_InsertItem(hListView, &lvItem);
		lvItem.iItem++;
		
		for (int comp=0, dec=12; comp<11; comp++, dec--) {
			fPorcent = lParImpar[comp] / fQuociente;
			wsprintf(cFormatar, "P(%d) I(%d) | (%d%%) -> %d de %d", dec, comp + 3, (INT)fPorcent, lParImpar[comp], lLimite);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
		}
		
		lvItem.pszText = (LPSTR) "••• BLOCOS MAX 10 | MIN 1";
		ListView_InsertItem(hListView, &lvItem);
		lvItem.iItem++;
		
		for (int comp=0; comp<10; comp++) {
			fPorcent = lSep[comp] / fQuociente;
			wsprintf(cFormatar, "Blocos: %d | (%d%%) -> %d de %d", comp+1, (INT)fPorcent, lSep[comp], lLimite);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
		}
		
		lvItem.pszText = (LPSTR) "••• QUANT LINHA";
		ListView_InsertItem(hListView, &lvItem);
		lvItem.iItem++;
		
		for (int comp=0, alter; comp<18; comp++) {
			switch (comp) {
				case 0: alter = 33333; break;
				case 1: alter = 43332; break;
				case 2: alter = 44322; break;
				case 3: alter = 44331; break;
				case 4: alter = 44421; break;
				case 5: alter = 44430; break;
				case 6: alter = 53322; break;
				case 7: alter = 53331; break;
				case 8: alter = 54222; break;
				case 9: alter = 54321; break;
				case 10: alter = 54330; break;
				case 11: alter = 54411; break;
				case 12: alter = 54420; break;
				case 13: alter = 55221; break;
				case 14: alter = 55311; break;
				case 15: alter = 55320; break;
				case 16: alter = 55410; break;
				case 17: alter = 55500; break;
			}
			
			fPorcent = iQuantLinha[comp] / fQuociente;
			wsprintf(cFormatar, "CL: %d | (%d%%) -> %d de %d", alter, (INT)fPorcent, iQuantLinha[comp], lLimite);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
		}
		
		for (int comp=EXT_A; comp<=EXT_G; comp++) ShowWindow(GetDlgItem(hwndPanelD, comp), SW_HIDE);
		TabCtrl_SetCurSel(GetDlgItem(hwndPanelD, TABCONTROL_01_D), 6);
		ShowWindow(hExtG, SW_NORMAL);
		SetFocus(hExtG);
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelAProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			panel_a_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			panel_a_wm_command(hwnd, wParam, lParam);
			break;
		
		case WM_PAINT:
			PAINTSTRUCT PaintStruct;
			HDC hdcWindow;
			hdcWindow = BeginPaint(hwnd, &PaintStruct);
			general_wm_paint(hwnd, hdcWindow);
			EndPaint(hwnd, &PaintStruct);
			break;
		
		case WM_SIZE:
			RECT rc;
			FLOAT fTh, fTv;
			GetClientRect(hwnd, &rc);
			fTh = rc.right / 10;
			fTv = rc.bottom / 10;
			MoveWindow(GetDlgItem(hwnd, BUTTON_01_A), fTh*0.70, fTv*0.50, fTh*8.60, fTv*0.90, TRUE);
			MoveWindow(GetDlgItem(hwnd, LISTVIEW_01_A), fTh*0.70, fTv*1.70, fTh*8.60, fTv*7.90, TRUE);
			break;
		
		case WM_LBUTTONDBLCLK:
			if (PathFileExists(DATA_LOTTERY_GAME)) PostMessage(hwnd, WM_COMMAND, BUTTON_01_A, 0);
			else show_message((LPSTR)"Arquivo não encontrado", 3);
			break;
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





