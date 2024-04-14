#pragma once
#include "string";
using namespace std;
class Product
{
private:
	string name;
	int price;
	bool inStock;
public:
	Product(){}
	Product(string name, int price, bool inStock) {
		this->name = name;
		this->price = price;
		this->inStock = inStock;
	}

	string getName() const {
		return name;
	}

	int getPrice() const {
		return price;
	}

	int areAvaible() const {
		return inStock;
	}

	void setAvailability(bool availability) {
		inStock = availability;
	}
};

