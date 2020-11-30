#include <math.h>
#include "resource.h"
#include "RgbtLgDlg.h"
#include "ReduceQuineMcCluskey.h"
#include "RgbtLgApp.h"
CRgbtLgDlg::CRgbtLgDlg(CWnd * pParentWnd):CDialog(IDD_MAIN,pParentWnd){
	m_nXoa= -1;//viec xoa khong o dau ca
				//0 la xoa o m_lstTenBien, 1 la m_lstDQuanTrong, 2 la m_lstDKQuanTrong
}
BOOL CRgbtLgDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	m_hIcon= AfxGetApp()->LoadIcon(IDI_MAIN);
	SetIcon(m_hIcon,FALSE);
	//m_editThem.Attach(GetDlgItem(IDCE_THEM)->m_hWnd);
	m_editThem.SubclassDlgItem(IDCE_THEM,this);
	m_bntThem.Attach(GetDlgItem(IDC_THEM)->m_hWnd);
	m_lstTenBien.Attach(GetDlgItem(IDCL_TENBIEN)->m_hWnd);
	m_lstDQuanTrong.Attach(GetDlgItem(IDCL_DQUANTRONG)->m_hWnd);
	m_lstDKQuanTrong.Attach(GetDlgItem(IDCL_DKQUANTRONG)->m_hWnd);
	m_bntXoa.Attach(GetDlgItem(IDC_XOA)->m_hWnd);	
	m_cboDangBt.Attach(GetDlgItem(IDCC_DANGBT)->m_hWnd);
	
	((CButton*)GetDlgItem(IDCR_THEM_1))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_THEM))->SetWindowText(_T("Them bien"));
	m_nThem= 1;//them mac dinh ban dau la them bien
	
	CString strload(_T("T\x1ED5ng \x63hu\x1EA9n"));
	m_cboDangBt.AddString(strload);
	m_cboDangBt.AddString(_T("TÝch chuÈn"));
	m_cboDangBt.SetCurSel(0);
	m_cboDangBt.SetWindowText(_T("T\x1ED5ng \x63hu\x1EA9n"));

	m_nDangBt= 1;//bieu thuc dang tong chuan
	((CStatic*)GetDlgItem(IDC_TDDQUANTRONG))->SetWindowText(_T("Cac dinh 1:"));
	((CButton*)GetDlgItem(IDCR_THEM_2))->SetWindowText(_T("Them dinh 1"));

	m_bTang1= TRUE;
	((CButton*)GetDlgItem(IDCCHK_KQTOTNHAT))->SetCheck(TRUE);
	SetDlgItemText(IDC_RUTGON,_T("Rút g\x1ECDn hàm : T\x1ED5ng s\x1ED1 \x111\x1EA7u vào \x1EDF t\x1EA7ng \x31 là nh\x1ECF nh\x1EA5t!"));
	
	SetDlgItemText(IDC_STATIC1,_T("\x44\x1EA1ng \x63\x1EE7\x61 \x62i\x1EC3u th\x1EE9\x63:"));
	return TRUE;
}
BEGIN_MESSAGE_MAP(CRgbtLgDlg,CDialog)
	ON_BN_CLICKED(IDC_THEM,OnThem)	
	ON_BN_CLICKED(IDC_LEN,OnLen)
	ON_BN_CLICKED(IDC_XUONG,OnXuong)
	ON_LBN_SETFOCUS(IDCL_TENBIEN,OnSetFocusTenBien)
	ON_LBN_SETFOCUS(IDCL_DQUANTRONG,OnSetFocusDQuanTrong)
	ON_LBN_SETFOCUS(IDCL_DKQUANTRONG,OnSetFocusDKQuanTrong)
	ON_BN_CLICKED(IDC_XOA,OnXoa)
	ON_BN_CLICKED(IDC_ST1,OnST1)
	ON_BN_CLICKED(IDC_STTATCA,OnSTTatCa)
	ON_BN_CLICKED(IDC_SP1,OnSP1)
	ON_BN_CLICKED(IDC_SPTATCA,OnSPTatCa)
	ON_BN_CLICKED(IDC_RUTGON,OnRutGon)
	ON_BN_CLICKED(IDCR_THEM_1,OnClkOption)
	ON_BN_CLICKED(IDCR_THEM_2,OnClkOption)
	ON_BN_CLICKED(IDCR_THEM_3,OnClkOption)
	ON_CBN_SELCHANGE(IDCC_DANGBT,OnSelChangeDangBt)
	ON_BN_CLICKED(IDC_RGHAMMOI,OnRGHamMoi)
	ON_EN_SETFOCUS(IDCE_THEM,OnEnSetFocusThem)
	ON_BN_CLICKED(IDC_GIOITHIEU,OnGioiThieu)
	ON_BN_CLICKED(IDCCHK_KQTOTNHAT,OnKQTotNhat)
	ON_BN_CLICKED(IDC_XOAKETQUA,OnXoaKetQua)
	ON_BN_CLICKED(IDC_COPYKETQUA,OnCopyKetQua)
