#include "resource.h"

#define ListView01_Style WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER

INT iPaintControle;
//-------------------------------------------------->>
void panel_b_wm_create(HWND hwnd) {
	HWND hListView;
	LV_COLUMN lvCol;
	HFONT hFont;
	
	hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Consolas");
	
	if (!(hListView = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysListView32", 0,
		ListView01_Style,
		0, 0, 0, 0, hwnd, (HMENU) LISTVIEW_01_B, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysListView01 PanelB!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "Salvar",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_01_B, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Button01 PanelB!\t", true);
	
	ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	ZeroMemory(&lvCol, sizeof(lvCol));
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_CENTER;
	lvCol.cx = 105;
	lvCol.pszText = (LPSTR) "Info";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView, 0, &lvCol);
	
	SendMessage(hListView, WM_SETFONT, (WPARAM) hFont, MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(hwnd, BUTTON_01_B, WM_SETFONT, (WPARAM) GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
}
//-------------------------------------------------->>
void panel_b_wm_paint(HWND hwnd, HDC hdcWindow) {
	HFONT hFont;
	RECT rect, rc;
	FLOAT fLargura, fAltura, fQuadrosLarg, fQuadrosAlt, fIniHoriz, fIniVert, fPx, fPy, fPl, fPa;
	CHAR cTexto[3];
	
	GetClientRect(hwnd, &rc);
	
	static HBRUSH
		hBrushA = CreateSolidBrush(COLOR_CARD_BACKGROUND),
		hBrushB = CreateSolidBrush(COLOR_CARD_BUTTON_MARKED),
		hBrushC = CreateSolidBrush(COLOR_CARD_BUTTON_NORMAL),
		hBrushD = CreateSolidBrush(COLOR_GRAPHIC_MARKED);
	
	static HPEN
		hPenA = CreatePen(PS_SOLID, 0, COLOR_CARD_LINE),
		hPenB = CreatePen(PS_SOLID, 0, COLOR_GRAPHIC_LINE);
	
	hFont = CreateFont(
		(rc.bottom/10)*0.60, (rc.right/10)*0.22,
		0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Tahoma"
	);
	
	SelectObject(hdcWindow, hBrushA);
	SelectObject(hdcWindow, hPenA);
	SelectObject(hdcWindow, hFont);
	SetTextColor(hdcWindow, COLOR_CARD_LINE);
	SetBkMode(hdcWindow, TRANSPARENT);
	
	fLargura = (rc.right/10)*5;
	fAltura = (rc.bottom/10)*8;
	fQuadrosLarg = fLargura / 6;
	fQuadrosAlt = fAltura / 6;
	fIniHoriz = rc.right/2 - fLargura/2;
	fIniVert = rc.bottom/2 - fAltura/2;
	
	RoundRect(hdcWindow, fIniHoriz, fIniVert, fIniHoriz+fLargura, fIniVert+fAltura, 28, 28);
	
	for (INT mod=1; mod<6; mod++) {
		for (INT inc=1; inc<6; inc++) {
			fPx = fIniHoriz - ((fQuadrosLarg/10)*4) + fQuadrosLarg * inc;
			fPy = fIniVert - ((fQuadrosAlt/10)*4) + fQuadrosAlt * mod;
			fPl = fIniHoriz - ((fQuadrosLarg/10)*6) + fQuadrosLarg * (inc + 1);
			fPa = fIniVert - ((fQuadrosAlt/10)*6) + fQuadrosAlt * (mod + 1);
			
			SelectObject(hdcWindow, hBrushC);
			
			if (iPaintControle == MESSAGE_A) {
				for (INT ver=0; ver<15; ver++) {
					if ((longCardExtA[0][ver]) == inc+((mod-1)*5)) {
						SelectObject(hdcWindow, hBrushB);
						break;
					}
				}
			} else if (iPaintControle == MESSAGE_B) {
				for (INT ver=0; ver<15; ver++) {
					if ((longNumExtG[ver]) == inc+((mod-1)*5)) {
						SelectObject(hdcWindow, hBrushB);
						break;
					}
				}
			}
			
			Rectangle(hdcWindow, fPx, fPy, fPl, fPa);
			
			wsprintf(cTexto, "%d", inc+((mod-1)*5));
			SetRect(&rect, fPx, fPy, fPl, fPa);
			DrawText(hdcWindow, cTexto, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		}
	}
	
	fLargura = (rc.right/10)*5;
	fAltura = (rc.bottom/10)*8;
	fQuadrosLarg = fLargura / 7;
	fQuadrosAlt = fAltura / 25;
	fIniHoriz = (rc.right/10)*0.4;
	fIniVert = rc.bottom/2 - fAltura/2;
	
	SelectObject(hdcWindow, hPenB);
	
	for (INT mod=0; mod<25; mod++) {
		SelectObject(hdcWindow, hBrushC);
		
		if (iPaintControle == MESSAGE_A) {
			for (INT ver=0; ver<15; ver++) {
				if ((longCardExtA[0][ver]) == mod+1) {
					SelectObject(hdcWindow, hBrushD);
					break;
				}
			}
		} else if (iPaintControle == MESSAGE_B) {
			for (INT ver=0; ver<15; ver++) {
				if ((longNumExtG[ver]) == mod+1) {
					SelectObject(hdcWindow, hBrushD);
					break;
				}
			}
		}
		
		fPx = fIniHoriz + fQuadrosLarg;
		fPy = fIniVert + fQuadrosAlt * mod;
		fPl = fIniHoriz + fQuadrosLarg * 2;
		fPa = fIniVert + fQuadrosAlt * (mod + 1) + 1;
		
		Rectangle(hdcWindow, fPx, fPy, fPl, fPa);
	}
	
	DeleteObject(hFont);
}
//-------------------------------------------------->>
void panel_b_wm_command(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	if (wParam == MESSAGE_A) {
		HWND hListView;
		LV_ITEM lvItem;
		RECT rc, rect;
		LONG lMax;
		INT iModif[25], iApoio[5], iPares, iImpares, iBlocos, iControle;
		FLOAT fLargura, fAltura, fIniHoriz, fIniVert;
		CHAR cFormatar[25], cData[12], cCasasLinha[5];
		
		iPaintControle = MESSAGE_A;
		iPares = iImpares = iBlocos = iControle = 0;
		
		ZeroMemory(&iApoio, sizeof(iApoio));
		ZeroMemory(&lvItem, sizeof(lvItem));
		lvItem.mask = LVIF_TEXT;
		
		hListView = GetDlgItem(hwnd, LISTVIEW_01_B);
		
		if (longCardExtA[0][16] == 1) {
			lMax = ListView_GetItemCount(hListView_ext_a);
			
			ListView_GetItemText(hListView_ext_a, longCardExtA[0][15], 1, cData, 11);
			
			for (int inc=0; inc<15; inc++) (longCardExtA[0][inc] % 2 > 0) ? iImpares++: iPares++;
			
			ZeroMemory(&iModif, sizeof(iModif));
			for (int inc=0; inc<15; inc++) iModif[(longCardExtA[0][inc]-1)] = 1;
			for (int inc=1; inc<25; inc++) if ((iModif[inc] != 0) && (iModif[inc-1] != 0)) iModif[inc] = 2;
			for (int inc=0; inc<25; inc++) if (iModif[inc] == 1) iBlocos++;
			
			ZeroMemory(&iModif, sizeof(iModif));
			for (int inc=0; inc<15; inc++) iModif[(longCardExtA[0][inc]-1)] = 1;
			iApoio[0] = iModif[0] + iModif[1] + iModif[2] + iModif[3] + iModif[4];
			iApoio[1] = iModif[5] + iModif[6] + iModif[7] + iModif[8] + iModif[9];
			iApoio[2] = iModif[10] + iModif[11] + iModif[12] + iModif[13] + iModif[14];
			iApoio[3] = iModif[15] + iModif[16] + iModif[17] + iModif[18] + iModif[19];
			iApoio[4] = iModif[20] + iModif[21] + iModif[22] + iModif[23] + iModif[24];
			
			wsprintf(cFormatar, "%d%d%d%d%d", iApoio[0], iApoio[1], iApoio[2], iApoio[3], iApoio[4]);
			for (int letra=53; letra>=48; letra--) {
				for (int vas=0; vas<5; vas++) {
					if (cFormatar[vas] == letra) {
						cCasasLinha[iControle] = letra;
						iControle++;
					}
				}
			}
			
			if ((ListView_GetItemCount(hListView)) > 1) ListView_DeleteAllItems(hListView);
			
			lvItem.pszText = (LPSTR) "Concurso";
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "nº %d", longCardExtA[0][17]);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "de %d", lMax);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "%s", cData);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "P(%d) I(%d)", iPares, iImpares);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "Blocos: %d", iBlocos);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "CL: %c%c%c%c%c", cCasasLinha[0], cCasasLinha[1], cCasasLinha[2], cCasasLinha[3], cCasasLinha[4]);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
		} else if (longCardExtA[0][16] == 2) {
			for (int inc=0; inc<15; inc++) (longCardExtA[0][inc] % 2 > 0) ? iImpares++: iPares++;
			
			ZeroMemory(&iModif, sizeof(iModif));
			for (int inc=0; inc<15; inc++) iModif[(longCardExtA[0][inc]-1)] = 1;
			for (int inc=1; inc<25; inc++) if ((iModif[inc] != 0) && (iModif[inc-1] != 0)) iModif[inc] = 2;
			for (int inc=0; inc<25; inc++) if (iModif[inc] == 1) iBlocos++;
			
			ZeroMemory(&iModif, sizeof(iModif));
			for (int inc=0; inc<15; inc++) iModif[(longCardExtA[0][inc]-1)] = 1;
			iApoio[0] = iModif[0] + iModif[1] + iModif[2] + iModif[3] + iModif[4];
			iApoio[1] = iModif[5] + iModif[6] + iModif[7] + iModif[8] + iModif[9];
			iApoio[2] = iModif[10] + iModif[11] + iModif[12] + iModif[13] + iModif[14];
			iApoio[3] = iModif[15] + iModif[16] + iModif[17] + iModif[18] + iModif[19];
			iApoio[4] = iModif[20] + iModif[21] + iModif[22] + iModif[23] + iModif[24];
			
			wsprintf(cFormatar, "%d%d%d%d%d", iApoio[0], iApoio[1], iApoio[2], iApoio[3], iApoio[4]);
			for (int letra=53; letra>=48; letra--) {
				for (int vas=0; vas<5; vas++) {
					if (cFormatar[vas] == letra) {
						cCasasLinha[iControle] = letra;
						iControle++;
					}
				}
			}
			
			if ((ListView_GetItemCount(hListView)) > 1) ListView_DeleteAllItems(hListView);
			
			lvItem.pszText = (LPSTR) "Fechamento";
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "nº %d", longCardExtA[0][17]);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "de %d", longMaxExtC);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "P(%d) I(%d)", iPares, iImpares);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "Blocos: %d", iBlocos);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "CL: %c%c%c%c%c", cCasasLinha[0], cCasasLinha[1], cCasasLinha[2], cCasasLinha[3], cCasasLinha[4]);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
		} else if (longCardExtA[0][16] == 3) {
			for (int inc=0; inc<15; inc++) (longCardExtA[0][inc] % 2 > 0) ? iImpares++: iPares++;
			
			ZeroMemory(&iModif, sizeof(iModif));
			for (int inc=0; inc<15; inc++) iModif[(longCardExtA[0][inc]-1)] = 1;
			for (int inc=1; inc<25; inc++) if ((iModif[inc] != 0) && (iModif[inc-1] != 0)) iModif[inc] = 2;
			for (int inc=0; inc<25; inc++) if (iModif[inc] == 1) iBlocos++;
			
			ZeroMemory(&iModif, sizeof(iModif));
			for (int inc=0; inc<15; inc++) iModif[(longCardExtA[0][inc]-1)] = 1;
			iApoio[0] = iModif[0] + iModif[1] + iModif[2] + iModif[3] + iModif[4];
			iApoio[1] = iModif[5] + iModif[6] + iModif[7] + iModif[8] + iModif[9];
			iApoio[2] = iModif[10] + iModif[11] + iModif[12] + iModif[13] + iModif[14];
			iApoio[3] = iModif[15] + iModif[16] + iModif[17] + iModif[18] + iModif[19];
			iApoio[4] = iModif[20] + iModif[21] + iModif[22] + iModif[23] + iModif[24];
			
			wsprintf(cFormatar, "%d%d%d%d%d", iApoio[0], iApoio[1], iApoio[2], iApoio[3], iApoio[4]);
			for (int letra=53; letra>=48; letra--) {
				for (int vas=0; vas<5; vas++) {
					if (cFormatar[vas] == letra) {
						cCasasLinha[iControle] = letra;
						iControle++;
					}
				}
			}
			
			if ((ListView_GetItemCount(hListView)) > 1) ListView_DeleteAllItems(hListView);
			
			lvItem.pszText = (LPSTR) "Resultado";
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "id %d", longCardExtA[0][17]);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "nº %d", longCardExtA[0][15]+1);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "de %d", longMaxExtE);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "P(%d) I(%d)", iPares, iImpares);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "Blocos: %d", iBlocos);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "CL: %c%c%c%c%c", cCasasLinha[0], cCasasLinha[1], cCasasLinha[2], cCasasLinha[3], cCasasLinha[4]);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
		}
		
		GetClientRect(hwnd, &rc);
		
		fLargura = (rc.right/10)*4.5;
		fAltura = (rc.bottom/10)*7.5;
		fIniHoriz = rc.right/2 - fLargura/2;
		fIniVert = rc.bottom/2 - fAltura/2;
		SetRect(&rect, fIniHoriz, fIniVert, fIniHoriz+fLargura, fIniVert+fAltura);
		InvalidateRect(hwnd, &rect, TRUE);
		
		fLargura = (rc.right/10)*5;
		fAltura = (rc.bottom/10)*8;
		fIniHoriz = (rc.right/10)*0.4;
		fIniVert = rc.bottom/2 - fAltura/2;
		SetRect(&rect, fIniHoriz, fIniVert, fIniHoriz+fLargura, fIniVert+fAltura);
		InvalidateRect(hwnd, &rect, TRUE);
		
	} else if (wParam == MESSAGE_B) {
		HWND hListView;
		LV_ITEM lvItem;
		RECT rc, rect;
		FLOAT fLargura, fAltura, fIniHoriz, fIniVert;
		CHAR cFormatar[25], cCasasLinha[5];
		INT iModif[25], iApoio[5], iPares, iImpares, iBlocos, iControle;
		
		iPaintControle = MESSAGE_B;
		iPares = iImpares = iBlocos = iControle = 0;
		
		ZeroMemory(&iApoio, sizeof(iApoio));
		ZeroMemory(&lvItem, sizeof(lvItem));
		lvItem.mask = LVIF_TEXT;
		
		hListView = GetDlgItem(hwnd, LISTVIEW_01_B);
		
		if (longNumExtG[15] = 1) {
			for (int inc=0; inc<15; inc++) (longNumExtG[inc] % 2 > 0) ? iImpares++: iPares++;
			
			ZeroMemory(&iModif, sizeof(iModif));
			for (int inc=0; inc<15; inc++) iModif[(longNumExtG[inc]-1)] = 1;
			for (int inc=1; inc<25; inc++) if ((iModif[inc] != 0) && (iModif[inc-1] != 0)) iModif[inc] = 2;
			for (int inc=0; inc<25; inc++) if (iModif[inc] == 1) iBlocos++;
			
			ZeroMemory(&iModif, sizeof(iModif));
			for (int inc=0; inc<15; inc++) iModif[(longNumExtG[inc]-1)] = 1;
			iApoio[0] = iModif[0] + iModif[1] + iModif[2] + iModif[3] + iModif[4];
			iApoio[1] = iModif[5] + iModif[6] + iModif[7] + iModif[8] + iModif[9];
			iApoio[2] = iModif[10] + iModif[11] + iModif[12] + iModif[13] + iModif[14];
			iApoio[3] = iModif[15] + iModif[16] + iModif[17] + iModif[18] + iModif[19];
			iApoio[4] = iModif[20] + iModif[21] + iModif[22] + iModif[23] + iModif[24];
			
			wsprintf(cFormatar, "%d%d%d%d%d", iApoio[0], iApoio[1], iApoio[2], iApoio[3], iApoio[4]);
			for (int letra=53; letra>=48; letra--) {
				for (int vas=0; vas<5; vas++) {
					if (cFormatar[vas] == letra) {
						cCasasLinha[iControle] = letra;
						iControle++;
					}
				}
			}
			
			if ((ListView_GetItemCount(hListView)) > 1) ListView_DeleteAllItems(hListView);
			
			lvItem.pszText = (LPSTR) "Conferir";
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "Pares: %d", iPares);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "Impares: %d", iImpares);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "Bloco: %d", iBlocos);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "%d %d %d %d %d", iApoio[0], iApoio[1], iApoio[2], iApoio[3], iApoio[4]);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
			
			wsprintf(cFormatar, "%c %c %c %c %c", cCasasLinha[0], cCasasLinha[1], cCasasLinha[2], cCasasLinha[3], cCasasLinha[4]);
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView, &lvItem);
			lvItem.iItem++;
		}
		
		GetClientRect(hwnd, &rc);
		
		fLargura = (rc.right/10)*4.5;
		fAltura = (rc.bottom/10)*7.5;
		fIniHoriz = rc.right/2 - fLargura/2;
		fIniVert = rc.bottom/2 - fAltura/2;
		SetRect(&rect, fIniHoriz, fIniVert, fIniHoriz+fLargura, fIniVert+fAltura);
		InvalidateRect(hwnd, &rect, TRUE);
		
		fLargura = (rc.right/10)*5;
		fAltura = (rc.bottom/10)*8;
		fIniHoriz = (rc.right/10)*0.4;
		fIniVert = rc.bottom/2 - fAltura/2;
		SetRect(&rect, fIniHoriz, fIniVert, fIniHoriz+fLargura, fIniVert+fAltura);
		InvalidateRect(hwnd, &rect, TRUE);
	} else if (LOWORD(wParam) == BUTTON_01_B) {
		if ((iPaintControle == MESSAGE_A) || (iPaintControle == MESSAGE_B)) {
			LONG lMatriz[16], lgId;
			INT retorno;
			
			ZeroMemory(&lMatriz, sizeof(lMatriz));
			
			if (!PathFileExists("cartelas")) CreateDirectory("cartelas", NULL);
			
			ShowWindow(hwndPaleta, SW_SHOWNORMAL);
			
			if (iPaintControle == MESSAGE_A) {
				lMatriz[0] = longCardExtA[0][17];
				for (int inc=0; inc<15; inc++) lMatriz[inc+1] = longCardExtA[0][inc];
				retorno = ext_g_save_image(lMatriz, 0);
			} else {
				for (int inc=0; inc<15; inc++) lMatriz[inc+1] = longNumExtG[inc];
				retorno = ext_g_save_image(lMatriz, 0);
			}
			
			(retorno) ?
				show_message((LPSTR)"Erro ao salvar imagens imagem", 3):
				show_message((LPSTR) "Salvo", 2);
			
			ShowWindow(hwndPaleta, SW_HIDE);
		}
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelBProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			panel_b_wm_create(hwnd);
			break;
			
		case WM_COMMAND:
			panel_b_wm_command(hwnd, wParam, lParam);
			break;
		
		case WM_PAINT:
			PAINTSTRUCT PaintStruct;
			HDC hdcWindow;
			hdcWindow = BeginPaint(hwnd, &PaintStruct);
			general_wm_paint(hwnd, hdcWindow);
			panel_b_wm_paint(hwnd, hdcWindow);
			EndPaint(hwnd, &PaintStruct);
			break;
		
		case WM_LBUTTONDBLCLK:
			CHAR cFormatar[60];
			if ((iPaintControle == MESSAGE_A) && (longCardExtA[0][0])) {
				wsprintf(cFormatar, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				longCardExtA[0][0], longCardExtA[0][1], longCardExtA[0][2], longCardExtA[0][3], longCardExtA[0][4],
				longCardExtA[0][5], longCardExtA[0][6], longCardExtA[0][7], longCardExtA[0][8], longCardExtA[0][9],
				longCardExtA[0][10], longCardExtA[0][11], longCardExtA[0][12], longCardExtA[0][13], longCardExtA[0][14]);
				SetDlgItemText(hExtG, EDIT_09_D_EXTG, cFormatar);
				show_message((LPSTR)cFormatar, 1);
			} else if ((iPaintControle == MESSAGE_B) && (longNumExtG[0])) {
				wsprintf(cFormatar, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				longNumExtG[0], longNumExtG[1], longNumExtG[2], longNumExtG[3], longNumExtG[4],
				longNumExtG[5], longNumExtG[6], longNumExtG[7], longNumExtG[8], longNumExtG[9],
				longNumExtG[10], longNumExtG[11], longNumExtG[12], longNumExtG[13], longNumExtG[14]);
				SetDlgItemText(hExtG, EDIT_09_D_EXTG, cFormatar);
				show_message((LPSTR)cFormatar, 1);
			}
			break;
		
		case WM_SIZE:
			RECT rc;
			FLOAT fTh, fTv;
			GetClientRect(hwnd, &rc);
			fTh = rc.right / 10;
			fTv = rc.bottom / 10;
			MoveWindow(GetDlgItem(hwnd, LISTVIEW_01_B), fTh*7.80, fTv*1.10, fTh*1.80, fTv*6.0, TRUE);
			MoveWindow(GetDlgItem(hwnd, BUTTON_01_B), fTh*7.80, fTv*7.20, fTh*1.80, fTv*0.70, TRUE);
			break;
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





