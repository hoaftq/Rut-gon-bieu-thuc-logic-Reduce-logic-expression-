#ifndef EDITRESULT_H
#define EDITRESULT_H
#include <afxwin.h>
class CEditResult: public CEdit{	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar(UINT nChar,UINT nRepCnt,UINT nFlags);
};
#endif