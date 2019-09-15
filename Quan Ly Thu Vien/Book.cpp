#include "Book.h"
using namespace std;

/* HAM THUA KE -------------------------------------------------------------------------------------------------*/

// Doi mau console
void Book::Color(int k) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, k);
}

// Kiem tra du lieu null
bool Book::isNull(string str)
{
	if (str == "") return true;
	int len = str.length();
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ' ') count++;
	}
	if (count == len) return true;
	return false;
}

// Kiem tra kieu so nguyen
bool Book::isInt(string str) 
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (i == 0)
		{
			if ((str[i] < '0' || str[i] > '9') && (str[i] != '-')) return false;
			if (str[i] == '-') {
				if (len <= 1) return false;
				else {
					if (str[i + 1] < '0' || str[i + 1] > '9') return false;
				}
			}
		}
		else
		{
			if (str[i] < '0' || str[i] > '9') return false;
		}

	}
	return true;
}

// Kiem tra ten 
bool Book::isHumanName(string str)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if (((str[i] < 'A') || (str[i] > 'Z' && str[i] < 'a') || (str[i] > 'z')) && (str[i] != '.') && (str[i] != ' ')) return false;
	}
	return true;
}

/*--------------------------------------------------------------------------------------------------------------*/





/* VALIDATE INPUT ----------------------------------------------------------------------------------------------*/

bool Book::isErrorID(string str,vector<string> &errMessages) {
	errMessages.clear();
	if (isNull(str)) {
		errMessages.push_back("ID khong duoc de trong. Vui long nhap lai !");
		return true;
	}
	else if (!isInt(str)) {
		errMessages.push_back("ID chi duoc chua chu so. Vui long nhap lai !");
		return true;
	}
	else {
		int id = stoi(str);
		if (id <= 0) {
			errMessages.push_back("ID phai la so tu nhien lon hon 0. Vui long nhap lai !");
			return true;
		}
	}
	return false;
}

bool Book::isErrorBookName(string str, vector<string>& errMessages) {
	errMessages.clear();
	if (isNull(str)) {
		errMessages.push_back("Ten sach khong duoc de trong. Vui long nhap lai !");
		return true;
	}
	return false;
}

bool Book::isErrorHumanName(string str, vector<string>& errMessages) {
	errMessages.clear();
	if (isNull(str)) {
		errMessages.push_back("Ten khong duoc de trong. Vui long nhap lai !");
		return true;
	}
	else if (!isHumanName(str)) {
		errMessages.push_back("Ten chi duoc chua chu cai, ky tu '.' va dau cach. Vui long nhap lai !");
		return true;
	}
	return false;
}

bool Book::isErrorYear(string str, vector<string>& errMessages) {
	errMessages.clear();
	if (isNull(str)) {
		errMessages.push_back("Nam xuat ban khong duoc de trong. Vui long nhap lai !");
		return true;
	}
	else if (!isInt(str)) {
		errMessages.push_back("Nam xuat ban chi duoc chua chu so. Vui long nhap lai !");
		return true;
	}
	else {
		int year = stoi(str);
		time_t now = time(0);
		tm* ltm = localtime(&now);
		int currentYear = 1900 + ltm->tm_year;
		if (year <= 0) {
			errMessages.push_back("Nam xuat ban phai lon hon 0. Vui long nhap lai !");
			return true;
		}
		if (year > currentYear) {
			string err = "Nam xuat ban phai nho hon hoac bang nam hien tai (";
			err.append(to_string(currentYear));
			err.append("). Vui long nhap lai !");
			errMessages.push_back(err);
			return true;
		}
	}
	return false;
}

bool Book::isErrorStatus(string str, vector<string>& errMessages) {
	errMessages.clear();
	if (isNull(str)) {
		errMessages.push_back("Trang thai sach khong duoc de trong. Vui long nhap lai !");
		return true;
	}
	else if (!isInt(str)) {
		errMessages.push_back("Trang thai sach chi duoc chua chu so. Vui long nhap lai !");
		return true;
	}
	else {
		int status = stoi(str);

		if (status < 0 || status > 1) {
			errMessages.push_back("Trang thai sach khong hop le. Vui long nhap 0 neu sach chua duoc muon hoac nhap 1 neu sach da duoc muon !");
			return true;
		}
	}
	return false;
}

/*--------------------------------------------------------------------------------------------------------------*/





/* KHOI TAO & GIAI PHONG CLASS ---------------------------------------------------------------------------------*/

// Khoi tao mac dinh
Book::Book(void) {
	year = 2019;
	status = false;
}

// Khoi tao tham so
Book::Book(unsigned int input_id, string input_name, string input_author, string input_publisher, int input_year, bool input_status) {
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

/*---------------------------------------------------------------------------------------------------------------*/





/* HAM XU LY ----------------------------------------------------------------------------------------------------*/

void Book::Input() {
	string idStr;
	string yearStr;
	string statusStr;
	vector<string> errMessages;
gtID:
	Color(11);
	cout << " Nhap ID: ";
	getline(cin, idStr);
	if (isErrorID(idStr,errMessages)) {
		Color(12);
		cout << " " << errMessages[0] << endl;
		goto gtID;
	}
	else {
		id = stoi(idStr);
	}
gtName:
	Color(11);
	cout << " Nhap ten sach: ";
	getline(cin, name);
	if (isErrorBookName(name, errMessages)) {
		Color(12);
		cout << " " << errMessages[0] << endl;
		goto gtName;
	}
gtAuthor:
	Color(11);
	cout << " Nhap ten tac gia: ";
	getline(cin, author);
	if (isErrorHumanName(author, errMessages)) {
		Color(12);
		cout << " " << errMessages[0] << endl;
		goto gtAuthor;
	}
gtPublisher:
	Color(11);
	cout << " Nhap ten nha xuat ban: ";
	getline(cin, publisher);
	if (isErrorHumanName(publisher, errMessages)) {
		Color(12);
		cout << " " << errMessages[0] << endl;
		goto gtPublisher;
	}
gtYear:
	Color(11);
	cout << " Nhap nam phat hanh: ";
	getline(cin, yearStr);
	if (isErrorYear(yearStr, errMessages)) {
		Color(12);
		cout << " " << errMessages[0] << endl;
		goto gtYear;
	}
	else {
		year = stoi(yearStr);
	}
	Color(12);
gtStatus:
	Color(11);
	cout << " Nhap tinh trang sach (Nhap 1 neu sach da duoc muon, 0 neu sach chua duoc muon): ";
	getline(cin, statusStr);
	if (isErrorStatus(statusStr, errMessages)) {
		Color(12);
		cout << " " << errMessages[0] << endl;
		goto gtStatus;
	}
	else {
		year = bool(stoi(statusStr));
	}
	Color(15);
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
	fo.open("./Database/data.txt",ios::out|ios::app);
	fo << id << "," << name << "," << author << "," << publisher << "," << year << "," << status << ";" << endl;
	fo.close();
}

/*---------------------------------------------------------------------------------------------------------------*/





/* GETTER - SETTER ----------------------------------------------------------------------------------------------*/

unsigned int Book::Getter_id() {
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

void Book::Setter_id(unsigned int input_id) {
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

/*---------------------------------------------------------------------------------------------------------------*/