#include "resource.h"

#define BORDA	5
#define MODIF	-2
//-------------------------------------------------->>
void general_wm_paint(HWND hwnd, HDC hdcWindow) {
	HDC hdcMemory;
	RECT rc, rect;
	
	GetClientRect(hwnd, &rc);
	hdcMemory = CreateCompatibleDC(hdcWindow);
	
	static HBRUSH
		hBrushA = CreateSolidBrush(RGB(209, 222, 239)),
		hBrushB = CreateSolidBrush(RGB(194, 207, 224)),
		hBrushC = CreateSolidBrush(RGB(173, 185, 203)),
		hBrushD = CreateSolidBrush(COLOR_PANEL_BACKGROUND);
	
	// Quadros
	SetRect(&rect, BORDA, BORDA, rc.right-BORDA+3, rc.bottom-BORDA+3);
	FrameRect(hdcWindow, &rect, hBrushA);
	
	SetRect(&rect, BORDA, BORDA, rc.right-BORDA+2, rc.bottom-BORDA+2);
	FrameRect(hdcWindow, &rect, hBrushB);
	
	SetRect(&rect, BORDA, BORDA, rc.right-BORDA+1, rc.bottom-BORDA+1);
	FrameRect(hdcWindow, &rect, hBrushC);
	
	SetRect(&rc, BORDA, BORDA, rc.right-BORDA, rc.bottom-BORDA);
	FillRect(hdcWindow, &rc, hBrushD);
	
	// Imagens das pontas
	SelectObject(hdcMemory, hPrimary);
	BitBlt(hdcWindow, BORDA, BORDA, 15, 15, hdcMemory, 0, 0, SRCAND);
	BitBlt(hdcWindow, BORDA, BORDA, 15, 15, hdcMemory, 0, 0, SRCPAINT);
	
	SelectObject(hdcMemory, hSecond);
	BitBlt(hdcWindow, (rc.right+BORDA+MODIF)-15, BORDA, 15, 15, hdcMemory, 0, 0, SRCAND);
	BitBlt(hdcWindow, (rc.right+BORDA+MODIF)-15, BORDA, 15, 15, hdcMemory, 0, 0, SRCPAINT);
	
	SelectObject(hdcMemory, hTertiary);
	BitBlt(hdcWindow, BORDA, (rc.bottom+BORDA+MODIF)-15, 15, 15, hdcMemory, 0, 0, SRCAND);
	BitBlt(hdcWindow, BORDA, (rc.bottom+BORDA+MODIF)-15, 15, 15, hdcMemory, 0, 0, SRCPAINT);
	
	SelectObject(hdcMemory, hQuaternay);
	BitBlt(hdcWindow, (rc.right+BORDA+MODIF)-15, (rc.bottom+BORDA+MODIF)-15, 15, 15, hdcMemory, 0, 0, SRCAND);
	BitBlt(hdcWindow, (rc.right+BORDA+MODIF)-15, (rc.bottom+BORDA+MODIF)-15, 15, 15, hdcMemory, 0, 0, SRCPAINT);
	
	DeleteDC(hdcMemory);
}
//-------------------------------------------------->>
void general_block(INT iModo) {
	if (iModo == MESSAGE_BLOCK) {
		EnableWindow(GetDlgItem(hwndPanelC, BUTTON_01_C), false);
		EnableWindow(GetDlgItem(hwndPanelC, BUTTON_02_C), false);
		EnableWindow(GetDlgItem(hwndPanelC, BUTTON_03_C), false);
		EnableWindow(GetDlgItem(hwndPanelC, BUTTON_04_C), false);
		EnableWindow(GetDlgItem(hwndPanelC, BUTTON_05_C), false);
		EnableWindow(GetDlgItem(hwndPanelC, BUTTON_06_C), false);
		SendMessage(hExtA, WM_COMMAND, MESSAGE_BLOCK, 0);
		SendMessage(hExtC, WM_COMMAND, MESSAGE_BLOCK, 0);
		SendMessage(hExtD, WM_COMMAND, MESSAGE_BLOCK, 0);
		SendMessage(hExtE, WM_COMMAND, MESSAGE_BLOCK, 0);
		SendMessage(hExtF, WM_COMMAND, MESSAGE_BLOCK, 0);
		SendMessage(hExtG, WM_COMMAND, MESSAGE_BLOCK, 0);
		return;
	}
	
	if (iModo == MESSAGE_UNBLOCK) {
		EnableWindow(GetDlgItem(hwndPanelC, BUTTON_01_C), true);
		EnableWindow(GetDlgItem(hwndPanelC, BUTTON_04_C), true);
		SendMessage(hExtA, WM_COMMAND, MESSAGE_UNBLOCK, 0);
		SendMessage(hExtC, WM_COMMAND, MESSAGE_UNBLOCK, 0);
		SendMessage(hExtD, WM_COMMAND, MESSAGE_UNBLOCK, 0);
		SendMessage(hExtE, WM_COMMAND, MESSAGE_UNBLOCK, 0);
		SendMessage(hExtF, WM_COMMAND, MESSAGE_UNBLOCK, 0);
		SendMessage(hExtG, WM_COMMAND, MESSAGE_UNBLOCK, 0);
		EnableWindow(GetDlgItem(hExtG, BUTTON_02_D_EXTG), false);
		EnableWindow(GetDlgItem(hExtG, BUTTON_03_D_EXTG), false);
		return;
	}
}
//-------------------------------------------------->>
int general_available_disk(HWND hwnd, LONG lMax) {
	CHAR cDirectoryName[MAX_PATH+1];
    ULARGE_INTEGER uiFreeBytesAvailableToCaller, uiTotalNumberOfBytes, uiTotalNumberOfFreeBytes;
    float fFreeSpace;
	
    GetCurrentDirectory(MAX_PATH, &cDirectoryName[0]);
	GetDiskFreeSpaceEx(cDirectoryName, &uiFreeBytesAvailableToCaller, &uiTotalNumberOfBytes, &uiTotalNumberOfFreeBytes);
	fFreeSpace = (float)(uiFreeBytesAvailableToCaller.QuadPart/1024)/1024;
	
	if ((long)fFreeSpace < lMax) {
		if ((MessageBox(hwnd,
		"\n   O espaço em disco parece não ser suficiente.\t\n   Deseja continuar mesmo assim?\n",
		" (--_) Ops ", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1 | MB_TOPMOST)) != IDYES) return 1;
	}
	
	return 0;
}
//-------------------------------------------------->>





