#ifndef _BOOK_DATABASE_H
#define _BOOK_DATABASE_H

#include "Book.h"
#include <iostream>
using namespace std;

class BookDatabase
{
private:
	Book books[/*some artbirtary number*/];
	int identifiercount;
	int size;
public:
	void addBook(Book book);
	int getPrice(int identifier);
	void printBook(int identifier);
	void printISBN(int isbn);
	void removeBook(int isbn);
	int searchIndentifier(int identifier);
	int sellBook(int identifier);
	void sortBook();
	void swapBook(int location1, int location2);
};

#endif