#include "resource.h"

#define ListView01_Style WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER

HWND hListView_ext_a;

LONG longCardExtA[7][18];
//[15] id item listview
//[16] local chamado
//[17] concurso / Identificador
//-------------------------------------------------->>
void ext_a_wm_create(HWND hwnd) {
	LV_COLUMN lvCol;
	HRSRC hrsrc;
	HGLOBAL hglobal;
	FILE *file;
	CHAR cTextoColuna[5];
	
	ZeroMemory(&longCardExtA, sizeof(longCardExtA));
	
	if (!(hListView_ext_a = CreateWindowEx(
		WS_EX_WINDOWEDGE, "SysListView32", 0,
		ListView01_Style,
		0, 0, 0, 0, hwnd, (HMENU) LISTVIEW_01_D_EXTA, GetModuleHandle(NULL), NULL
	))) error((LPSTR) "Erro: CreateWindowEx SysListView01 ExtA!\t", true);
	
	if (!PathFileExists(DATA_LOTTERY_GAME)) {
		hrsrc = FindResource(NULL, "DATA", RT_RCDATA);
	 	hglobal = LoadResource(NULL, hrsrc);
	 	
		if ((hrsrc) && (hglobal)) {
	 		if ((file = fopen(DATA_LOTTERY_GAME, "a")) != NULL) {
				fprintf(file, (LPSTR)hglobal);
				fclose(file);
			}
		}
	}
	
	ListView_SetExtendedListViewStyle(hListView_ext_a, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	ListView_SetTextColor(hListView_ext_a, COLORREF(COLOR_TEXT_LV01));
	ListView_SetTextBkColor(hListView_ext_a, COLORREF(COLOR_PANEL_BACKGROUND));
	ListView_SetBkColor(hListView_ext_a, COLORREF(COLOR_PANEL_BACKGROUND));
	
	ZeroMemory(&lvCol, sizeof(lvCol));
	lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	lvCol.fmt = LVCFMT_CENTER;
	
	lvCol.cx = 55;
	lvCol.pszText = (LPSTR) "Conc";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView_ext_a, 0, &lvCol);
	
	lvCol.cx = 80;
	lvCol.pszText = (LPSTR) "Data";
	lvCol.cchTextMax = strlen(lvCol.pszText);
	ListView_InsertColumn(hListView_ext_a, 1, &lvCol);
	
	for (int inc=0; inc<=14; inc++) {
		lvCol.cx = 40;
		(inc < 9) ? wsprintf(cTextoColuna, "0%d", inc+1): wsprintf(cTextoColuna, "%d", inc+1);
		lvCol.pszText = cTextoColuna;
		lvCol.cchTextMax = strlen(cTextoColuna);
		ListView_InsertColumn(hListView_ext_a, inc+2, &lvCol);
	}
}
//-------------------------------------------------->>
void ext_a_list_view_insert_data(HWND hwnd) {
	HANDLE hFile;
	LV_ITEM lvItem;
	LPSTR lpStrMemoria;
	DWORD dwTamanho, dwRead;
	CHAR cConfVerter[11];
	LONG longColuna;
	INT iPosAtual, iLinha;
	BOOL bStatus, bVerificar;
	
	iLinha = longColuna = 0;
	bStatus = bVerificar = false;
	
	hFile = CreateFile(DATA_LOTTERY_GAME, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
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
		lvItem.pszText = (LPSTR) "Não foi possível abrir o banco de dados":
		lvItem.pszText = (LPSTR) "Memória insuficiente para processar";
		
		ListView_InsertItem(hListView_ext_a, &lvItem);
		ListView_SetColumnWidth(hListView_ext_a, 0, 1500);
		return;
	}
	
	ZeroMemory(&lvItem, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT;
	
	ShowWindow(hListView_ext_a, SW_HIDE);
	
	for (long alternar=0; ; alternar++) {
		if (alternar >= dwTamanho) break;
		
		if ((lpStrMemoria[alternar] >= (int)'/') && (lpStrMemoria[alternar] <= (int)'9')) {
			if (bVerificar == false) {
				bVerificar = true;
				iPosAtual = 0;
				ZeroMemory(&cConfVerter, strlen(cConfVerter));
			}
			
			if (bVerificar == true) {
				cConfVerter[iPosAtual] = lpStrMemoria[alternar];
				iPosAtual++;
				
				if (iPosAtual >= 11) {
					GlobalFree(lpStrMemoria);
					ListView_DeleteAllItems(hListView_ext_a);
					lvItem.pszText = (LPSTR) "Erro: Banco de dados formatado incorretamente!";
					ListView_InsertItem(hListView_ext_a, &lvItem);
					ListView_SetColumnWidth(hListView_ext_a, 0, 1500);
					ShowWindow(hListView_ext_a, SW_SHOWNORMAL);
					return;
				}
				
				cConfVerter[iPosAtual] = 0;
			}
		} else {
			if (bVerificar == true) {
				bVerificar = false;
				
				if (iLinha == 0) {
					lvItem.pszText = (LPSTR) cConfVerter;
					ListView_InsertItem(hListView_ext_a, &lvItem);
					lvItem.iItem++;
					iLinha++;
				} else {
					ListView_SetItemText(hListView_ext_a, longColuna, iLinha, (LPSTR) cConfVerter);
					iLinha++;
				}
				
				if (iLinha >= 17) {
					iLinha = 0;
					longColuna++;
				}
			}
		}
	}
	
	GlobalFree(lpStrMemoria);
	
	ListView_SetColumnWidth(hListView_ext_a, 0, 55);
	PostMessage(hwnd, WM_SIZE, 0, 0);
	
	ShowWindow(hListView_ext_a, SW_SHOWNORMAL);
	ext_a_change(0, longColuna);
}
//-------------------------------------------------->>
void ext_a_change(int Item, int max) {
	CHAR cValor[11];
	
	ZeroMemory(&longCardExtA, sizeof(longCardExtA));
	longCardExtA[0][16] = 1;
	
	for (int imp=0; imp<7; imp++) {
		if (Item+imp >= max) break;
		
		longCardExtA[imp][15] = Item+imp;
		ListView_GetItemText(hListView_ext_a, Item+imp, 0, cValor, 10);
		longCardExtA[imp][17] = atoi(cValor);
		
		for (int inc=2; inc<17; inc++)
		{
			ListView_GetItemText(hListView_ext_a, Item+imp, inc, cValor, 10);
			longCardExtA[imp][inc-2] = atoi(cValor);
		}
	}
	
	PostMessage(hwndPanelB, WM_COMMAND, MESSAGE_A, 0);
}
//-------------------------------------------------->>
void ext_a_wm_notify(WPARAM wParam, LPARAM lParam) {
	if (((NMHDR*)lParam)->hwndFrom == hListView_ext_a) {
		DWORD dwStatus;
		UINT uCode, uVKey;
		LONG lMax, lModificador;
		CHAR cValor[11], cFormatar[60];
		
		static LONG lItem;
		
		lMax = ListView_GetItemCount(hListView_ext_a);
		uCode = ((NMHDR*)lParam)->code;
		uVKey = ((LV_KEYDOWN*)lParam)->wVKey;
		
		if (uCode == LVN_KEYDOWN) {
			if (lMax < 7) {
				show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
				return;
			}
			
			if (uVKey == VK_RETURN) {
				for (long inc=0; inc<lMax; inc++) {
					dwStatus = ListView_GetItemState(hListView_ext_a, inc, LVIS_SELECTED);
					if (dwStatus == LVIS_SELECTED) {
						if (inc == lItem) return;
						lItem = inc;
						break;
					}
				}
				ext_a_change(lItem, lMax);
			} else if (uVKey == VK_UP || uVKey == VK_DOWN) {
				for (long inc=0; inc<lMax; inc++) {
					dwStatus = ListView_GetItemState(hListView_ext_a, inc, LVIS_SELECTED);
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
				ext_a_change(lModificador, lMax);
			}
		}
		else if (uCode == NM_CLICK) {
			if (lMax < 7) {
				show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
				return;
			}
			
			lItem = ((NMLISTVIEW*) lParam)->iItem;
			ext_a_change(lItem, lMax);
		} else if (uCode == NM_RCLICK) {
			lItem = ((NMLISTVIEW*) lParam)->iItem;
			
			if (lMax < 7) {
				show_message((LPSTR)"Necessário uma quantidade maior na lista", 3);
				return;
			}
			
			for (int inc=2; inc<17; inc++) {
				ListView_GetItemText(hListView_ext_a, lItem, inc, cValor, 10);
				longNumExtG[inc-2] = atoi(cValor);
			}
			
			wsprintf(
				cFormatar, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				longNumExtG[0], longNumExtG[1], longNumExtG[2], longNumExtG[3], longNumExtG[4],
				longNumExtG[5], longNumExtG[6], longNumExtG[7], longNumExtG[8], longNumExtG[9],
				longNumExtG[10], longNumExtG[11], longNumExtG[12], longNumExtG[13], longNumExtG[14]
			);
			
			SetDlgItemText(hExtG, EDIT_09_D_EXTG, cFormatar);
			ext_g_analyze(hExtG);
		}
	}
}
//-------------------------------------------------->>
void ext_a_wm_command(HWND hwnd, WPARAM wParam) {
	if (wParam == MESSAGE_BLOCK) {
		EnableWindow(hListView_ext_a, false);
		return;
	}
	
	if (wParam == MESSAGE_UNBLOCK) {
		EnableWindow(hListView_ext_a, true);
		return;
	}
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelDExtProcA(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			ext_a_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			ext_a_wm_command(hwnd, wParam);
			break;
		
		case WM_NOTIFY:
			ext_a_wm_notify(wParam, lParam);
			break;
		
		case WM_SIZE: {
			RECT rc;
			FLOAT fHoriz;
			
			GetClientRect(hwnd, &rc);
			fHoriz = (rc.right-160) / 15;
			MoveWindow(hListView_ext_a, 0, 0, rc.right, rc.bottom, TRUE);
			
			ShowWindow(hListView_ext_a, SW_HIDE);
			for (int inc=2; inc < 17; inc++) ListView_SetColumnWidth(hListView_ext_a, inc, fHoriz);
			ShowWindow(hListView_ext_a, SW_NORMAL);
			break;
		}
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>
