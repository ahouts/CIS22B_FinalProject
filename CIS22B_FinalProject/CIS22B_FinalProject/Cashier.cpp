#define _CRT_SECURE_NO_WARNINGS
#include "Cashier.h"



//default constructor
Cashier::Cashier() 
{
}
Cashier::Cashier(BookDatabase* dtbs)
{
	database = dtbs;
}

//function to take the subtotal(total without tax) and multiply with tax (6.25%)
template <class Subtotal>
Subtotal calcSubtotal(Subtotal amount)
{
	const Subtotal TAX = 0.0625;
	return amount * TAX;
}

//function to allow the user to add a book to their cart
void Cashier::addBookMenu()
{
	system("CLS");
	int identifier = -1;

	bool correctInput = false;
	while (correctInput == false)
	{
		cout << "\nEnter the identifier of the book you wish to add to cart: ";
		if (cin >> identifier)
		{
			Book* tempBook = database->searchIdentifier(identifier);
			//if-statement will show if the book doesn't exist
			if (tempBook->getIdentifier() <= 0)
			{
				correctInput = true;
				cout << "A book with the identifier " << identifier << " was not found.\n";
				cout << "Press return to continue.";
				cin.ignore();
				cin.get();
			}
			// user prompt
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
					//to check if desired book is in the cart, cannot add if so
					if (bookAlreadyInCart)
					{
						cout << "That book is already in the cart.\n";
						cout << "Press return to continue.";
						cin.ignore();
						cin.get();
					}
					//the book is added to the cart when all other conditions are cleared
					else
					{
						correctInput = true;
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
					cout << "\nPlease try again.\n\n";
					cin.ignore();
				}
				else
				{
					cout << "Invalid response. Please try again\n";
					cout << "Press return to continue.";
					cin.ignore();
					cin.get();
				}
			}
		}
		else
		{
			cout << "Invalid response. Please try again.\n\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
}
//function to remove book based on identifier, to be used in 'removeBookMenu'
void Cashier::removeBookFromCart(int identifier)
{
	
	bool bookFound = false;
	int bookRemoved = -1;
	if (cartSize == 1)
	{
		if (cart[0] == identifier)
		{
			bookFound = true;
			bookRemoved = cart[0];
		}
	}

	int count = 0;
	bool condition = false;
	while (count < cartSize - 1)
	{
		if (condition)
		{
			cart[count] = cart[count + 1];
		}
		else if (cart[count] == identifier)
		{
			bookRemoved = cart[count];
			cart[count] = cart[count + 1];
			condition = true;
			bookFound = true;
		}
		count++;
	}
	//book will be removed if it exists and is in cart
	if (bookFound)
	{
		cout << "Book: " << database->searchIdentifier(bookRemoved)->getTitle()
			<< " was removed from the cart.\n";
		cartSize--;
	}
	//book will be removed because it doesn't exists and is not in cart
	else
	{
		cout << "No book with identifier " << identifier << ".\n";
	}
}
//UI function to remove books from user's cart with displayed book information
void Cashier::removeBookMenu()
{
	system("CLS");
	if (cartSize > 0)
	{
		cout << "  ID   Price\t   Title\n" << endl;
		for (int i = 0; i < cartSize; i++)
		{
			Book* book = database->searchIdentifier(cart[i]);

			cout << setw(4) << right << i + 1 << ". " << "$"
				<< setprecision(2) << fixed
				<< setw(12) << left << book->getRetailPrice()
				<< setw(20) << left << book->getTitle()
				<< endl;
		}
		cout << "\nWhat is the ID of the book you want to remove? ";
		int number = 0;
		cin >> number;

		if (number <= cartSize && number >= 1)
		{
			Book* book = database->searchIdentifier(cart[number -1]);
			char choice;
			cout << "\nYou have chosen to remove " << book->getTitle() << " from your cart. \n\nIs this acceptable? (Y/N)> ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
				removeBookFromCart(cart[number -1]);
				cout << "Press return to continue.";
				cin.ignore();
				cin.get();
			}
			else if (choice == 'N' || choice == 'n')
			{
				cout << book->getTitle() << " was not removed from your cart.\n" << endl;
				cout << "Press return to continue.";
				cin.ignore();
				cin.get();
			}
			else
			{
				cout << "That was an invalid choice.\n";
				cout << "Press return to continue.";
				cin.ignore();
				cin.get();
			}
		}
		else
		{
			cout << "That book was not found in the cart.\n";
			cout << "Press return to continue.";
			cin.ignore();
			cin.get();
		}
	}
	else
	{
		cout << "\n\n\t    The cart is empty!\n\n";
		cout << "Press return to continue.";
		cin.ignore();
		cin.get();
	}
}
//Shows the user their receipt for all the books they inputted
void Cashier::checkout()
{
	system("CLS");
	double subtotal = 0;
	if (cartSize > 0)
	{
		for (int i = 0; i < cartSize; i++)
		{
			subtotal += database->getPrice(cart[i]);
		}
		cout << "Serendipity Book Sellers" << endl << endl;
		cout << "Date: " << endl << endl;
		cout << "ISBN\t\t\tTitle\t\t\t\tPrice" << endl;
		cout << "______________________________________________________________" << endl << endl;
		for (int i = 0; i < cartSize; i++)
		{
			Book* book = database->searchIdentifier(cart[i]);
			cout << setw(24) << left << book->getIsbn()
				 << setw(30) << left << book->getTitle()
				 << setw(7) << right << book->getRetailPrice() << endl;
		}
		cout << "\t\t\t\t\t______________________" << endl << endl;
		cout << "\t\tSubtotal:\t\t\t\t" << subtotal << endl
			 << "\t\tSales Tax @ 6.25%:\t\t\t" << calcSubtotal(subtotal) << endl
			 << "\t\tTotal:\t\t\t\t\t" << subtotal + calcSubtotal(subtotal) << endl << endl;
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
			cout << "Invalid response. Please try again.\n";
			cout << "Press return to continue.";
			cin.ignore();
			cin.get();
		}
	}
	else
	{
		cout << "\n\n\t    The cart is empty!\n\n";
		cout << "Press return to continue.";
		cin.ignore();
		cin.get();
	}
}
//UI for all the Cashier functions in this program
void Cashier::mainMenu()
{
	bool done = false;
	while (!done)
	{
		system("CLS");
		cout << "\t\tSerendipity Booksellers\n\t\t\tCashier\n\n";
		cout << "\t    1. Add a Book to the Cart\n";
		cout << "\t    2. Proceed to Checkout\n";
		cout << "\t    3. Remove a Book from the Cart\n";
		cout << "\t    4. Exit\n";
		cout << "\n\t     Enter your choice: ";
		int choice = 0;
		cin >> choice;

		if (cin.fail())
		{
			system("CLS");
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "That is an invalid response. Press return to continue.";
			cin.get();
			done = false;
		}
		else if (choice == 1)
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

