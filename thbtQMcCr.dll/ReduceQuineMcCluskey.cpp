#include "StdAfx.h"
#include "ReduceQuineMcCluskey.h"
#include <math.h>
#include "Table.h"
#ifdef _DEBUG
#include <iostream.h>
#endif
//#include <afxwin.h>
CTabReduce::CTabReduce(bool bSum,bool bLayer1_Not12):CInputLogic(bSum){
	pCol= NULL;
	piUsed= NULL;
	bLayer1= bLayer1_Not12;//tieu chuan rut gon cho bieu thuc
}

CTabReduce::~CTabReduce(){
	if(pCol!= NULL) delete[] pCol;
	if(piUsed!= NULL) delete[] piUsed;
	arrstrProdRedu.RemoveAll();
	arruResult.RemoveAll();
	arrstrResult.RemoveAll();
}


//ham dien day cac mang chua tich chua cuc tieu arrstrProdRedu
void CTabReduce::FillProdRedu(){
	int i;
	bool con= true;
	CTable *tab1,*tab2= NULL;
	tab1= new CTable(GetNumDim(),GetNumDim()+1);//vi du neu co 4 bien thi so  Portion toi da la 4+1
	
	//khoi tao bang dau tien
	for(i=0; i< GetSizeIsImp(); i++)
		tab1->AddNumber(arrIsImp[i]);
	for(i=0; i< GetSizeIsX(); i++)
		tab1->AddNumber(arrIsX[i]);

	while(con){
		tab1->Conversion(tab2);//ham nay se xoa vung nho do tab2 tro toi		
		//tab2->ShowTable();
		//viec thuc hien convert se gan used cho bang tab1, neu co 1 tich cuc tieu nao do co gia
		//la false thi do la tich cuc
		for(i=0; i< tab1->GetCntRow(); i++)//duyet qua cac hang trong tab1 de tim tich cuc tieu con lai
			if(!(*tab1)[i].bUsed) arrstrProdRedu.Add((*tab1)[i].strBin);		
		//neu sau khi chuyen doi ma tab2 co so hang la 0 thi qua trinh chuyen doi ket thuc

		if(tab2==NULL || tab2->GetCntRow()==0) con= false;
		delete tab1;
		tab1= tab2; tab2= NULL;		
	}
	delete tab1;
	//for(i=0; i< arrstrProdRedu.GetSize(); i++)
	//	cout<<endl<<(char)('A'+i)<<" = "<<arrstrProdRedu[i];
}


bool CTabReduce::Overlay(int num,CString rowbin){
	CString strNum= ConvertNum(num,GetNumDim());
	for(int i=0; i< rowbin.GetLength(); i++){
		if((rowbin.GetAt(i)!= strNum.GetAt(i)) && (rowbin.GetAt(i)!= '_'))
			 return false;
	}
	return true;
}


//truoc khi goi ham nay phai goi hang FillProdRedu de tao arrstrProdRedu
//dang chinh la ham tao bang rut gon sau khi da tim ra cac tich cuc tieu trong pp QuineMcCluskey
void CTabReduce::FillColUsed(){
	int iCol= GetSizeIsImp();
	pCol= new CUIntArray[iCol];
	piUsed= new int[iCol];
	int i,j;
	for(i=0; i<iCol; i++){
		for(j=0; j< arrstrProdRedu.GetSize(); j++){
			//j la chi so trong mang arrstrProdReduce dac trung cho tich cuc tieu o phan tu tuong ung cua mang
			if(Overlay(arrIsImp[i],arrstrProdRedu[j])) pCol[i].Add(j);
			//pCol[i].Add(j): cot i luu j neu nhu so trong arrIsImp[i] so khop voi tich cuc tieu trong arrstrProdRedu[j]
		}
		piUsed[i]= 0; //bang 0 co nghia la dinh quan trong thu i chua bi xoa
					  //gia tri nay am thi co nghia la dinh quan da bi xoa
	}
	/*
	for(i= 0; i<iCol; i++){
		cout<<endl<<"Dong "<<(int)arrIsImp[i]<<" bao gom: ";
		//cout<<pCol[i].GetSize();
		for(j=0; j<pCol[i].GetSize(); j++){
			int l= pCol[i].GetAt(j);
			//cout<< arrstrProdRedu[l]<<" ";
			cout<<(char)(l+'A')<<" ";
		}
	}
	*/

}



