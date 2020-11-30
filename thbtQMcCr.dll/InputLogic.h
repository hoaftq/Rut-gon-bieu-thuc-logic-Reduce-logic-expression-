#if !defined(INPUTLOGIC_H)
#define INPUTLOGIC_H
#include <afxcoll.h>
/*
	Lop de nhap va chua cac thong so cua 1 ham logic

*/
class AFX_EXT_CLASS CInputLogic{
protected:
	//so bien cua bieu thuc logic
	INT iDim;
	//mang luu ten bien
	CStringArray arrDimName; 
	//mang luu cac dinh quan trong
	CUIntArray arrIsImp;
	//mang luu cac dinh khong quan trong
	CUIntArray arrIsX;
	//ham chuyen 1 tich cuc tieu ve dang bieu thuc cac bien
	//vi du _001_ thanh not(y).not(z).t voi x,y,z,t la ten cac bien
	CString Str2Exp(const CString & rowbin);
	
	//dang cua bieu thuc logic
	bool bSumStandard; //= true co nghia la tong chuan, false la tich chuan
	
	//ham dem so phan tu 0 va 1 trong 1 hang, bo qua phan tu _
	//ham nay se phu tro cho ham dem so dau vao o tang 1 o lop CTabReduce
	int GetCount01(const CString & rowbin);
public:
	//dimname la day ten bien duoc phan cach boi separate
	bool SetNameDim(CString dimname,TCHAR separate);
	//dimname la ten 1 bien
	bool AddNameDim(CString dimname);
	//them cac dinh quan trong
	bool AddIsImp(UINT isImp);
	//them cac dinh tuy y
	bool AddIsX(UINT isX);
	//tra ve so bien cua bieu thuc logic
	INT GetNumDim() const;
	//tra ve so dinh quan trong cua bieu thuc logic
	INT GetSizeIsImp() const;
	//tra ve so dinh tuy y cua bieu thuc logic
	INT GetSizeIsX() const;

	CInputLogic(bool styleSum= true); //bSum tuong ung voi dang cua bieu thuc
	~CInputLogic();
#ifdef _DEBUG
	//hien tat ca cac ten bien cua bieu thuc logic
	void ShowNameDim();
#endif
};
#endif