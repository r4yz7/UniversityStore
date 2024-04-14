#pragma once
#include "User.h";
using namespace std;
class Client : public User
{
private:
	bool clubMember;
public:
	Client(string firstname, string surname, string username, string password, bool clubMember)
		: User(firstname, surname, username, password), clubMember(clubMember) {}

	Client(){}

	bool isClubMember() const {
		return clubMember;
	}
};

