#include "Library.h"

/* VALIDATE INPUT -----------------------------------------------------------------------------------------*/

bool Library::isErrorChoose(string str, int start, int end, vector<string>& errMessages) {
	errMessages.clear();
	if (isNull(str)) {
		errMessages.push_back("Lua chon khong duoc de trong. Vui long nhap lai !");
		return true;
	}
	else if (!isInt(str)) {
		errMessages.push_back("Lua chon chi duoc chua chu so. Vui long nhap lai !");
		return true;
	}
	else {
		int status = stoi(str);
		if (status < start || status > end) {
			string err = "Lua chon khong ton tai. Vui long nhap lua chon nam trong khoang (";
			err.append(to_string(start));
			err.append(",");
			err.append(to_string(end));
			err.append(")");
			errMessages.push_back(err);
			return true;
		}
	}
	return false;
}

bool Library::isErrorSave(string str, vector<string>& errMessages) {
	errMessages.clear();
	if (isNull(str)) {
		errMessages.push_back("Lua chon khong duoc de trong. Vui long nhap lai !");
		return true;
	}
	else if (!isInt(str)) {
		errMessages.push_back("Lua chon chi duoc chua chu so. Vui long nhap lai !");
		return true;
	}
	else {
		int status = stoi(str);

		if (status < 0 || status > 1) {
			errMessages.push_back("Lua chon khong hop le. Vui long nhap 1 de luu hoac nhap 0 de huy bo thay doi !");
			return true;
		}
	}
	return false;
}

/*---------------------------------------------------------------------------------------------------------*/





/* IMPORT DU LIEU TU FILE ---------------------------------------------------------------------------------*/

// Ham doc du lieu file => string => luu vao bien data
void FileImport(string &data) {
	string tempData;
	ifstream fi;
	fi.open("./Database/data.txt");
	fi.seekg(0, ios::beg);
	while (!fi.eof()) {
		getline(fi, tempData); // Luu du lieu tu file vao bien data
		data.append(tempData);
	}
	fi.close();
}

// Ham tach du lieu tu data
Book Extract(string data, int index) {

	// Tach 1 thong tin sach => string => luu vao bien bookStr
	int countMatch = 0;
	int start = 0;
	int end = 0;
	if (index == 0) {
		end = data.find(';', start);
	} else {
		while (countMatch < index) {
			start = data.find(';', start) + 1;
			end = data.find(';', start);
			countMatch++;
		}
	}
	int len = end - start;
	string bookStr = data.substr(start, len);

	// Tach 1 thong tin sach tu bien bookStr => Book
	Book book;
	end = 0;
	for (int i = 0; end != bookStr.length(); i++) {
		switch (i)
		{
			case 0:
				end = data.find(',', start);
				len = end - start;
				book.Setter_id(unsigned int(stoi(data.substr(start, len))));
				break;
			case 1:
				start = end + 1;
				end = data.find(',', start);
				len = end - start;
				book.Setter_name(data.substr(start, len));
				break;
			case 2:
				start = end + 1;
				end = data.find(',', start);
				len = end - start;
				book.Setter_author(data.substr(start, len));
				break;
			case 3:
				start = end + 1;
				end = data.find(',', start);
				len = end - start;
				book.Setter_publisher(data.substr(start, len));
				break;
			case 4:
				start = end + 1;
				end = data.find(',', start);
				len = end - start;
				book.Setter_year(stoi(data.substr(start, len)));
				break;
			case 5:
				start = end + 1;
				end = bookStr.length();
				len = end - start;
				book.Setter_status(bool(stoi(data.substr(start, len))));
				break;
		}
	}
	return book;
}

// Ham dem so sach co trong thu vien
int BookCount(string data) {
	int count = 0;
	for (int i = 0; i < data.length(); i++) {
		if (data[i] == ';') count++;
	}
	return count;
}

/*----------------------------------------------------------------------------------------------------------*/





/* DANH SACH LIEN KET --------------------------------------------------------------------------------------*/

// Ham khoi tao danh sach lien ket don
void Library::Init() {
	l.pHead = l.pTail = NULL;
}

