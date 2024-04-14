#include <iostream>
#include "User.h"
#include "Store.h"
using namespace std;

int main()
{	
	Store store;
	bool menu = false;
	do
	{
		system("cls");
		int choice;
		cout << "1 - Create new account\n2 - Login\n3 - Exit\nChoice: ";
		cin >> choice;
		switch (choice)
		{
		case 1: {
			store.createAccount();
		}break;
		case 2: {
			store.login();
		}break;
		case 3: {
			exit(0);
		}break;
		default:
			break;
		}
		
	} while (menu!=true);
}
