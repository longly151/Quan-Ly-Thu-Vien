#include "Library.h"

/*--------------------------------------------------------------------------------------------------------------*/

// Ham doc du lieu file => string => luu vao bien data
void FileImport(string &data) {
	string tempData;
	ifstream fi;
	fi.open("data.txt");
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
				book.Setter_id(data.substr(start, len));
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

// Ham khoi tao danh sach lien ket don
void Library::Init() {
	l.pHead = l.pTail = NULL;
}

// Them Node p vao dau danh sach
void Library::AddHead(Node *p) {
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
void Library::AddTail(Node* p) {
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

// Dua du lieu vao Node
Library::Node* Library::GetNode(Book book) {
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
	Node* p = GetNode(book);
	AddTail(p);
}

// Xuat du lieu co trong danh sach
void Library::Show() {
	Book x;
	for (Node* p = l.pHead; p != NULL; p = p->pNext) {
		x = p->Data;
		x.Show();
	}
}

// Giai phong danh sach
void Library::Destroy() {
	Node* p;
	while (l.pHead != NULL) {
		p = l.pHead; // Cho p tro toi Head
		l.pHead = l.pHead->pNext; // Chuyen Head sang ben canh
		delete p;
	}
}
/*--------------------------------------------------------------------------------------------------------------*/

// Ham khoi tao thu vien & tao danh sach da duoc nhap du lieu tu file
Library::Library(void) { // Khai bao danh sach
	Init(); // Khoi tao danh sach rong
	int n; string data;
	FileImport(data); // Lay du lieu tu file luu vao bien data
	n = BookCount(data);

	// Them du lieu tu file vao danh sach
	Book x;
	for (int i = 0; i < n; i++) {
		x = Extract(data, i);
		Node* p = GetNode(x);
		AddTail(p);
	}
}
