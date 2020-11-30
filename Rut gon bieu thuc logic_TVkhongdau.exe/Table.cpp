#include "Table.h"
#include <stdlib.h>
#ifdef _DEBUG
#include <iostream.h>
#endif

/*******************************************************************************
	Cac phuong thuc cua SRow
********************************************************************************/
//Ham gan gia tri(cap phat vung nho) cho bien dang SRow
void SRow::Assign(CString str, bool used){
	int len= str.GetLength();
	//strBin= new CHAR(len+1); dung the nay bi loi- co the khong cho dung dong thoi new va malloc
	strBin= (PCHAR)malloc(len+1);//cap phat vung nho cho thanh phan strBin
	strBin[len]= 0;//chuoi co phan tu cuoi cung la NULL
	strcpy(strBin,(LPCSTR)str);//copy chuoi vao SRow
	bUsed= used;
}



/*******************************************************************************
  Cac ham chuyen so thanh chuoi nhi phan va Dem so cac chu so 1 trong khai trien
  nhi phan
********************************************************************************/
//CntChar la so ki tu phai co, sau nay thi day chinh la so bien, va string co dang 0100(vi du so bien la 4)
CString ConvertNum(UINT num,int CntChar){
	CString strdigit,strbin;	
	while(CntChar>0){//lam CntChar lan		
		strdigit.Format("%d",num%2);//lay chu so nhi phan cuoi cung 		
		strbin= strdigit+strbin;
		num= num/2;
		CntChar--;
	}
	return strbin;
}

//dem so ky tu '1' trong chuoi nhi phan nhu _00101_
UINT Count1(CString rowbin){
	UINT count= 0;
	for(int i=0; i<rowbin.GetLength(); i++)
		if(rowbin[i]=='1') count++;
	return count;
}

//ket hop 2 chuoi nhi phan
CString CombineStr(CString rowbin1, CString rowbin2){
	int i;
	int len;
	CString result;
	//neu 2 chuoi nhi phan co do dai khac nhau thi khong the thuc hien duoc, tra ve chuoi rong
	if((len= rowbin1.GetLength())!= rowbin2.GetLength()) return "";
	//duyet qua cac ky tu trong 2 chuoi, neu xay ra truong hop 1 vi tri ma trong 2 chuoi co ky tu khac
	//nhau va co ky tu '_' thi khong the ket hop 2 chuoi nay, vi ky tu khac nhau thi chi co the la 0 va 1
	//thi moi co the ket hop
	for(i=0; i<len; i++){
		if(rowbin1.GetAt(i)!= rowbin2.GetAt(i)){
			if((rowbin1.GetAt(i)== '_')||(rowbin2.GetAt(i)== '_')) return "";
			break;
		}
	}
	//neu xuong dau thi vi tri i chinh la vi tri dau tien tim ra 2 ky tu khac nhau trong hai chuoi
	//va 2 ky tu do la (0 va 1) hoac (1 va 0)
	//kiem tra cac ky tu con lai cua 2 chuoi, neu giong nhau hoan toan thi moi co the ket hop
	//hai chuoi nay duoc va luc do vi tri thay boi ky tu '_'
	if(i< len){
		for(int j=i+1; j< len; j++)
			if(rowbin1.GetAt(j)!= rowbin2.GetAt(j)) return "";
		result= rowbin1;
		result.SetAt(i,'_');
		return result;
	}else return "";
}



/*******************************************************************************
	Cac ham cua lop SPortion
********************************************************************************/
//cap phat vung nho cho block hang trong SPortion
//ham nay con duoc goi o vi tri khac ngoai cac ham khoi tao
//vi khi cap phat bien nho dang SPortion bang malloc thi ham khoi tao khong duoc goi
//tu dong nen ta phai tu goi Init(?,?)
void SPortion::Init(int CntDim,int block){
	iDim= CntDim;
	iCntRow= 0;
	if(block<=0) block= 1; iBlock= block;
	pRow=(SRow*)malloc(block* sizeof(SRow)); iCntMemory= block;	
}
SPortion::SPortion(int CntDim,int block){
	Init(CntDim, block);
}


