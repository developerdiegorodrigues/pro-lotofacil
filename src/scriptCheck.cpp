#include "resource.h"

//-------------------------------------------------->>
void panel_c_check(INT iModo, HWND hwnd) {
	static DWORD dwTamanho;
	static LPSTR lpStrMemoria;
	static LONG longLocalAtual;
	static LONG longColunas;
	static LONG longSorteados[5];
	
	if (iModo == START) {
		HANDLE hFile;
		DWORD dwRead;
		BOOL bStatus;
		
		bStatus = false;
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
				show_message((LPSTR)"res_data_base: Não foi possível abrir", 3):
				show_message((LPSTR)"res_data_base: Memória insuficiente para processar!", 3);
			show_message((LPSTR)"Abortar!", 2);
			return;
		}
		
		general_block(MESSAGE_BLOCK);
		longLocalAtual = longColunas = 0;
		ZeroMemory(&longSorteados, sizeof(longSorteados));
		SetTimer(hwnd, TIMER_CHECK_ID, TIMER_CHECK_ELAPSE, NULL);
		return;
	}
	
	if (iModo == EXECUTE) {
		LONG lMatriz[16], lColuna;
		INT iPosAtual, iLinha, iQuant;
		CHAR cConverter[11], cFormatar[20];
		BOOL bAlternar;
		FLOAT fPorcent, fQuociente;
		
		lColuna = iLinha = 0;
		bAlternar = false;
		ZeroMemory(&lMatriz, sizeof(lMatriz));
		
		while (true) {
			if (longLocalAtual >= dwTamanho) {
				GlobalFree(lpStrMemoria);
				panel_c_check(FINALIZE, hwnd);
				return;
			}
			
			if ((lpStrMemoria[longLocalAtual] >= (int)'0') && (lpStrMemoria[longLocalAtual] <= (int)'9')) {
				if (bAlternar == false) {
					bAlternar = true;
					iPosAtual = 0;
					ZeroMemory(&cConverter, strlen(cConverter));
				}
				
				if (bAlternar == true) {
					cConverter[iPosAtual] = lpStrMemoria[longLocalAtual];
					iPosAtual++;
					
					if (iPosAtual >= 11) {
						GlobalFree(lpStrMemoria);
						show_message((LPSTR)"res_data_base: Formatado incorretamente", 3);
						show_message((LPSTR)"Abortar", 2);
						return;
					}
					
					cConverter[iPosAtual] = 0;
				}
			} else {
				if (bAlternar == true) {
					bAlternar = false;
					
					lMatriz[iLinha] = atoi(cConverter);
					iLinha++;
					
					if (iLinha >= 16) {
						iLinha = iQuant = 0;
						lColuna++;
						longColunas++;
						
						for (int imp=1; imp<=25; imp++) {
							for (int inc=0; inc<15; inc++) {
								if (longNumExtG[inc] == imp) {
									for (int cnt=1; cnt<=15; cnt++) {
										if (lMatriz[cnt] == imp) iQuant++;
									}
								}
							}
						}
						
						switch (iQuant) {
							case 11: longSorteados[0]++; break;
							case 12: longSorteados[1]++; break;
							case 13: longSorteados[2]++; break;
							case 14: longSorteados[3]++; break;
							case 15: longSorteados[4]++; break;
						}
					}
					
					if (lColuna == 5000) {
						longLocalAtual++;
						break;
					}
				}
			}
			longLocalAtual++;
		}
		
		fQuociente = dwTamanho * 0.01;
		fPorcent = longLocalAtual / fQuociente;
		wsprintf(cFormatar, "[Conferir: %d%%]", (int)fPorcent);
		SetDlgItemText(hwndMain, STATUS_BAR_02, cFormatar);
		SetTimer(hwnd, TIMER_CHECK_ID, TIMER_CHECK_ELAPSE, NULL);
		return;
	}
	
	if (iModo == FINALIZE) {
		LV_ITEM lvItem;
		FLOAT fValor[5], fMult[5], fPorcent, fQuociente;
		CHAR cFormatar[40], cTexto[5][15];
		
		ZeroMemory(&lvItem, sizeof(lvItem));
		lvItem.mask = LVIF_TEXT;
		
		GetDlgItemText(hwnd, EDIT_10_D_EXTG, cTexto[0], 6);
		fValor[0] = atof(cTexto[0]);
		GetDlgItemText(hwnd, EDIT_11_D_EXTG, cTexto[1], 6);
		fValor[1] = atof(cTexto[1]);
		GetDlgItemText(hwnd, EDIT_12_D_EXTG, cTexto[2], 7);
		fValor[2] = atof(cTexto[2]);
		GetDlgItemText(hwnd, EDIT_13_D_EXTG, cTexto[3], 9);
		fValor[3] = atof(cTexto[3]);
		GetDlgItemText(hwnd, EDIT_14_D_EXTG, cTexto[4], 12);
		fValor[4] = atof(cTexto[4]);
		
		ShowWindow(hListView_Pc, SW_HIDE);
		if ((ListView_GetItemCount(hListView_Pc)) > 1) ListView_DeleteAllItems(hListView_Pc);
		
		fQuociente = longColunas * 0.01;
		
		wsprintf(cFormatar, "••• Cartelas: %d •••", longColunas);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fPorcent = longSorteados[0] / fQuociente;
		wsprintf(cFormatar, "[11] %d (%d%%)", longSorteados[0], (int)fPorcent);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fPorcent = longSorteados[1] / fQuociente;
		wsprintf(cFormatar, "[12] %d (%d%%)", longSorteados[1], (int)fPorcent);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fPorcent = longSorteados[2] / fQuociente;
		wsprintf(cFormatar, "[13] %d (%d%%)", longSorteados[2], (int)fPorcent);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fPorcent = longSorteados[3] / fQuociente;
		wsprintf(cFormatar, "[14] %d (%d%%)", longSorteados[3], (int)fPorcent);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fPorcent = longSorteados[4] / fQuociente;
		wsprintf(cFormatar, "[15] %d (%d%%)", longSorteados[4], (int)fPorcent);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		lvItem.pszText = (LPSTR) "••• Ganhos Aproximados •••";
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		if ((fValor[0] <= 0) || (fValor[0] > 20)) {
			fValor[0] = 4;
			SetDlgItemText(hwnd, EDIT_10_D_EXTG, "4.0");
		}
		
		if ((fValor[1] <= 0) || (fValor[1] > 40)) {
			fValor[1] = 8;
			SetDlgItemText(hwnd, EDIT_11_D_EXTG, "8.0");
		}
		
		if ((fValor[2] <= 0) || (fValor[2] > 100)) {
			fValor[2] = 20;
			SetDlgItemText(hwnd, EDIT_12_D_EXTG, "20.0");
		}
		
		if ((fValor[3] <= 0) || (fValor[3] > 10000)) {
			fValor[3] = 1500;
			SetDlgItemText(hwnd, EDIT_13_D_EXTG, "1500.0");
		}
		
		if ((fValor[4] <= 0) || (fValor[4] > 10000000)) {
			fValor[4] = 1500000;
			SetDlgItemText(hwnd, EDIT_14_D_EXTG, "1500000.0");
		}
		
		fMult[0] = longSorteados[0] * fValor[0];
		wsprintf(cFormatar, "[11] %d x %d = %d", longSorteados[0], (int)fValor[0], (int)fMult[0]);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fMult[1] = longSorteados[1] * fValor[1];
		wsprintf(cFormatar, "[12] %d x %d = %d", longSorteados[1], (int)fValor[1], (int)fMult[1]);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fMult[2] = longSorteados[2] * fValor[2];
		wsprintf(cFormatar, "[13] %d x %d = %d", longSorteados[2], (int)fValor[2], (int)fMult[2]);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fMult[3] = longSorteados[3] * fValor[3];
		wsprintf(cFormatar, "[14] %d x %d = %d", longSorteados[3], (int)fValor[3], (int)fMult[3]);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fMult[4] = longSorteados[4] * fValor[4];
		wsprintf(cFormatar, "[15] %d x %d = %d", longSorteados[4], (int)fValor[4], (int)fMult[4]);
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		wsprintf(cFormatar, "Total: R$%d", (int)(fMult[0] + fMult[1] + fMult[2] + fMult[3] + fMult[4]));
		lvItem.pszText = (LPSTR) cFormatar;
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		general_block(MESSAGE_UNBLOCK);
		ShowWindow(hListView_Pc, SW_SHOWNORMAL);
		show_message((LPSTR)"Concluído", 2);
		return;
	}
}
//-------------------------------------------------->>





