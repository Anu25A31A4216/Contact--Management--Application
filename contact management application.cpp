#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Contact {
public:
    string name;
    string phone;
    string email;

    void input() {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Email: ";
        getline(cin, email);
    }

    void display() const {
        cout << "\nName: " << name
             << "\nPhone: " << phone
             << "\nEmail: " << email << endl;
    }
};

vector<Contact> contacts;

// Load contacts from file
void loadFromFile() {
    ifstream file("contacts.txt");
    if (!file) return;

    Contact c;
    while (getline(file, c.name) &&
           getline(file, c.phone) &&
           getline(file, c.email)) {
        contacts.push_back(c);
    }
    file.close();
}

// Save contacts to file
void saveToFile() {
    ofstream file("contacts.txt");
    for (const auto &c : contacts) {
        file << c.name << endl;
        file << c.phone << endl;
        file << c.email << endl;
    }
    file.close();
}

// Add contact
void addContact() {
    Contact c;
    c.input();
    contacts.push_back(c);
    saveToFile();
    cout << "Contact added successfully!\n";
}

// View all contacts
void viewContacts() {
    if (contacts.empty()) {
        cout << "No contacts available.\n";
        return;
    }
    for (const auto &c : contacts) {
        c.display();
    }
}

// Search contact
void searchContact() {
    string name;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, name);

    for (const auto &c : contacts) {
        if (c.name == name) {
            c.display();
            return;
        }
    }
    cout << "Contact not found.\n";
}

// Delete contact
void deleteContact() {
    string name;
    cout << "Enter name to delete: ";
    cin.ignore();
    getline(cin, name);

    for (auto it = contacts.begin(); it != contacts.end(); ++it) {
        if (it->name == name) {
            contacts.erase(it);
            saveToFile();
            cout << "Contact deleted.\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

int main() {
    loadFromFile();

    int choice;
    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}   