void SPortion::AddRow(CString rowbin,bool used){
	iCntRow++; //tang them so hang
	if(iCntRow> iCntMemory){ //neu thieu vung nho cap phat them 1 khoi nho
		iCntMemory+= iBlock;
		pRow= (SRow*)realloc(pRow,iCntMemory*sizeof(SRow));
	}
	pRow[iCntRow-1].Assign(rowbin,used);//gan gia tri cho hang moi
}
bool SPortion::AddNumber(UINT num){
	AddRow(ConvertNum(num,iDim));//chuyen so thanh chuoi nhi phan roi them vao
	return true;
}

//duyet qua tat cac row trong SPortion por roi thuc hien copy bang ham AddRow(ban than
//trong ham nay co cap phat vung nho
void SPortion::Copy(const SPortion & por){	 	
	iCnt1= por.iCnt1;
	for(int i= 0; i< por.iCntRow; i++)
		AddRow(por.pRow[i].strBin,por.pRow[i].bUsed);	
}
SPortion SPortion::operator=(const SPortion & por){	
	iDim= por.iDim;
	Copy(por);
	return *this;
}
SPortion::SPortion(const SPortion & por){
	Init(por.iDim,por.iBlock);// can goi ham nay de cap phat vung nho ban dau
	Copy(por);
}


//Chi goi ham nay khi biet 2 Portion co the ket hop duoc, tuc ham 2 Portion co Cnt1 hon kem nhau 1 don vi
//doi tuong goi phuong thuc nay se duoc gan cac bien can thiet chi tru iBlock se van giu nguyen cho doi tuong
bool SPortion::Combine(SPortion & por1, SPortion & por2){	
	CString strCom;
	if(por1.iDim!= por2.iDim) return false;	//neu so bien cua 2 Portion khac nhau thi khong the ket hop duoc
	for(int i=0; i< por1.iCntRow; i++)//duyet qua tat cac cac hang trong por1
		for(int j= 0; j< por2.iCntRow; j++){//ung voi moi hang cua por1 duyet qua tat ca cac hang trong por2
			strCom= CombineStr(por1.pRow[i].strBin,por2.pRow[j].strBin);//kiem tra xem co ket hop duoc khong
			if(strCom!=""){//neu ket hop duoc
				por1.pRow[i].bUsed= true;//thi 2 hang i,j tuong ung trong por1 va por2 coi nhu da su dung va day se ko la tich cuc tieu
				por2.pRow[j].bUsed= true;				
				//kiem tra xem da co hang nay hay chua vi van co truong hop cac hang khac nhau nhung ket hop lai thi cho 1 ket qua
				for(int k= 0; k< iCntRow; k++)
					if(strcmp(strCom,pRow[k].strBin)==0) goto notadd; //(LPCSTR)
				//neu chua co hang nay thi them vao
				AddRow(strCom);			
			}
notadd: ;
		}	
	if(iCntRow!= 0){//neu ket hop duoc thi cap nhat cac thanh phan khac cua SPortion
		iDim= por1.iDim;
		iCnt1= por1.iCnt1>por2.iCnt1?por2.iCnt1:por1.iCnt1;
		return true;
	}	
	return false;
}

//chinh la ham Combine
SPortion operator+(SPortion & por1, SPortion & por2){
	SPortion porResult(por1.iDim,por1.iBlock);
	porResult.Combine(por1,por2);
	return porResult;
}


SRow & SPortion::operator[](int i){
	return pRow[i]; 
}

SPortion::~SPortion(){
	//do trong moi pRow[?] co thanh phan con tro nen can giai phong truoc
	for(int i=0; i<iCntRow; i++){
		//delete [] pRow[i].strBin;
		free(pRow[i].strBin);
	}
	free(pRow);
}

