#pragma once
#include "Book.h"

class Library
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

	void Init();
	void AddHead(Node*);
	void AddTail(Node*);
	Node* GetNode(Book);
	void Input();
	void Show();
	void Destroy();

};