END_MESSAGE_MAP()

void CRgbtLgDlg::DoDataExchange(CDataExchange * pDX){
	CDialog::DoDataExchange(pDX);
}
void CRgbtLgDlg::OnThem(){
	int i;	
	CString strThem,strItem;
	
	m_editThem.GetWindowText(strThem);
	if(strThem=="") return;
	if(m_nThem==1){//them bien
		for(int i=0; i< m_lstTenBien.GetCount(); i++){
			m_lstTenBien.GetText(i,strItem);		
			if(strThem == strItem) goto lblSetFocus;
		}
		m_lstTenBien.AddString(strThem);
		m_lstTenBien.SetTopIndex(m_lstTenBien.GetTopIndex()+1);
	}else{//them dinh quan trong hay khong tuy vao m_nThem= 2/3
		
		//neu them vao phan dinh thi phai la so		
		while(strThem.GetAt(0)==_T('0') && strThem.GetLength()> 1){
			strThem.Delete(0);
		}

		for(i=0; i<strThem.GetLength(); i++)
			if(strThem[i]<_T('0') || strThem[i]>_T('9')) goto lblSetFocus;
		for(i=0; i< m_lstDQuanTrong.GetCount(); i++){
			m_lstDQuanTrong.GetText(i,strItem);		
			if(strThem == strItem) goto lblSetFocus;
		}
		for(i=0; i< m_lstDKQuanTrong.GetCount(); i++){
			m_lstDKQuanTrong.GetText(i,strItem);		
			if(strThem == strItem) goto lblSetFocus;
		}
		if(m_nThem==2){
			m_lstDQuanTrong.AddString(strThem);
			m_lstDQuanTrong.SetTopIndex(m_lstDQuanTrong.GetTopIndex()+1);
		}else{
			m_lstDKQuanTrong.AddString(strThem);
			m_lstDKQuanTrong.SetTopIndex(m_lstDKQuanTrong.GetTopIndex()+1);
		}
	}
lblSetFocus:
	m_editThem.SetFocus();
	//m_editThem.SetSel(0,-1);
}
void CRgbtLgDlg::OnLen(){
	if(m_lstTenBien.GetCount()==0) return;
	UINT nSel= m_lstTenBien.GetCurSel();
	if(nSel==LB_ERR) return;
	if(nSel !=0){
		CString strMove;
		m_lstTenBien.GetText(nSel,strMove);
		m_lstTenBien.DeleteString(nSel);
		m_lstTenBien.InsertString(nSel-1,strMove);
		m_lstTenBien.SetCurSel(nSel-1);
	}
}
void CRgbtLgDlg::OnXuong(){
	if(m_lstTenBien.GetCount()==0) return;
	int nSel= m_lstTenBien.GetCurSel();
	if(nSel==LB_ERR) return;
	if(nSel != m_lstTenBien.GetCount()-1){
		CString strMove;
		m_lstTenBien.GetText(nSel,strMove);
		m_lstTenBien.DeleteString(nSel);
		m_lstTenBien.InsertString(nSel+1,strMove);
		m_lstTenBien.SetCurSel(nSel+1);
	}
}
void CRgbtLgDlg::OnSetFocusTenBien(){
	m_bntXoa.SetWindowText(_T("Xoa ten bien"));
	m_nXoa= 0;
}

void CRgbtLgDlg::OnSetFocusDQuanTrong(){
	if(m_nDangBt==1)
		m_bntXoa.SetWindowText(_T("Xoa dinh 1"));
	else 
		m_bntXoa.SetWindowText(_T("Xoa dinh 0"));
	m_nXoa= 1;
}

void CRgbtLgDlg::OnSetFocusDKQuanTrong(){
	m_bntXoa.SetWindowText(_T("Xoa dinh khong xac dinh"));
	m_nXoa= 2;
}

