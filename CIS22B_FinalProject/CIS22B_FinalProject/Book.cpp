#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"

Book::Book()
{
	author = "default author";
	bookIdentifier = -1;
	dateAdded = "XX/XX/XXXX";
	isbn = "defualt isbn";
	publisher = "default publisher";
	retailPrice = 0.0;
	title = "default title";
	wholesaleCost = 0.0;
}

Book::Book(string titl, string auth, string Isbn, string publish, double wholesaleCos, double retailPric, string dateAdd, int identifier)
{
	title = titl;
	author = auth;
	isbn = Isbn;
	publisher = publish;
	wholesaleCost = wholesaleCos;
	retailPrice = retailPric;
	dateAdded = dateAdd;
	bookIdentifier = identifier;
}

string Book::getAuthor()
{
	return author;
}

string Book::getDateAdded()
{
	return dateAdded;
}

int Book::getIdentifier()
{
	return bookIdentifier;
}

string Book::getIsbn()
{
	return isbn;
}

string Book::getPublisher()
{
	return publisher;
}

double Book::getRetailPrice()
{
	return retailPrice;
}

string Book::getTitle()
{
	return title;
}

double Book::getWholesaleCost()
{
	return wholesaleCost;
}

void Book::setAuthor(string auth)
{
	author = auth;
}

void Book::setDateAdded(string dateAdd)
{
	dateAdded = dateAdd;
}

void Book::setIdentifier(int identifier)
{
	bookIdentifier = identifier;
}

void Book::setIsbn(string Isbn)
{
	isbn = Isbn;
}

void Book::setPublisher(string publish)
{
	publisher = publish;
}

void Book::setRetailPrice(double retailPric)
{
	retailPrice = retailPric;
}

void Book::setTitle(string titl)
{
	title = titl;
}

void Book::setWholesaleCost(double wholesaleCos)
{
	wholesaleCost = wholesaleCos;
}

ostream& operator<<(ostream& out, Book& book)
{
	out << fixed << setprecision(2);			// makes doubles round to two digits
	out << "ISBN: " << book.getIsbn() << endl;
	out << "Title: " << book.getTitle() << endl;
	out << "Author: " << book.getAuthor() << endl;
	out << "Publisher: " << book.getPublisher() << endl;
	out << "Date Added: " << book.getDateAdded() << endl;
	out << "Wholesale Cost: $" << book.getWholesaleCost() << endl;
	out << "Retail Price: $" << book.getRetailPrice() << endl;
	return out;
}