#include "resource.h"

#define ListView01_Style WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER

HWND hListView_ext_e;
LONG longPosAtualExtE, longMaxExtE;
//-------------------------------------------------->>
void ext_e_wm_create(HWND hwnd) {
	LV_COLUMN lvCol;
	CHAR cTextoColuna[5];
	
	longPosAtualExtE = 0;
	
	if (!(hListView_ext_e = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysListView32", 0,
		ListView01_Style,
		0, 0, 0, 0, hwnd, (HMENU) LISTVIEW_01_D_EXTE, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysListView01 ExtE!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "<",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_01_D_EXTE, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Button01 ExtE!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", ">",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_02_D_EXTE, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Button02 ExtE!\t", true);
	
	ListView_SetExtendedListViewStyle(hListView_ext_e, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	ListView_SetTextBkColor(hListView_ext_e, COLORREF(COLOR_PANEL_BACKGROUND));
	ListView_SetTextColor(hListView_ext_e, COLORREF(COLOR_TEXT_LV01));
	ListView_SetBkColor(hListView_ext_e, COLORREF(COLOR_PANEL_BACKGROUND));
	
	ZeroMemory(&lvCol, sizeof(lvCol));
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvCol.fmt = LVCFMT_CENTER;
	
	lvCol.cx = 60;
	lvCol.pszText = (LPSTR) "Id";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView_ext_e, 0, &lvCol);
	
	for (int inc=0; inc<=14; inc++) {
		lvCol.cx = 36;
		wsprintf(cTextoColuna, "%d", inc+1);
		lvCol.pszText = cTextoColuna;
		lvCol.cchTextMax = strlen(cTextoColuna);
		ListView_InsertColumn(hListView_ext_e, inc+1, &lvCol);
	}
	
}
//-------------------------------------------------->>
void ext_e_list_view_insert_data(HWND hwnd) {
	HANDLE hFile;
	LV_ITEM lvItem;
	LPSTR lpStrMemoria;
	DWORD dwTamanho, dwRead;
	CHAR cConfVerter[16], cFormatar[75];
	LONG longPosIniciar, longLinhasCont, longColuna;
	INT iLinha, iPosAtual;
	BOOL bStatus, bVerificar;
	
	longMaxExtE = longPosIniciar = longLinhasCont = longColuna = iLinha = iPosAtual = 0;
	bStatus = bVerificar = false;
	
	hFile = CreateFile(DATA_RESULT, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
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
			lvItem.pszText = (LPSTR) "Você pode usar a opção [Rodar] para criar um novo":
			lvItem.pszText = (LPSTR) "Memória insuficiente para processar";
		
		ListView_SetColumnWidth(hListView_ext_e, 0, 1500);
		ListView_InsertItem(hListView_ext_e, &lvItem);
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
	
	longMaxExtE = longColuna;
	
	if (!longMaxExtE) {
		GlobalFree(lpStrMemoria);
		show_message((LPSTR)"Erro: Arquivo de dados formatado incorretamente", 3);
		return;
	}
	
	iLinha = longColuna = 0;
	bVerificar = bStatus = false;
	
	if (longPosAtualExtE >= 1) {
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
					
					if (longColuna == longPosAtualExtE * 1000) {
						bStatus = true;
						break;
					}
				}
			}
			
			longPosIniciar++;
		}
		
		if (bStatus == false) {
			longPosIniciar = 0;
			longPosAtualExtE = 0;
			wsprintf(cFormatar, "Somente %d", longMaxExtE);
			show_message((LPSTR)cFormatar, 3);
		} else if (longPosAtualExtE*1000+1 > longMaxExtE) {
			longPosIniciar = 0;
			longPosAtualExtE = 0;
			show_message((LPSTR)"Voltando para o início - final atingido", 3);
		} else {
			wsprintf(cFormatar, "Visualizando entre %d e %d de um total de %d", longPosAtualExtE*1000+1, (longMaxExtE < 1000) ? longMaxExtE: longPosAtualExtE*1000+1000, longMaxExtE);
			show_message((LPSTR)cFormatar, 3);
		}
	} else {
		wsprintf(cFormatar, "Visualizando entre %d e %d de um total de %d", longPosAtualExtE*1000+1, (longMaxExtE < 1000) ? longMaxExtE: longPosAtualExtE*1000+1000, longMaxExtE);
		show_message((LPSTR)cFormatar, 3);
	}
	
	ZeroMemory(&lvItem, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT;
	iLinha = longColuna = 0;
	bVerificar = false;
	
	ShowWindow(hListView_ext_e, SW_HIDE);
	
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
					longMaxExtE = 0;
					ListView_DeleteAllItems(hListView_ext_e);
					lvItem.pszText = (LPSTR) "Erro: Arquivo de dados formatado incorretamente!";
					ListView_InsertItem(hListView_ext_e, &lvItem);
					ListView_SetColumnWidth(hListView_ext_e, 0, 1500);
					ShowWindow(hListView_ext_e, SW_SHOWNORMAL);
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
					ListView_InsertItem(hListView_ext_e, &lvItem);
					lvItem.iItem++;
					iLinha++;
				} else {
					ListView_SetItemText(hListView_ext_e, longColuna, iLinha, (LPSTR) cConfVerter);
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
	ListView_SetColumnWidth(hListView_ext_e, 0, 60);
	PostMessage(hwnd, WM_SIZE, 0, 0);
	ShowWindow(hListView_ext_e, SW_SHOWNORMAL);
}
//-------------------------------------------------->>
void ext_e_wm_command(HWND hwnd, WPARAM wParam) {
	if (wParam == MESSAGE_BLOCK) {
		EnableWindow(GetDlgItem(hwnd, BUTTON_01_D_EXTE), false);
		EnableWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTE), false);
		return;
	}
	
	if (wParam == MESSAGE_UNBLOCK) {
		EnableWindow(GetDlgItem(hwnd, BUTTON_01_D_EXTE), true);
		EnableWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTE), true);
		return;
	}
	
	if (longMaxExtE == 0) {
		show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
		return;
	}
	
	if (LOWORD(wParam) == BUTTON_01_D_EXTE) {
		if (longPosAtualExtE == 0) {
			show_message((LPSTR)"Já está no início", 3);
			return;
		}
		longPosAtualExtE--;
		ListView_DeleteAllItems(hListView_ext_e);
		ext_e_list_view_insert_data(hwnd);
	} else if (LOWORD(wParam) == BUTTON_02_D_EXTE) {
		longPosAtualExtE++;
		ListView_DeleteAllItems(hListView_ext_e);
		ext_e_list_view_insert_data(hwnd);
	}
}
//-------------------------------------------------->>
void ext_e_change(int Item, int max) {
	CHAR cValor[11];
	
	ZeroMemory(&longCardExtA, sizeof(longCardExtA));
	longCardExtA[0][16] = 3;
	
	for (int imp=0; imp<7; imp++) {
		if (Item+imp >= max) break;
		
		longCardExtA[imp][15] = Item+imp;
		ListView_GetItemText(hListView_ext_e, Item+imp, 0, cValor, 10);
		longCardExtA[imp][17] = atoi(cValor);
		
		for (int inc=1; inc<16; inc++) {
			ListView_GetItemText(hListView_ext_e, Item+imp, inc, cValor, 10);
			longCardExtA[imp][inc-1] = atoi(cValor);
		}
	}
	
	PostMessage(hwndPanelB, WM_COMMAND, MESSAGE_A, 0);
}
//-------------------------------------------------->>
void ext_e_wm_notify(WPARAM wParam, LPARAM lParam) {
	if (((NMHDR*)lParam)->hwndFrom == hListView_ext_e) {
		DWORD dwStatus;
		UINT uCode, uVKey;
		LONG lMax, lItem, lModificador;
		
		uCode = ((NMHDR*)lParam)->code;
		uVKey = ((LV_KEYDOWN*)lParam)->wVKey;
		lMax = ListView_GetItemCount(hListView_ext_e);
		
		if (uCode == LVN_KEYDOWN) {
			if (lMax < 7) {
				show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
				return;
			}
			
			if (uVKey == VK_RETURN) {	
				for (long inc=0; inc<lMax; inc++) {
					dwStatus = ListView_GetItemState(hListView_ext_e, inc, LVIS_SELECTED);
					if (dwStatus == LVIS_SELECTED) {
						lItem = inc;
						break;
					}
				}
				ext_e_change(lItem, lMax);
			} else if (uVKey == VK_UP || uVKey == VK_DOWN) {
				for (long inc=0; inc<lMax; inc++) {
					dwStatus = ListView_GetItemState(hListView_ext_e, inc, LVIS_SELECTED);
					if (dwStatus == LVIS_SELECTED) {
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
				ext_e_change(lModificador, lMax);
			}
		} else if ((uCode == NM_CLICK) || uCode == NM_RCLICK) {
			if (lMax < 7) {
				show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
				return;
			}
			
			lItem = ((NMLISTVIEW*) lParam)->iItem;
			ext_e_change(lItem, lMax);
		}
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelDExtProcE(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			ext_e_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			ext_e_wm_command(hwnd, wParam);
			break;
		
		case WM_NOTIFY:
			ext_e_wm_notify(wParam, lParam);
			break;
		
		case WM_SIZE: {
			RECT rc;
			FLOAT fHoriz;
			
			GetClientRect(hwnd, &rc);
			fHoriz = (rc.right-60) / 18.7;
			
			MoveWindow(hListView_ext_e, (rc.right/10)*0.70, 0, (rc.right/10)*8.60, rc.bottom, TRUE);
			MoveWindow(GetDlgItem(hwnd, BUTTON_01_D_EXTE), 0, 5, (rc.right/10)*0.50, rc.bottom-10, TRUE);
			MoveWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTE), rc.right-(rc.right/10)*0.50, 5, (rc.right/10)*0.50, rc.bottom-10, TRUE);
			
			ShowWindow(hListView_ext_e, SW_HIDE);
			for (int inc=1; inc < 16; inc++) ListView_SetColumnWidth(hListView_ext_e, inc, fHoriz);
			ShowWindow(hListView_ext_e, SW_NORMAL);
			break;
		}
		
		case WM_LBUTTONDBLCLK:
			if (PathFileExists(DATA_RESULT)) {
				general_block(MESSAGE_BLOCK);
				ext_e_list_view_insert_data(hwnd);
				general_block(MESSAGE_UNBLOCK);
			} else {
				show_message((LPSTR)"Arquivo não encontrado", 3);
			}
			break;
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





