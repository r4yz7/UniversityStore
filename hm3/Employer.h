#pragma once
#include "User.h"

using namespace std;

class Employer : public User
{
private:
	int rank;
public:
	Employer(string firstname, string surname, string username, string password, int rank)
	: User(firstname, surname, username, password), rank(rank) {}
	
	Employer(){}

	int getRank() const {
		return rank;
	}
};

