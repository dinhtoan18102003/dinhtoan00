#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

struct BenhNhan {
	int ma;
	string name;
	int tuoi;
	string gioiTinh;
	string benhAn;
	string diaChi;
};

struct Node
{
	BenhNhan data;
	Node *next;
};
struct List
{
	Node *first;
	Node *last;
}L;

void Init(List &L)
{
	L.first = L.last = NULL;
}

Node *getNode(BenhNhan x)
{
	Node *p;
	p = new Node;
	if (p==NULL)
		return NULL;
	p->data = x;
	p->next = NULL;
	return p;
}

//Chen 1 node vao dau danh sach
void addFirst(List &L, Node* new_node)
{
	if (L.first == NULL)  // DS rong
	{
		L.first = L.last = new_node;	
	}
	else 
	{	
		new_node->next = L.first;  
		L.first = new_node; 	 
	}
}

//Chen giua: Chen 1 node vao sau node q trong danh sach
void addAfter(List &L, Node *q, Node* new_node)
{
	if (q!=NULL)  
	{
		new_node->next = q->next;
		q->next = new_node; 	
		if(q == L.last)  	L.last = new_node; 
	}
}

//chen 1 node vao cuoi danh sach
void addLast(List &L, Node* new_node)
{
    if (L.first==NULL)   //Danh sach rong
	{
        L.first = L.last = new_node;
    }
    else {
        L.last->next = new_node; 
        L.last = new_node; 
    }
}

//them 1 benh nhan x vao dau danh sach
void insertFirst(List &L,BenhNhan x)
{
	Node* new_node = getNode(x);
	if (new_node == NULL)
		return;
	addFirst(L,new_node);
}

//them 1 benh nhan x vao giua danh sach 
void insertAfter(List &L, Node *q, BenhNhan x)
{
	Node* new_node = getNode(x);
	if (new_node == NULL)
		return;
	addAfter(L,q,new_node);
}

//them 1 benh nhan x vao cuoi danh sach
void insertLast(List &L,BenhNhan x)
{
	Node* new_node = getNode(x);
	if (new_node == NULL)
		return;
	addLast(L,new_node);
}

//------------------------------------------
int nhap_one(BenhNhan &x)
{	
	cin.ignore(); 
	cout << "Ma benh nhan: ";
	cin >> x.ma; 
	if(x.ma==0)
		return 0;
	cout << "Ho ten: ";
	cin >> x.name;
	cout << "Tuoi: ";
	cin >> x.tuoi;
	cout << "Gioi Tinh: ";
	cin >> x.gioiTinh;
	cout << "Benh an: ";
	cin >> x.benhAn;
	cout << "Dia chi: ";
	cin >> x.diaChi; 
	return 1;
}

void xuat_one(BenhNhan x) {

	cout << x.ma << ",     " << x.name << ",      " << x.tuoi << ",      " << x.gioiTinh << ",      " << x.benhAn << ",      " << x.diaChi <<"\n"; 
}

void nhapDs(List &L)
{
	BenhNhan x;
	cout << "Bat dau nhap danh sach benh nhan.Nhap ma = 0 de ket thuc: \n";
	while(nhap_one(x))
	{
		cout <<"----------------\n";
		insertLast(L,x);
		cout << "\n";
	}
}

void tieuDe()
{
	cout << "------------------------------------------------\n";
	cout <<"Ma" << ", "  << "Ho Ten" << ",  " << "Tuoi" << ",  " << "Gioi tinh" << ",  " << "Benh an" << ", " << "Dia chi" << endl;
	cout << "------------------------------------------------\n";
}

void xuatDs(List L)
{
	Node *p=L.first;
	while (p != NULL)
	{
		xuat_one(p->data);
		p=p->next;
	}
}

//------------------------------------------
//Nhap tu ban phim vi tri muon them vao giua 
int themGiua(List &L)
{
	int maChen;
	BenhNhan x; 
	cout << "Tien hanh chen them 1 benh nhan vao sau 1 node(BenhNhan) giua danh sach:\n"; 
	nhap_one(x);
	cout << "Chen vao sau benh nhan co ma la: ";
	cin >> maChen;
	
	Node *p = L.first;
	while(p != NULL)
	{
		if(p->data.ma == maChen)
		{
			insertAfter(L,p,x); 
			return 1; 
		} 
		p=p->next; 
	} 
	return -1; 
} 

//xoa 1 phan tu dau danh sach 
void removeFirst(List &L)
{
	Node *p=L.first;
	L.first = p->next;
	if (p==L.last) L.last = NULL;
	delete p;
}

//Xoa 1 phan tu sau node q(Giua danh sach) 
int removeAfter(List &L, Node *q)
{
	if (q!=NULL && q->next!=NULL)
	{
		Node *p = q->next;
		q->next = p->next;
		if (p == L.last) 
			L.last = q;
		delete p;
		return 1;
	}
	else
		return 0;
}

