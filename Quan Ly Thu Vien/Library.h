#pragma once
#include "Book.h"

class Library : public Book
{
private:
	struct Node
	{
		Book Data;
		struct Node* pNext;
	};
	struct List
	{
		Node* pHead;
		Node* pTail;
	};
	List l;
public:
	Library(void); // Ham khoi tao mac dinh
	~Library(void); // Ham huy


	Node* GetNode(unsigned int);
	void Init();
	void InsertFirst(Node*);
	void InsertLast(Node*);
	void InsertAfter(Node*, Node*);
	Node* ObjectToNode(Book);
	void Input();
	void Show();



	void Insert();
	


	void Menu();
};
