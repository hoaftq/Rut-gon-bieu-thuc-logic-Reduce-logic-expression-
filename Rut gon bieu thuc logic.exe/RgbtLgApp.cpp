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

BOOL CGioiThieuDlg::OnInitDialog(){
	CString strload;
	if(!CDialog::OnInitDialog()) return FALSE;
	SetDlgItemText(IDC_STATIC_ABOUT1,_T("\x43h\x1B0\x1A1ng tr�nh r�t g\x1ECDn h�m logi\x63-V\x31"));
	SetDlgItemText(IDC_STATIC_ABOUT2,_T("Vi\x1EBFt \x62\x1EDFi: Tr�\x63 Qu\x61ng Ho�"));
	SetDlgItemText(IDC_STATIC_ABOUT3,_T("L\x1EDBp \x110i\x1EC1u Khi\x1EC3n T\x1EF1 \x110\x1ED9ng \x31,\n Kho\x61 \x110i\x1EC7n, \x42�\x63h Kho\x61 H� N\x1ED9i"));
	SetDlgItemText(IDC_STATIC_ABOUT4,_T("Ng�y \x32\x37-\x30\x38-\x32\x30\x30\x38"));
	SetDlgItemText(IDC_STATIC_ABOUTCHUY,_T("Ch� �: \x42\x1EA1n \x63� th\x1EC3 nh\x1EADp t�n \x62i\x1EBFn v� \x63�\x63 \x111\x1EC9nh \x62\x1EB1ng ph�m Sp\x61\x63\x65"));	
	return TRUE;
}