//xoa 1 phan tu cuoi danh sach 
int removeLast(List &L)
{
	Node *p, *pxoa;
	p = L.first; 
	if(p == NULL) return 0; //Ds rong
	if(p->next == NULL) //Ds 1 phan tu
	 {
		p = L.first;
		L.first = L.last = NULL;
		delete p; 
		return 1;
	 }
	while(p->next->next != NULL) //Nhieu hon 1 pt 
	{
		 p = p->next; 
	}
	{
	Node *pxoa = p->next;
	p->next=pxoa->next;
	L.last=p;
	delete pxoa;
	}
}

Node* timXoa(List L, int a)
{
	Node *p=L.first;
	while (p!=L.last && p->next->data.ma != a)
	{
		p=p->next;
	}
	if (p!=L.last)
		return p;
	return NULL;
}
void xoaBenhNhan(List &L,int b)
{
	if (L.first->data.ma == b)
	{
		removeFirst(L);
		cout << "Xoa thanh cong!! Danh sach cap nhat sau khi xoa:\n";
		tieuDe(); 
		xuatDs(L);
	}
	else
	{
		Node *p=timXoa(L,b);
		if (p==NULL)
		{
			cout << "Khong tim thay ma de xoa!!\n";
		}
		else
		{
			removeAfter(L,p);
			cout << "Xoa thanh cong!! Danh sach cap nhat sau khi xoa:\n";
			tieuDe(); 
			xuatDs(L);
		}
	}
}

void Swap1(BenhNhan &x,BenhNhan &y)
{
	BenhNhan temp = x;
	x = y;
	y = temp;
}
void sapXepTheoTuoi(List &L)
{
	for (Node *p=L.first ; p!=L.last ; p=p->next)
	{
		for(Node *q=p->next ; q!=NULL ; q=q->next)
		{
			if (p->data.tuoi > q->data.tuoi)
				{
					Swap1(p->data,q->data);
				}
		}
	}
}

void Menu()
{
	cout << "\n\tCHUONG TRINH QUAN LY BENH NHAN                   *\n";
	cout << "\t1. Nhap danh sach benh nhan                      *\n";
	cout << "\t2. Xuat danh sach benh nhan(dua vao chen cuoi)   *\n";
	cout << "\t3. Chen them benh nhan vao dau danh sach         *\n";
	cout << "\t4. Chen them benh nhan vao cuoi danh sach        *\n";
	cout << "\t5. Chen them benh nhan vao giua danh sach        *\n";
	cout << "\t6. Xoa phan tu o dau                             *\n";
	cout << "\t7. Xoa phan tu o cuoi                            *\n";
	cout << "\t8. Xoa phan tu bat ky                            *\n";
	cout << "\t9. Sap xep danh sach tang dan theo tuoi          *\n";
	cout << "\t0. Thoat                                         *\n";
	cout << "\t-------------------------------------            *\n";
}

int main()
{
	BenhNhan x;
	Init(L);
	int chon;
	do
	{
		Menu();
		cout << "Nhap lua chon: ";
		cin >> chon;
		switch(chon)
		{
			case 1:
			{
				nhapDs(L);
				cout << "Da nhap xong danh sach!!\n"; 
				break;
			}
			case 2:
			{
				cout << "Danh sach vua nhap:\n"; 
				tieuDe(); 
				xuatDs(L);
				break;
			}
			case 3:
			{
				cout << "Tien hanh chen them 1 benh nhan vao dau danh sach:\n"; 
				nhap_one(x);
				insertFirst(L,x);
				cout << "Chen Thanh cong!! Danh sach sau khi chen:\n"; 
				tieuDe(); 
				xuatDs(L);
				break;
			}
			case 4:
			{
				cout << "Tien hanh chen them 1 benh nhan vao cuoi danh sach:\n"; 
				nhap_one(x);
				insertLast(L,x);
				cout << "Chen Thanh cong!! Danh sach sau khi chen:\n";
				tieuDe(); 
				xuatDs(L);
				break;
			}
			
			case 5:
			{
				if(themGiua(L)==1)
				{
					cout << "Chen Thanh cong!! Danh sach sau khi chen:\n";
					tieuDe(); 
					xuatDs(L);
				} 
				else
					printf("Them khong thanh cong!!\n"); 
				break;
			}
			
			case 6:
				removeFirst(L);
				cout << "Danh sach sau khi thuc hien xoa dau la:\n";
				tieuDe(); 
				xuatDs(L);
				break;
			case 7:
				removeLast(L);
				cout << "Danh sach sau khi thuc hien xoa cuoi la:\n";
				tieuDe(); 
				xuatDs(L);
				break;
			case 8:
			{
				int maXoa;
				cout << "Nhap ma can xoa: ";
				cin >> maXoa; 
				xoaBenhNhan(L,maXoa);
				break;
			}
			case 9:
				sapXepTheoTuoi(L);
				cout <<"Sap xep thanh cong!! Danh sach sau khi sap xep: \n";
				tieuDe(); 
				xuatDs(L);
				break;
		}
	}while(chon!=0);
	
}