#ifdef _DEBUG
void SPortion::ShowRow(){
	cout<<"Ham ShowRow"<<endl;
	cout<<endl<<"Memory= "<<iCntMemory<<endl;
	for(int i= 0; i< iCntRow; i++)
		cout<< pRow[i].strBin<<" "<<pRow[i].bUsed<<endl;
	cout<<"Het ham ShowRow";
}
#endif


/*******************************************************************************
	Cac ham cua lop Table
********************************************************************************/
//so Portion can duoc cung cap truoc trong doi so cntPor
CTable::CTable(int cntDim,int cntPor, int block){
	iCntPor= cntPor;
	pPortion= (SPortion*)malloc(iCntPor*sizeof(SPortion));//cap phat co dinh so Portion cua bang(sau nay khong co cap phat lai)
	for(int i=0; i<iCntPor; i++){
		pPortion[i].Init(cntDim,block);//cap phat dang nay thi phai tu goi ham khoi tao
		pPortion[i].iCnt1= i;//trong bang chi co duy nhat '1 Portion co so ki tu 1 trong chuoi nhi phan la i'
		//chu y trong cac thanh phan cua lop SPortion thi iCnt1 khong duoc su dung, no chi duoc
		//su dung ke tu day, vi trong Table can phan biet cac SPortion thong qua iCnt1
	}
}
CTable::~CTable(){
	for(int i= 0; i< iCntPor; i++)
		pPortion[i].~SPortion();
	free(pPortion);
}
//trong moi pPortion da chua so bien logic iDim vi vay trong CTable khong can co bien de luu
//so bien logic lai ma lay so bien thong qua ham nay
int CTable::GetCntDim(){
	return pPortion[0].iDim;
}
//tuong tu voi iBlock
int CTable::GetBlock(){
	return pPortion[0].iBlock;
}
//them 1 so vao bang, no se them vao Portion nao tuy vao so chu so 1 trong so do
void CTable::AddNumber(int num){
	CString strNum= ConvertNum(num,GetCntDim());	
	pPortion[Count1(strNum)].AddRow(strNum);
}
//gan por cho 1 vi tri trong mang pPortion
void CTable::AddPortion(const SPortion & por){
	pPortion[por.iCnt1]= por;
}

bool CTable::Conversion(CTable * & table){	
	if(iCntPor<=1) return false;
	SPortion por(GetCntDim(),GetBlock());
	//neu table != NULL thi no se giai phong vung nho cua table truoc sau do cap phat vung nho de chua Table sau chuyen doi
	if(table!= NULL) delete table;
	//so Portion cua bang sau khi ket hop khong vuot qua iCntPor-1
	table= new CTable(GetCntDim(),iCntPor-1,GetBlock());	
	for(int i=0; i< iCntPor-1; i++){
		por.iCntRow= 0;//xoa por, day la bien tam de luu cac Portion tao ra khi ket hop
		//neu 2 portion ket hop duoc thi them vao bang
		if(por.Combine(pPortion[i],pPortion[i+1])) table->AddPortion(por);
	}
	return true;
}

int CTable::GetCntRow(){
	int ret= 0;
	for(int i= 0; i<iCntPor; i++)
		ret+= pPortion[i].iCntRow;
	return ret;
}

//ham nay chi xu ly dung khi thong so dua vao la hop le
SRow & CTable::operator[](int i){
	int pos= 0; 
	for(int j=0; j<iCntPor; j++){		
		if(pos+pPortion[j].iCntRow<= i) pos+=pPortion[j].iCntRow;
		else break;
	}	
	//j chua Portion, con i-pos chua chi so cua cot trong Portion
	return pPortion[j].pRow[i-pos];
}
#ifdef _DEBUG

//ham hien tat ca cac hang trong bang
void CTable::ShowTable(){
	char c;
	for(int i=0; i< iCntPor; i++){
		cout<<"\nPortion" <<i;
		if(pPortion[i].iCntRow!=0) pPortion[i].ShowRow();
		cin>>c;
	}
}
#endif
