#ifndef RGBTLGAPP_H
#define RGBTLGAPP_H
#include <afxwin.h>
#include "resource.h"
class CRgbtLgApp: public CWinApp{
protected:	
	BOOL InitInstance();	
};

class CGioiThieuDlg: public CDialog{
public:
	CGioiThieuDlg(CWnd* pParentWnd):CDialog(IDD_GIOITHIEU,pParentWnd){}
};
#endif