#include "EditResult.h"
#include "RgbtLgDlg.h"
BEGIN_MESSAGE_MAP(CEditResult,CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()
void CEditResult::OnChar(UINT nChar,UINT nRepCnt,UINT nFlags){
	if(nChar==32){
		((CRgbtLgDlg*)GetParent())->OnThem();
		SetSel(0,-1);
	}else{
		CEdit::OnKeyDown(nChar,nRepCnt,nFlags);
	}
}