#define _CRT_SECURE_NO_WARNINGS
#include "Report.h"

/*
This module generates reports based on the users choice
listInventory() lists all books in the inventory
listRetailValue() lists retail value of all books in the inventory
listWholesaleValue() lists wholesale value of all books in the inventory
listAge() lists books sorted by date added to the inventory via the inventory database module
listCost() lists books sorted by wholesale cost, greatest first to least last
listQuantity() lists books sorted by quantity on hand. The book with the most copies is listed first
*/

//we need default constructor
Report::Report()
{

}
Report::Report(BookDatabase* dtbs)
{
	database = dtbs;
}

//used for sorting by quantity
struct BooksWithIsbn
{
	string Isbn;
	int bookIdentifiers[1024];
	int numBookIdentifiers = 0;
};

//A list of information on all books in the inventory
//List books by title
void Report::listInventory()
{
	system("CLS"); //clear screen of other modules and text
	cout << "Listing current inventory...\n\n";

	Book* books = database->getBooks();
	int size = database->getSize();
	bool swap;

	do
	{
		swap = false;
		for (int i = 0; i < size; i++)
		{

			if ((i + 1) < size) //if next book index < size
			{
				if (books[i].getTitle() > books[i + 1].getTitle())
				{
					Book temp = books[i];
					books[i] = books[i + 1];
					books[i + 1] = temp;
					swap = true;
				}
			}
		}
	} while (swap);

	//list all books in the inventory with some relevant information for each book
	cout << "\n\tTitle\t\t   Author\t      Publisher\t\t    ISBN\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << setw(5) << right << i + 1 << ". "
			<< setw(20) << left << books[i].getTitle()
			<< setw(20) << left << books[i].getAuthor()
			<< setw(20) << left << books[i].getPublisher()
			<< setw(12) << left << books[i].getIsbn() << endl;
	}
	cout << endl;

	//wait until user is done with the information
	cout << "\n\t    Press return to continue.";
	cin.clear();
	cin.ignore(1000, '\n');
	cin.get();
}

//A list of the retail value of all books in the inventory
//and the total retail value of the inventory.
void Report::listRetailValue()
{
	system("CLS"); //clear screen of other modules and text
	cout << "Listing inventory sorted by retail value...\n\n";

	Book* books = database->getBooks();
	int size = database->getSize();
	bool swap;
	double sum = 0;

	do
	{
		swap = false;
		for (int i = 0; i < (size - 1); i++)
		{
			if (books[i].getRetailPrice() > books[i + 1].getRetailPrice())
			{
				Book temp = books[i];
				books[i] = books[i + 1];
				books[i + 1] = temp;
				swap = true;
			}
		}
	} while (swap);

	//output the total retail prices of the books in inventory sorted from least to greatest
	cout << "    Retail Price\tTitle\t\t\t ISBN\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << fixed << setprecision(2)
			<< setw(5) << right << i + 1 << ". $"
			<< setw(12) << left << books[i].getRetailPrice()
			<< setw(30) << left << books[i].getTitle()
			<< setw(12) << books[i].getIsbn()
			<< endl;
		sum += books[i].getRetailPrice();
	}

	//print the total retail value
	cout << fixed << setprecision(2) << "\nTotal Retail Value: $" << sum << endl << endl;

	//wait until user is done with the information
	cout << "\n\t    Press return to continue.";
	cin.clear();
	cin.ignore(1000, '\n');
	cin.get();
}

//A list of the wholesale value of all books in the
//inventory and the total wholesale value of the inventory
void Report::listWholesaleValue()
{
	system("CLS"); //clear screen of other modules and text
	cout << "Listing wholesale value of the inventory...\n\n";

	Book* books = database->getBooks();
	int size = database->getSize();
	bool swap;
	double sum = 0;

	do
	{
		swap = false;
		for (int i = 0; i < (size - 1); i++)
		{
			if (books[i].getWholesaleCost() > books[i + 1].getWholesaleCost())
			{
				Book temp = books[i];
				books[i] = books[i + 1];
				books[i + 1] = temp;
				swap = true;
			}
		}
	} while (swap);

	//output the books from least to greatest wholesale price
	cout << " Wholesale Price\tTitle\t\t\t ISBN\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << fixed << setprecision(2)
			<< setw(5) << right << i + 1 << ". $"
			<< setw(12) << left << books[i].getWholesaleCost()
			<< setw(30) << books[i].getTitle()
			<< setw(12) << books[i].getIsbn()
			<< endl;
		sum += books[i].getWholesaleCost();
	}

	//print the total retail value
	cout << fixed << setprecision(2) << "\nTotal Wholesale Value: $" << sum << endl << endl;

	//wait until user is done with the information
	cout << "\n\t    Press return to continue.";
	cin.clear();
	cin.ignore(1000, '\n');
	cin.get();
}

