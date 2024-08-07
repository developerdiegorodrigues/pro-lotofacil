#include "resource.h"

//-------------------------------------------------->>
int ext_g_save_image(LONG lMatriz[16], LONG lIdent) {
	RECT rect;
	HDC hdcWindow, hdc, nHdc;
	DWORD dwWidth, dwHeight, dwBPP, dwNumColors;
	HBITMAP hBitmap;
	BITMAPINFO bitMapInfo;
	LPVOID pBits;
	HGDIOBJ gdiobj;
	BITMAPFILEHEADER bFileHeader;
	BITMAPINFOHEADER bInfoHeader;
	RGBQUAD colors[256];
	HANDLE hFile;
	DWORD dwBytes;
	CHAR cTexto[50];
	INT PH, TH, EH, PV, TV, EV, PHU, PVU;
	
	static RECT rectPos[26];
	
	static HBRUSH
		hBrushA = (HBRUSH) GetStockObject(WHITE_BRUSH),
		hBrushB = (HBRUSH) GetStockObject(BLACK_BRUSH);
	
	if (lIdent <= 1) {
		GetDlgItemText(hExtG, EDIT_01_D_EXTG, cTexto, 5);
		PH = atoi(cTexto);
		GetDlgItemText(hExtG, EDIT_02_D_EXTG, cTexto, 5);
		TH = atoi(cTexto);
		GetDlgItemText(hExtG, EDIT_03_D_EXTG, cTexto, 5);
		EH = atoi(cTexto);
		GetDlgItemText(hExtG, EDIT_04_D_EXTG, cTexto, 5);
		PV = atoi(cTexto);
		GetDlgItemText(hExtG, EDIT_05_D_EXTG, cTexto, 5);
		TV = atoi(cTexto);
		GetDlgItemText(hExtG, EDIT_06_D_EXTG, cTexto, 5);
		EV = atoi(cTexto);
		GetDlgItemText(hExtG, EDIT_07_D_EXTG, cTexto, 5);
		PHU = atoi(cTexto);
		GetDlgItemText(hExtG, EDIT_08_D_EXTG, cTexto, 5);
		PVU = atoi(cTexto);
		
		if (!PH) PH = 37;		// Ponto inicial fHorizontal
		if (!TH) TH = 14;		// Tamanho fHorizontal
		if (!EH) EH = 48;		// Espaçamento fHorizontal
		if (!PV) PV = 84;		// Ponto inicial fVertical
		if (!TV) TV = 9;		// Tamanho fVertical
		if (!EV) EV = 17;		// Espaçamento fVertical
		if (!PHU) PHU = 38;		// PIH Ultimo quadro
		if (!PVU) PVU = 277;	// PIV Ultimo quadro
		
		if (!IsDlgButtonChecked(hExtG, BUTTON_04_D_EXTG)) {
			SetRect(&rectPos[0], PH+(EH*4), PV, PH+TH+(EH*4), PV+TV);
			SetRect(&rectPos[1], PH+(EH*4), PV+EV, PH+TH+(EH*4), PV+TV+EV);
			SetRect(&rectPos[2], PH+(EH*4), PV+(EV*2), PH+TH+(EH*4), PV+TV+(EV*2));
			SetRect(&rectPos[3], PH+(EH*4), PV+(EV*3), PH+TH+(EH*4), PV+TV+(EV*3));
			SetRect(&rectPos[4], PH+(EH*4), PV+(EV*4), PH+TH+(EH*4), PV+TV+(EV*4));
			SetRect(&rectPos[5], PH+(EH*3), PV, PH+TH+(EH*3), PV+TV);
			SetRect(&rectPos[6], PH+(EH*3), PV+EV, PH+TH+(EH*3), PV+TV+EV);
			SetRect(&rectPos[7], PH+(EH*3), PV+(EV*2), PH+TH+(EH*3), PV+TV+(EV*2));
			SetRect(&rectPos[8], PH+(EH*3), PV+(EV*3), PH+TH+(EH*3), PV+TV+(EV*3));
			SetRect(&rectPos[9], PH+(EH*3), PV+(EV*4), PH+TH+(EH*3), PV+TV+(EV*4));
			SetRect(&rectPos[10], PH+(EH*2), PV, PH+TH+(EH*2), PV+TV);
			SetRect(&rectPos[11], PH+(EH*2), PV+EV, PH+TH+(EH*2), PV+TV+EV);
			SetRect(&rectPos[12], PH+(EH*2), PV+(EV*2), PH+TH+(EH*2), PV+TV+(EV*2));
			SetRect(&rectPos[13], PH+(EH*2), PV+(EV*3), PH+TH+(EH*2), PV+TV+(EV*3));
			SetRect(&rectPos[14], PH+(EH*2), PV+(EV*4), PH+TH+(EH*2), PV+TV+(EV*4));
			SetRect(&rectPos[15], PH+EH, PV, PH+TH+EH, PV+TV);
			SetRect(&rectPos[16], PH+(EH*1), PV+EV, PH+TH+(EH*1), PV+TV+EV);
			SetRect(&rectPos[17], PH+(EH*1), PV+(EV*2), PH+TH+(EH*1), PV+TV+(EV*2));
			SetRect(&rectPos[18], PH+(EH*1), PV+(EV*3), PH+TH+(EH*1), PV+TV+(EV*3));
			SetRect(&rectPos[19], PH+(EH*1), PV+(EV*4), PH+TH+(EH*1), PV+TV+(EV*4));
			SetRect(&rectPos[20], PH, PV, PH+TH, PV+TV);
			SetRect(&rectPos[21], PH, PV+EV, PH+TH, PV+TV+EV);
			SetRect(&rectPos[22], PH, PV+(EV*2), PH+TH, PV+TV+(EV*2));
			SetRect(&rectPos[23], PH, PV+(EV*3), PH+TH, PV+TV+(EV*3));
			SetRect(&rectPos[24], PH, PV+(EV*4), PH+TH, PV+TV+(EV*4));
		} else {
			SetRect(&rectPos[0], PH, PV, PH+TH, PV+TV);
			SetRect(&rectPos[1], PH+EH, PV, PH+TH+EH, PV+TV);
			SetRect(&rectPos[2], PH+(EH*2), PV, PH+TH+(EH*2), PV+TV);
			SetRect(&rectPos[3], PH+(EH*3), PV, PH+TH+(EH*3), PV+TV);
			SetRect(&rectPos[4], PH+(EH*4), PV, PH+TH+(EH*4), PV+TV);
			SetRect(&rectPos[5], PH, PV+EV, PH+TH, PV+TV+EV);
			SetRect(&rectPos[6], PH+(EH*1), PV+EV, PH+TH+(EH*1), PV+TV+EV);
			SetRect(&rectPos[7], PH+(EH*2), PV+EV, PH+TH+(EH*2), PV+TV+EV);
			SetRect(&rectPos[8], PH+(EH*3), PV+EV, PH+TH+(EH*3), PV+TV+EV);
			SetRect(&rectPos[9], PH+(EH*4), PV+EV, PH+TH+(EH*4), PV+TV+EV);
			SetRect(&rectPos[10], PH, PV+(EV*2), PH+TH, PV+TV+(EV*2));
			SetRect(&rectPos[11], PH+(EH*1), PV+(EV*2), PH+TH+(EH*1), PV+TV+(EV*2));
			SetRect(&rectPos[12], PH+(EH*2), PV+(EV*2), PH+TH+(EH*2), PV+TV+(EV*2));
			SetRect(&rectPos[13], PH+(EH*3), PV+(EV*2), PH+TH+(EH*3), PV+TV+(EV*2));
			SetRect(&rectPos[14], PH+(EH*4), PV+(EV*2), PH+TH+(EH*4), PV+TV+(EV*2));
			SetRect(&rectPos[15], PH, PV+(EV*3), PH+TH, PV+TV+(EV*3));
			SetRect(&rectPos[16], PH+(EH*1), PV+(EV*3), PH+TH+(EH*1), PV+TV+(EV*3));
			SetRect(&rectPos[17], PH+(EH*2), PV+(EV*3), PH+TH+(EH*2), PV+TV+(EV*3));
			SetRect(&rectPos[18], PH+(EH*3), PV+(EV*3), PH+TH+(EH*3), PV+TV+(EV*3));
			SetRect(&rectPos[19], PH+(EH*4), PV+(EV*3), PH+TH+(EH*4), PV+TV+(EV*3));
			SetRect(&rectPos[20], PH, PV+(EV*4), PH+TH, PV+TV+(EV*4));
			SetRect(&rectPos[21], PH+(EH*1), PV+(EV*4), PH+TH+(EH*1), PV+TV+(EV*4));
			SetRect(&rectPos[22], PH+(EH*2), PV+(EV*4), PH+TH+(EH*2), PV+TV+(EV*4));
			SetRect(&rectPos[23], PH+(EH*3), PV+(EV*4), PH+TH+(EH*3), PV+TV+(EV*4));
			SetRect(&rectPos[24], PH+(EH*4), PV+(EV*4), PH+TH+(EH*4), PV+TV+(EV*4));
		}
		
		SetRect(&rectPos[25], PHU, PVU, PHU+10, PVU+6);
	}
	
	hdcWindow = GetDC(hwndPaleta);
	SetBkMode(hdcWindow, TRANSPARENT);
	SelectObject(hdcWindow, GetStockObject(DEFAULT_GUI_FONT));
	
	SetRect(&rect, 0, 0, 296, 500);
	FillRect(hdcWindow, &rect, hBrushA);
	
	for (int inc=1; inc<=25; inc++)
		for (int imp=1; imp<=15; imp++)
			if (lMatriz[imp] == inc) FillRect(hdcWindow, &rectPos[inc-1], hBrushB);
	
	FillRect(hdcWindow, &rectPos[25], hBrushB);
	
	SetRect(&rect, 190, 270, 270, 290);
	wsprintf(cTexto, "%d:%d", lIdent, lMatriz[0]);
	DrawText(hdcWindow, cTexto, -1, &rect, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
	
	ReleaseDC(hwndPaleta, hdcWindow);
	UpdateWindow(hwndPaleta);
	
	hdc = GetDC(hwndPaleta);
	nHdc = CreateCompatibleDC(hdc);
	dwWidth = 296;
	dwHeight = 500;
	((dwBPP = GetDeviceCaps(hdc, BITSPIXEL)) <= 8) ? dwNumColors = 256: dwNumColors = 0;
	
	bitMapInfo.bmiHeader.biSize				= sizeof(BITMAPINFOHEADER);
	bitMapInfo.bmiHeader.biWidth			= dwWidth;
	bitMapInfo.bmiHeader.biHeight			= dwHeight;
	bitMapInfo.bmiHeader.biPlanes			= 1;
	bitMapInfo.bmiHeader.biBitCount			= (WORD) dwBPP;
	bitMapInfo.bmiHeader.biCompression		= BI_RGB;
	bitMapInfo.bmiHeader.biSizeImage		= 0;
	bitMapInfo.bmiHeader.biXPelsPerMeter	= 0;
	bitMapInfo.bmiHeader.biYPelsPerMeter	= 0;
	bitMapInfo.bmiHeader.biClrUsed			= dwNumColors;
	bitMapInfo.bmiHeader.biClrImportant		= dwNumColors;
	
	if ((hBitmap = CreateDIBSection(hdc, &bitMapInfo, DIB_PAL_COLORS, &pBits, NULL, 0)) == (HBITMAP)NULL) {
		DeleteDC(nHdc);
		ReleaseDC(hwndPaleta, hdc);
		return 1;
	}
	
	gdiobj = SelectObject(nHdc, (HGDIOBJ) hBitmap);
	
	if ((gdiobj == NULL) || (gdiobj == (void *)GDI_ERROR)) {
		DeleteDC(nHdc);
		ReleaseDC(hwndPaleta, hdc);
		return 2;
	}
	
	if (!BitBlt(nHdc, 0, 0, dwWidth, dwHeight, hdc, 0,0, SRCCOPY)) {
		DeleteDC(nHdc);
		ReleaseDC(hwndPaleta, hdc);
		return 3;
	}
	
	if (dwNumColors != 0)
		dwNumColors = GetDIBColorTable(nHdc, 0, dwNumColors, colors);
	
	bFileHeader.bfType			= 0x4D42;
	bFileHeader.bfSize			= ((dwWidth*dwHeight*dwBPP)/8) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors*sizeof(RGBQUAD));
	bFileHeader.bfReserved1		= 0;
	bFileHeader.bfReserved2		= 0;
	bFileHeader.bfOffBits		= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));
	
	bInfoHeader.biSize			= sizeof(BITMAPINFOHEADER);
	bInfoHeader.biWidth			= dwWidth;
	bInfoHeader.biHeight		= dwHeight;
	bInfoHeader.biPlanes		= 1;
	bInfoHeader.biBitCount		= (WORD)dwBPP;
	bInfoHeader.biCompression	= BI_RGB;
	bInfoHeader.biSizeImage		= 0;
	bInfoHeader.biXPelsPerMeter	= 0;
	bInfoHeader.biYPelsPerMeter	= 0;
	bInfoHeader.biClrUsed		= dwNumColors;
	bInfoHeader.biClrImportant	= 0;
	
	wsprintf(cTexto, "cartelas\\%d_%d.bmp", lIdent, lMatriz[0]);
	
	if ((hFile = CreateFile(cTexto, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
		DeleteObject(hBitmap);
		DeleteDC(nHdc);
		ReleaseDC(hwndPaleta, hdc);
		return 4;
	}
	
	if ((WriteFile(hFile, &bFileHeader, sizeof(BITMAPFILEHEADER), &dwBytes, NULL)) == FALSE) return 5;
	if ((WriteFile(hFile, &bInfoHeader, sizeof(BITMAPINFOHEADER), &dwBytes, NULL)) == FALSE) return 6;
	
	if (dwNumColors != 0)
		if ((WriteFile(hFile, colors, sizeof(RGBQUAD)*dwNumColors,& dwBytes, NULL)) == FALSE) return 7;
	
	if ((WriteFile(hFile, pBits, (dwWidth*dwHeight*dwBPP)/8, &dwBytes, NULL)) == FALSE) return 8;
	
	CloseHandle(hFile);
	DeleteObject(hBitmap);
	DeleteDC(nHdc);
	ReleaseDC(hwndPaleta, hdc);
	
	return 0;
}
//-------------------------------------------------->>
void ext_g_save_card(INT iModo, HWND hwnd) {
	static DWORD dwTamanho;
	static LPSTR lpStrMemoria;
	static LONG longLocalAtual;
	static LONG longImagemAtual;
	
	if (iModo == START) {
		HANDLE hFile;
		DWORD dwRead;
		BOOL bStatus;
		
		longLocalAtual = longImagemAtual = 0;
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
			return;
		}
		
		general_block(MESSAGE_BLOCK);
		
		EnableWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTG), true);
		EnableWindow(GetDlgItem(hwnd, BUTTON_03_D_EXTG), true);
		SetDlgItemText(hwnd, BUTTON_03_D_EXTG, "Cancelar");
		
		if (!PathFileExists("cartelas")) CreateDirectory("cartelas", NULL);
		
		ShowWindow(hwndPaleta, SW_SHOWNORMAL);
		SetTimer(hwnd, TIMER_GENERATE_IMAGE_ID, TIMER_GENERATE_IMAGE_ELAPSE, NULL);
		return;
	}
	
	if (iModo == EXECUTE) {
		LONG lMatriz[16], lColuna;
		INT linha, iPosAtual;
		CHAR cConverter[11], cFormatar[25];
		BOOL bAlternar;
		FLOAT fQuociente, fPorcent;
		
		lColuna = linha = 0;
		bAlternar = false;
		
		while (true) {
			if (longLocalAtual >= dwTamanho) {
				ext_g_save_card(FINALIZE, hwnd);
				show_message((LPSTR)"Concluído", 2);
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
						ext_g_save_card(FINALIZE, hwnd);
						show_message((LPSTR)"res_data_base: Formatado incorretamente", 3);
						show_message((LPSTR)"Abortar", 2);
						return;
					}
					
					cConverter[iPosAtual] = 0;
				}
			} else {
				if (bAlternar == true) {
					bAlternar = false;
					
					lMatriz[linha] = atoi(cConverter);
					linha++;
					
					if (linha >= 16) {
						lColuna++;
						linha = 0;
						
						if (ext_g_save_image(lMatriz, ++longImagemAtual)) {
							ext_g_save_card(FINALIZE, hwnd);
							show_message((LPSTR)"Erro ao salvar imagens imagens", 3);
							show_message((LPSTR)"Abortar", 2);
							return;
						}
						
						if (lColuna >= 1) {
							longLocalAtual++;
							break;
						}
					}
				}
			}
			longLocalAtual++;
		}
		
		fQuociente = dwTamanho * 0.01;
		fPorcent = longLocalAtual / fQuociente;
		wsprintf(cFormatar, "[Salvar Cartelas: %d%%]", (int)fPorcent);
		SetDlgItemText(hwndMain, STATUS_BAR_02, cFormatar);
		SetTimer(hwnd, TIMER_GENERATE_IMAGE_ID, TIMER_GENERATE_IMAGE_ELAPSE, NULL);
		return;
	}
	
	if (iModo == FINALIZE) {
		GlobalFree(lpStrMemoria);
		ShowWindow(hwndPaleta, SW_HIDE);
		
		general_block(MESSAGE_UNBLOCK);
		SetDlgItemText(hwnd, BUTTON_02_D_EXTG, "Pausar");
		return;
	}
}
//-------------------------------------------------->>