//mang ovl chua cac chi so cua mang arrstrResult (mang arruResult cung chua cac chi so nhu vay,nhung ung voi nhieu ket qua)
//ham nay tra ve so dau vao o tang 1 ung voi ovl
//vi du neu ovl la 0,1 chang han thi vi du 2 chuoi tuong ung la _001_ va 0_1__ thi ket qua
//tra ve la 3+2= 5
int CTabReduce::CountLayer1(CUIntArray & ovl){
	int nRet= 0;
	for(int i=0; i< ovl.GetSize(); i++){
		nRet+= GetCount01(arrstrProdRedu[ovl[i]]);
	}
	return nRet;
}

//ham nay con tinh them so dau vao o tang 2
//voi vi du nhu tren thi gia tri tra lai cua ham nay la 5+2= 7
int CTabReduce::CountLayer12(CUIntArray & ovl){
	return CountLayer1(ovl)+ovl.GetSize();
}

//ham nham tranh tinh huong 2 ket qua giong nhau cung duoc dua vao
//mang arruResult, su dung trong Recursive
bool CTabReduce::Exist(const CUIntArray & ovl){
	int iLow, iUp;
	CString _1Result;
	bool bEqual;
	//arrCntForResult chua cac chi so cuoi cua moi doan mang ket qua trong arruResult
	for(int i= 0; i< arrCntForResult.GetSize(); i++){		
		if(i==0){
			iLow= 0; 
			iUp= arrCntForResult[0];
		}else{
			iLow= arrCntForResult[i-1]+1;
			iUp= arrCntForResult[i];
		}
		//iLow,iUp la chi so dau va cuoi cua 1 ket qua luu trong mang arruResult
		
		//duyet qua 1 ket qua		
		for(int j= iLow; j<= iUp; j++){
			bEqual= false;
			//duyet qua tung gia tri trong ovl xem co gia tri nao bang voi phan tu arruResult[j] khong
			for(int k= 0; k< ovl.GetSize(); k++){
				if(ovl.GetAt(k)== arruResult.GetAt(j)){bEqual= true; break;}
				//neu co bang thi dat bEqual= true va chuyen sang kiem tra voi phan tu tiep theo trong mang arruResult
			}
			//neu khong co phan tu nao trong mang arruResult bang voi phan tu arruResult[j]
			//thi tuc la 2 mang ovl va arruResult[iLow->iUp] khong bang nhau
			//va luc do bEqual van bang false
			if(!bEqual) break;//thoat viec kiem tra voi phan mang iLow->iUp, de kiem tra tiep mang tiep theo
		}//cuoi cua duyet qua 1 ket qua( tu iLow->iUp)
		
		//sau khi kiem tra xong 1 doan mang arruResult[iLow->iUp]
		//neu bEqual== true thi co nghia la ovl= arruResult[iLow->iUp]
		//ta tra lai gia tri true cho ham
		if(bEqual) return true;

		//neu khong thi qua trinh thuc hien den cho nay
		//va se chuyen sang so sanh doan mang tiep theo voi ovl

	}//cuoi cua vong lap qua tat ca cac phan tu cua arruResult
	
	//neu thuc hien den day thi co nghia la ovl khong so khop voi bat cu doan mang nao
	return false;
}

