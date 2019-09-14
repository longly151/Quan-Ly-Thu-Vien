#include "Library.h"


/*--------------------------------------------------------------------------------------------------------------*/

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


/*--------------------------------------------------------------------------------------------------------------*/
Library::Node* Library::GetNode(unsigned int id)
{
	int i = 0;
	for (Node* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (i == id) return p;
		i++;
	}
	return 0;
}

/*--------------------------------------------------------------------------------------------------------------*/

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
Library::Node* Library::ObjectToNode(Book book) {
	Node* p = new Node;
	if (p == NULL) {
		return NULL;
	}
	p->Data = book; // Luu x vao data
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

/*--------------------------------------------------------------------------------------------------------------*/

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




/*--------------------------------------------------------------------------------------------------------------*/
// SubMenu

// Insert(4)
void Library::Insert() {
	int choose;
	do {
		Color(180); cout << "\n     "; Color(6); cout << " ----------- Them sach -----------";
		Color(180); cout << "\n     "; cout << "\n     "; Color(10); cout << " 1: Them vao dau danh sach";
		Color(180); cout << "\n     "; Color(10); cout << " 2: Them vao cuoi danh sach";
		Color(180); cout << "\n     "; Color(10); cout << " 3: Them vao sau 1 cuon sach";
		Color(180); cout << "\n     "; Color(6); cout << " --------------------------------";
		Color(180); cout << "\n     "; cout << "\n     "; Color(7); cout << " Nhap vao lua chon cua ban: ";
		cin >> choose;
		Color(15);
		switch (choose)
		{
		case 1:
			// InsertFirst
			break;
		case 2:
			// InsertLast
			break;
		case 3:
			// InsertAfter
			break;
		default:
			Color(12);
			cout << "\nLua chon khong ton tai. Vui long nhap lai !\n";
			Color(15);
			break;
		}
	} while (true);
}
/*--------------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------*/
// Menu
void Library::Menu() {
	int choose;
	do {
		Color(11);
		cout << "\n----------- Menu -----------";
		Color(10);
		cout << "\n\n1: Xem danh sach";
		cout << "\n2: Tim kiem sach";
		cout << "\n3: Muon & Tra sach";
		cout << "\n4: Them sach";
		cout << "\n5: Chinh sua sach";
		cout << "\n6: Xoa sach";
		cout << "\n7: Thoat";
		Color(11);
		cout << "\n\n----------------------------";
		Color(7);
		cout << "\nNhap vao lua chon cua ban: ";
		cin >> choose;
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
			Insert();
			break;
		case 5:
			// Chinh sua
			break;
		case 6:
			// Xoa sach
			break;
		default:
			Color(12);
			cout << "\nLua chon khong ton tai. Vui long nhap lai !\n";
			Color(15);
			break;
		}
	} while (choose != 7);
}

//void Library::Menu() {
//	int choose;
//	do {
//		Color(60);
//		cout << "Mau 1 (Black)";
//		Color(21);
//		cout << "\nMau 2 (Green)";
//		Color(22);
//		cout << "\nMau 3 (Cyan)";
//		Color(23);
//		cout << "\nMau 4 (Red)";
//		Color(24);
//		cout << "\nMau 5 (Red)";
//		Color(25);
//		cout << "\nMau 6 (Magenta)";
//		Color(26);
//		cout << "\nMau 7 (Lightgray)";
//		Color(27);
//		cout << "\nMau 9 (Lightblue)";
//		cin >> choose;
//		if (choose == 1) {
//			Insert();
//		}
//		else {
//			Color(12);
//			cout << "\nLua chon khong ton tai. Vui long nhap lai !\n";
//			Color(15);
//		}
//	} while (choose != 4);
//}

/*--------------------------------------------------------------------------------------------------------------*/
