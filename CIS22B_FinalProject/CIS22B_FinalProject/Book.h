#ifndef _BOOK_H
#define _BOOK_H

#include <string>
#include <ostream>
#include <iomanip>
using namespace std;

class Book
{
private:
	string author;			// full name of the author
	int bookIdentifier;		// unique identifier for this specific book
	string dateAdded;		// date added in format MM/DD/YYYY
	string isbn;			// isbn of book
	string publisher;		// publisher of the book
	double retailPrice;		// retail price of book
	string title;			// full title of the book
	double wholesaleCost;	// wholesale cost of the book
public:
	// default constructor
	Book();
	// constructor with all attributes
	Book(string titl, string auth, string Isbn, string publish,
		double wholesaleCos, double retailPric, string dateAdd, int identifier);
	// set all attributes of a Book
	void setAll(string titl, string auth, string Isbn, string publish,
		double wholesaleCos, double retailPric, string dateAdd, int identifier);
	// retuns the author attribute
	string getAuthor();
	// returns the date that the book was added
	string getDateAdded();
	// returns the unique identifier
	int getIdentifier();
	// returns the isbn
	string getIsbn();
	// returns the publisher
	string getPublisher();
	// returns the retail price
	double getRetailPrice();
	// returns the title 
	string getTitle();
	// returns the wholesale cost
	double getWholesaleCost();
	// sets the author attribute to author
	void setAuthor(string author);
	// sets the dateAdded attribute to dateAdded
	void setDateAdded(string dateAdd);
	// sets the bookIdentifier attribute to identifier
	void setIdentifier(int identifier);
	// sets the isbn attribute to isbn
	void setIsbn(string Isbn);
	// sets the publisher attribute to publisher
	void setPublisher(string publish);
	// sets the retailPrice attribute to retailPrice
	void setRetailPrice(double retailPric);
	// sets the title attribute to title
	void setTitle(string titl);
	// sets the wholesaleCost attribute to wholesaleCost
	void setWholesaleCost(double wholesaleCost);
	/*
	* allows books to be printed out in an easy to read format using ostream
	* eg.
	* Book a = Book();
	* cout << a; //would print out all of the information about a
	* @param out ostream object to print to
	* @param book book object to print
	* @return returns out
	*/
	friend ostream& operator<<(ostream& out, Book& book);
	/*
	* replaces all parameters with the paramters of toCopy
	* eg.
	* assuming book1 is a book with all attributes set
	* book2 = book1;
	* book2 would now be identical to book1
	* @param toCopy a book to copy
	*/
	void operator=(Book& toCopy);
};

#endif
