#include "mRgbtLg.h"
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){	
	HWND hwnd;
	MSG msg;
	DialogBox(hInstance,"MAINDLG",NULL,(DLGPROC)DlgProc);	
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}	
	return msg.wParam;
}
BOOL CALLBACK DlgProc(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam){
	switch(msg){
	case WM_INITDIALOG:
		return TRUE;
	}
	return TRUE;
}