void CRgbtLgDlg::OnXoa(){
	int i;
	switch(m_nXoa){
	case 0://xoa ten bien
		if(m_lstTenBien.GetCurSel()!= LB_ERR){
			i= m_lstTenBien.GetCurSel();
			m_lstTenBien.DeleteString(i);
			if(i< m_lstTenBien.GetCount()) m_lstTenBien.SetCurSel(i);
			else if(i-1>=0) m_lstTenBien.SetCurSel(i-1);
		}
		break;
	case 1://xoa dinh quan trong
		for(i=0; i< m_lstDQuanTrong.GetCount(); i++)
			if(m_lstDQuanTrong.GetSel(i)>0){
				m_lstDQuanTrong.DeleteString(i);
				i--;
			}
		break;
	case 2://xoa dinh khong quan trong
		for(i=0; i< m_lstDKQuanTrong.GetCount(); i++)
			if(m_lstDKQuanTrong.GetSel(i)>0){
				m_lstDKQuanTrong.DeleteString(i);		
				i--;
			}
	}
}
void CRgbtLgDlg::OnST1(){
	CString strCopy;
	for(int i=0; i< m_lstDQuanTrong.GetCount(); i++)
			if(m_lstDQuanTrong.GetSel(i)>0){
				m_lstDQuanTrong.GetText(i,strCopy);
				m_lstDKQuanTrong.AddString(strCopy);
				m_lstDQuanTrong.DeleteString(i);
				i--;
			}	
}
void CRgbtLgDlg::OnSTTatCa(){
	CString strCopy;
	for(int i=0; i< m_lstDQuanTrong.GetCount(); i++){
		m_lstDQuanTrong.GetText(i,strCopy);
		m_lstDQuanTrong.DeleteString(i); i--;
		m_lstDKQuanTrong.AddString(strCopy);
	}	
}
void CRgbtLgDlg::OnSP1(){
	CString strCopy;
	for(int i=0; i< m_lstDKQuanTrong.GetCount(); i++)
			if(m_lstDKQuanTrong.GetSel(i)>0){
				m_lstDKQuanTrong.GetText(i,strCopy);
				m_lstDQuanTrong.AddString(strCopy);
				m_lstDKQuanTrong.DeleteString(i);
				i--;
			}		
}
void CRgbtLgDlg::OnSPTatCa(){
	CString strCopy;
	for(int i=0; i< m_lstDKQuanTrong.GetCount(); i++){
		m_lstDKQuanTrong.GetText(i,strCopy);
		m_lstDKQuanTrong.DeleteString(i); i--;
		m_lstDQuanTrong.AddString(strCopy);
	}		
}
void CRgbtLgDlg::OnRutGon(){
	int i;				
	CTabReduce tr(m_nDangBt==1?true:false,m_bTang1);
	int nSoBien= m_lstTenBien.GetCount();
	if(nSoBien==0){MessageBox(_T("Phai nhap bien cho ham !"),NULL,MB_OK|MB_ICONINFORMATION); return;}
	if(m_lstDQuanTrong.GetCount()==0){
		if(m_nDangBt==1) MessageBox(_T("Phai nhap dinh 1 !"),NULL,MB_OK|MB_ICONINFORMATION);
		else MessageBox(_T("Phai nhap dinh 0 !"),NULL,MB_OK|MB_ICONINFORMATION);
		return;
	}
	int nNum;
	CString strMess;
	CString strItem;
	for(i=0; i< m_lstDQuanTrong.GetCount(); i++){
		m_lstDQuanTrong.GetText(i,strItem);
		nNum= _wtoi(strItem);//(LPCSTR)
		if(nNum>= pow(2,nSoBien)){
			strMess.Format(_T("Dinh xac dinh %d khong hop ly."),nNum);	
			MessageBox(strMess,NULL,MB_OK|MB_ICONINFORMATION);
			m_lstDQuanTrong.SetSel(i);
			OnSetFocusDQuanTrong();
			return;
		}else{
			tr.AddIsImp(nNum);
		}
			
	}
	for(i=0; i< m_lstDKQuanTrong.GetCount(); i++){
		m_lstDKQuanTrong.GetText(i,strItem);
		nNum= _wtoi(strItem);//(LPCSTR)
		if(nNum>= pow(2,nSoBien)){
			strMess.Format(_T("Dinh khong xac dinh %d khong hop ly."),nNum);	
			MessageBox(strMess,NULL,MB_OK|MB_ICONINFORMATION);
			m_lstDKQuanTrong.SetSel(i);
			OnSetFocusDKQuanTrong();
			return;
		}else{
			tr.AddIsX(nNum);
		}
	}
	for(i=0; i< m_lstTenBien.GetCount(); i++){
		m_lstTenBien.GetText(i,strItem);
		tr.AddNameDim(strItem);
	}
	tr.Reduce();
	CString strResult;
	((CEdit*)GetDlgItem(IDCE_KETQUA))->SendMessage(WM_KEYDOWN,VK_END,0);//ve cuoi text
	for(i=0; i< ((CEdit*)GetDlgItem(IDCE_KETQUA))->GetLineCount(); i++)
		((CEdit*)GetDlgItem(IDCE_KETQUA))->SendMessage(WM_KEYDOWN,VK_DOWN,0);//ve dong cuoi cung
	strResult= "**Ket qua rut gon cua ham f(";
	for(i=0; i< m_lstTenBien.GetCount()-1; i++){
		m_lstTenBien.GetText(i,strItem);
		strResult= strResult+ strItem +",";
	}
	m_lstTenBien.GetText(i,strItem);
	strResult= strResult+strItem +") = ";
	if(m_nDangBt==1) strResult+= "Tong("; else strResult+="Tich(";
	for(i= 0; i< m_lstDQuanTrong.GetCount(); i++){
		m_lstDQuanTrong.GetText(i,strItem);
		if(i!= m_lstDQuanTrong.GetCount()-1) strResult= strResult+ strItem+",";
		else strResult+= strItem;
	}
	strResult+="); N(";
	for(i= 0; i< m_lstDKQuanTrong.GetCount(); i++){
		m_lstDKQuanTrong.GetText(i,strItem);
		if(i!= m_lstDKQuanTrong.GetCount()-1) strResult= strResult+strItem+",";
		else strResult+=strItem;
	}
	strResult+= ") la:";
	//MessageBox(strResult);
	((CEdit*)GetDlgItem(IDCE_KETQUA))->ReplaceSel(strResult);//viet thong so cua ham
	((CEdit*)GetDlgItem(IDCE_KETQUA))->SendMessage(WM_CHAR,13,0); //xuong dong
	
	if(m_bTang1)
		strResult.Format(_T(" (Ca(min) = %d, Toi thieu theo tieu chuan tong so dau vao o tang thu nhat la nho nhat)"),tr.GetCaCb());
	else
		strResult.Format(_T(" (Cb(min) = %d, Toi thieu theo tieu chuan tong so dau vao o ca hai tang la nho nhat)"),tr.GetCaCb());
	((CEdit*)GetDlgItem(IDCE_KETQUA))->ReplaceSel(strResult); //viet tieu chuan
	((CEdit*)GetDlgItem(IDCE_KETQUA))->SendMessage(WM_CHAR,13,0); //xuong dong
	
	strResult.Format(_T(" (Co %d ket qua)"),tr.GetCountResult());
	((CEdit*)GetDlgItem(IDCE_KETQUA))->ReplaceSel(strResult); //viet so ket qua
	((CEdit*)GetDlgItem(IDCE_KETQUA))->SendMessage(WM_CHAR,13,0); //xuong dong
	
	for(i=0; i< tr.GetCountResult(); i++){//viet lan luot cac ket qua		
		//if(tr.GetResult(i)=="") strResult= " 1";
		//else 
		strResult= " "+ tr.GetResult(i);
		((CEdit*)GetDlgItem(IDCE_KETQUA))->ReplaceSel(strResult);		
		((CEdit*)GetDlgItem(IDCE_KETQUA))->SendMessage(WM_CHAR,13,0);
	}
}

