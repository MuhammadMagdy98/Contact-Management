#include <iostream>
#include <string>
#include <vector>

class Contact;
class Controller;
class View;

class Contact {
private:
	std::string name;
	std::string phone;
public:
	std::string get_name();
	std::string get_phone();
	void set_name(std::string name);
	void set_phone(std::string phone);
};
std::string Contact::get_name() {
	return name;
}
std::string Contact::get_phone() {
	return phone;
}
void Contact::set_name(std::string name) {
	this->name = name;
}
void Contact::set_phone(std::string phone) {
	this->phone = phone;
}
class Controller {
public:
	void delete_contact(std::vector<Contact> &data);
	void delete_by_id(std::vector<Contact> &data, const int id);
	void delete_by_name(std::vector<Contact> &data, const std::string name);
	void delete_by_phone(std::vector<Contact> &data, const std::string phone);
	void add_contact(Contact new_contact, std::vector<Contact> &data);
	void search_contact(std::vector<Contact> &data);
	void search_by_id(std::vector<Contact> &data, int id);
	void search_by_name(std::vector<Contact> &data, const std::string name);
	void search_by_phone(std::vector<Contact> &data, const std::string phone);
	void edit_contact(std::vector<Contact> &data);
};

class View {
public:
	std::vector<Contact> data;
	void print_contact_data(Contact data);
	void print_all_contacts();
	Contact get_contact_data();
	void main_menu();
};


void Controller::delete_contact(std::vector<Contact> &data) {
	std::cout << "Choose a number from 1 to 3.\n";
	std::cout << "1. Delete by id\n";
	std::cout << "2. Delete by name\n";
	std::cout << "3. Delte by phone\n";
	int choice;
	std::cin >> choice;
	enum { ID = 1, NAME = 2, PHONE = 3 };
	if (choice == ID) {
		int id;
		std::cout << "Enter id: \n";
		std::cin >> id;
		delete_by_id(data, id);
	}
	else if (choice == NAME) {
		std::string name;
		std::cout << "Enter name: \n";
		std::cin >> name;
		delete_by_name(data, name);
	}
	else if (choice == PHONE) {
		std::string phone;
		std::cout << "Enter phone: \n";
		std::cin >> phone;
		delete_by_phone(data, phone);
	}
	else {
		std::cerr << "Wrong choice.\n";
	}

}

void Controller::delete_by_id(std::vector<Contact> &data, const int id) {
	// valid ids are in range [1 .. data.size()]
	if (id < data.size() || id > data.size()) {
		std::cerr << "id not found\n";
		return;
	}
	data.erase(data.begin() + id - 1);
	std::cout << "Contact " << id << " deleted successfully\n";
}

void Controller::delete_by_name(std::vector<Contact> &data, const std::string name) {
	int id = -1;
	// assuming unique names
	for (int i = 0; i < data.size(); i++) {
		if (data[i].get_name() == name) {
			id = i;
			break;
		}
	}
	if (id == -1) {
		std::cerr << "Contact with " << name << " is not found\n";
		return;
	}
	data.erase(data.begin() + id);
}
void Controller::delete_by_phone(std::vector<Contact> &data, const std::string phone) {
	int id = -1;
	for (int i = 0; i < data.size(); i++) {
		if (data[i].get_name() == phone) {
			id = i;
			break;
		}
	}
	if (id == -1) {
		std::cerr << "Contact with " << phone << " is not found\n";
		return;
	}
	data.erase(data.begin() + id);
}

void Controller::add_contact(Contact new_contact, std::vector<Contact> &data) {
	data.push_back(new_contact);
}

