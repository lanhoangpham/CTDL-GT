#include<iostream>
#include<string.h>
#include<string>
#include<fstream>
using namespace std;

void strcpy_s(char* name1, int n, char* nam2){
    for ( int i = 0; i < n; i ++){
        name1[i] = nam2[i];
    }
}
template <class T> T* truyCap (T* , int );
template <class T, class V> int demGiaTri(T* );

struct NodeGiangVien;
struct NodeChuyenMon;
struct NodeKhoaVien;
struct NodeTruong;

struct NodeGiangVien{
    char name[20];
    int id;
    int data;// so luong sach xuat ban
    char mail[30];
    NodeGiangVien* right;
    NodeChuyenMon* father;
};
struct NodeChuyenMon{
    char name[40];
    NodeChuyenMon* right;
    NodeGiangVien* left;
    NodeKhoaVien* father;
};
struct NodeKhoaVien{
    char name[40];
    NodeChuyenMon* left;
    NodeKhoaVien* right;
    NodeTruong* father;
};
struct NodeTruong
{
    char name[40];
    NodeKhoaVien* left;
    NodeTruong* right;
};

//them vao giang vien
NodeGiangVien* themGiangVien(NodeGiangVien* giangVien, NodeChuyenMon* nodeCha, 
int Data, char* Name, int ID, char* mail){
    if (giangVien == NULL ){
        NodeGiangVien *temp = new NodeGiangVien;
        strcpy_s(temp->name, 19, Name);
        strcpy_s(temp->mail, 29, mail);
        temp->id = ID;
        temp->data = Data;
        temp->right = NULL;
        temp->father = nodeCha;
        return temp;
    }else{
        giangVien->right = themGiangVien(giangVien->right, nodeCha, Data, Name, ID, mail);
    }
}
//them vao cac node truong, khoa vien, chuyen mon
template <class T, class V, class A>
T* themNode(T* nodeCha, A* nodeChaLon ,V* nodeCon, char* Name){
    if ( nodeCha == NULL){
        T* temp = new T;
        strcpy_s(temp->name, 39, Name);
        temp->left = nodeCon;
        temp->right = NULL;
        temp->father = nodeChaLon;
        return temp;
    }
    else {
        nodeCha->right = themNode(nodeCha->right, nodeChaLon, nodeCon, Name);
    }
}
NodeTruong* themNodeTruong(NodeTruong* truong, NodeKhoaVien* khoaVien, char* name){
    if (truong == NULL){
        NodeTruong* temp = new NodeTruong;
        strcpy_s(temp->name, 39, name);
        temp->left = khoaVien;
        temp->right = truong;
        return temp;
    }
    else  truong->right = themNodeTruong(truong->right, khoaVien, name);
}

//cac ham hien thi tung node cua cay
void hienThiGiangVien(NodeGiangVien* t, int count){
    if( t != NULL){
        cout << count << ".Giang vien: " << t->name << endl ;
        hienThiGiangVien(t->right, count + 1);
    }
}
void hienThiNhomChuyenMon(NodeChuyenMon* t, int count){
    if(t != NULL){
        cout << count << ". Nhom chuyen mon: "  << t->name <<  endl;
        hienThiNhomChuyenMon(t->right, count+1);
    }
}
void hienThiKhoaVien(NodeKhoaVien *t, int count){
    if(t != NULL ){
        cout << count << ". Khoa/vien " <<  t->name << endl;
        hienThiKhoaVien(t->right, count+1);
    }
}
void hienThi(NodeTruong* t, int count){
    if(t != NULL){
        cout << count <<". Truong " << t->name << endl ;
        hienThi(t->right, count + 1);
    }
}


//ham hien thi hang loat

void hienThiGiangVien1(NodeGiangVien* t){
    if( t != NULL){
        hienThiGiangVien1(t->right);
        cout << "\t\t\t"<< "Giang vien: " << t->name << endl ;
        cout << "\t\t\t\t.ID: " << t->id << endl;
        cout << "\t\t\t\t.Mail: " << t->mail << endl;
        cout << "\t\t\t\t.So xuat ban: " << t->data << endl;
    }
}
void hienThiNhomChuyenMon1(NodeChuyenMon* t){
    if(t != NULL){
        hienThiNhomChuyenMon1(t->right);//
        cout << "\t\tNhom chuyen mon: " << t->name <<  endl;
        hienThiGiangVien1(t->left);
    }
}
void hienThiKhoaVien1(NodeKhoaVien *t){
    if(t != NULL ){ 
        hienThiKhoaVien1(t->right);
        cout  << "\tKhoa/vien: " <<  t->name << endl;
        hienThiNhomChuyenMon1(t->left);
    }
}
void hienThi1(NodeTruong* t){
    if(t != NULL){
        hienThi1(t->right);
        cout  <<"Truong: " << t->name << endl ;
        hienThiKhoaVien1(t->left);
    }
}

