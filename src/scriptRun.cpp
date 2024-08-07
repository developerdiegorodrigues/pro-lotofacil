#include "resource.h"

INT intGrupoAExtD[11];
INT intGrupoBExtD[10];
INT intGrupoCExtD[18];
INT intGrupoDExtF[25];
INT intGrupoEExtF[25];

FILE *fileResultado;
LONG longFiltrados;
//-------------------------------------------------->>
void panel_c_intervir(LONG cn[16]) {
	CHAR cFormatar[70], cCasasLinha[6];
	INT modif[25], apoio[5], pares, impares, iBlocos, iControle;
	
	pares = impares = 0;
	for (int inc=1; inc<16; inc++) (cn[inc] % 2 > 0) ? impares++: pares++;
	
	iBlocos = 0;
	ZeroMemory(&modif, sizeof(modif));
	for (int inc=1; inc<16; inc++) modif[(cn[inc]-1)] = 1;
	for (int inc=1; inc<25; inc++) if ((modif[inc] != 0) && (modif[inc-1] != 0)) modif[inc] = 2;
	for (int inc=0; inc<25; inc++) if (modif[inc] == 1) iBlocos++;
	
	iControle = 0;
	ZeroMemory(&modif, sizeof(modif));
	for (int inc=1; inc<16; inc++) modif[(cn[inc]-1)] = 1;
	apoio[0] = modif[0] + modif[1] + modif[2] + modif[3] + modif[4];
	apoio[1] = modif[5] + modif[6] + modif[7] + modif[8] + modif[9];
	apoio[2] = modif[10] + modif[11] + modif[12] + modif[13] + modif[14];
	apoio[3] = modif[15] + modif[16] + modif[17] + modif[18] + modif[19];
	apoio[4] = modif[20] + modif[21] + modif[22] + modif[23] + modif[24];
	
	ZeroMemory(&cCasasLinha, sizeof(cCasasLinha));
	wsprintf(cFormatar, "%d%d%d%d%d", apoio[0], apoio[1], apoio[2], apoio[3], apoio[4]);
	for (int letra=53; letra>=48; letra--) {
		for (int vas=0; vas<5; vas++) {
			if (cFormatar[vas] == letra) {
				cCasasLinha[iControle] = letra;
				iControle++;
			}
		}
	}
	
	switch (pares) {
		case 12: if (intGrupoAExtD[0]) return; break;
		case 11: if (intGrupoAExtD[1]) return; break;
		case 10: if (intGrupoAExtD[2]) return; break;
		case 9: if (intGrupoAExtD[3]) return; break;
		case 8: if (intGrupoAExtD[4]) return; break;
		case 7: if (intGrupoAExtD[5]) return; break;
		case 6: if (intGrupoAExtD[6]) return; break;
		case 5: if (intGrupoAExtD[7]) return; break;
		case 4: if (intGrupoAExtD[8]) return; break;
		case 3: if (intGrupoAExtD[9]) return; break;
		case 2: if (intGrupoAExtD[10]) return; break;
	}
	
	switch (iBlocos) {
		case 1: if (intGrupoBExtD[0]) return; break;
		case 2: if (intGrupoBExtD[1]) return; break;
		case 3: if (intGrupoBExtD[2]) return; break;
		case 4: if (intGrupoBExtD[3]) return; break;
		case 5: if (intGrupoBExtD[4]) return; break;
		case 6: if (intGrupoBExtD[5]) return; break;
		case 7: if (intGrupoBExtD[6]) return; break;
		case 8: if (intGrupoBExtD[7]) return; break;
		case 9: if (intGrupoBExtD[8]) return; break;
		case 10: if (intGrupoBExtD[9]) return; break;
	}
	
	// Casas por linha
	switch (atoi(cCasasLinha)) {
		case 33333: if (intGrupoCExtD[0]) return; break;
		case 43332: if (intGrupoCExtD[1]) return; break;
		case 44322: if (intGrupoCExtD[2]) return; break;
		case 44331: if (intGrupoCExtD[3]) return; break;
		case 44421: if (intGrupoCExtD[4]) return; break;
		case 44430: if (intGrupoCExtD[5]) return; break;
		case 53322: if (intGrupoCExtD[6]) return; break;
		case 53331: if (intGrupoCExtD[7]) return; break;
		case 54222: if (intGrupoCExtD[8]) return; break;
		case 54321: if (intGrupoCExtD[9]) return; break;
		case 54330: if (intGrupoCExtD[10]) return; break;
		case 54411: if (intGrupoCExtD[11]) return; break;
		case 54420: if (intGrupoCExtD[12]) return; break;
		case 55221: if (intGrupoCExtD[13]) return; break;
		case 55311: if (intGrupoCExtD[14]) return; break;
		case 55320: if (intGrupoCExtD[15]) return; break;
		case 55410: if (intGrupoCExtD[16]) return; break;
		case 55500: if (intGrupoCExtD[17]) return; break;
	}
	
	for (int inc=1; inc<16; inc++) {
		switch (cn[inc]) {
			case 1: if (intGrupoDExtF[0]) return; break;
			case 2: if (intGrupoDExtF[1]) return; break;
			case 3: if (intGrupoDExtF[2]) return; break;
			case 4: if (intGrupoDExtF[3]) return; break;
			case 5: if (intGrupoDExtF[4]) return; break;
			case 6: if (intGrupoDExtF[5]) return; break;
			case 7: if (intGrupoDExtF[6]) return; break;
			case 8: if (intGrupoDExtF[7]) return; break;
			case 9: if (intGrupoDExtF[8]) return; break;
			case 10: if (intGrupoDExtF[9]) return; break;
			case 11: if (intGrupoDExtF[10]) return; break;
			case 12: if (intGrupoDExtF[11]) return; break;
			case 13: if (intGrupoDExtF[12]) return; break;
			case 14: if (intGrupoDExtF[13]) return; break;
			case 15: if (intGrupoDExtF[14]) return; break;
			case 16: if (intGrupoDExtF[15]) return; break;
			case 17: if (intGrupoDExtF[16]) return; break;
			case 18: if (intGrupoDExtF[17]) return; break;
			case 19: if (intGrupoDExtF[18]) return; break;
			case 20: if (intGrupoDExtF[19]) return; break;
			case 21: if (intGrupoDExtF[20]) return; break;
			case 22: if (intGrupoDExtF[21]) return; break;
			case 23: if (intGrupoDExtF[22]) return; break;
			case 24: if (intGrupoDExtF[23]) return; break;
			case 25: if (intGrupoDExtF[24]) return; break;
		}
	}
	
	// Números fixos
	ZeroMemory(&apoio, sizeof(apoio));
	for (int imp=0; imp<25; imp++) {
		if (intGrupoEExtF[imp]) {
			for (int inc=1; inc<16; inc++) {
				if (cn[inc] == imp+1) {
					apoio[0]++;
					break;
				}
			}
		}
	}
	
	for (int inc=0; inc<25; inc++) apoio[1] += intGrupoEExtF[inc];
	if (apoio[0] != apoio[1]) return;
	
	wsprintf (
		cFormatar,
		"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		cn[0], cn[1], cn[2], cn[3], cn[4], cn[5], cn[6], cn[7], cn[8], cn[9], cn[10], cn[11], cn[12], cn[13], cn[14], cn[15]
	);
	
	longFiltrados++;
	fprintf(fileResultado, cFormatar);
}
//-------------------------------------------------->>
void panel_c_run(INT iModo, HWND hwnd) {
	static DWORD dwTamanho;
	static LPSTR lpStrMemoria;
	static LONG longLocalAtual;
	static INT intPorcentMod;
	
	if (iModo == START) {
		HANDLE hFile;
		DWORD dwRead;
		BOOL bStatus;
		INT verif[5];
		
		ZeroMemory(&verif, sizeof(verif));
		ZeroMemory(&intGrupoAExtD, sizeof(intGrupoAExtD));
		ZeroMemory(&intGrupoBExtD, sizeof(intGrupoBExtD));
		ZeroMemory(&intGrupoCExtD, sizeof(intGrupoCExtD));
		ZeroMemory(&intGrupoDExtF, sizeof(intGrupoDExtF));
		ZeroMemory(&intGrupoEExtF, sizeof(intGrupoEExtF));
		
		longLocalAtual = longFiltrados = 0;
		intPorcentMod = 1;
		bStatus = false;
		
		for (int inc=0, id=CHECKBOX_01_D_EXTD; id<=CHECKBOX_11_D_EXTD; inc++, id++) {
			if (IsDlgButtonChecked(hExtD, id) == BST_CHECKED) {
				intGrupoAExtD[inc] = 1;
				verif[0]++;
			}
		}
		
		if (verif[0] == 11) {
			show_message((LPSTR)"Com o primeiro grupo totalmente marcado o resultado será zero", 3);
			return;
		}
		
		for (int inc=0, id=CHECKBOX_12_D_EXTD; id<=CHECKBOX_21_D_EXTD; inc++, id++) {
			if (IsDlgButtonChecked(hExtD, id) == BST_CHECKED) {
				intGrupoBExtD[inc] = 1;
				verif[1]++;
			}
		}
		
		if (verif[1] == 10) {
			show_message((LPSTR)"Com o segundo grupo totalmente marcado o resultado será zero", 3);
			return;
		}
		
		for (int inc=0, id=CHECKBOX_22_D_EXTD; id<=CHECKBOX_39_D_EXTD; inc++, id++) {
			if (IsDlgButtonChecked(hExtD, id) == BST_CHECKED) {
				intGrupoCExtD[inc] = 1;
				verif[2]++;
			}
		}
		
		if (verif[2] == 18) {
			show_message((LPSTR)"Com o terceiro grupo totalmente marcado o resultado será zero", 3);
			return;
		}
		
		for (int inc=0, id=CHECKBOX_01_D_EXTF; id<=CHECKBOX_25_D_EXTF; inc++, id++) {
			if (IsDlgButtonChecked(hExtF, id) == BST_CHECKED) {
				intGrupoDExtF[inc] = 1;
				verif[3]++;
			}
		}
		
		if (verif[3] > 10) {
			show_message((LPSTR)"Com mais de 10 números marcados no quarto grupo o resultado será zero", 3);
			return;
		}
		
		for (int inc=0, id=CHECKBOX_26_D_EXTF; id<=CHECKBOX_50_D_EXTF; inc++, id++) {
			if (IsDlgButtonChecked(hExtF, id) == BST_CHECKED) {
				intGrupoEExtF[inc] = 1;
				verif[4]++;
			}
		}
		
		if (verif[4] > 15) {
			show_message((LPSTR)"Com mais de 15 números marcados quinto grupo o resultado será zero", 3);
			return;
		}
		
		if (PathFileExists(DATA_RESULT)) remove(DATA_RESULT);
		
		if ((fileResultado = fopen(DATA_RESULT, "a")) == NULL) {
			show_message((LPSTR)"Erro ao criar arquivo!\t", 3);
			return;
		}
		
		hFile = CreateFile(DATA_LOTTERY_TOTAL, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		
		if (hFile != INVALID_HANDLE_VALUE) {
			dwTamanho = GetFileSize(hFile, NULL);
			if (dwTamanho != 0xFFFFFFFF) {
				lpStrMemoria = LPSTR(GlobalAlloc(GPTR, dwTamanho + 2));
				if (lpStrMemoria != NULL) {
					if (ReadFile(hFile, lpStrMemoria, dwTamanho, &dwRead, NULL)) {
						lpStrMemoria[dwTamanho] = ' ';
						dwTamanho +=1;
						lpStrMemoria[dwTamanho] = 0;
						bStatus = true;
					}
				}
			}
			CloseHandle(hFile);
		}
		
		if (bStatus == false) {
			(dwTamanho != 0xFFFFFFFF) ?
				show_message((LPSTR)"O arquivo de dados precisa estar disponível", 3):
				show_message((LPSTR)"Memória insuficiente para processar!", 3);
			return;
		}
		
		general_block(MESSAGE_BLOCK);
		EnableWindow(GetDlgItem(hwnd, BUTTON_05_C), true);
		EnableWindow(GetDlgItem(hwnd, BUTTON_06_C), true);
		SendDlgItemMessage(hwndMain, PROGRESS_01, PBM_SETPOS, 0, 0);
		ShowWindow(GetDlgItem(hwndMain, PROGRESS_01), SW_SHOWNORMAL);
		SetDlgItemText(hwnd, BUTTON_06_C, "Cancelar");
		SetTimer(hwnd, TIMER_EXEC_ID, TIMER_EXEC_ELAPSE, NULL);
		return;
	}
	
	if (iModo == EXECUTE) {
		CHAR cConverter[11], cFormatar[70];
		LONG cn[16];
		INT iPosAtual, linha, iControle;
		BOOL verificar;
		FLOAT fPorcent, fQuociente;
		
		static INT info = 0;
		iPosAtual = linha = iControle = 0;
		verificar = false;
		ZeroMemory(&cn, sizeof(cn));
		
		while (true) {
			if (longLocalAtual >= dwTamanho) {
				panel_c_run(FINALIZE, hwnd);
				
				if (longFiltrados > 0) {
					ShowWindow(hListView_ext_e, SW_HIDE);
					ListView_DeleteAllItems(hListView_ext_e);
					ext_e_list_view_insert_data(hwnd);
					ShowWindow(hListView_ext_e, SW_SHOWNORMAL);
					panel_c_resume(START, hwnd);
					return;
				}
				
				show_message((LPSTR)"Nenhum jogo passou pelos filtros", 2);
				return;
			}
			
			if ((lpStrMemoria[longLocalAtual] >= (int)'0') && (lpStrMemoria[longLocalAtual] <= (int)'9')) {
				if (verificar == false) {
					verificar = true;
					iPosAtual = 0;
					ZeroMemory(&cConverter, strlen(cConverter));
				}
				
				if (verificar == true) {
					cConverter[iPosAtual] = lpStrMemoria[longLocalAtual];
					iPosAtual++;
					
					if (iPosAtual >= 11) {
						panel_c_run(FINALIZE, hwnd);
						SetDlgItemText(hwndMain, STATUS_BAR_02, "Erro: Banco de dados formatado incorretamente!");
						return;
					}
					
					cConverter[iPosAtual] = 0;
				}
			} else {
				if (verificar == true) {
					verificar = false;
					
					cn[linha] = atoi(cConverter);
					linha++;
										
					if (linha >= 16) {
						linha = 0;
						iControle++;
						panel_c_intervir(cn);
					}
					
					if (iControle >= 5000) {
						iControle = 0;
						break;
					}
				}
			}
			
			longLocalAtual++;
		}
		
		switch (info) {
			case 0: SetDlgItemText(hwndMain, STATUS_BAR_02, "•"); info++; break;
			case 4: SetDlgItemText(hwndMain, STATUS_BAR_02, "••"); info++; break;
			case 8: SetDlgItemText(hwndMain, STATUS_BAR_02, "•••"); info++; break;
			case 12: SetDlgItemText(hwndMain, STATUS_BAR_02, "••••"); info++; break;
			case 16: SetDlgItemText(hwndMain, STATUS_BAR_02, "•••••"); info++; break;
			case 20: SetDlgItemText(hwndMain, STATUS_BAR_02, "••••••"); info++; break;
			case 24: SetDlgItemText(hwndMain, STATUS_BAR_02, "•••••••"); info++; break;
			case 28: SetDlgItemText(hwndMain, STATUS_BAR_02, "••••••••"); info++; break;
			case 32: SetDlgItemText(hwndMain, STATUS_BAR_02, "•••••••••"); info++; break;
			case 36: SetDlgItemText(hwndMain, STATUS_BAR_02, "••••••••••"); info++; break;
			case 40: SetDlgItemText(hwndMain, STATUS_BAR_02, "•••••••••"); info++; break;
			case 44: SetDlgItemText(hwndMain, STATUS_BAR_02, "•••••••"); info++; break;
			case 48: SetDlgItemText(hwndMain, STATUS_BAR_02, "••••••"); info++; break;
			case 52: SetDlgItemText(hwndMain, STATUS_BAR_02, "•••••"); info++; break;
			case 56: SetDlgItemText(hwndMain, STATUS_BAR_02, "••••"); info++; break;
			case 60: SetDlgItemText(hwndMain, STATUS_BAR_02, "•••"); info++; break;
			case 64: SetDlgItemText(hwndMain, STATUS_BAR_02, "••"); info=0; break;
			default: info++; break;
		}
		
		fQuociente = dwTamanho * 0.01;
		fPorcent = longLocalAtual / fQuociente;
		
		if (fPorcent >= intPorcentMod) {
			intPorcentMod++;
			SendDlgItemMessage(hwndMain, PROGRESS_01, PBM_DELTAPOS, 1, 0);
		}
		
		SetTimer(hwnd, TIMER_EXEC_ID, TIMER_EXEC_ELAPSE, NULL);
		return;
	}
	
	if (iModo == FINALIZE) {
		KillTimer(hwnd, TIMER_EXEC_ID);
		
		GlobalFree(lpStrMemoria);
		fclose(fileResultado);
		
		general_block(MESSAGE_UNBLOCK);
		EnableWindow(GetDlgItem(hwnd, BUTTON_05_C), false);
		EnableWindow(GetDlgItem(hwnd, BUTTON_06_C), false);
		ShowWindow(GetDlgItem(hwndMain, PROGRESS_01), SW_HIDE);
		SetDlgItemText(hwnd, BUTTON_05_C, "Pausar");
		return;
	}
}
//-------------------------------------------------->>





