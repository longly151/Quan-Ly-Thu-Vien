#include "Book.h"
using namespace std;

/*--------------------------------------------------------------------------------------------------------------*/

bool checkID(string id) {
	if (id == "0") return false;
	return true;
}
bool checkName(string name) {
	if (name == "0") return false;
	return true;
}
bool checkYear(int year) {
	if (year == 0) return false;
	return true;
}
bool checkStatus(int status) {
	if (status == 0) return false;
	return true;
}

/*--------------------------------------------------------------------------------------------------------------*/

// Khoi tao mac dinh
Book::Book(void) {
	year = 2019;
	status = false;
}

// Khoi tao tham so
Book::Book(string input_id, string input_name, string input_author, string input_publisher, int input_year, bool input_status) {
	id = input_id;
	name = input_name;
	author = input_author;
	publisher = input_publisher;
	year = input_year;
	status = input_status;
}

// Khoi tao sao chep
Book::Book(const Book &book) {
	id = book.id;
	name = book.name;
	author = book.author;
	publisher = book.publisher;
	year = book.year;
	status = book.status;
}

// Huy
Book::~Book(void) {

}

// Method

void Book::Input() {

gtID:
	cout << "Nhap ID: ";
	getline(cin, id);
	if (!checkID(id)) {
		cout << "ID sach chi duoc chua chu so va chu cai. Vui long nhap lai !";
		goto gtID;
	}
gtName:
	cout << "Nhap ten sach: ";
	getline(cin, name);
	if (!checkName(name)) {
		cout << "Ten sach khong hop le. Vui long nhap lai !";
		goto gtName;
	}
gtAuthor:
	cout << "Nhap ten tac gia: ";
	getline(cin, author);
	if (!checkName(author)) {
		cout << "Ten tac gia khong hop le. Vui long nhap lai !";
		goto gtAuthor;
	}
gtPublisher:
	cout << "Nhap ten nha xuat ban: ";
	getline(cin, publisher);
	if (!checkName(publisher)) {
		cout << "Ten nha xuat ban khong hop le. Vui long nhap lai !";
		goto gtPublisher;
	}
gtYear:
	cout << "Nhap nam phat hanh: ";
	cin >> year;
	if (!checkYear(year)) {
		cout << "Nam phat hanh khong hop le. Vui long nhap lai !";
		goto gtYear;
	}
gtStatus:
	cout << "Nhap tinh trang sach (Nhap 1 neu sach da duoc muon, 0 neu sach chua duoc muon): ";
	cin >> status;
	if (!checkStatus(status)) {
		cout << "Tinh trang sach khong hop le. Vui long nhap lai !";
		goto gtStatus;
	}
}

void Book::Show() {
	cout << "ID: " << id;
	cout << "\nTen sach: " << name;
	cout << "\nTen tac gia: " << author;
	cout << "\nTen nha phat hanh: " << publisher;
	cout << "\nNam xuat ban: " << year;
	cout << "\nTinh trang sach: " << status;
}

void Book::FileExport() {
	ofstream fo;
	fo.open("data.txt",ios::out|ios::app);
	fo << id << "," << name << "," << author << "," << publisher << "," << year << "," << status << ";" << endl;
	fo.close();
}

/*--------------------------------------------------------------------------------------------------------------*/

// Getter - Setter

string Book::Getter_id() {
	return id;
}
string Book::Getter_name() {
	return name;
}
string Book::Getter_author() {
	return author;
}
string Book::Getter_publisher() {
	return publisher;
}
int Book::Getter_year() {
	return year;
}
int Book::Getter_status() {
	return status;
}

void Book::Setter_id(string input_id) {
	id = input_id;
}
void Book::Setter_name(string input_name) {
	name = input_name;
}
void Book::Setter_author(string input_author) {
	author = input_author;
}
void Book::Setter_publisher(string input_publisher) {
	publisher = input_publisher;
}
void Book::Setter_year(int input_year) {
	year = input_year;
}
void Book::Setter_status(int input_status) {
	status = input_status;
}

/*--------------------------------------------------------------------------------------------------------------*/