// UPDATE
void UpdateGiangVien1(NodeGiangVien* t, ofstream &FileOut){
    if( t != NULL){
        UpdateGiangVien1(t->right, FileOut);
        FileOut << t->name << ',' << t->id << ',' << t->mail << ',' << t->data << ',';
    }
}
void updateNhomChuyenMon1(NodeChuyenMon* t, ofstream &FileOut){
    if(t != NULL){
        updateNhomChuyenMon1(t->right, FileOut);//
        int a = demGiaTri<NodeChuyenMon, NodeGiangVien>(t);
        // cout << "\t\tNhom chuyen mon: " << t->name <<  endl;
        FileOut << t->name << ',' << a << ',';
        UpdateGiangVien1(t->left, FileOut);
    }
}
void updateKhoaVien1(NodeKhoaVien *t, ofstream &FileOut){
    if(t != NULL ){ 
        updateKhoaVien1(t->right, FileOut);
        int a = demGiaTri<NodeKhoaVien, NodeChuyenMon>(t);
        // cout  << "\tKhoa/vien: " <<  t->name << endl;
        FileOut << t->name << ',' << a << ',';
        updateNhomChuyenMon1(t->left, FileOut);
    }
}
void updateTruong(NodeTruong* t, ofstream &FileOut){
    if(t != NULL){
        updateTruong(t->right, FileOut);
        int a = demGiaTri<NodeTruong, NodeKhoaVien>(t);
        // cout  <<"Truong: " << t->name << endl ;
        FileOut << t->name << ',' << a << ',';
        updateKhoaVien1(t->left, FileOut);
    }
}

/*-------------------------Ham nhap cac gia tri ban dau cho cay----------------------*/
int demKiTu(char* name){
    int i = 0;
    while(name[i] != '\0'){
        i++;
    }
    return i;
}

