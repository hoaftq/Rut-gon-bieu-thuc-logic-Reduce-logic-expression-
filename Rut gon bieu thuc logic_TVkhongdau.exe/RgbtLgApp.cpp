#include "RgbtLgApp.h"
#include "RgbtLgDlg.h"
#include "resource.h"
CRgbtLgApp theRgbtLgApp;

CRgbtLgApp::InitInstance(){
	CRgbtLgDlg mainDlg(NULL);	
	m_pMainWnd= &mainDlg;
	mainDlg.DoModal();
	return FALSE;
}
