#include <list>
#include <iostream>
#include "Employer.h"
#include "Client.h"
#include "User.h"
#include "Product.h"
#include <fstream>

using namespace std;

class Store {
private:
	list<Employer> employers;
	list<Client> customers;
	list<Product> products;

public:
	Store() {
		readEmployeesFromFile("Employees.txt");
		readCustomersFromFile("Customers.txt");
		readProductsFromFile("Products.txt");
	}

	void readProductsFromFile(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Error opening products file for reading\n";
			return;
		}
		string name;
		int price;
		bool inStock;
		while (file >> name >> price >> inStock) {
			products.emplace_back(name, price, inStock);
		}
		file.close();
	}

	void readEmployeesFromFile(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Error opening employees file for reading\n";
			return;
		}

		string firstname, surname, username, password;
		int rank;
		while (file >> firstname >> surname >> username >> password >> rank) {
			employers.emplace_back(firstname, surname, username, password, rank);
		}
		file.close();
	}

	void readCustomersFromFile(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Error opening customers file for reading\n";
			return;
		}

		string firstname, surname, username, password;
		bool clubMember;
		while (file >> firstname >> surname >> username >> password >> clubMember) {
			customers.emplace_back(firstname, surname, username, password, clubMember);
		}
		file.close();
	}

	void createAccount() {
		int clientOrEmployee = 0;
		do {
			system("cls");
			cout << "Do you want create a customer or employee account?\nCustomer - 1\nEmployee - 2\nChoice: ";
			cin >> clientOrEmployee;
		} while (clientOrEmployee != 1 && clientOrEmployee != 2);

		switch (clientOrEmployee) {
		case 1: {
			string firstname, surname, username, password;
			bool clubMember = false;
			int club;
			do {
				system("cls");
				cout << "Enter firstname: ";
				cin >> firstname;
			} while (!correctFirstnameAndSurname(firstname));

			do {
				system("cls");
				cout << "Enter surname: ";
				cin >> surname;
			} while (!correctFirstnameAndSurname(surname));

			do {
				system("cls");
				cout << "Enter username: ";
				cin >> username;
			} while (isUsernameTaken(username));

			do {
				system("cls");
				cout << "Enter password (minimum 6 characters):";
				cin >> password;
			} while (password.length() < 6);

			do {
				system("cls");
				cout << "Are you a member of the club?\n1 - Yes\n 2 - No\nChoice: ";
				cin >> club;
			} while (club < 1 || club > 2);
			if (club == 1) {
				clubMember = true;
			}

			Client client = Client(firstname, surname, username, password, clubMember);
			customers.push_back(client);
			ofstream file("Customers.txt", ios::app);
			if (!file.is_open()) {
				cout << "Error opening customers file for writing\n";
				return;
			}
			file << firstname << " " << surname << " " << username << " " << password << " " << clubMember << endl;
			file.close();
		} break;

		case 2: {
			string firstname, surname, username, password;
			int rank;
			do {
				system("cls");
				cout << "Enter firstname: ";
				cin >> firstname;
			} while (!correctFirstnameAndSurname(firstname));

			do {
				system("cls");
				cout << "Enter surname: ";
				cin >> surname;
			} while (!correctFirstnameAndSurname(surname));

			do {
				system("cls");
				cout << "Enter username: ";
				cin >> username;
			} while (isUsernameTaken(username));

			do {
				system("cls");
				cout << "Enter password (minimum 6 characters):";
				cin >> password;
			} while (password.length() < 6);

			do {
				system("cls");
				cout << "Enter your rank(1-3): ";
				cin >> rank;
			} while (rank < 1 || rank > 3);
			Employer employee = Employer(firstname, surname, username, password, rank);
			employers.push_back(employee);
			ofstream file("Employees.txt", ios::app);
			if (!file.is_open()) {
				cout << "Error opening customers file for writing\n";
				return;
			}
			file << firstname << " " << surname << " " << username << " " << password << " " << rank << endl;
			file.close();
		} break;
		default:
			break;
		}
	}

	void login() {
		int clientOrEmployee = 0;
		do {
			cout << "Do you want to log in with a customer or employee account?\n1 - Customer\n2 - Employee\nChoice: ";
			cin >> clientOrEmployee;
		} while (clientOrEmployee < 1 || clientOrEmployee > 2);

		switch (clientOrEmployee) {
		case 1: {
			system("cls");
			Client currentClient;
			string username, password;
			cout << "Enter username: ";
			cin >> username;
			cout << "Enter password: ";
			cin >> password;
			bool isLogged = false;

			for (const Client& client : customers) {
				if (client.getUsername() == username && client.getPassword() == password) {
					isLogged = true;
					currentClient = client;
					cout << "Logged in as a customer!\n";
					break;
				}
			}

			if (!isLogged) {
				cout << "Invalid username or password.\n";
			}
			else {
				int choice = 0;
				do {

					system("cls");
					if (currentClient.isClubMember()) {
						cout << "Hello, " << currentClient.getFirstname() << " " << currentClient.getSurname() << " (VIP)" << endl << endl;
					}
					else {
						cout << "Hello, " << currentClient.getFirstname() << " " << currentClient.getSurname() << endl << endl;
					}

					int i = 0;
					for (auto it = products.begin(); it != products.end(); ++it) {
						if (it->areAvaible()) {
							cout << i << ") " << it->getName() << " - " << it->getPrice() << "UAH" << endl;
						}
						i++;
					}

					int choice;
					cout << "Choose what you want to buy (0 to exit): ";
					cin >> choice;
					system("cls");

					if (choice >= 0 && choice < products.size()) {
						int count = 1;
						auto it = products.begin();
						advance(it, choice);
						const Product& selectedProduct = *it;
						do
						{
							system("cls");
							cout << "Enter count: ";
							cin >> count;

						} while (count <= 0);

						cout << "You will pay: " << selectedProduct.getPrice() * count << " UAH" << endl;
						system("pause");
					}
					else if (choice != 0) {
						cout << "Invalid choice!" << endl;
					}

				} while (choice != 0);
			}
		} break;

		case 2: {
			system("cls");
			Employer currentEmployee;
			string username, password;
			cout << "Enter username: ";
			cin >> username;
			cout << "Enter password: ";
			cin >> password;
			bool isLogged = false;

			for (const Employer& employer : employers) {
				if (employer.getUsername() == username && employer.getPassword() == password) {
					isLogged = true;
					currentEmployee = employer;
					cout << "Logged in as an employee!\n";
					break;
				}
			}

			if (!isLogged) {
				cout << "Invalid username or password.\n";
			}
			else {
				int menu;
				do {
					system("cls");
					int rank = currentEmployee.getRank();
					if (rank == 1) {
						cout << "Hello, " << currentEmployee.getFirstname() << " " << currentEmployee.getSurname() << " (employee)";
					}
					else if (rank == 2) {
						cout << "Hello, " << currentEmployee.getFirstname() << " " << currentEmployee.getSurname() << " (manager)";
					}
					else if (rank == 3) {
						cout << "Hello, " << currentEmployee.getFirstname() << " " << currentEmployee.getSurname() << " (director)";
					}
					cout << "0 - exit\n1 - Print out a list of all clients.\n2 - Print out a list of clients who are members only\n3 - Adding a new product to the store\n4 - Change inventory status for a product\n5 - Making purchase\nChoice: ";
					cin >> menu;
					switch (menu)
					{
					case 1: {
						for (const Client& client : customers)
						{
							cout << client.getFirstname() << " " << client.getSurname() << " - " << client.getUsername() << endl;
						}
						system("pause");
					}break;
					case 2:
					{
						for (const Client& client : customers)
						{
							if (client.isClubMember())
								cout << client.getFirstname() << " " << client.getSurname() << " - " << client.getUsername() << endl;
						}
						system("pause");
					}break;
					case 3: {
						system("cls");
						string name;
						int price;
						bool inStock = false;
						int stock;
						cout << "Name of product: ";
						cin >> name;
						do
						{
							system("cls");
							cout << "Enter price: ";
							cin >> price;
						} while (price <= 0);
						do
						{
							system("cls");
							cout << "In stock(2-no, 1-yes): ";
							cin >> stock;
						} while (stock < 1 || stock>2);
						if (stock == 1)
							inStock = true;
						Product product = Product(name, price, inStock);
						products.push_back(product);
						ofstream file("Products.txt", ios::app);
						if (!file.is_open()) {
							cout << "Error opening customers file for writing\n";
							return;
						}
						file << name << " " << price << " " << inStock << endl;
						file.close();
					}break;
					case 4: {
						int index = 1;
						for (auto it = products.begin(); it != products.end(); ++it) {
							cout << index << ") " << it->getName() << " - Available: " << (it->areAvaible() ? "Yes" : "No") << endl;
							index++;
						}

						int choice;
						do {
							cout << "Enter the number of the product you want to update: ";
							cin >> choice;
						} while (choice < 1 || choice > products.size());

						int current_index = 1;
						for (auto it = products.begin(); it != products.end(); ++it) {
							if (current_index == choice) {
								cout << "Change availability for " << it->getName() << " (1 for available, 0 for not available): ";
								bool newAvailability;
								cin >> newAvailability;
								it->setAvailability(newAvailability);
								break;
							}
							current_index++;
						}
					}break;
					case 5: {
						int i = 0;
						for (auto it = products.begin(); it != products.end(); ++it) {
							if (it->areAvaible()) {
								cout << i << ") " << it->getName() << " - " << it->getPrice() << "UAH" << endl;
							}
							i++;
						}
						int choice;
						cout << "Choose what you want to buy (0 to exit): ";
						cin >> choice;
						system("cls");

						if (choice >= 0 && choice < products.size()) {
							int count = 1;
							auto it = products.begin();
							advance(it, choice);
							const Product& selectedProduct = *it;
							do
							{
								system("cls");
								cout << "Enter count: ";
								cin >> count;

							} while (count <= 0);

							int rank = currentEmployee.getRank();
							if (rank == 1) {
								double sum = (selectedProduct.getPrice() * count) * 0.1;
								cout << "You will pay: " << sum;
							}
							else if (rank == 2) {
								double sum = (selectedProduct.getPrice() * count) * 0.2;
								cout << "You will pay: " <<sum;

							}
							else if (rank == 3) {
								double sum = (selectedProduct.getPrice() * count) * 0.3;
								cout << "You will pay: " << sum;

							}
							
							system("pause");


						} while (choice != 0);
					}break;
					default:
						break;
					}
				} while (menu != 0);
			}
		} break;
		default:
			break;
		}
	}

	bool correctFirstnameAndSurname(const string& name) {
		for (char c : name) {
			if (!isalpha(c))
				return false;
		}
		return true;
	}

	bool isUsernameTakenByEmployer(const string& username) {
		for (const Employer& employer : employers) {
			if (username == employer.getUsername()) {
				return true;
			}
		}
		return false;
	}

	bool isUsernameTakenByClient(const string& username) {
		for (const Client& client : customers) {
			if (username == client.getUsername()) {
				return true;
			}
		}
		return false;
	}

	bool isUsernameTaken(const string& username) {
		return isUsernameTakenByEmployer(username) || isUsernameTakenByClient(username);
	}
};