NodeGiangVien* nhapGiangVien(ifstream &FileIn, NodeGiangVien* giangVien, NodeChuyenMon* nodeCha, int soGiangVien, ofstream &FileOut, bool save_file ){
    int xuatBan;
    string name, mail;
    char name1[20];
    char mail1[15];
    int id;
    for ( int i = 0; i < soGiangVien; i ++){
    	if (save_file == false){
    		getline(FileIn, name,',');
        	char* Name = new char[name.size() + 1];
	    	strcpy(Name, name.c_str());

        	FileIn >> id;
        	char x; FileIn >> x;

        	getline(FileIn, mail, ',');
        	char* Mail = new char[name.size() + 1];
	    	strcpy(Mail, mail.c_str());

        	FileIn >> xuatBan;
        	char y; FileIn >> y;

        	giangVien = themGiangVien(((i == 0)? NULL: giangVien), nodeCha, xuatBan, Name, id, Mail);
        	delete Name;
        	delete Mail;
    	}
        else{
        	cout << "------>Nhap ten giang vien thu " << i + 1 << ": ";
        	fgets(name1, sizeof(name1) + 1, stdin);
        	int a = demKiTu(name1);
        	name1[a - 1] = '\0';
       
        	cout << "------>ID cua giang vien thu " << i + 1 << ": "; cin >> id;
        	cin.ignore();
        	cout << "------>Nhap vao mail cua giang  vien thu " << i + 1 << ": ";
        	fgets(mail1, sizeof(mail1) + 1, stdin);
        	int b = demKiTu(mail1);
        	mail1[b - 1] = '\0';

        	cout << "------>So xuat ban cua giang vien thu " << i + 1 << ": "; cin >> xuatBan;
        	cin.ignore();
        	giangVien = themGiangVien(((i == 0)? NULL: giangVien), nodeCha, xuatBan, name1, id, mail1);

        	FileOut << name1 << ',' << id << ',' << mail1 << ',' << xuatBan << ',';
        }
    }
    return giangVien;
}
NodeChuyenMon* nhapNhomChuyenMon(ifstream &FileIn, NodeChuyenMon* chuyenMon, NodeKhoaVien* nodeCha, int soNhom, ofstream &FileOut, bool save_file ){
    NodeGiangVien* giangVien = new NodeGiangVien[soNhom];

    for ( int i = 0; i < soNhom; i ++){
    	if (save_file == false){
    		string name;
        	getline(FileIn, name, ',');
        	char* c = new char[name.size() + 1];
	    	strcpy(c, name.c_str());

        	NodeGiangVien* pGiangVien = &giangVien[i];
        	chuyenMon = themNode<NodeChuyenMon, NodeGiangVien, NodeKhoaVien>(((i == 0)? NULL: chuyenMon), nodeCha, pGiangVien,  c);

        	int soGiangVien; FileIn >> soGiangVien;
        	char x; FileIn >> x;
        	*pGiangVien = *nhapGiangVien(FileIn, pGiangVien, truyCap<NodeChuyenMon>(chuyenMon, i+1), soGiangVien, FileOut, save_file);
        	delete c;
    	}
        else{
        	cout << "---->Nhap ten nhom chuyen mon thu " << i + 1 << ": ";
        	char name[40];
        	fgets(name, sizeof(name) + 1, stdin);

        	int a = demKiTu(name);
        	name[a - 1] = '\0';

        	NodeGiangVien* pGiangVien = &giangVien[i];
        	chuyenMon = themNode<NodeChuyenMon, NodeGiangVien, NodeKhoaVien>(((i == 0)? NULL: chuyenMon), nodeCha, pGiangVien,  name);

        	cout << "----->Nhap vao so giang vien cua nhom chuyen mon " << chuyenMon->name ;//
        	cout << endl;
        	int soGiangVien; cin >> soGiangVien;

        	cin.ignore();
        	FileOut << name << ',' << soGiangVien << ',';
        	*pGiangVien = *nhapGiangVien(FileIn, pGiangVien, truyCap<NodeChuyenMon>(chuyenMon, i+1), soGiangVien, FileOut, true);
        }
    }
    return chuyenMon;
}
NodeKhoaVien* nhapKhoaVien(ifstream &FileIn,NodeKhoaVien* khoaVien, NodeTruong* nodeCha, int soKhoaVien, ofstream &FileOut, bool save_file ){
    NodeChuyenMon* chuyenMon = new NodeChuyenMon[soKhoaVien];

    for ( int i = 0; i < soKhoaVien; i++){
    	if (save_file == false){
    		string name;
        	getline(FileIn, name,',');
        	char* c = new char[name.size() + 1];
	    	strcpy(c, name.c_str());

        	NodeChuyenMon* pChuyenMon = &chuyenMon[i];
        	khoaVien = themNode<NodeKhoaVien, NodeChuyenMon, NodeTruong>(((i == 0)? NULL: khoaVien), nodeCha, &chuyenMon[i], c);

        	int soNhomChuyenMOn; FileIn >> soNhomChuyenMOn;
        	char x; FileIn >> x;
        	*pChuyenMon = *nhapNhomChuyenMon(FileIn, pChuyenMon, truyCap<NodeKhoaVien>(khoaVien,i+1), soNhomChuyenMOn, FileOut, save_file);
        	delete c;
    	}
        else{
        	cout <<"-->Nhap ten khoa vien thu " << i + 1 << ": ";
        	char name[40];
        	fgets(name, sizeof(name) + 1, stdin);

        	int a = demKiTu(name);
        	name[a - 1] = '\0';

        	NodeChuyenMon* pChuyenMon = &chuyenMon[i];
        	khoaVien = themNode<NodeKhoaVien, NodeChuyenMon, NodeTruong>(((i == 0)? NULL: khoaVien), nodeCha, &chuyenMon[i], name);///

        	cout << "--->Nhap vao so nhom chuyen mon cua " << khoaVien->name ; //
        	cout << endl; 
        	int soNhomChuyenMOn; cin >> soNhomChuyenMOn;

        	cin.ignore();
        	FileOut << name << ',' << soNhomChuyenMOn << ',';
        	*pChuyenMon = *nhapNhomChuyenMon(FileIn, pChuyenMon, truyCap<NodeKhoaVien>(khoaVien,i+1), soNhomChuyenMOn, FileOut, true);
    	}
    }
    FileOut << '\n';
    
    return khoaVien;
}

