#include "resource.h"

//-------------------------------------------------->>
LRESULT CALLBACK PltProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_SIZE:
			MoveWindow(hwnd, 1, 1, 300, 504, TRUE);
			break;
		
		case WM_CLOSE:
			return 0;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hwnd, Message, wParam, lParam);
}
//-------------------------------------------------->>





