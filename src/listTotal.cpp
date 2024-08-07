#include "resource.h"

#define ListView01_Style WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER

HWND hListView_ext_c;
LONG longPosAtualExtC, longMaxExtC;
//-------------------------------------------------->>
void ext_c_wm_create(HWND hwnd) {
	LV_COLUMN lvCol;
	CHAR cTextoColuna[5];
	
	longPosAtualExtC = 0;
	
	if (!(hListView_ext_c = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysListView32", 0,
		ListView01_Style,
		0, 0, 0, 0, hwnd, (HMENU) LISTVIEW_01_D_EXTC, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysListView01 ExtC!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "<",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_01_D_EXTC, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Button01 ExtC!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", ">",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_02_D_EXTC, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Button02 ExtC!\t", true);
	
	ListView_SetExtendedListViewStyle(hListView_ext_c, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	ListView_SetTextBkColor(hListView_ext_c, COLORREF(COLOR_PANEL_BACKGROUND));
	ListView_SetTextColor(hListView_ext_c, COLORREF(COLOR_TEXT_LV01));
	ListView_SetBkColor(hListView_ext_c, COLORREF(COLOR_PANEL_BACKGROUND));
	
	ZeroMemory(&lvCol, sizeof(lvCol));
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvCol.fmt = LVCFMT_CENTER;
	
	lvCol.cx = 60;
	lvCol.pszText = (LPSTR) "Id";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView_ext_c, 0, &lvCol);
	
	for (int inc=0; inc<=14; inc++) {
		lvCol.cx = 36;
		wsprintf(cTextoColuna, "%d", inc+1);
		lvCol.pszText = cTextoColuna;
		lvCol.cchTextMax = strlen(cTextoColuna);
		ListView_InsertColumn(hListView_ext_c, inc+1, &lvCol);
	}
}
//-------------------------------------------------->>
void ext_c_list_view_insert_data(HWND hwnd) {
	HANDLE hFile;
	LV_ITEM lvItem;
	LPSTR lpStrMemoria;
	DWORD dwTamanho, dwRead;
	CHAR cConfVerter[16], cFormatar[75];
	LONG longPosIniciar, longLinhasCont, longColuna;
	INT iLinha, iPosAtual;
	BOOL bStatus, bVerificar;
	
	longMaxExtC = longPosIniciar = longLinhasCont = longColuna = iLinha = iPosAtual = 0;
	bStatus = bVerificar = false;
	
	hFile = CreateFile(DATA_LOTTERY_TOTAL, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	if (hFile != INVALID_HANDLE_VALUE) {
		dwTamanho = GetFileSize(hFile, NULL);
		if (dwTamanho != 0xFFFFFFFF) {
			lpStrMemoria = LPSTR(GlobalAlloc(GPTR, dwTamanho + 2));
			if (lpStrMemoria != NULL) {
				if (ReadFile(hFile, lpStrMemoria, dwTamanho, &dwRead, NULL)) {
					lpStrMemoria[dwTamanho] = ' ';
					dwTamanho += 1;
					lpStrMemoria[dwTamanho] = 0;
					bStatus = true;
				}
			}
		}
		CloseHandle(hFile);
	}
	
	if (bStatus == false) {
		(dwTamanho != 0xFFFFFFFF) ?
			lvItem.pszText = (LPSTR) "Você pode usar a opção [Gerar Arquivo] para criar um novo":
			lvItem.pszText = (LPSTR) "Memória insuficiente para processar!";
		
		ListView_InsertItem(hListView_ext_c, &lvItem);
		ListView_SetColumnWidth(hListView_ext_c, 0, 1500);
		return;
	}
	
	// Verificar quantidade total
	while (true) {
		if (longLinhasCont >= dwTamanho) break;
		
		if ((lpStrMemoria[longLinhasCont] >= (int)'0') && (lpStrMemoria[longLinhasCont] <= (int)'9')) {
			if (bVerificar == false) bVerificar = true;
		} else {
			if (bVerificar == true) {
				bVerificar = false;
				iLinha++;
				
				if (iLinha >= 16) {
					iLinha = 0;
					longColuna++;
				}
			}
		}
		longLinhasCont++;
	}
	
	longMaxExtC = longColuna;
	
	if (!longMaxExtC) {
		GlobalFree(lpStrMemoria);
		show_message((LPSTR)"Erro: Arquivo de dados formatado incorretamente", 3);
		return;
	}
	
	iLinha = longColuna = 0;
	bVerificar = bStatus = false;
	
	if (longPosAtualExtC >= 1) {
		while (true) {
			if (longPosIniciar >= dwTamanho) break;
			
			if ((lpStrMemoria[longPosIniciar] >= (int)'0') && (lpStrMemoria[longPosIniciar] <= (int)'9')) {
				if (bVerificar == false) bVerificar = true;
			} else {
				if (bVerificar == true) {
					bVerificar = false;
					iLinha++;
					
					if (iLinha >= 16) {
						iLinha = 0;
						longColuna++;
					}
					
					if (longColuna == longPosAtualExtC * 1000) {
						bStatus = true;
						break;
					}
				}
			}
			
			longPosIniciar++;
		}
		
		if (bStatus == false) {
			longPosIniciar = 0;
			longPosAtualExtC = 0;
			wsprintf(cFormatar, "Somente %d", longMaxExtC);
			show_message((LPSTR)cFormatar, 3);
		} else if (longPosAtualExtC*1000+1 > longMaxExtC) {
			longPosIniciar = 0;
			longPosAtualExtC = 0;
			show_message((LPSTR)"Voltando para o início - final atingido", 3);
		} else {
			wsprintf(cFormatar, "Visualizando entre %d e %d de um total de %d", longPosAtualExtC*1000+1, (longMaxExtC < 1000) ? longMaxExtC: longPosAtualExtC*1000+1000, longMaxExtC);
			show_message((LPSTR)cFormatar, 3);
		}
	} else {
		wsprintf(cFormatar, "Visualizando entre %d e %d de um total de %d", longPosAtualExtC*1000+1, (longMaxExtC < 1000) ? longMaxExtC: longPosAtualExtC*1000+1000, longMaxExtC);
		show_message((LPSTR)cFormatar, 3);
	}
	
	ZeroMemory(&lvItem, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT;
	iLinha = longColuna = 0;
	bVerificar = false;
	
	ShowWindow(hListView_ext_c, SW_HIDE);
	
	while (true) {
		if (longPosIniciar >= dwTamanho) break;
		
		if ((lpStrMemoria[longPosIniciar] >= (int)'0') && (lpStrMemoria[longPosIniciar] <= (int)'9')) {
			if (bVerificar == false) {
				bVerificar = true;
				iPosAtual = 0;
				ZeroMemory(&cConfVerter, strlen(cConfVerter));
			}
			
			if (bVerificar == true) {
				cConfVerter[iPosAtual] = lpStrMemoria[longPosIniciar];
				iPosAtual++;
				
				if (iPosAtual >= 8) {
					GlobalFree(lpStrMemoria);
					longMaxExtC = 0;
					ListView_DeleteAllItems(hListView_ext_c);
					lvItem.pszText = (LPSTR) "Erro: Arquivo de dados formatado incorretamente!";
					ListView_InsertItem(hListView_ext_c, &lvItem);
					ListView_SetColumnWidth(hListView_ext_c, 0, 1500);
					ShowWindow(hListView_ext_c, SW_SHOWNORMAL);
					return;
				}
				
				cConfVerter[iPosAtual] = 0;
			}
		} else {
			if (bVerificar == true) {
				bVerificar = false;
				
				if (iLinha == 0) {
					if (lvItem.iItem >= 1000) break;
					
					lvItem.pszText = (LPSTR) cConfVerter;
					ListView_InsertItem(hListView_ext_c, &lvItem);
					lvItem.iItem++;
					iLinha++;
				} else {
					ListView_SetItemText(hListView_ext_c, longColuna, iLinha, (LPSTR) cConfVerter);
					iLinha++;
				}
				
				if (iLinha >= 16) {
					iLinha = 0;
					longColuna++;
				}
			}
		}
		
		longPosIniciar++;
	}
	
	GlobalFree(lpStrMemoria);
	ListView_SetColumnWidth(hListView_ext_c, 0, 60);
	PostMessage(hwnd, WM_SIZE, 0, 0);
	ShowWindow(hListView_ext_c, SW_SHOWNORMAL);
}
//-------------------------------------------------->>
void ext_c_wm_command(HWND hwnd, WPARAM wParam) {
	if (wParam == MESSAGE_BLOCK) {
		EnableWindow(GetDlgItem(hwnd, BUTTON_01_D_EXTC), false);
		EnableWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTC), false);
		return;
	}
	
	if (wParam == MESSAGE_UNBLOCK) {
		EnableWindow(GetDlgItem(hwnd, BUTTON_01_D_EXTC), true);
		EnableWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTC), true);
		return;
	}
	
	if (longMaxExtC == 0) {
		show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
		return;
	}
	
	if (LOWORD(wParam) == BUTTON_01_D_EXTC) {
		if (longPosAtualExtC == 0) {
			show_message((LPSTR)"Já está no início", 3);
			return;
		}
		
		longPosAtualExtC--;
		ListView_DeleteAllItems(hListView_ext_c);
		ext_c_list_view_insert_data(hwnd);
	} else if (LOWORD(wParam) == BUTTON_02_D_EXTC) {
		longPosAtualExtC++;
		ListView_DeleteAllItems(hListView_ext_c);
		ext_c_list_view_insert_data(hwnd);
	}
}
//-------------------------------------------------->>
void ext_c_change(int Item, int max) {
	CHAR cValor[11];
	
	ZeroMemory(&longCardExtA, sizeof(longCardExtA));
	longCardExtA[0][16] = 2;
	
	for (int imp=0; imp<7; imp++) {
		if (Item+imp >= max) break;
		
		longCardExtA[imp][15] = Item+imp;
		ListView_GetItemText(hListView_ext_c, Item+imp, 0, cValor, 10);
		longCardExtA[imp][17] = atoi(cValor);
		
		for (int inc=1; inc<16; inc++) {
			ListView_GetItemText(hListView_ext_c, Item+imp, inc, cValor, 10);
			longCardExtA[imp][inc-1] = atoi(cValor);
		}
	}
	
	PostMessage(hwndPanelB, WM_COMMAND, MESSAGE_A, 0);
}
//-------------------------------------------------->>
void ext_c_wm_notify(WPARAM wParam, LPARAM lParam) {
	if (((NMHDR*)lParam)->hwndFrom == hListView_ext_c) {
		DWORD dwStatus;
		UINT uCode, uVKey;
		LONG lMax, lItem, lModificador;
		
		uCode = ((NMHDR*)lParam)->code;
		uVKey = ((LV_KEYDOWN*)lParam)->wVKey;
		lMax = ListView_GetItemCount(hListView_ext_c);
		
		if (uCode == LVN_KEYDOWN) {
			if (lMax < 7) {
				show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
				return;
			}
			
			if (uVKey == VK_RETURN) {	
				for (long inc=0; inc<lMax; inc++) {
					dwStatus = ListView_GetItemState(hListView_ext_c, inc, LVIS_SELECTED);
					if (dwStatus == LVIS_SELECTED) {
						lItem = inc;
						break;
					}
				}
				ext_c_change(lItem, lMax);
			} else if (uVKey == VK_UP || uVKey == VK_DOWN) {
				for (long inc=0; inc<lMax; inc++) {
					dwStatus = ListView_GetItemState(hListView_ext_c, inc, LVIS_SELECTED);
					if (dwStatus == LVIS_SELECTED)
					{
						lItem = inc;
						break;
					}
				}
				
				lModificador = (uVKey == VK_UP) ? lItem-1: lItem+1;
				if (lModificador < 0) {
					lModificador++;
				} else if (lModificador == lMax) {
					lModificador--;
				}
				ext_c_change(lModificador, lMax);
			}
		}
		else if ((uCode == NM_CLICK) || (uCode == NM_RCLICK)) {
			if (lMax < 7) {
				show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
				return;
			}
			
			lItem = ((NMLISTVIEW*) lParam)->iItem;
			ext_c_change(lItem, lMax);
		}
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelDExtProcC(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			ext_c_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			ext_c_wm_command(hwnd, wParam);
			break;
		
		case WM_NOTIFY:
			ext_c_wm_notify(wParam, lParam);
			break;
		
		case WM_SIZE: {
			RECT rc;
			FLOAT fHoriz;
			
			GetClientRect(hwnd, &rc);
			fHoriz = (rc.right-60) / 18.7;
			
			MoveWindow(hListView_ext_c, (rc.right/10)*0.70, 0, (rc.right/10)*8.60, rc.bottom, TRUE);
			MoveWindow(GetDlgItem(hwnd, BUTTON_01_D_EXTC), 0, 5, (rc.right/10)*0.50, rc.bottom-10, TRUE);
			MoveWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTC), rc.right-(rc.right/10)*0.50, 5, (rc.right/10)*0.50, rc.bottom-10, TRUE);
			
			ShowWindow(hListView_ext_c, SW_HIDE);
			for (int inc=1; inc < 16; inc++) ListView_SetColumnWidth(hListView_ext_c, inc, fHoriz);
			ShowWindow(hListView_ext_c, SW_NORMAL);
			break;
		}
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





