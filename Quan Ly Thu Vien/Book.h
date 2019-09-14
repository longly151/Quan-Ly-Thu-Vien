#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

using namespace std;

class Book
{
private:
	unsigned int id;
	string name;
	string author;
	string publisher;
	int year;
	bool status;
public:
	void Color(int);

	Book(void); // Ham khoi tao mac dinh
	Book(unsigned int, string, string, string, int, bool); // Ham khoi tao tham so
	Book(const Book&); // Ham khoi tao sao chep
	~Book(void); // Ham huy
	void Input();
	void Show();
	void FileExport();

	// Getter - Setter
	unsigned int Getter_id();
	string Getter_name();
	string Getter_author();
	string Getter_publisher();
	int Getter_year();
	int Getter_status();

	void Setter_id(unsigned int);
	void Setter_name(string);
	void Setter_author(string);
	void Setter_publisher(string);
	void Setter_year(int);
	void Setter_status(int);
};
