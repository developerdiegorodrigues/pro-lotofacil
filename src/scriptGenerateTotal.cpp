#include "resource.h"

//-------------------------------------------------->>
void panel_c_gerate_total(INT iModo, HWND hwnd) {
	static FILE *fileTotal;
	static LONG longContador;
	static INT intCasas[15];
	static INT intPorcentMod;
	
	if (iModo == START) {
		general_block(MESSAGE_BLOCK);
		EnableWindow(GetDlgItem(hwnd, BUTTON_02_C), true);
		EnableWindow(GetDlgItem(hwnd, BUTTON_03_C), true);
		SendDlgItemMessage(hwndMain, PROGRESS_01, PBM_SETPOS, 0, 0);
		ShowWindow(GetDlgItem(hwndMain, PROGRESS_01), SW_SHOWNORMAL);
		SetDlgItemText(hwnd, BUTTON_03_C, "Cancelar");
		
		for (INT i=0; i<15; i++) intCasas[i] = i+1;
		longContador = 0;
		intPorcentMod = 1;
		
		if (PathFileExists(DATA_LOTTERY_TOTAL)) remove(DATA_LOTTERY_TOTAL);
		
		if ((fileTotal = fopen(DATA_LOTTERY_TOTAL, "a")) == NULL) {
			show_message((LPSTR) "Erro ao criar arquivo!\t", 3);
			return;
		}
		
		SetTimer(hwnd, TIMER_TOTAL_ID, TIMER_TOTAL_ELAPSE, NULL);
		return;
	}
	
	if (iModo == EXECUTE) {
		CHAR cFormatar[100];
		FLOAT fQuociente, fPorcent;
		
		for (int inc=0; inc<5000; inc++) {
			longContador++;
			
			wsprintf (
				cFormatar,
				"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ",
				longContador,
				intCasas[0], intCasas[1], intCasas[2], intCasas[3], intCasas[4],
				intCasas[5], intCasas[6], intCasas[7], intCasas[8], intCasas[9],
				intCasas[10], intCasas[11], intCasas[12], intCasas[13], intCasas[14]
			);
			
			fprintf(fileTotal, cFormatar);
			
			if (ferror(fileTotal)) {
				panel_c_gerate_total(FINALIZE, hwnd);
				ListView_DeleteAllItems(hListView_ext_c);
				show_message((LPSTR) "Erro ao gravar no arquivo", 3);
				show_message((LPSTR) "Abortar", 2);
				return;
			}
			
			intCasas[14]++;
			if (intCasas[14] > 25) {
				intCasas[13]++;
				intCasas[14] = intCasas[13] + 1;
				if (intCasas[13] > 24) {
					intCasas[12]++;
					for (int inc=13; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
					if (intCasas[12] > 23) {
						intCasas[11]++;
						for (int inc=12; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
						if (intCasas[11] > 22) {
							intCasas[10]++;
							for (int inc=11; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
							if (intCasas[10] > 21) {
								intCasas[9]++;
								for (int inc=10; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
								if (intCasas[9] > 20) {
									intCasas[8]++;
									for (int inc=9; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
									if (intCasas[8] > 19) {
										intCasas[7]++;
										for (int inc=8; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
										if (intCasas[7] > 18) {
											intCasas[6]++;
											for (int inc=7; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
											if (intCasas[6] > 17) {
												intCasas[5]++;
												for (int inc=6; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
												if (intCasas[5] > 16) {
													intCasas[4]++;
													for (int inc=5; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
													if (intCasas[4] > 15) {
														intCasas[3]++;
														for (int inc=4; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
														if (intCasas[3] > 14) {
															intCasas[2]++;
															for (int inc=3; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
															if (intCasas[2] > 13) {
																intCasas[1]++;
																for (int inc=2; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
																if (intCasas[1] > 12) {
																	intCasas[0]++;
																	for (int inc=1; inc<=14; inc++) intCasas[inc] = intCasas[inc-1] + 1;
																	if (intCasas[0] > 11) {
																		panel_c_gerate_total(FINALIZE, hwnd);
																		
																		ShowWindow(hListView_ext_c, SW_HIDE);
																		ListView_DeleteAllItems(hListView_ext_c);
																		ext_c_list_view_insert_data(hwnd);
																		ShowWindow(hListView_ext_c, SW_SHOWNORMAL);
																		
																		show_message((LPSTR) "Concluído", 2);
																		return;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		
		fQuociente = 3268760 * 0.01;
		fPorcent = longContador / fQuociente;
		
		if (fPorcent >= intPorcentMod) {
			intPorcentMod++;
			SendDlgItemMessage(hwndMain, PROGRESS_01, PBM_DELTAPOS, 1, 0);
		}
		
		SetDlgItemText(hwndMain, STATUS_BAR_02, cFormatar);
		SetTimer(hwnd, TIMER_TOTAL_ID, TIMER_TOTAL_ELAPSE, NULL);
		return;
	}
	
	if (iModo == FINALIZE) {
		KillTimer(hwnd, TIMER_TOTAL_ID);
		fclose(fileTotal);
		
		general_block(MESSAGE_UNBLOCK);
		EnableWindow(GetDlgItem(hwnd, BUTTON_02_C), false);
		EnableWindow(GetDlgItem(hwnd, BUTTON_03_C), false);
		ShowWindow(GetDlgItem(hwndMain, PROGRESS_01), SW_HIDE);
		SetDlgItemText(hwnd, BUTTON_02_C, "Pausar");
		return;
	}
}
//-------------------------------------------------->>





