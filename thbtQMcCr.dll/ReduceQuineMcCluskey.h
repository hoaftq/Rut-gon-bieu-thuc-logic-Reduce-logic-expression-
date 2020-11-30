#ifndef REDUCEQUINEMCCLUSKEY_H
#define REDUCEQUINEMCCLUSKEY_H
#include <afxcoll.h>
#include "InputLogic.h"

class AFX_EXT_CLASS CTabReduce: public CInputLogic{
	//so phan tu cua 2 mang nay chinh la CInputLogic.GetSizeIsImp(), so cac dinh quan trong
	CUIntArray *pCol;
	int * piUsed;

	//luu tat ca cac tich cuc tieu sau khi da ket hop cac bang xong
	CStringArray arrstrProdRedu;
	

	//luu lan luot cac tich phu het, day la cac bo chi? so tich cuc tieu nho nhat phu het cac dinh quan trong
	//so phan tu cua moi bo chinh la iMinProd
	CUIntArray arruResult;
	//int iMinProd;//so nho nhat cac tich phu het hien tai(cach lam cu, chi xet den so phan tu o tang 2)
	//vi du: phan tu arrCntForResult[0] chua chi so cuoi cua ket qua thu nhat trong mang ket qua arruResult
	//so phan tu cua mang nay chinh la so ket qua
	CUIntArray arrCntForResult;
	//tong so dau vao
	//neu bLayer1== true thi day chinh la tong so dau vao nho nhat o tang 1 dang luu trong mang arruResult
	//neu bLayer1== false thi day chinh la tong so dau vao nho nhat o ca hai tang
	int iLayer;


	//hai ham nay phu tro cho ham Recursive,dung de lay ve nhung ket qua phu
	//hop voi mot trong hai yeu cau la: tong so dau vao o tang 1 la nho nhat hoac
	//tong so dau vao o ca hai tang la nho nhat
	//!ham nay dem so phan tu o tang 1 ung voi cac chi so cua ket qua trong ovl
	//(cac chi so nay su dung de truy nhap arrstrProdRedu)
	int CountLayer1(CUIntArray & ovl);
	//ham nay tinh them o ca tang 2
	int CountLayer12(CUIntArray & ovl);	
	//tieu chuan rut gon, neu la true thi tong dau vao o tang 1 la nho nhat
	//neu la false thi tong dau vao o ca hai tang la nho nhat
	bool bLayer1;	

	//dien day mang arrstrProdRedu chua cac tich cuc tieu
	void FillProdRedu();
	
	//ham kiem tra xem tich cuc tieu rowbin co phu? duoc so num hay khong
	bool Overlay(int num, CString rowbin);
	
	//ham su dung gia tri trong arrstrProdRedu de dien day pCol va pbUsed
	//phuc vu cho viec tim phu dinh quan cuc tieu
	void FillColUsed();
	
	//kiem tra xem mang ovl da ton tai trong arruResult hay chua
	bool Exist(const CUIntArray & ovl);
	
	//thuc hien de qui quay lui tim tat ca cac phu cuc tieu( chua ket qua trong arruRsult va iMinProd)
	void Recursive(int col,CUIntArray & ovl);

	
	CStringArray arrstrResult;//luu ket qua cuoi cung(dang bieu thuc bien) sau khi da rut gon
	//ham doi ket qua thu duoc trong arruResult(mooxi ket qua gom iMinProd phan tu) 
	//thanh dang chuoi, ket qua luu trong arrstrResult
	void MakeStrResult();
public:
	CTabReduce(bool bSum= true,bool bLayer1_Not12= true);
	~CTabReduce();
	//toi gian bieu thuc logic
	void Reduce();
	//ham tra ve so ket qua
	int GetCountResult();
	//ham tra ve ket qua dang chuoi
	CString GetResult(int i);

	//ham tra ve tong so dau vao ung voi ket qua rut gon duoc
	//o tang 1 hoac tang 2 tuy vao dang bieu thuc rut gon la
	//tong chuan hay tich chuan
	int GetCaCb();

#ifdef _DEBUG
	//hien cac ket qua rut gon duoc
	void ShowResult();
#endif
};
#endif
