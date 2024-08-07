#include "resource.h"

HWND hwndMain, hwndSec;
HINSTANCE hInstance;
//-------------------------------------------------->>
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_CREATE:
			wm_create(hwndMain = hwnd);
			break;
		
		case WM_COMMAND:
			wm_command(hwnd, wParam, lParam);
			break;
		
		case WM_PAINT:
			wm_paint();
			break;
		
		case WM_LBUTTONDOWN:
			if (!bWindowStatus) to_size(START, LOWORD(lParam), HIWORD(lParam), 0);
			break;
		
		case WM_LBUTTONDBLCLK:
			SendDlgItemMessage(hwndMain, OBJ_ID_MAX, WM_LBUTTONUP, 0, 0);
			break;
		
		case WM_TIMER:
			wm_timer(wParam);
			break;
		
		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED) wm_size();
			break;
		
		case WM_SHOWWINDOW:
			ext_a_list_view_insert_data(hwnd);
			ext_c_list_view_insert_data(hwnd);
			ext_e_list_view_insert_data(hwnd);
			PostMessage(hwndPanelA, WM_COMMAND, BUTTON_01_A, 0);
			if (hwndSec) DestroyWindow(hwndSec);
			break;
		
		case WM_CTLCOLORSTATIC:
			static HBRUSH hBrush = CreateSolidBrush(COLOR_MAIN_TITLE_BAR);
			if ((HWND) lParam == GetDlgItem(hwndMain, STATIC_ICON)) return (LRESULT) hBrush;
			break;
		
		case WM_KEYDOWN:
			if (wParam==VK_ESCAPE) DestroyWindow(hwnd);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SYSTEMTIME SystemTime;
	WNDCLASSEX wndClasseEx;
	MSG Msg;
	
	hInstance = hThisInstance;
	ZeroMemory(&wndClasseEx, sizeof(wndClasseEx));
	GetLocalTime(&SystemTime);
	
	//if ((SystemTime.wYear != 2017) || (SystemTime.wMonth != 4) || (SystemTime.wDay > 7)) return 0;
	
	wndClasseEx.cbSize			= sizeof(WNDCLASSEX);
	wndClasseEx.style			= CS_DBLCLKS;
	wndClasseEx.lpfnWndProc		= WndProc;
	wndClasseEx.hInstance		= hInstance;
	wndClasseEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wndClasseEx.hbrBackground	= (HBRUSH) CreateSolidBrush(COLOR_MAIN_BACKGROUND);
	wndClasseEx.lpszClassName	= MAIN_CLASS_NAME;
	wndClasseEx.hIcon			= LoadIcon(hInstance, "icone");
	wndClasseEx.hIconSm			= LoadIcon(hInstance, "icone");
	
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx MainClass!\t", true);
	
	wndClasseEx.hbrBackground	= CreateSolidBrush(COLOR_SECARY);
	wndClasseEx.lpfnWndProc		= MinProc;
	wndClasseEx.lpszClassName	= MIN_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx MinClass!\t", true);
	
	wndClasseEx.lpfnWndProc		= MaxProc;
	wndClasseEx.lpszClassName	= MAX_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx MaxClass!\t", true);
	
	wndClasseEx.lpfnWndProc		= CloseProc;
	wndClasseEx.lpszClassName	= CLOSE_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx CloseClass\t", true);
	
	wndClasseEx.hbrBackground	= (HBRUSH) COLOR_BACKGROUND;
	wndClasseEx.lpfnWndProc		= SecProc;
	wndClasseEx.lpszClassName	= SEC_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx SecClass!\t", true);
	
	wndClasseEx.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClasseEx.lpfnWndProc		= PltProc;
	wndClasseEx.lpszClassName	= PLT_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PltClass!\t", true);
	
	wndClasseEx.hbrBackground	= CreateSolidBrush(COLOR_MAIN_BACKGROUND);
	wndClasseEx.lpfnWndProc		= PanelAProc;
	wndClasseEx.lpszClassName	= PAINEL_A_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelA!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelBProc;
	wndClasseEx.lpszClassName	= PAINEL_B_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelB!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelCProc;
	wndClasseEx.lpszClassName	= PAINEL_C_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelC!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelDProc;
	wndClasseEx.lpszClassName	= PAINEL_D_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelD!\t", true);
	
	wndClasseEx.hbrBackground	= CreateSolidBrush(COLOR_PANEL_BACKGROUND);
	wndClasseEx.lpfnWndProc		= PanelDExtProcA;
	wndClasseEx.lpszClassName	= PD_EXT_A_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelDExtA!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelDExtProcB;
	wndClasseEx.lpszClassName	= PD_EXT_B_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelDExtB!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelDExtProcC;
	wndClasseEx.lpszClassName	= PD_EXT_C_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelDExtC!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelDExtProcD;
	wndClasseEx.lpszClassName	= PD_EXT_D_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelDExtD!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelDExtProcE;
	wndClasseEx.lpszClassName	= PD_EXT_E_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelDExtE!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelDExtProcF;
	wndClasseEx.lpszClassName	= PD_EXT_F_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelDExtF!\t", true);
	
	wndClasseEx.lpfnWndProc		= PanelDExtProcG;
	wndClasseEx.lpszClassName	= PD_EXT_G_CLASS_NAME;
	if (!RegisterClassEx(&wndClasseEx))
		error((LPSTR) "Erro: RegisterClassEx PanelDExtG!\t", true);
	
	if (!(hwndSec = CreateWindowEx(
		WS_EX_WINDOWEDGE | WS_EX_TOPMOST, SEC_CLASS_NAME, PROJECT_TITLE,
		WS_POPUPWINDOW | WS_VISIBLE,
		0, 0, 0, 0, 0, 0, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx hwndSec!\t", true);
	
	UpdateWindow(hwndSec);
	
	if (!(CreateWindowEx(
		WS_EX_WINDOWEDGE, MAIN_CLASS_NAME, PROJECT_TITLE,
		WS_POPUP | WS_SYSMENU,
		0, 0, 0, 0, 0, 0, hInstance, 0
	))) error((LPSTR) "Erro: CreateWindowEx hwndMain!\t", true);
	
	while(GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	
	return 0;
}
//-------------------------------------------------->>





