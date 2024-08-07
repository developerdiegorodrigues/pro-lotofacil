#include "resource.h"

//-------------------------------------------------->>
void ext_b_wm_create(HWND hwnd) {
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", "<",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_01_D_EXTB, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Button01 ExtB!\t", true);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, "Button", ">",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0, hwnd, (HMENU) BUTTON_02_D_EXTB, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx Button02 ExtB!\t", true);
}
//-------------------------------------------------->>
void ext_b_wm_paint(HWND hwnd) {
	PAINTSTRUCT PaintStruct;
	HDC hdcWindow;
	HFONT hFont;
	RECT rect, rc;
	FLOAT fInicial, fTamanho, fQuadrosLarg, fQuadrosAlt, fQuadrosHoriz, fQuadrosVert;
	CHAR cConverte[3], cAtual[15];
	
	static HBRUSH
		hBrushA = CreateSolidBrush(COLOR_CARD_BACKGROUND),
		hBrushB = CreateSolidBrush(COLOR_CARD_BUTTON_MARKED),
		hBrushC = CreateSolidBrush(COLOR_CARD_BUTTON_NORMAL);
	
	static HPEN
		hPen = CreatePen(PS_SOLID, 0, COLOR_CARD_LINE);
	
	GetClientRect(hwnd, &rc);
	
	hFont = CreateFont((
		rc.bottom/10)*0.80, ((rc.right/10)/10)*0.60,
		0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FF_SWISS | DEFAULT_PITCH, "Tahoma"
	);
	
	hdcWindow = BeginPaint(hwnd, &PaintStruct);
	
	SelectObject(hdcWindow, hPen);
	SelectObject(hdcWindow, hFont);
	SetBkMode(hdcWindow, TRANSPARENT);
	
	fTamanho = rc.right / 9;
	fQuadrosLarg = fTamanho / 6;
	fQuadrosAlt = rc.bottom / 6;
	
	for (INT inc=1; inc<8; inc++) {
		SelectObject(hdcWindow, hBrushA);
		fInicial = (rc.right/8*inc)-(fTamanho/2);
		RoundRect(hdcWindow, fInicial, 0, fInicial+fTamanho, rc.bottom, 20, 20);
		
		if (longCardExtA[inc-1][17]) {
			SetTextColor(hdcWindow, RGB(40, 40, 40));
			(inc == 1) ?
				wsprintf(cAtual, "• %d •", longCardExtA[inc-1][17]):
				wsprintf(cAtual, "%d", longCardExtA[inc-1][17]);
			SetRect(&rect, fInicial, 0, fInicial+fTamanho, rc.bottom-3);
			DrawText(hdcWindow, cAtual, -1, &rect, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);
		}
		
		for (INT imp=1; imp<6; imp++) {
			for (INT cont=1; cont<6; cont++) {
				fQuadrosHoriz = fInicial + fQuadrosLarg*cont - ((fQuadrosLarg/10)*4);
				fQuadrosVert = fQuadrosAlt*imp - ((fQuadrosAlt/10)*4);
				
				SelectObject(hdcWindow, hBrushC);
				
				for (INT ver=0; ver<15; ver++) {
					if ((longCardExtA[inc-1][ver]) == cont+((imp-1)*5)) {
						SelectObject(hdcWindow, hBrushB);
						break;
					}
				}
				
				Rectangle(hdcWindow, fQuadrosHoriz, fQuadrosVert, fQuadrosHoriz + ((fQuadrosLarg/10)*9), fQuadrosVert + ((fQuadrosAlt/10)*9));
				
				SetTextColor(hdcWindow, COLOR_CARD_LINE);
				wsprintf(cConverte, "%d", cont+((imp-1)*5));
				SetRect(&rect, fQuadrosHoriz, fQuadrosVert, fQuadrosHoriz + ((fQuadrosLarg/10)*9), fQuadrosVert + ((fQuadrosAlt/10)*9));
				DrawText(hdcWindow, cConverte, -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			}
		}
	}
	
	EndPaint(hwnd, &PaintStruct);
	DeleteObject(hFont);
}
//-------------------------------------------------->>
void ext_b_wm_command(HWND hwnd, WPARAM wParam) {
	RECT rect, rc;
	LONG lMax, lItem;
	FLOAT fDif;
	
	GetClientRect(hwnd, &rc);
	lItem = longCardExtA[0][15];
	
	if (longCardExtA[0][16] == 1) {
		lMax = ListView_GetItemCount(hListView_ext_a);
		
		if (LOWORD(wParam) == BUTTON_01_D_EXTB) {
			(lItem > 0) ?
			ext_a_change(lItem-1, lMax):
			ext_a_change(lMax-1, lMax);
		} else if (LOWORD(wParam) == BUTTON_02_D_EXTB) {
			(lItem < lMax - 1) ?
			ext_a_change(lItem+1, lMax):
			ext_a_change(0, lMax);
		}
	} else if (longCardExtA[0][16] == 2) {
		lMax = ListView_GetItemCount(hListView_ext_c);
		
		if (LOWORD(wParam) == BUTTON_01_D_EXTB) {
			(lItem > 0) ?
			ext_c_change(lItem-1, lMax):
			ext_c_change(lMax-1, lMax);
		} else if (LOWORD(wParam) == BUTTON_02_D_EXTB) {
			(lItem < lMax - 1) ?
			ext_c_change(lItem+1, lMax):
			ext_c_change(0, lMax);
		}
	} else if (longCardExtA[0][16] == 3) {
		lMax = ListView_GetItemCount(hListView_ext_e);
		
		if (LOWORD(wParam) == BUTTON_01_D_EXTB) {
			(lItem > 0) ?
			ext_e_change(lItem-1, lMax):
			ext_e_change(lMax-1, lMax);
		} else if (LOWORD(wParam) == BUTTON_02_D_EXTB) {
			(lItem < lMax - 1) ?
			ext_e_change(lItem+1, lMax):
			ext_e_change(0, lMax);
		}
	} else {
		show_message((LPSTR)"Selecione um item em uma das listas", 3);
		return;
	}
	
	fDif = (rc.right/10) * 0.80;
	SetRect(&rect, fDif, rc.bottom/10, rc.right-fDif, rc.bottom);
	InvalidateRect(hwnd, &rect, TRUE);
	
	SetFocus(hwnd);
}
//-------------------------------------------------->>
LRESULT CALLBACK PanelDExtProcB(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			ext_b_wm_create(hwnd);
			break;
		
		case WM_COMMAND:
			ext_b_wm_command(hwnd, wParam);
			break;
		
		case WM_KEYDOWN:
			if ((wParam == VK_LEFT) || (wParam == VkKeyScan('a'))) {
				PostMessage(hwnd, WM_COMMAND, BUTTON_01_D_EXTB, 0);
				break;
			}
			
			if ((wParam == VK_RIGHT) || (wParam == VkKeyScan('d'))) {
				PostMessage(hwnd, WM_COMMAND, BUTTON_02_D_EXTB, 0);
				break;
			}
			break;
		
		case WM_SIZE:
			RECT rc;
			GetClientRect(hwnd, &rc);
			MoveWindow(GetDlgItem(hwnd, BUTTON_01_D_EXTB), 0, 5, (rc.right/10)*0.50, rc.bottom-10, TRUE);
			MoveWindow(GetDlgItem(hwnd, BUTTON_02_D_EXTB), rc.right-(rc.right/10)*0.50, 5, (rc.right/10)*0.50, rc.bottom-10, TRUE);
			break;
		
		case WM_PAINT:
			ext_b_wm_paint(hwnd);
			break;
		
		case WM_CTLCOLORBTN:
			return (LRESULT)(HBRUSH) hBrushButton;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





