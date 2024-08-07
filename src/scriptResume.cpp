#include "resource.h"

//-------------------------------------------------->>
void panel_c_resume(INT iModo, HWND hwnd) {
	static DWORD dwTamanho;
	static LPSTR lpStrMemoria;
	static LONG longLocalAtual;
	static LONG longColunas;
	
	static LONG longQuantParImpar[11];
	static LONG longQuantBlocos[10];
	static LONG longQuantLinha[18];
	static LONG longQuantNumeros[25];
	
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
				show_message((LPSTR)"Arquivo de dados de resultado: Não foi possível abrir", 3):
				show_message((LPSTR)"Memória insuficiente para processar", 3);
			return;
		}
		
		general_block(MESSAGE_BLOCK);
		
		longLocalAtual = longColunas = 0;
		ZeroMemory(&longQuantBlocos, sizeof(longQuantBlocos));
		ZeroMemory(&longQuantNumeros, sizeof(longQuantNumeros));
		ZeroMemory(&longQuantParImpar, sizeof(longQuantParImpar));
		ZeroMemory(&longQuantLinha, sizeof(longQuantLinha));
		SetTimer(hwnd, TIMER_SUMMARIZE_ID, 500, NULL);
		return;
	}
	
	if (iModo == EXECUTE) {
		LONG lMatriz[16], lOrganizar[25], lColuna;
		INT iApoio[5], iPosAtual, iLinha, iPares, iImpares, iBlocos, iControle;
		CHAR cConverter[11], cFormatar[20], cCasasLinha[6];
		FLOAT fPorcent, fQuociente;
		BOOL bAlternar;
		
		lColuna = iLinha = 0;
		bAlternar = false;
		
		ZeroMemory(&lMatriz, sizeof(lMatriz));
		
		while (true) {
			if (longLocalAtual >= dwTamanho) {
				GlobalFree(lpStrMemoria);
				panel_c_resume(FINALIZE, hwnd);
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
					
					if (iPosAtual >= 11)
					{
						GlobalFree(lpStrMemoria);
						general_block(MESSAGE_UNBLOCK);
						show_message((LPSTR)"Resultado: Formatado incorretamente", 3);
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
						lColuna++;
						longColunas++;
						iLinha = 0;
						
						iPares = iImpares = 0;
						for (int inc=1; inc<16; inc++) (lMatriz[inc] % 2 > 0) ? iImpares++: iPares++;
						
						switch (iPares) {
							case 12: longQuantParImpar[0]++; break;
							case 11: longQuantParImpar[1]++; break;
							case 10: longQuantParImpar[2]++; break;
							case 9: longQuantParImpar[3]++; break;
							case 8: longQuantParImpar[4]++; break;
							case 7: longQuantParImpar[5]++; break;
							case 6: longQuantParImpar[6]++; break;
							case 5: longQuantParImpar[7]++; break;
							case 4: longQuantParImpar[8]++; break;
							case 3: longQuantParImpar[9]++; break;
							case 2: longQuantParImpar[10]++; break;
						}
						
						iBlocos=0;
						ZeroMemory(&lOrganizar, sizeof(lOrganizar));
						for (int inc=1; inc<16; inc++) lOrganizar[(lMatriz[inc]-1)] = 1;
						for (int inc=1; inc<25; inc++) if ((lOrganizar[inc] != 0) && (lOrganizar[inc-1] != 0)) lOrganizar[inc] = 2;
						for (int inc=0; inc<25; inc++) if (lOrganizar[inc] == 1) iBlocos++;
						longQuantBlocos[iBlocos-1]++;
						
						iControle = 0;
						ZeroMemory(&iApoio, sizeof(iApoio));
						ZeroMemory(&lOrganizar, sizeof(lOrganizar));
						for (int inc=1; inc<16; inc++) lOrganizar[(lMatriz[inc]-1)] = 1;
						iApoio[0] = lOrganizar[0] + lOrganizar[1] + lOrganizar[2] + lOrganizar[3] + lOrganizar[4];
						iApoio[1] = lOrganizar[5] + lOrganizar[6] + lOrganizar[7] + lOrganizar[8] + lOrganizar[9];
						iApoio[2] = lOrganizar[10] + lOrganizar[11] + lOrganizar[12] + lOrganizar[13] + lOrganizar[14];
						iApoio[3] = lOrganizar[15] + lOrganizar[16] + lOrganizar[17] + lOrganizar[18] + lOrganizar[19];
						iApoio[4] = lOrganizar[20] + lOrganizar[21] + lOrganizar[22] + lOrganizar[23] + lOrganizar[24];
						
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
						
						switch (atoi(cCasasLinha)) {
							case 33333: longQuantLinha[0]++; break;
							case 43332: longQuantLinha[1]++; break;
							case 44322: longQuantLinha[2]++; break;
							case 44331: longQuantLinha[3]++; break;
							case 44421: longQuantLinha[4]++; break;
							case 44430: longQuantLinha[5]++; break;
							case 53322: longQuantLinha[6]++; break;
							case 53331: longQuantLinha[7]++; break;
							case 54222: longQuantLinha[8]++; break;
							case 54321: longQuantLinha[9]++; break;
							case 54330: longQuantLinha[10]++; break;
							case 54411: longQuantLinha[11]++; break;
							case 54420: longQuantLinha[12]++; break;
							case 55221: longQuantLinha[13]++; break;
							case 55311: longQuantLinha[14]++; break;
							case 55320: longQuantLinha[15]++; break;
							case 55410: longQuantLinha[16]++; break;
							case 55500: longQuantLinha[17]++; break;
						}
						
						for (int inc=1; inc<16; inc++) {
							switch (lMatriz[inc]) {
								case 1: longQuantNumeros[0]++; break;
								case 2: longQuantNumeros[1]++; break;
								case 3: longQuantNumeros[2]++; break;
								case 4: longQuantNumeros[3]++; break;
								case 5: longQuantNumeros[4]++; break;
								case 6: longQuantNumeros[5]++; break;
								case 7: longQuantNumeros[6]++; break;
								case 8: longQuantNumeros[7]++; break;
								case 9: longQuantNumeros[8]++; break;
								case 10: longQuantNumeros[9]++; break;
								case 11: longQuantNumeros[10]++; break;
								case 12: longQuantNumeros[11]++; break;
								case 13: longQuantNumeros[12]++; break;
								case 14: longQuantNumeros[13]++; break;
								case 15: longQuantNumeros[14]++; break;
								case 16: longQuantNumeros[15]++; break;
								case 17: longQuantNumeros[16]++; break;
								case 18: longQuantNumeros[17]++; break;
								case 19: longQuantNumeros[18]++; break;
								case 20: longQuantNumeros[19]++; break;
								case 21: longQuantNumeros[20]++; break;
								case 22: longQuantNumeros[21]++; break;
								case 23: longQuantNumeros[22]++; break;
								case 24: longQuantNumeros[23]++; break;
								case 25: longQuantNumeros[24]++; break;
							}
						}
						
					}
					
					if (lColuna >= 10000) {
						longLocalAtual++;
						break;
					}
				}
			}
			longLocalAtual++;
		}
		
		fQuociente = dwTamanho * 0.01;
		fPorcent = longLocalAtual / fQuociente;
		wsprintf(cFormatar, "[Resumir: %d%%]", (int)fPorcent);
		SetDlgItemText(hwndMain, STATUS_BAR_02, cFormatar);
		SetTimer(hwnd, TIMER_SUMMARIZE_ID, TIMER_SUMMARIZE_ELAPSE, NULL);
		return;
	}
	
	if (iModo == FINALIZE) {
		LV_ITEM lvItem;
		FLOAT fPorcent, fQuociente;
		CHAR cFormatar[70];
		
		ZeroMemory(&lvItem, sizeof(lvItem));
		
		ShowWindow(hListView_Pc, SW_HIDE);
		
		if ((ListView_GetItemCount(hListView_Pc)) > 1) ListView_DeleteAllItems(hListView_Pc);
		
		lvItem.mask = LVIF_TEXT;
		lvItem.pszText = (LPSTR) "[Primeira Parte]";
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		fQuociente = longColunas * 0.01;
		
		for (int comp=0, dec=12; comp<11; comp++, dec--) {
			fPorcent = longQuantParImpar[comp] / fQuociente;
			wsprintf(cFormatar, "P(%d) I(%d) | (%d%%) -> %d de %d",
			dec, comp+3, (((INT)fPorcent>0)?(INT)fPorcent:0), longQuantParImpar[comp], longColunas);
			
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView_Pc, &lvItem);
			lvItem.iItem++;
		}
		
		lvItem.pszText = (LPSTR) "[Segunda Parte]";
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		for (int comp=0; comp<10; comp++) {
			fPorcent = longQuantBlocos[comp] / fQuociente;
			wsprintf(cFormatar, "B: %d | (%d%%) -> %d de %d",
			comp+1, (((INT)fPorcent>0)?(INT)fPorcent:0), longQuantBlocos[comp], longColunas);
			
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView_Pc, &lvItem);
			lvItem.iItem++;
		}
		
		lvItem.pszText = (LPSTR) "[Terceira Parte]";
		ListView_InsertItem(hListView_Pc, &lvItem);
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
			
			fPorcent = longQuantLinha[comp] / fQuociente;
			wsprintf(cFormatar, "CL: %d | (%d%%) -> %d de %d",
			alter, (((INT)fPorcent>0)?(INT)fPorcent:0), longQuantLinha[comp], longColunas);
			
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView_Pc, &lvItem);
			lvItem.iItem++;
		}
		
		lvItem.pszText = (LPSTR) "[Quarta Parte]";
		ListView_InsertItem(hListView_Pc, &lvItem);
		lvItem.iItem++;
		
		for (int comp=0; comp<25; comp++) {
			fPorcent = longQuantNumeros[comp] / fQuociente;
			wsprintf(cFormatar, "Num: %d | (%d%%) -> %d de %d",
			comp+1, (((INT)fPorcent>0)?(INT)fPorcent:0), longQuantNumeros[comp], longColunas);
			
			lvItem.pszText = (LPSTR) cFormatar;
			ListView_InsertItem(hListView_Pc, &lvItem);
			lvItem.iItem++;
		}
		
		general_block(MESSAGE_UNBLOCK);
		ShowWindow(hListView_Pc, SW_SHOWNORMAL);
		show_message((LPSTR) "Concluído", 2);
		return;
	}
}
//-------------------------------------------------->>