void CRgbtLgDlg::OnCancel(){
	//m_editThem.Detach();
	m_bntThem.Detach();
	m_lstTenBien.Detach();
	m_lstDQuanTrong.Detach();
	m_lstDKQuanTrong.Detach();
	m_bntXoa.Detach();
	m_cboDangBt.Detach();
	CDialog::OnCancel();
}

void CRgbtLgDlg::OnSelChangeDangBt(){
	int nCurSel= m_cboDangBt.GetCurSel();
	if(nCurSel==0){
		m_nDangBt= 1; //dang tong chuan
		((CStatic*)GetDlgItem(IDC_TDDQUANTRONG))->SetWindowText(_T("Cac dinh 1:"));
		((CButton*)GetDlgItem(IDCR_THEM_2))->SetWindowText(_T("Them dinh 1"));
		if(m_nThem==2) m_bntThem.SetWindowText(_T("Them dinh 1"));
		if(m_nXoa==1) m_bntXoa.SetWindowText(_T("Xoa dinh 1"));
	}else{
		m_nDangBt= 2;//dang tich chuan
		((CStatic*)GetDlgItem(IDC_TDDQUANTRONG))->SetWindowText(_T("Cac dinh 0:"));
		((CButton*)GetDlgItem(IDCR_THEM_2))->SetWindowText(_T("Them dinh 0"));
		if(m_nThem==2) m_bntThem.SetWindowText(_T("Them dinh 0"));
		if(m_nXoa==1) m_bntXoa.SetWindowText(_T("Xoa dinh 0"));
	}
}