NodeTruong* nhapTruong(ifstream &FileIn, NodeTruong* truong, int sotruong, ofstream &FileOut, bool save_file){
    NodeKhoaVien* khoaVien = new NodeKhoaVien[sotruong];
    for ( int i = 0; i < sotruong; i++){

    	if (save_file == false)
    	{
    		string name;
        	getline(FileIn, name, ',' );
        	char* c = new char[name.size() + 1];
	    	strcpy(c, name.c_str());

        	NodeKhoaVien* pKhoaVien = &khoaVien[i];
        	truong = themNodeTruong(((i == 0)? NULL: truong), &khoaVien[i], c);

        	int soKhoaVien; FileIn >> soKhoaVien;
        	char x; FileIn >> x;
        	*pKhoaVien = *nhapKhoaVien(FileIn, pKhoaVien, truyCap<NodeTruong>(truong,i+1), soKhoaVien, FileOut, save_file);
        	delete c;
    	}
        else{
        	cout << "Nhap ten truong: ";
        	char name[40];
        	fgets(name, sizeof(name) + 1, stdin);
        	
        	int a = demKiTu(name);
        	name[a - 1] = '\0';

        	NodeKhoaVien* pKhoaVien = &khoaVien[i];
        	truong = themNodeTruong(((i == 0)? NULL: truong), &khoaVien[i], name);

        	int soKhoaVien;
        	cout << "->Nhap vao so khoa/vien cua truong " << truong->name; cout << endl; cin >> soKhoaVien;
        	//FileOut << soKhoaVien << "\n";
        	// FileOut << name << ',' << soKhoaVien << ',';

        	cin.ignore();
        	FileOut << name << ',' << soKhoaVien << ',';
        	*pKhoaVien = *nhapKhoaVien(FileIn, pKhoaVien, truyCap<NodeTruong>(truong,i+1), soKhoaVien, FileOut, true);
        }
    }
    return truong;
}

/*---------------------------------------Ham them mot giang vien vao cay------------------------*/
//truy cap toi node mong muon
template <class T> T* truyCap (T* nodeTruyCap, int n){
    for ( int i = 0; i < n; i ++){
        if ( (i == n - 1) || (n == 1)) {
            return nodeTruyCap;
            break;            
        }
        nodeTruyCap = nodeTruyCap->right; 
    }
}
NodeTruong* themMoiGV(NodeTruong* truong){
    int chonTruong, chonKhoaVien, chonNhomChuyenMon, id, data;
    char hoTen[20], mail[30];
    cout << "Chon truong cua giang vien: " << endl; 
    hienThi(truong,1);
    cin >> chonTruong;
    NodeKhoaVien* pKhoaVien = truyCap<NodeTruong>(truong, chonTruong)->left;
    cout << "Chon khoa/vien cua giang vien: " << endl;

    hienThiKhoaVien(pKhoaVien,1);
    cin >> chonKhoaVien;
    NodeChuyenMon* pChuyenMon = truyCap<NodeKhoaVien>(pKhoaVien, chonKhoaVien)->left;
    cout << "Chon nhom chuyen mon cua giang vien: " << endl;

    hienThiNhomChuyenMon(pChuyenMon,1);
    cin >> chonNhomChuyenMon; cin.ignore();

    NodeGiangVien* pGiangVien = pChuyenMon->left;
    cout << "Nhap vao giang vien: ";
    fgets(hoTen, sizeof(hoTen) + 1, stdin);

    int a = demKiTu(hoTen);
    hoTen[a - 1] = '\0';

     cout << "Nhap vao ID cua giang vien: "; 
    cin >> id; cin.ignore();
    cout << "Nhap vao gmail cua giang vien: ";
    fgets(mail, sizeof(mail) + 1, stdin);

    int b = demKiTu(mail);
    mail[b - 1] = '\0';

    cout << "Nhap vao xuat ban: " << endl;
    cin >> data; cin.ignore();
    pGiangVien = themGiangVien(pGiangVien, pChuyenMon, data, hoTen, id, mail);

    return truong;
}


//ham diem cac node cua mot cau truc
template <class T, class V> int demGiaTri(T* temp){ 
    if ( temp == NULL) return 0;
    V* temp1 = temp->left;
    int count = 0;
    while(temp1 != NULL){
        count++;
        temp1 = temp1->right;
    }
    return count;
}
/*--------------------------Cac ham de quy tim truong co nhieu khoa nhat---------------------------*/
NodeTruong* truongCoNhieuKhoaNhat(NodeTruong* truong){
    if ( truong == NULL) return NULL;
    if ( demGiaTri<NodeTruong, NodeKhoaVien>(truong) > demGiaTri<NodeTruong, NodeKhoaVien>(truongCoNhieuKhoaNhat(truong->right))) 
        return truong;
    else return truongCoNhieuKhoaNhat(truong->right);
}
NodeTruong* nhungTruongCoNhieuKhoaNhat(NodeTruong* truong){
    NodeTruong* p = truongCoNhieuKhoaNhat(truong);
    int soLuong = demGiaTri<NodeTruong, NodeKhoaVien>(truongCoNhieuKhoaNhat(truong));
    while(truong != NULL){
        if ( (demGiaTri<NodeTruong, NodeKhoaVien>(truong) == soLuong) && (truong != p)) p->right = truong;
        truong = truong->right;
    }
    return truong;
}