//phai co dong khoi tao iMinProd= GetSizeIsImp()+1 truoc khi goi ham nay de dam bao luu duoc gia tri moi vao
//ovl la bien chua ket qua phai dung chung cho moi lan goi ham de qui
//goi ham nay thi dat col= 0
void CTabReduce::Recursive(int col,CUIntArray & ovl){
	int i,j;
	//duyet tat ca cac phan tu o cot col
	for(i=0; i<pCol[col].GetSize(); i++){///////
		//them phan tu o cot col vao phu? ovl
		ovl.Add(pCol[col][i]);

		//cout<<"col= "<<(int)arrIsImp[col]<<"them "<<(char)(pCol[col][i]+'A')<<endl;
		

		//xoa cot nay va cac cot lien quan
		for(j= 0; j< GetSizeIsImp(); j++){//duyet qua tat ca cac cot
			//arrIsImp[j] la so thap phan ung voi cot j
			//pCol[col] chua cac phan tu cua cot col, moi phan tu la chi so trong mang arrstrProdRedu de chi tich cuc tieu nao
			//pCol[col][i] chua chi so cua arrstrProdRedu ung voi cot col, va lan lap i
			if(Overlay(arrIsImp[j],arrstrProdRedu[pCol[col][i]])){
				piUsed[j]--;//xoa dinh quan trong thu j thi giam gia tri di 1
				//cout<<"xoa= "<<(int)arrIsImp[j]<<endl;
			}
		}
		
		int tmpCol= col+1;//tim cot tiep theo chua bi loai bo
		if(tmpCol> GetSizeIsImp()-1) goto lblresult;//da la cot cuoi cung
		while(piUsed[tmpCol]<0){//truong hop cot dinh quan trong tmpCol dang bi xoa thi tim tiep cot tiep theo
			tmpCol++; 
			if(tmpCol> GetSizeIsImp()-1) goto lblresult;//da la cot cuoi cung (ko co cot tiep theo)
		}
		
		
		//da tim duoc cot tiep theo
		Recursive(tmpCol,ovl);	goto lblend;

lblresult://ghi nhan ket qua va dat tro lai cac cot bi xoa (ben phai) o trong ham de qui nay		

		//cout<<"tmpCol= "<<tmpCol<<";";
		//cout<<"ovl= ";
		//for(j= 0; j< ovl.GetSize(); j++){
		//	cout<<(char)(ovl[j]+'A')<<" ";
		//}
		//cout<<endl;
		
		//neu so phan tu trong phu moi bang phu cuc tieu luu trong arruResult
		//(doan ma nay chinh la dieu kien lay cua bieu thuc rut gon)
		
		
		/*
		//day la doan ma cu ung voi viec chi xet den so dau vao o tang 2
		//luc do bien iMinProd duoc su dung con mang arrCntForResult khong can su dung
		if(ovl.GetSize()== iMinProd){arruResult.Append(ovl);}//them vao do co nhieu phu cuc tieu cung so tich cuc tieu
		if(ovl.GetSize()< iMinProd){arruResult.Copy(ovl); iMinProd= ovl.GetSize();}//phu cuc tieu trong ovl it tich cuc tieu hon
		*/

	
		int iTempLayer;
		if(bLayer1){//truong hop lay cac gia tri rut gon co tong dau vao o tang mot nho nhat
			iTempLayer= CountLayer1(ovl);			
		}else{//truong hop tong so dau vao o tang 1 va tang 2 nho nhat
			iTempLayer= CountLayer12(ovl);
		}
		if(iTempLayer== iLayer){//truong hop ket qua trong ovl co do gon bang ket qua luu trong arruResult
			//can kiem tra xem ovl co trung voi 1 ket qua nao do khong
			//truoc khi them vao vi co the co 2 ket qua trung nhau trong de qui
			//ma chi khac nhau ve thu tu
			if(!Exist(ovl)){ //goi ham kiem tra, neu chua ton tai ket qua trong ovl thi moi them vao

				arruResult.Append(ovl);
				arrCntForResult.Add(arruResult.GetSize()-1);
			}
			//else{
			//	MessageBox(AfxGetMainWnd()->m_hWnd,"Da ton tai","on recursive",MB_OK);
			//}
		}
		if(iTempLayer< iLayer){//truong hop ket qua trong ovl co do gon hon cac ket qua luu trong arruResult
			arruResult.Copy(ovl);
			arrCntForResult.SetSize(1);
			arrCntForResult.SetAt(0,ovl.GetSize()-1);
			iLayer= iTempLayer;
		}
		//^|^(phia tren la) doan chuong trinh loai bo nhung rut gon khong tot
	

lblend:

		//dat lai cac cot da bi xoa (CHU Y: chi dat lai cac cot ben phai)
		//khong sua lai roi: phai dat lai tat ca
		//for(j= col; j<
		for(j= 0; j< GetSizeIsImp(); j++){			
			if(Overlay(arrIsImp[j],arrstrProdRedu[pCol[col][i]])){
				piUsed[j]++;//dat lai thi tang gia tri len 1
							//den khi gia tri nay bang 0, thi coi nhu khong co viec lay tich cuc tieu nao xoa no
				//cout<<"Dat lai cot " <<(int)arrIsImp[j]<<endl;
			}
		}

		//loai ra phan tu them vao, chinh la phan tu cuoi cung
		//cout<<"Loai phan tu "<<(char)(ovl[ovl.GetSize()-1]+'A');
		//char a; //dung man hinh
		//cin>>a;
		ovl.RemoveAt(ovl.GetSize()-1);	
	}///////

}