void Controller::search_contact(std::vector<Contact> &data) {
	std::cout << "1. Search by id.\n";
	std::cout << "2. Search by name.\n";
	std::cout << "3. Search by phone.\n";
	enum { ID = 1, NAME = 2, PHONE = 3 };
	int choice;
	std::cin >> choice;
	if (choice == ID) {
		int id;
		std::cout << "Enter id: \n";
		std::cin >> id;
		search_by_id(data, id);
	}
	else if (choice == NAME) {
		std::string name;
		std::cout << "Enter name: \n";
		std::cin >> name;
		search_by_name(data, name);
	}
	else if (choice == PHONE) {
		std::string phone;
		std::cout << "Enter phone: \n";
		std::cin >> phone;
		search_by_phone(data, phone);
	}
	else {
		std::cerr << "Wrong choice.\n";
	}


}

void Controller::search_by_id(std::vector<Contact> &data, int id) {
	if (id < data.size() || id > data.size()) {
		std::cerr << "Contact not found\n";
		return;
	}
	View v;
	v.print_contact_data(data[id - 1]);

}

void Controller::search_by_name(std::vector<Contact> &data, const std::string name) {
	int id = -1;
	for (int i = 0; i < data.size(); i++) {
		if (data[i].get_name() == name) {
			id = i;
			break;
		}
	}
	if (id == -1) {
		std::cerr << "Contact not found\n";
		return;
	}
	View v;
	v.print_contact_data(data[id]);
}

void Controller::search_by_phone(std::vector<Contact> &data, const std::string phone) {
	int id = -1;
	for (int i = 0; i < data.size(); i++) {
		if (data[i].get_phone() == phone) {
			id = i;
			break;
		}
	}
	if (id == -1) {
		std::cerr << "Contact not found\n";
		return;
	}
	View v;
	v.print_contact_data(data[id]);
}

void Controller::edit_contact(std::vector<Contact> &data) {
	std::cout << "Enter contact id\n";
	int id;
	std::cin >> id;
	if (id < data.size() || id > data.size()) {
		std::cerr << "Sorry, wrong id\n";
	}
	std::cout << "Do you want to edit this contact? [Y, N]\n";
	View v;
	v.print_contact_data(data[id - 1]);
	std::string choice;
	std::cin >> choice;
	if (choice.front() == 'Y') {
		std::cout << "Enter new name:\n";
		std::string name;
		std::cin >> name;
		data[id - 1].set_name(name);
		std::cout << "Enter new phone:\n";
		std::string phone;
		std::cin >> phone;
		data[id - 1].set_phone(phone);
		std::cout << "Done\n";

	}
	else {
		std::cerr << "Wrong choice.\n";
	}

}

void View::main_menu() {
	enum {
		ADD = 1, DELETE = 2, EDIT = 3,
		SEARCH = 4, PRINT = 5, EXIT = 6
	};
	while (true) {
		std::cout << "1. Add contact\n";
		std::cout << "2. Delete contact\n";
		std::cout << "3. Edit contact\n";
		std::cout << "4. Search contact\n";
		std::cout << "5. Print all contacts\n";
		std::cout << "6. Exit\n";
		int choice;
		std::cin >> choice;
		Controller temp;
		if (choice == ADD) {

			temp.add_contact(get_contact_data(), data);

		}
		else if (choice == DELETE) {
			temp.delete_contact(data);

		}
		else if (choice == EDIT) {
			temp.edit_contact(data);
		}
		else if (choice == SEARCH) {
			temp.search_contact(data);
		}
		else if (choice == PRINT) {
			print_all_contacts();
		}
		else if (choice == EXIT) {
			exit(0);
		}
		else {
			std::cout << "Wrong choice\n";
		}
	}

}
void View::print_contact_data(Contact data) {
	std::cout << data.get_name() << ' ' << data.get_phone() << '\n';
}
void View::print_all_contacts() {
	int curr = 1;
	for (auto x : data)
		std::cout << curr++ << ". " << x.get_name()
		<< ' ' << x.get_phone() << '\n';

}
Contact View::get_contact_data() {
	Contact data;
	std::cout << "Enter contact name:\n";
	std::string name;
	std::cin >> name;
	std::cout << "Enter contact phone:\n";
	std::string phone;
	std::cin >> phone;
	data.set_name(name);
	data.set_phone(phone);
	return data;

}



int main() {
	View v;
	v.main_menu();
	return 0;
}