/*------------------------Cac ham de quy tim khoa vien co nhieu nhom chuyen mon nhat-----------------*/
NodeKhoaVien* khoaVienMax(NodeKhoaVien* k){
    if (k == NULL) return NULL;
    if ( demGiaTri<NodeKhoaVien, NodeChuyenMon>(k) > demGiaTri<NodeKhoaVien, NodeChuyenMon>(khoaVienMax(k->right)))
        return k;
    else return khoaVienMax(k->right);
}
NodeKhoaVien* KVM(NodeTruong* truong){
    if (truong == NULL ) return NULL;
    if ( demGiaTri<NodeKhoaVien, NodeChuyenMon>(khoaVienMax(truong->left)) > demGiaTri<NodeKhoaVien, NodeChuyenMon>(KVM(truong->right))) 
        return khoaVienMax(truong->left);
    else  return KVM(truong->right);
}

/*----------------------------Cac ham de quy tim giang vien co xuat ban cao nhat--------------------*/
int xuatBanCuaGV(NodeGiangVien* g){
    if (g == NULL) return 0;
    else return g->data;
}
NodeGiangVien* xuatBanMax(NodeGiangVien* gv){
    if ( gv == NULL) return NULL;
    if ( xuatBanCuaGV(gv) > xuatBanCuaGV(xuatBanMax(gv->right))) return gv;
    else return xuatBanMax(gv->right);
}
NodeGiangVien* nhomCMCoXuatBanMax(NodeChuyenMon* chuyenMon){
    if (chuyenMon == NULL) return NULL;
    if ( xuatBanCuaGV(xuatBanMax(chuyenMon->left)) > xuatBanCuaGV(xuatBanMax(nhomCMCoXuatBanMax(chuyenMon->right)))) 
        return xuatBanMax(chuyenMon->left);
    else return nhomCMCoXuatBanMax(chuyenMon->right);
}
NodeGiangVien* khoaVienCoXuatBanMax(NodeKhoaVien* kv){
    if ( kv == NULL) return NULL;
    if (xuatBanCuaGV(nhomCMCoXuatBanMax(kv->left)) > xuatBanCuaGV(khoaVienCoXuatBanMax(kv->right)))
        return nhomCMCoXuatBanMax(kv->left);
    else return khoaVienCoXuatBanMax(kv->right);
}
NodeGiangVien* truongCoXuatBanMax(NodeTruong* t){
    if ( t == NULL) return NULL;
    if (xuatBanCuaGV(khoaVienCoXuatBanMax(t->left)) > xuatBanCuaGV(truongCoXuatBanMax(t->right)))
        return khoaVienCoXuatBanMax(t->left);
    else return truongCoXuatBanMax(t->right);
}

/*-----------------------------------------------Cac ham de quy tim kiem giang vien bang id-----------------------------*/
NodeGiangVien* timKiemGVTrongNhomCM(NodeGiangVien* gv, int id){
    if (gv == NULL) return NULL;
    if (gv->id == id) return gv;  
    else return timKiemGVTrongNhomCM(gv->right, id);
}
NodeGiangVien* timKiemGVTrongKhoaVien(NodeChuyenMon* chuyenMOn, int id){
    if (chuyenMOn == NULL) return NULL;
    if (timKiemGVTrongNhomCM(chuyenMOn->left, id) == NULL) return timKiemGVTrongKhoaVien(chuyenMOn->right, id);
    else return timKiemGVTrongNhomCM(chuyenMOn->left, id);
}
NodeGiangVien* timKiemGVTrongTruong(NodeKhoaVien* khoa, int id){
    if ( khoa == NULL) return NULL;
    if (timKiemGVTrongKhoaVien(khoa->left, id) == NULL) return timKiemGVTrongTruong(khoa->right, id);
    else return timKiemGVTrongKhoaVien(khoa->left, id);
}
NodeGiangVien* timKiemTrongCacTruong(NodeTruong* truong, int id){
    if ( truong == NULL) return NULL;
    if ( timKiemGVTrongTruong(truong->left, id) == NULL) return timKiemTrongCacTruong(truong->right, id);
    else return timKiemGVTrongTruong(truong->left, id);
}