void CRgbtLgDlg::OnClkOption(){
	for(int i= IDCR_THEM_1; i<= IDCR_THEM_3; i++){
		if(((CButton*)GetDlgItem(i))->GetCheck()==1){
			m_nThem= i-IDCR_THEM_1+1;
			break;
		}
	}
	switch(m_nThem){
	case 1:
		((CButton*)GetDlgItem(IDC_THEM))->SetWindowText(_T("Them bien")); break;
	case 2:
		if(m_nDangBt==1)
			((CButton*)GetDlgItem(IDC_THEM))->SetWindowText(_T("Them dinh 1"));
		else
			((CButton*)GetDlgItem(IDC_THEM))->SetWindowText(_T("Them dinh 0"));
		break;
	case 3:
		((CButton*)GetDlgItem(IDC_THEM))->SetWindowText(_T("Them dinh khong xac dinh"));
	}

	m_editThem.SetFocus();
	//m_editThem.SetSel(0,-1);
}

void CRgbtLgDlg::OnRGHamMoi(){
	int i;
	for(i= 0; i< m_lstDQuanTrong.GetCount(); i++){
		m_lstDQuanTrong.DeleteString(i);
		i--;
	}
	for(i= 0; i< m_lstDKQuanTrong.GetCount(); i++){
		m_lstDKQuanTrong.DeleteString(i);
		i--;
	}
	m_editThem.SetFocus();
}

void CRgbtLgDlg::OnEnSetFocusThem(){
	m_editThem.SetSel(0,-1);
}

void CRgbtLgDlg::OnGioiThieu(){	
	CGioiThieuDlg gtDlg(this);
	gtDlg.DoModal();
}

void CRgbtLgDlg::OnKQTotNhat(){
	m_bTang1= !m_bTang1;
	((CButton*)GetDlgItem(IDCCHK_KQTOTNHAT))->SetCheck(m_bTang1);
	if(m_bTang1)
		SetDlgItemText(IDC_RUTGON,_T("Rút g\x1ECDn hàm logi\x63 : t\x1ED5ng s\x1ED1 \x111\x1EA7u vào \x1EDF t\x1EA7ng \x31 là nh\x1ECF nh\x1EA5t!"));
	else
		SetDlgItemText(IDC_RUTGON,_T("Rút g\x1ECDn hàm logi\x63 : t\x1ED5ng s\x1ED1 \x111\x1EA7u vào \x1EDF \x63\x1EA3 h\x61i t\x1EA7ng là nh\x1ECF nh\x1EA5t!"));
}

void CRgbtLgDlg::OnXoaKetQua(){
	SetDlgItemText(IDCE_KETQUA,_T(""));
}

void CRgbtLgDlg::OnCopyKetQua(){	
	HGLOBAL hClipboard;
	LPSTR lpClipboard;
	CString strKetQua;	
	GetDlgItemText(IDCE_KETQUA,strKetQua);
	if(strKetQua=="") return;///???
	OpenClipboard();
	EmptyClipboard();
	hClipboard= GlobalAlloc(GMEM_MOVEABLE,strKetQua.GetLength()+1);
	lpClipboard= (char*)GlobalLock(hClipboard);
	memcpy(lpClipboard,LPCTSTR(strKetQua),strKetQua.GetLength());
	GlobalUnlock(hClipboard);
	SetClipboardData(CF_TEXT,lpClipboard);
	//GlobalFree(hClipboard);
	CloseClipboard();	
}
