#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <ctime>

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

	/* HAM THUA KE -------------------------------------------------------------------------------------------------*/

	void Color(int);
	bool isNull(string);
	bool isInt(string);
	bool isHumanName(string);

	/*--------------------------------------------------------------------------------------------------------------*/



	/* VALIDATE INPUT ----------------------------------------------------------------------------------------------*/
	
	bool isErrorID(string, vector<string> &);
	bool isErrorBookName(string, vector<string> &);
	bool isErrorHumanName(string, vector<string>&);
	bool isErrorYear(string, vector<string> &);
	bool isErrorStatus(string, vector<string> &);

	/* KHOI TAO & GIAI PHONG CLASS ---------------------------------------------------------------------------------*/

	Book(void); // Ham khoi tao mac dinh
	Book(unsigned int, string, string, string, int, bool); // Ham khoi tao tham so
	Book(const Book&); // Ham khoi tao sao chep
	~Book(void); // Ham huy

	/*---------------------------------------------------------------------------------------------------------------*/



	/* HAM XU LY ----------------------------------------------------------------------------------------------------*/

	void Input();
	void Show();
	void FileExport();

	/*---------------------------------------------------------------------------------------------------------------*/



	/* GETTER - SETTER ----------------------------------------------------------------------------------------------*/

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

	/*---------------------------------------------------------------------------------------------------------------*/
};