/*-----------------------------------------------Cac ham de quy tim kiem giang vien bang ho ten-----------------------------*/
int soSanh(char* s1, char* s2){
    int n= 0, flag = 1;
     while (s1[n] != '\0') {
      if(s1[n] != s2[n]) {
         flag = 0;
         break;
      }
      n++;
   }
   return ((flag == 1)? 1: 0);
}
NodeGiangVien* timKiemGVTrongNhomCM_bangTen(NodeGiangVien* g, char* ten){
    if (g == NULL) return NULL;
    if (soSanh(g->name, ten)) return g;  
    else return timKiemGVTrongNhomCM_bangTen(g->right, ten);
}
NodeGiangVien* timKiemGVTrongKhoaVien_bangTen(NodeChuyenMon* chuyenMOn, char* name){
    if (chuyenMOn == NULL) return NULL;
    if (timKiemGVTrongNhomCM_bangTen(chuyenMOn->left, name) == NULL) return timKiemGVTrongKhoaVien_bangTen(chuyenMOn->right, name);
    else return timKiemGVTrongNhomCM_bangTen(chuyenMOn->left, name);
}
NodeGiangVien* timKiemGVTrongTruong_bangTen(NodeKhoaVien* khoa, char* name){
    if ( khoa == NULL) return NULL;
    if (timKiemGVTrongKhoaVien_bangTen(khoa->left, name) == NULL) return timKiemGVTrongTruong_bangTen(khoa->right, name);
    else return timKiemGVTrongKhoaVien_bangTen(khoa->left, name);
}
NodeGiangVien* timKiemTrongCacTruong_bangTen(NodeTruong* truong, char* name){
    if ( truong == NULL) return NULL;
    if ( timKiemGVTrongTruong_bangTen(truong->left, name) == NULL) return timKiemTrongCacTruong_bangTen(truong->right, name);
    else return timKiemGVTrongTruong_bangTen(truong->left, name);
}

/*-------------------------------------------Xoa mot giang vien----------------------------------------------------*/
NodeGiangVien *xoaNode(NodeGiangVien* nodeTruoc, NodeGiangVien* nodeXoa, NodeGiangVien* nodeSau){
    nodeTruoc->right = nodeSau;
    nodeXoa = NULL;
    return nodeTruoc;
}
NodeTruong* xoa_chinhSuaGV(NodeTruong* truong, int n){
    int chonTruong, chonKhoaVien, chonNhomChuyenMon, chonGV, id, data;
    cout << "Chon truong can truy cap: " << endl; 
    hienThi(truong,1);
    cin >> chonTruong;
    NodeKhoaVien* pKhoaVien = truyCap<NodeTruong>(truong, chonTruong)->left;
    cout << "Chon khoa/vien can truy cap: " << endl;

    hienThiKhoaVien(pKhoaVien,1);
    cin >> chonKhoaVien;
    NodeChuyenMon* pChuyenMon = truyCap<NodeKhoaVien>(pKhoaVien, chonKhoaVien)->left;
    cout << "Chon nhom chuyen mon can truy cap: " << endl;
    hienThiNhomChuyenMon(pChuyenMon,1);
    cin >> chonNhomChuyenMon; cin.ignore();
    
    cout << endl << "Chon giang vien." << endl;
    hienThiGiangVien(pChuyenMon->left,1);
    cin >> chonGV; cin.ignore();
    if(n == 1){
        NodeGiangVien* nodeSau = truyCap<NodeGiangVien>(pChuyenMon->left, chonGV+1);
        NodeGiangVien* nodeXoa = truyCap<NodeGiangVien>(pChuyenMon->left, chonGV);
        if(chonGV == 1){
            pChuyenMon->left = nodeSau;
            nodeXoa = NULL;
        }
        NodeGiangVien* nodeTruoc = truyCap<NodeGiangVien>(pChuyenMon->left, chonGV-1);
        if(chonGV == demGiaTri<NodeChuyenMon,NodeGiangVien>(pChuyenMon)) {
            nodeTruoc->right = NULL;
        }
        if ( chonGV != 1 && chonGV != demGiaTri<NodeChuyenMon,NodeGiangVien>(pChuyenMon))
        nodeTruoc = xoaNode(nodeTruoc, nodeXoa, nodeSau);
    }
    else{
        NodeGiangVien* chinhSua = truyCap<NodeGiangVien>(pChuyenMon->left, chonGV);
        int luaChon;
        cout << endl << "------------------------Cac lua chon.-------------------" << endl;
        cout << endl << "1.Sua ten." << endl << "2.Sua ID." << endl << "3.Sua Gmail." << endl << "4.Sua so luong xuat ban." << endl;
        cin >> luaChon; cin.ignore();
        switch (luaChon)
        {
        case 1:
            cout << endl <<"Nhap ten chinh sua:" << endl;
            char name[20];
            fgets(name, sizeof(name) + 1, stdin);
            strcpy_s(chinhSua->name,19,name);
            break;
        case 2:
            cout << endl <<"Nhap ID chinh sua:" << endl;
            int id; 
            cin >> id; cin.ignore();
            chinhSua->id = id;
            break;
        case 3:
            cout << endl <<"Nhap gmail chinh sua:" << endl;
            char mail[20];
            fgets(mail, sizeof(name) + 1, stdin);
            strcpy_s(chinhSua->mail,19,name);
            break;
        case 4:
            cout << endl <<"Nhap ID chinh sua:" << endl;
            int xuatBan; 
            cin >> xuatBan; cin.ignore();
            chinhSua->data = xuatBan;
            break;
        default:
            break;
        }
    }
    return truong;
}