void CTabReduce::MakeStrResult(){

/*
//trong truong hop chi tinh den so dau vao o tang 2 thi viet the nay
	CString _1Result="";	
	for(int i= 0; i<= arruResult.GetSize(); i++){
		if(i% iMinProd==0){//cu iMinProd phan tu la cac tich toi thieu trong 1 ket qua(1 phu toi thieu)
			if(_1Result!=""){arrstrResult.Add(_1Result); _1Result="";}
		}
		if(i== arruResult.GetSize()) return;
		if(_1Result!= ""){
			if(bSumStandard) _1Result+= "+"; //truoc khi them vao 1 tong moi thi them dau +
			else _1Result+=".";
		}
		_1Result+= Str2Exp(arrstrProdRedu[arruResult[i]]);
	}
*/


	//!arruResult bay gio dang chua cac chi so cua tat ca cac ket qua
	// cac chi so nay dung de truy nhap arrstrProdRedu
	
	//duyet qua tat ca cac chi so cuoi cac tich cuc tieu thu duoc
	int iLow, iUp;
	CString _1Result;
	for(int i= 0; i< arrCntForResult.GetSize(); i++){		
		if(i==0){
			iLow= 0; 
			iUp= arrCntForResult[0];
		}else{
			iLow= arrCntForResult[i-1]+1;
			iUp= arrCntForResult[i];
		}
		//xu ly 1 ket qua, arrstrProdRedu[j] chua 1 tich (hay 1tong) cuc tieu
		_1Result= "";
		for(int j= iLow; j<= iUp; j++){
			if(_1Result!= ""){
				if(bSumStandard) _1Result+= "+"; //truoc khi them vao 1 tong moi thi them dau +
				else _1Result+=".";
			}
			_1Result+= Str2Exp(arrstrProdRedu[arruResult[j]]);
		}
		arrstrResult.Add(_1Result);//them ket qua
	}

}


//chu y thu tu goi ham phai la FillProdRedu->FillColUsed->Recursive->MakeStrResult
void CTabReduce::Reduce(){
	CUIntArray ovl;
	FillProdRedu();
	FillColUsed();
	//iMinProd= GetSizeIsImp()+1;
	//khoi tao moi tai day
	iLayer= (int)pow(2,GetNumDim())+GetNumDim();//day la gia tri lon hon gia tri lon nhat cua iLayer cho ca 2 truong hop
	Recursive(0,ovl);
	MakeStrResult();
	
	//cout<<"Ket qua"<<endl;
	//for(int i= 0; i< arrstrResult.GetSize(); i++){
	//	cout<<arrstrResult[i]<<endl;
	//}
	//cout<<"Het";
}
int CTabReduce::GetCountResult(){
	return arrstrResult.GetSize();
}
CString CTabReduce::GetResult(int i){
	ASSERT((i>=0) && (i< arrstrResult.GetSize()));
	//(neu chuoi ket qua tra ve la chuoi rong tuc la ket qua trong arruResult
	//chi co 1 chi so, va chi so do ung voi tong(tich) cuc tieu co dang ____
	//tuc la khong co chu so 0 hay 1 nao

	//ham MakeStrResult se dung hang nhi phan dang 0_1_ thi se chuyen tuong
	//ung thanh not(x)y hoac (not(x)+y) tuy vao dang tong chuan hay tich chuan
	//con voi ____ thi se chuyen thanh "" neu la dang tong chuan
	//								   "()" neu la tich chuan
	if(arrstrResult[i]=="") return "1"; 
	if(arrstrResult[i]=="()") return "0";	
	return arrstrResult[i];
}

int CTabReduce::GetCaCb(){
	return iLayer;
}
#ifdef _DEBUG
void CTabReduce::ShowResult(){
	/*
	cout<<endl<<"iMinProd= " <<iMinProd<<endl;
	for(int i= 0; i< arruResult.GetSize(); i++){
		if(i% iMinProd==0) cout<<endl;
		cout<< (char)('A'+arruResult[i])<<endl;
	}
	*/
}
#endif