// Them Node p vao dau danh sach
void Library::InsertFirst(Node *p) {
	if (l.pHead == NULL) // Danh sach bi rong
	{ 
		l.pHead = l.pTail = p;
	}
	else
	{
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

// Them Node p vao cuoi danh sach
void Library::InsertLast(Node* p) {
	if (l.pHead == NULL) // Danh sach bi rong
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

// Them Node p vao sau Node q
void Library::InsertAfter(Node* p, Node* q) {
	Node* g = q->pNext;
	q->pNext = p;
	p->pNext = g;
}

// Dua du lieu vao Node
Library::Node* Library::ObjectToNode(Book x) {
	Node* p = new Node;
	if (p == NULL) {
		return NULL;
	}
	p->Data = x; // Luu x vao data
	p->pNext = NULL; // Khoi tao moi lien ket
	return p;
}

// Nhap du lieu cho danh sach tu ban phim
void Library::Input() {
	Book book;
	book.Input();
	Node* p = ObjectToNode(book);
	InsertLast(p);
}

// Xuat du lieu co trong danh sach
void Library::Show() {
	Book x;
	for (Node* p = l.pHead; p != NULL; p = p->pNext) {
		x = p->Data;
		x.Show();
		cout << endl;
	}
}

// Ham lay Node theo ID
Library::Node* Library::GetNode(unsigned int id)
{
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->Data.Getter_id() == id) return p;
	}
	return 0;
}

/*------------------------------------------------------------------------------------------------------------*/





/* KHOI TAO & GIAI PHONG CLASS -------------------------------------------------------------------------------*/

// Ham khoi tao thu vien & tao danh sach da duoc nhap du lieu tu file
Library::Library(void) {
	Init(); // Khoi tao danh sach rong
	int n; string data;
	FileImport(data); // Lay du lieu tu file luu vao bien data
	n = BookCount(data);

	// Them du lieu tu file vao danh sach
	Book x;
	for (int i = 0; i < n; i++) {
		x = Extract(data, i);
		Node* p = ObjectToNode(x);
		InsertLast(p);
	}
}

// Ham huy
Library::~Library(void) {
	Node* p;
	while (l.pHead != NULL) {
		p = l.pHead; // Cho p tro toi Head
		l.pHead = l.pHead->pNext; // Chuyen Head sang ben canh
		delete p;
	}
}

/*------------------------------------------------------------------------------------------------------------*/





/* HAM XU LY -------------------------------------------------------------------------------------------------*/

void Library::Insert(string type) {
	if (type == "InsertFirst") {
		system("cls");
		Book x;
		Color(10);
		cout << "\n----------- Nhap thong tin sach -----------\n\n";
		x.Input();
		Node* p = ObjectToNode(x);
		InsertFirst(p);
		Color(9);
		cout << "\n Them sach thanh cong\n ";
		Color(15);
		system("pause");
		Color(15);
	}
	else if (type == "InsertLast") {
		system("cls");
		Book x;
		Color(10);
		cout << "\n----------- Nhap thong tin sach -----------\n\n";
		x.Input();
		Node* p = ObjectToNode(x);
		InsertLast(p);
		Color(9);
		cout << "\n Them sach thanh cong\n ";
		Color(15);
		system("pause");
		Color(15);
	}
	else if (type == "InsertAfter") {
		system("cls");
		unsigned int id;
	gtInputID:
		Color(14);
		cout << "\n Nhap ID cua sach ban muon them vao phia sau: ";
		cin >> id;
		Node* q = GetNode(id);
		if (!q) {
			Color(12);
			cout << " Khong tim thay sach. Vui long nhap lai !\n";
			goto gtInputID;
		}
		Book x;
		Color(10);
		cout << "\n----------- Nhap thong tin sach -----------\n\n";
		x.Input();
		Node* p = ObjectToNode(x);
		InsertAfter(p,q);
		Color(9);
		cout << "\n Them sach thanh cong\n\n ";
		Color(15);
		system("pause");
		Color(15);
	}
	else return;
}
void Library::Save() {
	ofstream fo;
	fo.open("./Database/data.txt", ios::out); fo << "";
	fo.close();
	for (Node* p = l.pHead; p != NULL; p = p->pNext) {
		p->Data.FileExport();
	}
	Color(9);
	cout << "\n Luu file thanh cong\n ";
	Color(15);
}

/*------------------------------------------------------------------------------------------------------------*/





/* MENU ------------------------------------------------------------------------------------------------------*/

/* SubMenu ----------------------------------*/

// InsertMenu(4)
void Library::InsertMenu() {
	int choose = 0;
	bool isError = false;
	string chooseStr;
	vector<string> errMessages;
	do {
		system("cls");
		Color(180); cout << "\n     "; Color(6); cout << " ----------- Them sach -----------";
		Color(180); cout << "\n     "; cout << "\n     "; Color(10); cout << " 1: Them vao dau danh sach";
		Color(180); cout << "\n     "; Color(10); cout << " 2: Them vao cuoi danh sach";
		Color(180); cout << "\n     "; Color(10); cout << " 3: Them vao sau 1 cuon sach";
		Color(180); cout << "\n     "; Color(10); cout << " 4: Quay lai";
		Color(180); cout << "\n     "; cout << "\n     "; Color(6); cout << " ---------------------------------";
		if (isError) {
			Color(180); cout << "\n     "; cout << "\n     "; Color(12); cout << " " << errMessages[0];
		}
		Color(180); cout << "\n     "; cout << "\n     "; Color(7); cout << " Nhap vao lua chon cua ban: ";
		getline(cin, chooseStr);
		isError = isErrorChoose(chooseStr, 1, 4, errMessages);
		if (!isError) choose = stoi(chooseStr);
		Color(15);
		switch (choose)
		{
		case 1:
			Insert("InsertFirst");
			break;
		case 2:
			Insert("InsertLast");
			break;
		case 3:
			Insert("InsertAfter");
			break;
		case 4:
			Menu();
			return;
		default:
			isError = true;
			break;
		}
	} while (choose != 4);
}

void Library::ExitMenu() {
	bool choose = 0;
	string chooseStr;
	bool isError = false;
	vector <string> errMessages;
gtSave:
	Color(14);
	cout << "\n Ban co muon luu thay doi khong ? (Nhap 1 de luu, 0 de huy bo thay doi): ";
	getline(cin, chooseStr);
	isError = isErrorSave(chooseStr, errMessages);
	if (isError) {
		Color(12);
		cout << "\n " << errMessages[0] << endl;
		Color(15);
		goto gtSave;
	}
	else {
		choose = stoi(chooseStr);
	}
	if (choose) {
		Save();
	}
	Color(15);
	exit(0);
}

/*-------------------------------------------*/



/* Main Menu --------------------------------*/

void Library::Menu() {
	int choose = 0;
	string chooseStr;
	bool isError = false;
	vector<string> errMessages;
	do {
		system("cls");
		Color(11);
		cout << "\n ----------- Menu -----------";
		Color(10);
		cout << "\n\n 1: Xem danh sach";
		cout << "\n 2: Tim kiem sach";
		cout << "\n 3: Muon & Tra sach";
		cout << "\n 4: Them sach";
		cout << "\n 5: Chinh sua sach";
		cout << "\n 6: Xoa sach";
		cout << "\n 7: Thoat";
		Color(11);
		cout << "\n\n ----------------------------";
		if (isError) {
			Color(12);
			cout << "\n\n " << errMessages[0];
			Color(15);
		}
		Color(7);
		cout << "\n\n Nhap vao lua chon cua ban: ";
		getline(cin, chooseStr);
		isError = isErrorChoose(chooseStr, 1, 7, errMessages);
		if (!isError) choose = stoi(chooseStr);
		switch (choose)
		{
		case 1:
			// Xem danh sach
			break;
		case 2:
			// Tim kiem sach
			break;
		case 3:
			// Muon & Tra sach
			break;
		case 4:
			// Xem danh sach
			InsertMenu();
			break;
		case 5:
			// Chinh sua
			break;
		case 6:
			// Xoa sach
			break;
		case 7:
			ExitMenu();
			break;
		default:
			isError = true;
			break;
		}
	} while (choose != 7);
}

/*-------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------*/