/*-----------------------------------------------Cac chuc nang ---------------------------------------------------------*/
//1. Tim kiem giang vien bang ID
void timkiemBangID(NodeTruong* truong){
    cout << "Nhap vao ID cua giang vien: " ; int id;
    cin >> id; cin.ignore();
    NodeGiangVien* gv = timKiemTrongCacTruong(truong, id);
    cout << "=============================================Ket qua========================================" << endl;
    if ( gv == NULL) cout << "Khong tim thay giang vien!" << endl;
    else {
        cout << "Giang vien can tim la: " << gv->name << endl << "Co gmail la: " << gv->mail << endl << "So luong xuat ban: " << gv->data << endl;
        cout << "Nhom chuyen mon: " <<  gv->father->name << endl;
        cout << "Khoa/Vien: " << gv->father->father->name << endl;
        cout << "Truong: " << gv->father->father->father->name << endl;
        //cout << "==============================================================" << endl;
    }
}

//2. Tim kiem giang vien bang ten
void timkiemBangTen(NodeTruong* truong){
    cout << "Nhap vao ten giang vien: " << endl;
    char name[20];
    fgets(name, sizeof(name) + 1, stdin);
    NodeGiangVien* h = timKiemTrongCacTruong_bangTen(truong, name);
    cout << "===========================Ket qua============================" << endl;
    if ( h == NULL) cout << "Khong tim thay giang vien!" << endl;
    else {
        cout << "Giang vien can tim la: " << h->name <<endl<< "Co gmail la: " << h->mail <<endl << "So luong xuat ban: " << h->data << endl;
        cout << "ID: " << h->id << "\n";
        cout << "Nhom chuyen mon: " <<  h->father->name << endl;
        cout << "Khoa/Vien: " << h->father->father->name << endl;
        cout << "Truong: " << h->father->father->father->name << endl;
        cout << "==============================================================" << endl;
    }
}
//3. Tim kiem khoa co nhieu nhom chuyen mon nhat
void timKhoaNhieuNhomChuyenMonNhat(NodeTruong* truong){
    NodeKhoaVien* khoaMax = KVM(truong);
    cout << "===========================Ket qua============================" << endl;
    cout << "Khoa co nhieu nhom chuyen mon nhat: " <<khoaMax->name << endl << "Voi " << demGiaTri<NodeKhoaVien, NodeChuyenMon>(khoaMax) << " nhom chuyen mon" << endl;
    cout << "=============================================================="<< endl;
}
//4. Tim kiem giang vien co nhieu xuat ban nhat trong toan truong
void giangVienCoXuatBanMax(NodeTruong* t){
    NodeGiangVien* g = truongCoXuatBanMax(t);
    //cout << "===========================Ket qua============================" << endl;
    cout << g->name << endl << "ID: " << g->id << "\n" <<"Gmail: " << g->mail << endl << "Voi " << xuatBanCuaGV(g) << " xuat ban" << "\n";
    cout << "Nhom chuyen mon: " <<  g->father->name << endl;
    cout << "Khoa/Vien: " << g->father->father->name << endl;
    cout << "Truong: " << g->father->father->father->name << endl;
    //cout << "=============================================================="<< endl;
}

