#define _CRT_SECURE_NO_WARNINGS
#include "BookDatabase.h"


BookDatabase::BookDatabase()
{
	books = new Book[1024];
	identifierCount = 1;
	size = 0;
	databaseFile = "database.txt";
}

BookDatabase::~BookDatabase()
{
	delete[] books;
}

void BookDatabase::readFile()
{
	try
	{
		ifstream fin;
		fin.open(databaseFile);
		if (fin.fail())
		{
			throw "Failed to open " + databaseFile + " for reading.\n";
		}

		fin >> identifierCount;
		fin >> size;

		string tempAuthor, tempDateAdded, tempIsbn, tempPublisher, tempTitle;
		int tempIdentifier;
		double tempRetailPrice, tempWholesaleCost;

		for (int i = 0; i < size; i++)
		{
			fin.ignore();
			getline(fin, tempAuthor);
			fin.ignore();
			getline(fin, tempDateAdded);
			fin >> tempIdentifier;
			fin.ignore();
			getline(fin, tempIsbn);
			fin.ignore();
			getline(fin, tempPublisher);
			fin >> tempRetailPrice;
			fin.ignore();
			getline(fin, tempTitle);
			fin >> tempWholesaleCost;
			books[i].setAll(tempTitle, tempAuthor, tempIsbn, tempPublisher, tempWholesaleCost, tempRetailPrice, tempDateAdded, tempIdentifier);
		}
	}
	catch (string e)
	{
		cout << e;
	}
}

void BookDatabase::writeFile()
{
	try
	{
		// if file already exists, renames it to file.bak
		// if file.bak already exists, delete it
		ifstream ifile(databaseFile.c_str());
		if (ifile)
		{
			string newName = databaseFile + ".bak";
			ifstream bakIsFile(newName.c_str());
			if (bakIsFile)
			{
				remove(newName.c_str());
			}
			rename(databaseFile.c_str(), newName.c_str());
		}

		ofstream fout;
		fout.open(databaseFile);
		if (fout.fail())
		{
			throw "Failed to open " + databaseFile + " for writing.\n";
		}

		fout << identifierCount << endl;
		fout << size << endl;
		for (int i = 0; i < size; i++)
		{
			fout << books[i].getAuthor() << endl;
			fout << books[i].getDateAdded() << endl;
			fout << books[i].getIdentifier() << endl;
			fout << books[i].getIsbn() << endl;
			fout << books[i].getPublisher() << endl;
			fout << books[i].getRetailPrice() << endl;
			fout << books[i].getTitle() << endl;
			fout << books[i].getWholesaleCost() << endl;
		}
	}
	catch (string e)
	{
		cout << e;
	}
}

void BookDatabase::setDatabaseFile(string file)
{
	databaseFile = file;
}

string BookDatabase::getDatabaseFile()
{
	return databaseFile;
}

void BookDatabase::addBook(Book book)
{
	books[size].setAll(book.getTitle(), book.getAuthor(), book.getIsbn(), book.getPublisher(),
		book.getWholesaleCost(), book.getRetailPrice(), book.getDateAdded(), identifierCount);
	identifierCount++;
	size++;
}
double BookDatabase::getPrice(int identifier)
{
	int count = 0;
	while (count < size)
	{
		if (books[count].getIdentifier() == identifier)
		{
			return books[count].getRetailPrice();
		}
		count++;
	}
	return -1;
}
void BookDatabase::printISBN(string isbn)
{
	cout << "Inventory of books with ISBN: " << isbn << endl;
	for (int i = 0; i < size; i++)
	{
		if (isbn == books[i].getIsbn())
		{
			cout << books[i] << endl;;
		}
	}
	writeFile();
}
Book * BookDatabase::getBooks()
{
	return books;
}
int BookDatabase::getSize()
{
	return size;
}
void BookDatabase::removeBook(int identifier)
{
	int count = 0;
	bool foundBook = false;
	while (count < size - 1)
	{
		if (foundBook)
		{
			books[count] = books[count++];
		}
		else if (books[count].getIdentifier() == identifier)
		{
			books[count] = books[count++];
			foundBook = true;
		}
		count++;
	}
	size--;
	writeFile();
}
Book* BookDatabase::searchIdentifier(int identifier)
{
	int count = 0;
	while (count < size)
	{
		if (books[count].getIdentifier() == identifier)
		{
			return &books[count];
		}
		count++;
	}
	return &books[1023];
}

