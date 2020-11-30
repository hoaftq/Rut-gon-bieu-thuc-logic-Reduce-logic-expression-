#ifndef TABLE_H
#define TABLE_H
#include <afxcoll.h>

/*
	mot hang trong bang rut gon theo phuong phan QuineMcCluskey

*/
struct SRow{
	//chuoi nhi phan chang han 0011,_011_0
	WCHAR * strBin;

	//hang nay da duoc su dung hay chua,dung khi ket hop 2 SPortion 
	//neu sau khi rut gon het ma la false thi co nghia hang nay chinh la 1 tich cuc tieu
	bool	bUsed;

	//ham gan gia tri cho bien SRow, phep gan thong thuong hoat dong khong dung
	//vi trong SRow co cac con tro
	void Assign(CString str, bool used= false);
};




/*
	cac ham chuyen doi toan cuc

*/
//ham chuyen 1 so ve dang chuoi nhi phan
CString ConvertNum(UINT num, int CntChar);
//ham dem so cac so 1 trong 1 hang	
UINT Count1(CString rowbin);
//ham ket hop 2 chuoi nhi phan, vi du _001_0 va _000_0 thanh _00__0
CString CombineStr(CString rowbin1, CString rowbin2);



/*
	bao gom cac hang co cung so chu so 1 trong bang rut gon theo 
	phuong phap QuineMcCluskey

*/
struct SPortion{
private:
	//so phan tu pRow da duoc cap phat, vi moi lan cap phat them block phan tu
	int iCntMemory;
	//chinh la ham khoi tao,no cap phat vung nho ban dau
	void Init(int CntDim, int block);
	//dung trong cac ham gan va ham sao chep
	void Copy(const SPortion & por);
public:
	int iDim;	//so bien cung chinh la do dai cua chuoi nhi phan trong moi hang
	
	int iCntRow;//so cac hang trong Portion	
	int iBlock; //do lon cho moi lan cap phat them
	SRow* pRow; //thong so cho moi hang
	
	int iCnt1;	//so cac so 1 trong Portion, cac Portion phan biet nhau o dac diem nay
	
	SPortion(int CntDim, int block= 4); //cac doi so phai >=1
	~SPortion();
	
	//them 1 chuoi nhi phan hay la 1 hang vao SPortion
	void AddRow(CString rowbin, bool used= false);
	//them 1 so vao SPortion,dung de khoi tao cac Portion o bang a (sau do ket hop cac Portion nay de duoc cac Portion moi)
	bool AddNumber(UINT num);
	
	//su dung ham copy,(chu y theo mac dinh luc nao thi su dung ham sao chep, luu nao thi su dung ham=)
	SPortion operator=(const SPortion & por);	
	SPortion(const SPortion & por);
	
	//ket hop 2 Portion thanh 1 Portion moi,phep nay dung de bien doi bang a-> bang b, v.v...
	bool Combine(SPortion & por1, SPortion & por2);//Ham gop 2 Portion thanh 1 Portion
	friend SPortion operator+(SPortion & por1,SPortion & por2);

	//lay den 1 hang trong Portion
	SRow & operator[](int i);

	friend class CTable;

#ifdef _DEBUG
	//hien tat ca cac hang trong Portion
	void ShowRow();
#endif
};


/*
	mot bang trong phuong phap rut gon theo QuineMcCluskey,bao gom cac Portion co so cac
	chu so 1 khac nhau

*/
class CTable{
	//bang gom cac Portion
	SPortion * pPortion;	
	//so Portion trong bang
	int iCntPor;
	//them 1 Portion vao bang
	void AddPortion(const SPortion & por);
public:
	//cntDim: so bien cua ham logic, cntPor: so Portion(phai xac dinh truoc),
	//block chi dung de truyen cho cac pPortion[?], con so Portion duoc cap phat san voi
	//so Portion la cntPor
	CTable(int cntDim,int cntPor, int block= 4);//Cac doi so phai >=1
	~CTable();

	//lay so bien cua ham logic
	int GetCntDim();
	//lay pPortion[?]->iBlock
	int GetBlock();

	//them 1 so vao bang, no se tinh toan de dua vao Portion hop ly
	void AddNumber(int num);

	//thuc hien bien doi bang de thu duoc bang moi
	//CHU Y:khi khai bao 1 bien dang con tro thi phai khoi gan gia tri dau la NULL
	bool Conversion(CTable * & table);
	
	//tra ve so hang trong Table
	int GetCntRow();

	//tra ve hang thu i trong Table
	SRow & operator[](int i);

#ifdef _DEBUG
	//hien tat ca cac hang trong bang
	void ShowTable();
#endif
};
#endif