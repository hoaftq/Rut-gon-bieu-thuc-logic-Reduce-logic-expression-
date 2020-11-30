#ifndef RGBTLGDLG_H
#define RGBTLGDLG_H
#include <afxwin.h>
#include "EditResult.h"
class CRgbtLgDlg: public CDialog{
	HICON m_hIcon;
	CComboBox m_cboDangBt;
	int m_nDangBt;//1 la dang tong chuan, 2 la dang tich chuan
	CEditResult m_editThem;
	CButton m_bntThem;
	int m_nThem; //1 la them bien, 2 la them dinh quan trong,3 la them dinh khong xac dinh
	CListBox m_lstTenBien,m_lstDQuanTrong,m_lstDKQuanTrong;
	CButton m_bntXoa;	
	int m_nXoa;//0 la dang o list ten bien, 1 la o list dinh quan trong, 2 la dinh khong quan trong
	
	bool m_bTang1;//dk thu gon la: tong so dau vao o tang 1 la nho nhat
public:
	CRgbtLgDlg(CWnd* pParentWnd);
	BOOL OnInitDialog();
	void DoDataExchange(CDataExchange * pDX);
	void OnCancel();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnThem();
	afx_msg void OnLen();
	afx_msg void OnXuong();

	afx_msg void OnSetFocusTenBien();
	afx_msg void OnSetFocusDQuanTrong();
	afx_msg void OnSetFocusDKQuanTrong();

	afx_msg void OnXoa();

	afx_msg void OnST1();
	afx_msg void OnSTTatCa();
	afx_msg void OnSP1();
	afx_msg void OnSPTatCa();

	afx_msg void OnRutGon();
	afx_msg void OnSelChangeDangBt();
	afx_msg void OnClkOption();

	afx_msg void OnRGHamMoi();

	afx_msg void OnEnSetFocusThem();

	afx_msg void OnGioiThieu();

	afx_msg void OnKQTotNhat();
	
	afx_msg void OnXoaKetQua();
	afx_msg void OnCopyKetQua();

	friend class CEditResult;
};
#endif