Book* BookDatabase::operator[](int i)
{
	return searchIdentifier(i);
}

void BookDatabase::mainMenu()
{
	system("CLS");
	bool done = false;
	while (!done)
	{
		cout << "\t\tSerendipity Booksellers\n\t\t\tInventory Main Menu\n\n";
		cout << "\t    1. Look Up a Book\n";
		cout << "\t    2. Add a Book\n";
		cout << "\t    3. Edit a Books Record\n";
		cout << "\t    4. Delete a Book\n";
		cout << "\t    5. Exit\n";
		cout << "\n\t     Enter your choice: ";
		int response;
		cin >> response;
		switch (response)
		{
		case 1:
			lookupBookMenu();
			break;
		case 2:
			addBookMenu();
			break;
		case 3:
			changeBook();
			break;
		case 4:
			removeBookMenu();
			break;
		case 5:
			done = true;
			break;
		default:
			cout << "Invalid response.\n";
			system("CLS");
			break;
		}
	}
}

void BookDatabase::swapBooks(int index1, int index2)
{
	Book temp = books[index1];
	books[index1] = books[index2];
	books[index2] = temp;
}
void BookDatabase::addBookMenu()
{
	system("CLS");
	string title, author, isbn, publisher, dateadded;
	double wholesalecost, retailcost;
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "What is the title of the book you want to add?";
	getline(cin, title);
	cout << "\nWhat is the name of the author? \n";
	getline(cin, author);
	cout << "\nWhat is the isbn of the book?\n";
	getline(cin, isbn);
	cout << "\nWhat is the publisher of the book? \n";
	getline(cin, publisher);
	cout << "\nWhat date is this book added";
	getline(cin, dateadded);
	cout << "\nWhat is the retail cost? \n";
	cin >> retailcost;
	cin.ignore(1000, '\n');
	cout << "\nWhat is the wholesalecost? \n";
	cin >> wholesalecost;
	cin.ignore(1000, '\n');

	Book a;
	a.setAll(title, author, isbn, publisher, wholesalecost, retailcost, dateadded, identifierCount);
	addBook(a);
}
void BookDatabase::removeBookMenu()
{
	system("CLS");
	int identifier;
	cout << "Enter the identifier of the book that you want to remove\n";
	cin >> identifier;

	removeBook(identifier);

}