//A list of all books in the inventory, sorted by purchase date. The
//books that have been in the inventory longest will be listed first.
void Report::listAge()
{
	system("CLS"); //clear screen of other modules and text
	cout << "Listing inventory by date added...\n\n";

	Book* books = database->getBooks();
	int size = database->getSize();
	bool swap = true;

	bool yearDone = true;
	bool dayDone = true;
	bool monthDone = true;

	string str1day;
	string str2day;
	string str1month;
	string str2month;
	string str1year;
	string str2year;


	while (swap)
	{
		swap = false;
		for (int i = 0; i < (size - 1); i++)
		{
			string str1 = books[i].getDateAdded();
			string str2 = books[i + 1].getDateAdded();

			str1month = str1[0];
			str1month += str1[1];
			str2month = str2[0];
			str2month += str2[1];

			str1day = str1[3];
			str1day += str1[4];
			str2day = str2[3];
			str2day += str2[4];

			str1year = str1[6];
			str2year = str2[6];
			for (int j = 7; j <= 9; j++)
			{
				str1year += str1[j];
				str2year += str2[j];
			}

			int month1Int = stoi(str1month);
			int year1Int = stoi(str1year);
			int day1Int = stoi(str1day);

			int month2Int = stoi(str2month);
			int year2Int = stoi(str2year);
			int day2Int = stoi(str2day);

			for (int j = 0; j < size - 1; j++)
			{
				if (year1Int < year2Int)
				{
					Book temp = books[j];
					books[j] = books[j + 1];
					books[j + 1] = temp;
					swap = true;
				}
				if (year1Int == year2Int && month1Int < month2Int)
				{
					Book temp = books[j];
					books[j] = books[j + 1];
					books[j + 1] = temp;
					swap = true;
				}
				if (year1Int == year2Int && month1Int == month2Int && day1Int < day2Int)
				{
					Book temp = books[j];
					books[j] = books[j + 1];
					books[j + 1] = temp;
					swap = true;
				}
			}
		}
	}

	//output the books sorted with the oldest book in the inventory shown first
	cout << "\tDate added\t\tTitle\t\t\t ISBN\n";
	for (int i = 0; i < size; i++)
	{
		cout << setw(5) << right
			<< i + 1 << ". "
			<< setw(20) << left << books[i].getDateAdded()
			<< setw(30) << left << books[i].getTitle()
			<< setw(12) << left << books[i].getIsbn()
			<< endl;
	}
	cout << endl;

	

	//wait until user is done with the information
	cout << "\n\t    Press return to continue.";
	cin.clear();
	cin.ignore(1000, '\n');
	cin.get();
}

//A list of all books in the inventory, sorted by wholesale cost. The
//books with the greatest wholesale cost will be listed first.
void Report::listCost()
{
	system("CLS"); //clear screen of other modules and text
	cout << "Listing inventory sorted by wholesale cost...\n\n";

	Book* books = database->getBooks();
	int size = database->getSize();
	bool swap;
	double sum = 0;

	do
	{
		swap = false;
		for (int i = 0; i < (size - 1); i++)
		{
			if (books[i].getWholesaleCost() < books[i + 1].getWholesaleCost())
			{
				Book temp = books[i];
				books[i] = books[i + 1];
				books[i + 1] = temp;
				swap = true;
			}
		}
	} while (swap);

	//output the books listed with highest wholesale price first
	cout << " Wholesale Price\tTitle\t\t\t    ISBN\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << fixed << setprecision(2)
			<< setw(5) << right << i + 1 << ". $"
			<< setw(12) << left << books[i].getWholesaleCost()
			<< setw(30) << books[i].getTitle()
			<< setw(12) << books[i].getIsbn()
			<< endl;
		sum += books[i].getWholesaleCost();
	}
	//print the total retail value
	cout << fixed << setprecision(2) << "\nTotal Wholesale Value: $" << sum << endl << endl;

	//wait until user is done with the information
	cout << "\n\t    Press return to continue.";
	cin.clear();
	cin.ignore(1000, '\n');
	cin.get();
}

