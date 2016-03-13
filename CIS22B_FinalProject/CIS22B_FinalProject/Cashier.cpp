#define _CRT_SECURE_NO_WARNINGS
#include "Cashier.h"




Cashier::Cashier()
{
}
Cashier::Cashier(BookDatabase* dtbs)
{
	database = dtbs;
}

void Cashier::listIsbn(string isbn)
{
	Book * books = database->getBooks();
	for (int i = 0; i < database->getSize(); i++)
	{
		if (books[i].getIsbn() == isbn)
		{
			cout << books[i] << endl;
		}
	}
}


void Cashier::addBookMenu()
{
	int identifier = -1;
	cout << "Enter the identifier of the book you wish to add to cart: ";
	cin >> identifier;
	Book* tempBook = database->searchIdentifier(identifier);
	if (tempBook->getIdentifier() == -1)
	{
		cout << "A book with the identifier " << identifier << " was not found.\n";
		cout << "Press return to continue.";
		cin.ignore();
		cin.get();
	}
	else
	{
		cout << "Does this look correct?\n\n" << *tempBook << endl;
		cout << "Response (Y/N)> ";
		string response;
		cin >> response;
		if (response == "y" || response == "Y")
		{
			bool bookAlreadyInCart = false;
			for (int i = 0; i < cartSize; i++)
			{
				if (cart[i] == identifier)
				{
					bookAlreadyInCart = true;
				}
			}

			if (bookAlreadyInCart)
			{
				cout << "That book is already in the cart.\n";
				cout << "Press return to continue.";
				cin.ignore();
				cin.get();
			}
			else
			{
				cart[cartSize] = identifier;
				cartSize++;
				cout << "The book " << tempBook->getTitle() << " was added to the cart.\n";
				cout << "Press return to continue.";
				cin.ignore();
				cin.get();
			}
		}
		else if (response == "n" || response == "N")
		{
			cout << "Exiting...\n";
			cout << "Press return to continue.";
			cin.ignore();
			cin.get();
		}
		else
		{
			cout << "Invalid response...\n";
			cout << "Press return to continue.";
			cin.ignore();
			cin.get();
		}
	}
	database->removeBook(identifier);
}

void Cashier::removeBookFromCart(int identifier)
{
	int count = 0;
	bool condition = false;
	while (count < cartSize - 1)
	{
		if (condition)
		{
			cart[count] = cart[count++];
		}
		else if (cart[count] == identifier)
		{
			cart[count] = cart[count++];
			condition = true;
		}
		count++;
	}
	cartSize--;
		
}
void Cashier::removeBookMenu()
{
	for (int i = 0; i < cartSize; i++)
	{
		cout << &database[cart[i]];
	}
	cout << "What book would you like to remove?" << endl;
	int identifier = 0;
	cin >> identifier;
	for (int i = 0; i < cartSize; i++)
	{
		if (identifier == cart[i])
		{
			char choice;
			cout << "You have chosen to remove " << &database[cart[i]] << " from your list. Is this acceptable? (y/n)" << endl;
			cin >> choice;
			if (choice == 'y')
			{
				cout << "This book will be removed from your cart. " << endl;
				removeBookFromCart(identifier);
			}
			if (choice == 'n')
			{
				cout << "You will move back to the main menu." << endl;
			}
		}
	}
	system("PAUSE");
}
void Cashier::checkout()
{
	double subtotal = 0;
	for (int i = 0; i < cartSize; i++)
	{
		subtotal += database->getPrice(cart[i]);
	}
	cout << "Serendipity Book Sellers" << endl << endl;
	cout << "Date: " << endl << endl;
	cout << "ISBN\t\tTitle\t\t\t\tPrice" << endl;
	cout << "____________________________________________________________" << endl << endl;
	for (int i = 0; i < cartSize; i++)
	{
		Book* book = database->searchIdentifier(cart[i]);
		cout << book->getIsbn() << "\t\t" << book->getTitle() << "\t\t\t\t" << book->getRetailPrice() << endl;
	}
	cout << "\t\t\t\t\t____________________" << endl << endl;
	cout << "\t\tSubtotal:\t\t\t" << subtotal << endl << "\t\tTax: " << "Sales Tax @ 6.25%:\t\t" << (subtotal * 0.0625) << endl << "\t\tTotal:\t\t\t\t" << subtotal + subtotal*0.0625 << endl << endl;
	cout << "Does this look correct? (Y/N)> ";
	string response;
	cin >> response;
	if (response == "y" || response == "Y")
	{
		for (int i = 0; i < cartSize; i++)
		{
			database->removeBook(cart[i]);
		}
		cartSize = 0;
		cout << "Transaction successful.\n";
		cout << "Press return to continue.";
		cin.ignore();
		cin.get();
	}
	else if (response == "n" || response == "N")
	{
		cout << "Exiting...\n";
		cout << "Press return to continue.";
		cin.ignore();
		cin.get();
	}
	else
	{
		cout << "Invalid response...\n";
		cout << "Press return to continue.";
		cin.ignore();
		cin.get();
	}
}
void Cashier::mainMenu()
{
	bool done = false;
	while (!done)
	{
		system("CLS");
		cout << "What would you like to do?" << endl << endl << "Press '1' to add a book. " << endl << "Press '2' to go to checkout." << endl << "Press '3' to remove a book." << endl << "Press '4' to go back of the menu." << endl;
		int choice = 0;
		cin >> choice;
		if (choice == 1)
		{
			addBookMenu();
		}
		else if (choice == 2)
		{
			checkout();
		}
		else if (choice == 3)
		{
			removeBookMenu();
		}
		else if (choice == 4)
		{
			done = true;
		}
		else
		{
			cout << "Invalid choice! ";
		}
	}
}