void BookDatabase::lookupBookMenu()
{
	system("CLS");
	bool done = false;
	bool idenfound = false;
	int identifier;
	bool isbnfound = false;
	string isbn;
	bool datefound = false;
	string dateadded;
	bool retailfound = false;
	double retailprice;
	double wholecost;
	bool wholefound = false;

	
	
	while (!done)
	{
		cout << "\t\tSerendipity Booksellers\n\t\t\tBook Lookup\n\n";
		cout << "\t    1. Look Up by Identifier\n";
		cout << "\t    2. Look Up by Title\n";
		cout << "\t    3. Look Up by Author\n";
		cout << "\t    4. Look Up by ISBN\n";
		cout << "\t    5. Look Up by Publisher\n";
		cout << "\t    6. Look Up by Date Added\n";
		cout << "\t    7. Look Up by Retail Cost\n";
		cout << "\t    8. Look Up by Wholesale Cost\n";
		cout << "\t    9. Exit\n";
		cout << "\n\t     Enter your choice: ";
		int response;
		cin >> response;

		bool pubFound = false;
		string publisher;
		string title;
		bool titleFound = false;
		string author;
		bool authorFound = false;


		switch (response)
		{
		case 1:
			cout << "Enter the identifier you are looking for: ";
			
			cin >> identifier;
			for (int i = 0; i < size; i++)
			{
				if (books[i].getIdentifier() == identifier)
				{
					cout << books[i];
					idenfound = true;
				}
			}
			if (!idenfound)
			{
				cout << "nothing was found\n";
			}
			break;
		case 2:
			cout << "Enter the title you want to search for: ";
			cin >> title;
			for (int i = 0; i < size; i++)
			{
				if (books[i].getTitle().find(title) != std::string::npos)
				{
					cout << books[i];
					titleFound = true;
				}
			}
			if (!titleFound)
			{
				cout << "No book with that title found.\n";
			}
			break;
		case 3:
			cout << "Enter the author you want to search for: ";
			cin >> author;
			for (int i = 0; i < size; i++)
			{
				if (books[i].getAuthor().find(author) != std::string::npos)
				{
					cout << books[i];
					authorFound = true;
				}
			}
			if (!authorFound)
			{
				cout << "No book with that author found.\n";
			}
			break;
		case 4:
			cout << "Enter the ISBN you are looking for: ";
			
			cin >> isbn;
			for (int i = 0; i < size; i++)
			{
				if (books[i].getIsbn() == isbn)
				{
					cout << books[i];
					isbnfound = true;
				}
			}
		if (!isbnfound)
		{
			cout << "nothing was found\n";
		}
			break;
		case 5:
			cout << "Enter the publisher you want to search for: ";
			cin >> publisher;
			for (int i = 0; i < size; i++)
			{
				if (books[i].getPublisher().find(publisher) != std::string::npos)
				{
					cout << books[i];
					pubFound = true;
				}
			}
			if (!pubFound)
			{
				cout << "No book with that publisher found.\n";
			}
			break;
		case 6:
			cout << "Enter the date added you are looking for: ";
			
			cin >> dateadded;
			for (int i = 0; i < size; i++)
			{
				if (books[i].getDateAdded() == dateadded)
				{
					cout << books[i];
					datefound = true;
				}
			}
		if (!datefound)
		{
			cout << "nothing was found\n";
		}
			break;
		case 7:
			cout << "Enter the retail price you are looking for: ";
		
			cin >> retailprice;
			for (int i = 0; i < size; i++)
			{
				if (books[i].getRetailPrice() == retailprice)
				{
					cout << books[i];
					retailfound = true;
				}
			}
			if (!retailfound)
			{
				cout << "nothing was found\n";
			}
			break;
		case 8:
			cout << "Enter the wholesale cost you are looking for: ";

			cin >> wholecost;
			for (int i = 0; i < size; i++)
			{
				if (books[i].getWholesaleCost() == wholecost)
				{
					cout << books[i];
					wholefound = true;
				}
			}
			if (!wholefound)
			{
				cout << "nothing was found\n";
			}
			break;
		case 9:
			done = true;
			break;
		default:
			break;
		}
	}
}
void BookDatabase::changeBook()
{
	string title, author, ISBN, publisher, dateadded;
	double retailcost, wholesalecost;
	int choice, identifier;
	bool done = false;
	system("CLS");
	while (!done);
	{
		cout << "which book would you liek to change";
		cin >> identifier;
		cout << "What would you like to change about that book?" << endl;
		cout << "1. Title" << endl;
		cout << "2. Author" << endl;
		cout << "3. ISBN" << endl;
		cout << "4. Publisher" << endl;
		cout << "5. Date Added" << endl;
		cout << "6. Retail Cost" << endl;
		cout << "7. Wholesale Cost" << endl;
		cout << "8. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			Book* book = searchIdentifier(identifier);
			cout << "What is the new title: ";
			cin >> title;
			book->setTitle(title);
			break;
		}
		case 2:
		{
			Book* book = searchIdentifier(identifier);
			cout << "What is the new Author name: "; 
			cin >> author;
			book->setAuthor(author);
			break;
		}
		case 3:
		{
			Book* book = searchIdentifier(identifier);
			cout << "What is the new ISBN: ";
			cin >> ISBN;
			book->setIsbn(ISBN);
			break;
		}
		case 4:
		{
			Book* book = searchIdentifier(identifier);
			cout << "Who is the new publisher: ";
			cin >> publisher;
			book->setPublisher(publisher);
			break;
		}
		case 5:
		{
			Book* book = searchIdentifier(identifier);
			cout << "What is the new date added: ";
			cin >> dateadded;
			book->setDateAdded(dateadded);
			break;
		}
		case 6:
		{
			Book* book = searchIdentifier(identifier);
			cout << "What is the new retail cost: " ;
			cin >> retailcost;
			book->setRetailPrice(retailcost);
			break;
		}
		case 7:
		{
			Book* book = searchIdentifier(identifier);
			cout << "What is the new wholesale cost: ";
			cin >> wholesalecost;
			book->setWholesaleCost(wholesalecost);
			break;
		}
		case 8:
		{
			done = true;
			break;
		}
		default:
			break;
		}
	}

}