//A list of all books in the inventory sorted by quantity on hand.
//The books with the greatest quantity on hand will be listed first.
void Report::listQuantity()
{
	system("CLS"); //clear screen of other modules and text
	cout << "Listing inventory sorted by quantity on hand...\n\n";

	Book* books = database->getBooks();
	int size = database->getSize();
	BooksWithIsbn* isbnDatabase = new BooksWithIsbn[1024];
	int numIsbns = 0;

	// goes through the entire database finding books with the same isbn
	// and putting their identifiers in bookIdentifiers of the element
	// in isbnDatabase that has the same isbn as them
	for (int i = 0; i < size; i++)
	{
		bool foundIsbn = false;
		for (int j = 0; j < numIsbns; j++)
		{
			if (isbnDatabase[j].Isbn == books[i].getIsbn())
			{
				foundIsbn = true;
				isbnDatabase[j].bookIdentifiers[isbnDatabase[j].numBookIdentifiers] = books[i].getIdentifier();
				isbnDatabase[j].numBookIdentifiers++;
			}
		}
		if (!foundIsbn)
		{
			isbnDatabase[numIsbns].Isbn = books[i].getIsbn();
			isbnDatabase[numIsbns].bookIdentifiers[isbnDatabase[numIsbns].numBookIdentifiers] = books[i].getIdentifier();
			isbnDatabase[numIsbns].numBookIdentifiers++;
			numIsbns++;
		}
	}

	//sort the titles corresponding to the quantity
	//to keep the book attributes matched with the quantity
	int sorted = 0;
	while (sorted < numIsbns - 1)
	{
		int maxLocation = sorted;
		int maxValue = isbnDatabase[sorted].numBookIdentifiers;
		for (int i = sorted; i < numIsbns; i++)
		{
			if (isbnDatabase[i].numBookIdentifiers > maxValue)
			{
				maxLocation = i;
				maxValue = isbnDatabase[i].numBookIdentifiers;
			}
		}
		BooksWithIsbn temp = isbnDatabase[maxLocation];
		isbnDatabase[maxLocation] = isbnDatabase[sorted];
		isbnDatabase[sorted] = temp;
		sorted++;
	}

	//output the books sorted by highest quantity first
	cout << "Quantity\t\tTitle\t\t\t\tISBN\n";
	for (int i = 0; i < numIsbns; i++)
	{
		cout <<
			setw(20) << left << isbnDatabase[i].numBookIdentifiers
			<< setw(30) << left << database->searchIdentifier(isbnDatabase[i].bookIdentifiers[0])->getTitle()
			<< setw(20) << left << isbnDatabase[i].Isbn << endl;
	}
	cout << endl;

	//wait until user is done with the information
	cout << "\n\t    Press return to continue.";
	cin.clear();
	cin.ignore(1000, '\n');
	cin.get();

	delete[] isbnDatabase;
}

//main menu for the module
void Report::mainMenu()
{
	system("CLS"); //clear screen of other modules and text
	int selection = 0; //to hold the user selection

	//ask user what they want to have shown
	do
	{
		system("CLS");

		cout << "\t\tReport Module\n\n";
		cout << "\t    1. Inventory Listing\n";
		cout << "\t    2. Inventory Retail Value\n";
		cout << "\t    3. Inventory Wholesale Value\n";
		cout << "\t    4. List by Age\n";
		cout << "\t    5. List by Quantity\n";
		cout << "\t    6. List by Cost\n";
		cout << "\t    7. Return to Main Menu\n";
		cout << "\n\n\tPlease enter a number corresponding to a selection: ";
		if (cin >> selection)
		{
			//run the choice selected 1-6
			//break if == 7
			if (selection == 1)
			{
				listInventory();
			}
			else if (selection == 2)
			{
				listRetailValue();
			}
			else if (selection == 3)
			{
				listWholesaleValue();
			}
			else if (selection == 4)
			{
				listAge();
			}
			else if (selection == 5)
			{
				listQuantity();
			}
			else if (selection == 6)
			{
				listCost();
			}
			else if (selection == 7)
			{
				break;
			}
			else
			{
				cout << "\n\t    Please enter a valid selection.\n\n";
			}
		}
		else
		{
			cout << "\n\t    Please enter a valid selection.\n\t    Press return to continue.";
			cin.clear();
			cin.ignore(1000, '\n');
			selection = 0;
			cin.get();
		}
	} while (selection != 7); //7 here is return to front main menu
	return;
}