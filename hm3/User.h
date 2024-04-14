#pragma once
#include "string"
#include "Product.h"
#include <list>;
using namespace std;
class User
{
private:
	string firstname;
	string surname;
	string password;
	string username;
	list<Product> shoppingList;

public:
	User(string firstname, string surname, string username, string password)
		: firstname(firstname), surname(surname), username(username), password(password) {}
	User(){}

	string getUsername() const {
		return username;
	}
	string getFirstname() const {
		return firstname;
	}

	string getSurname() const {
		return surname;
	}

	string getPassword() const {
		return password;
	}
};

