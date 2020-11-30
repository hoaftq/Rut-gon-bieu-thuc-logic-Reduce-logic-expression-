#include "InputLogic.h"
#ifdef _DEBUG
#include <iostream.h>
#endif
#include <afxcoll.h>
CInputLogic::CInputLogic(bool styleSum){
	iDim= 0;
	bSumStandard= styleSum; //gia tri cua bSumStandard co anh huong den ham Str2Exp
}
//ham nhan dau vao la 1 chuoi cac ten bien co ngan cach la separate
bool CInputLogic::SetNameDim(CString dimname,TCHAR separate){
	int	posPreSeparate= 0;//vi tri cua dau phan cach truoc
	int posSeparate= 0;//vi tri cua dau phan cach tiep theo
	while(true){
		posSeparate= dimname.Find(separate,posSeparate+1);
		if(posSeparate== -1) break;//khong tim thay dau phan cach tuc la doan cuoi la ten bien cuoi cung
		arrDimName.Add(dimname.Mid(posPreSeparate,posSeparate-posPreSeparate));//them 1 ten bien
		posPreSeparate= posSeparate+1;//vi tri ki tu dau cua 1 ten bien
	}
	arrDimName.Add(dimname.Mid(posPreSeparate));//them ten bien cuoi cung
	iDim= arrDimName.GetSize(); //cap nhat so bien cua ham logic
	return true;
}
//them 1 ten bien vao mang arrDimName chua ten cua cac bien
bool CInputLogic::AddNameDim(CString dimname){
	arrDimName.Add(dimname);
	iDim++;
	return true; 
}
//them 1 so thap phan la dinh quan trong vao mang arrIsImp
bool CInputLogic::AddIsImp(UINT isImp){
	arrIsImp.Add(isImp);
	return true;
}
//them 1 so thap phan la 1 dinh tuy chon vao mang arrIsX
bool CInputLogic::AddIsX(UINT isX){
	arrIsX.Add(isX);
	return true;
}
//tra ve so bien cua bieu thuc, tuy vao so ten bien them vao
INT CInputLogic::GetNumDim() const{
	return iDim;
}
//tra ve so cac dinh quan trong
INT CInputLogic::GetSizeIsImp() const{
	return arrIsImp.GetSize();
}
//tra ve so cac dinh khong quan trong
INT CInputLogic::GetSizeIsX() const{
	return arrIsX.GetSize();
}

CInputLogic::~CInputLogic(){
	arrDimName.RemoveAll();
	arrIsImp.RemoveAll();
	arrIsX.RemoveAll();
}

//rowbin co dang 1_00_ chang han
CString CInputLogic::Str2Exp(const CString & rowbin){
	CString ret;
	int i;
	if(bSumStandard){ //truong hop la tong chuan
		for(i=0; i<rowbin.GetLength(); i++){//duyet qua tat ca cac ky tu trng rowbin
			switch(rowbin[i]){
			case _T('1'): //neu ky tu la 1 thi them ten bien
				if(!ret.IsEmpty()) ret+=_T('.'); //neu khong la ky tu dau thi truoc khi them ten bien ta them dau va
				ret+=arrDimName[i]; break;
			case _T('0'): //neu ky tu la 0 thi them dang: not(ten bien)
				if(!ret.IsEmpty()) ret+=_T('.');//neu khong la ky tu dau thi truoc khi them not(ten bien) ta them dau va
				ret= ret+"not("+arrDimName[i]+")";
			}
		}
	}else{ //truong hop la tich chuan
		bool bNot1Term= false; //neu la true thi ket qua dang ...+...+... co khong it hon hai so hang
					//vi du neu ket qua la x+not(y) chang han thi bNot1Term== true, con neu la x chang han thi bNot1Term== false
		for(i=0; i<rowbin.GetLength(); i++){//duyet qua tat ca cac ky tu trng rowbin
			switch(rowbin[i]){
			case _T('1'): //neu ky tu la 1 thi them ten bien
				if(!ret.IsEmpty()){
					ret+=_T('+');//neu khong la ky tu dau thi truoc khi them ten bien ta them dau va
					bNot1Term= true;
				}
				ret= ret+_T("not(")+arrDimName[i]+_T(")"); break;				
			case _T('0'): //neu ky tu la 0 thi them dang: not(ten bien)
				if(!ret.IsEmpty()){
					ret+=_T('+');//neu khong la ky tu dau thi truoc khi them not(ten bien) ta them dau va
					bNot1Term= true;
				}
				ret+=arrDimName[i];
			}
		}
		if(bNot1Term) ret= _T("(")+ret+_T(")"); //neu chi co 1 so hang trong tong cuc tieu thi khong can dat dau ngoac don

	}
	return ret;
}

//ham dem so phan tu 0,1 trong 1 hang dang _001_1_
int CInputLogic::GetCount01(const CString & rowbin){
	int nRet= 0;
	for(int i=0; i<rowbin.GetLength(); i++){
		if(rowbin.GetAt(i)==_T('0') || rowbin.GetAt(i)==_T('1')) nRet++;
	}
	return nRet;
}

#if defined( _DEBUG)
void CInputLogic::ShowNameDim(){
	cout<< iDim<<endl;//hien so bien
	for(int i= 0; i< iDim; i++){//duyet qua va in tat ca cac ten bien trong arrDimName
		cout<<"|"<<arrDimName.GetAt(i)<<"|"<<endl;
	}
}
#endif