//5. Tim kiem giang vien co xuat ban cao nhat trong khoa
void GVCoXuatbanCaoNhatKhoa(NodeTruong* truong){
    cout << "Chon truong cua giang vien: " << endl; 
    hienThi(truong,1); int chonTruong;
    cin >> chonTruong;
    NodeKhoaVien* khoaVien = truyCap<NodeTruong>(truong, chonTruong)->left;
    cout << "Chon khoa/vien cua giang vien: " << endl;
            hienThiKhoaVien(khoaVien,1);
            int chonKhoaVien; cin >> chonKhoaVien;
            NodeGiangVien* g = nhomCMCoXuatBanMax(truyCap<NodeKhoaVien>(khoaVien, chonKhoaVien)->left);
            cout << "=======================================Ket qua===================================" << endl;
            cout << g->name << endl << "ID: " << g->id << "\n" <<"Gmail: " << g->mail << endl << "Voi " << xuatBanCuaGV(g) << " xuat ban" << "\n";
            cout << "Nhom chuyen mon: " <<  g->father->name << endl;
            cout << "Khoa/Vien: " << g->father->father->name << endl;
            cout << "Truong: " << g->father->father->father->name << endl;
            //cout << "==============================================================" << endl;
 }
int main(){

    int luachon_du_lieu;
    bool isWrite;

    cout << endl << "=================================Write or Read Data===============================" << endl;
    cout << "1. Read exist data" << endl << "2. Write new data" << endl;
    cout << endl << "Nhap vao lua chon: " << endl;
    cin >> luachon_du_lieu; cin.ignore();
    switch (luachon_du_lieu)
    {
    case 1:
    	cout << "===================================Read Exist Data=================================" << endl;
    	isWrite = false;
    	break;
    case 2:
    	cout << "===================================Write New Data=================================" << endl;
    	isWrite = true;
    	break;
    }

    int soTruong;

    if ( isWrite == true) {
        cout << "Nhap so truong can nhap:" << endl;
        cin >> soTruong; cin.ignore();
    }

    ifstream FileIn;
    ofstream FileOut;

    string existData = "input.txt";
    string outData = "out.txt";

    NodeTruong* truong = NULL;

    FileIn.open(existData, ios_base::in);
    FileOut.open(outData, ios::ios_base::out);
    truong = nhapTruong(FileIn, truong, (isWrite == 1)? soTruong: 4 , FileOut, isWrite);
    FileOut.close();
    FileIn.close();

    int luaChon = 10;
    while(luaChon != 0){
        
        cout << endl << "========================================Menu======================================" << endl;
        cout << "0.Thoat" << endl << "1.Them moi giang vien"  << endl << "2.Tim khoa co nhieu nhom chuyen mon nhat"  <<
        endl<< "3.Tim giang vien co xuat ban cao nhat truong" << endl << "4.Tim giang vien co xuat ban cao nhat khoa" <<
        endl << "5.Tim kiem giang vien bang ID." << endl  << "6.Tim kiem bang ten." << endl<< "7.Lua chon xoa giang vien."
        << endl << "8.Chinh sua thong tin giang vien." << endl <<"9.Hien thi tat ca giang vien cua cac truong." << endl
        << "10.Update." << endl;
        cout << endl << "Nhap vao lua chon: " << endl;
        cin >> luaChon; cin.ignore();
        switch (luaChon)
        {
        case 1:
            cout << "----------------------------Them Giang Vien----------------------------------" << endl;
            truong = themMoiGV(truong);
            break;
        case 2:
            cout << "--------------------------------Tim kiem Khoa--------------------------------" << endl;
            timKhoaNhieuNhomChuyenMonNhat(truong);
            break;
        case 3:
            cout << "-------------------Tim Giang Vien co nhieu xuat ban nhat truong---------------" << endl;
            giangVienCoXuatBanMax(truong);
            break;
        case 4:
            cout << "--------------------Tim Giang Vien co nhieu xuat ban nhat khoa---------------" << endl;
            GVCoXuatbanCaoNhatKhoa(truong);
            break;
        case 5: 
            cout << "---------------------------Tim Giang Vien bang ID----------------------------" << endl;
            timkiemBangID(truong);
            break;
        case 6: 
            cout << "---------------------------Tim Giang Vien bang ho ten------------------------" << endl;
            timkiemBangTen(truong);
            break;   
        case 7:
            cout << "---------------------------Xoa giang vien khoi truong-------------------------" << endl;
            truong = xoa_chinhSuaGV(truong,1);
            break;
        case 8: 
            cout << "---------------------------Chinh sua thong tin giang vien---------------------" << endl;
            truong = xoa_chinhSuaGV(truong,0);
            break;
        case 9:
            cout << "---------------------------------------Ket qua---------------------------------" << endl;
            hienThi1(truong);
            //cout << "==============================================================" << endl;
            break;
        case 10:
        	cout << "---------------------------------------Update----------------------------------" << endl;
        	ofstream updateFile;
        	updateFile.open(outData);
        	updateTruong(truong, updateFile);
        	updateFile.close();
        	break;
        }
        
    }
}





 

































