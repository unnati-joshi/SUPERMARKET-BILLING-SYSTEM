#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// ========== CLASS DEFINITIONS ==========
class Item {
private:
    string name;
    double price;
    int quantity;
public:
    Item(string n = "", double p = 0.0, int q = 0) : name(n), price(p), quantity(q) {}

    void setName(string n) { name = n; }
    void setPrice(double p) { price = p; }
    void setQuantity(int q) { quantity = q; }

    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void display() const {
        cout << name << "\t" << price << "\t" << quantity << endl;
    }
};

class Customer {
private:
    string name;
    string phone;
public:
    Customer(string n = "", string p = "") : name(n), phone(p) {}

    void setName(string n) { name = n; }
    void setPhone(string p) { phone = p; }

    string getName() const { return name; }
    string getPhone() const { return phone; }

    void display() const {
        cout << "Name: " << name << "\nPhone: " << phone << endl;
    }
};

class Bill {
private:
    Customer customer;
    vector<Item> items;
    string date;
public:
    Bill(Customer c) : customer(c) {
        date = "Today"; // Simplified without ctime
    }

    void addItem(Item item) { items.push_back(item); }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.getPrice() * item.getQuantity();
        }
        return total;
    }

    void print() const {
        system("clear");
        cout << "\n========== SUPERMARKET BILL ==========\n";
        cout << "Date: " << date << endl;
        customer.display();
        cout << "------------------------------------\n";
        cout << "Item\tPrice\tQty\tTotal\n";
        cout << "------------------------------------\n";

        for (const auto& item : items) {
            cout << item.getName() << "\t" 
                 << item.getPrice() << "\t"
                 << item.getQuantity() << "\t"
                 << item.getPrice() * item.getQuantity() << endl;
        }

        cout << "------------------------------------\n";
        cout << "Total: $" << calculateTotal() << endl;
        cout << "====================================\n";
    }
};

// ========== GLOBAL VARIABLES ==========
vector<Item> inventory;
vector<Customer> customers;
vector<Bill> bills;

// ========== FUNCTION PROTOTYPES ==========
void loadInventory();
void saveInventory();
void loadCustomers();
void saveCustomers();
void mainMenu();
void inventoryMenu();
void customerMenu();
void billingMenu();
void reportsMenu();
void addItemToInventory();
void viewInventory();
void updateItem();
void deleteItem();
void addCustomer();
void viewCustomers();
void createBill();
void viewBills();
void dailyReport();
void monthlyReport();

// ========== UTILITY FUNCTIONS ==========
void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ========== INVENTORY FUNCTIONS ==========
void loadInventory() {
    ifstream file("inventory.dat");
    if (file.is_open()) {
        inventory.clear();
        string name;
        double price;
        int quantity;
        
        while (file >> name >> price >> quantity) {
            inventory.emplace_back(name, price, quantity);
        }
        file.close();
    }
}

void saveInventory() {
    ofstream file("inventory.dat");
    for (const auto& item : inventory) {
        file << item.getName() << " " << item.getPrice() << " " << item.getQuantity() << "\n";
    }
    file.close();
}

void addItemToInventory() {
    system("clear");
    string name;
    double price;
    int quantity;

    cout << "\n=== ADD NEW ITEM ===\n";
    cout << "Item Name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Price: ";
    cin >> price;
    
    cout << "Quantity: ";
    cin >> quantity;

    inventory.emplace_back(name, price, quantity);
    saveInventory();
    cout << "\nItem added successfully!\n";
    pressEnterToContinue();
}

void viewInventory() {
    system("clear");
    cout << "\n=== CURRENT INVENTORY ===\n";
    cout << "Item\tPrice\tQty\n";
    cout << "----------------------------\n";

    for (const auto& item : inventory) {
        item.display();
    }
    pressEnterToContinue();
}

void updateItem() {
    system("clear");
    viewInventory();
    
    string name;
    cout << "\nEnter item name to update: ";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (auto& item : inventory) {
        if (item.getName() == name) {
            double newPrice;
            int newQty;
            
            cout << "Enter new price: ";
            cin >> newPrice;
            
            cout << "Enter new quantity: ";
            cin >> newQty;

            item.setPrice(newPrice);
            item.setQuantity(newQty);
            found = true;
            break;
        }
    }

    if (found) {
        saveInventory();
        cout << "Item updated successfully!\n";
    } else {
        cout << "Item not found!\n";
    }
    pressEnterToContinue();
}

void deleteItem() {
    system("clear");
    viewInventory();
    
    string name;
    cout << "\nEnter item name to delete: ";
    cin.ignore();
    getline(cin, name);

    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->getName() == name) {
            inventory.erase(it);
            saveInventory();
            cout << "Item deleted successfully!\n";
            pressEnterToContinue();
            return;
        }
    }

    cout << "Item not found!\n";
    pressEnterToContinue();
}

// ========== CUSTOMER FUNCTIONS ==========
void loadCustomers() {
    ifstream file("customers.dat");
    if (file.is_open()) {
        customers.clear();
        string name, phone;
        
        while (getline(file, name) && getline(file, phone)) {
            customers.emplace_back(name, phone);
        }
        file.close();
    }
}

void saveCustomers() {
    ofstream file("customers.dat");
    for (const auto& customer : customers) {
        file << customer.getName() << "\n" << customer.getPhone() << "\n";
    }
    file.close();
}

void addCustomer() {
    system("clear");
    string name, phone;

    cout << "\n=== ADD NEW CUSTOMER ===\n";
    cout << "Customer Name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Phone Number: ";
    getline(cin, phone);

    customers.emplace_back(name, phone);
    saveCustomers();
    cout << "\nCustomer added successfully!\n";
    pressEnterToContinue();
}

void viewCustomers() {
    system("clear");
    cout << "\n=== CUSTOMER LIST ===\n";
    for (const auto& customer : customers) {
        customer.display();
        cout << "----------------------------\n";
    }
    pressEnterToContinue();
}

// ========== BILLING FUNCTIONS ==========
void createBill() {
    system("clear");
    
    // Select customer
    viewCustomers();
    int custIndex;
    cout << "Enter customer number (0 for new customer): ";
    cin >> custIndex;

    Customer customer;
    if (custIndex == 0) {
        addCustomer();
        customer = customers.back();
    } else if (custIndex > 0 && custIndex <= customers.size()) {
        customer = customers[custIndex-1];
    } else {
        cout << "Invalid selection!\n";
        pressEnterToContinue();
        return;
    }

    Bill bill(customer);
    char addMore = 'y';

    while (tolower(addMore) == 'y') {
        system("clear");
        viewInventory();
        
        int itemIndex, quantity;
        cout << "\nEnter item number to add to bill: ";
        cin >> itemIndex;
        
        if (itemIndex > 0 && itemIndex <= inventory.size()) {
            cout << "Enter quantity: ";
            cin >> quantity;
            
            Item selected = inventory[itemIndex-1];
            if (quantity <= selected.getQuantity()) {
                selected.setQuantity(quantity);
                bill.addItem(selected);
                
                // Update inventory
                inventory[itemIndex-1].setQuantity(inventory[itemIndex-1].getQuantity() - quantity);
                saveInventory();
            } else {
                cout << "Not enough stock available!\n";
            }
        } else {
            cout << "Invalid item selection!\n";
        }

        cout << "Add another item? (y/n): ";
        cin >> addMore;
    }

    bill.print();
    bills.push_back(bill);
    pressEnterToContinue();
}

void viewBills() {
    system("clear");
    cout << "\n=== BILL HISTORY ===\n";
    for (const auto& bill : bills) {
        bill.print();
        cout << "\n";
    }
    pressEnterToContinue();
}

// ========== REPORT FUNCTIONS ==========
void dailyReport() {
    system("clear");
    string date;
    cout << "Enter date (DD/MM/YYYY): ";
    cin >> date;

    cout << "\n=== DAILY SALES REPORT (" << date << ") ===\n";
    double total = 0.0;
    for (const auto& bill : bills) {
        total += bill.calculateTotal();
    }
    cout << "Total Sales: $" << total << endl;
    pressEnterToContinue();
}

void monthlyReport() {
    system("clear");
    string month, year;
    cout << "Enter month (MM): ";
    cin >> month;
    cout << "Enter year (YYYY): ";
    cin >> year;

    cout << "\n=== MONTHLY SALES REPORT (" << month << "/" << year << ") ===\n";
    double total = 0.0;
    for (const auto& bill : bills) {
        total += bill.calculateTotal();
    }
    cout << "Total Sales: $" << total << endl;
    pressEnterToContinue();
}

// ========== MENU FUNCTIONS ==========
void inventoryMenu() {
    int choice;
    do {
        system("clear");
        cout << "\n=== INVENTORY MANAGEMENT ===\n";
        cout << "1. Add New Item\n";
        cout << "2. View Inventory\n";
        cout << "3. Update Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addItemToInventory(); break;
            case 2: viewInventory(); break;
            case 3: updateItem(); break;
            case 4: deleteItem(); break;
            case 5: break;
            default: cout << "Invalid choice!\n"; pressEnterToContinue();
        }
    } while (choice != 5);
}

void customerMenu() {
    int choice;
    do {
        system("clear");
        cout << "\n=== CUSTOMER MANAGEMENT ===\n";
        cout << "1. Add New Customer\n";
        cout << "2. View Customers\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addCustomer(); break;
            case 2: viewCustomers(); break;
            case 3: break;
            default: cout << "Invalid choice!\n"; pressEnterToContinue();
        }
    } while (choice != 3);
}

void billingMenu() {
    int choice;
    do {
        system("clear");
        cout << "\n=== BILLING ===\n";
        cout << "1. Create New Bill\n";
        cout << "2. View Bill History\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: createBill(); break;
            case 2: viewBills(); break;
            case 3: break;
            default: cout << "Invalid choice!\n"; pressEnterToContinue();
        }
    } while (choice != 3);
}

void reportsMenu() {
    int choice;
    do {
        system("clear");
        cout << "\n=== REPORTS ===\n";
        cout << "1. Daily Sales Report\n";
        cout << "2. Monthly Sales Report\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: dailyReport(); break;
            case 2: monthlyReport(); break;
            case 3: break;
            default: cout << "Invalid choice!\n"; pressEnterToContinue();
        }
    } while (choice != 3);
}

// ========== MAIN FUNCTION ==========
int main() {
    loadInventory();
    loadCustomers();

    int choice;
    do {
        system("clear");
        cout << "\n=== SUPERMARKET BILLING SYSTEM ===\n";
        cout << "1. Inventory Management\n";
        cout << "2. Customer Management\n";
        cout << "3. Billing\n";
        cout << "4. Reports\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: inventoryMenu(); break;
            case 2: customerMenu(); break;
            case 3: billingMenu(); break;
            case 4: reportsMenu(); break;
            case 5: 
                saveInventory();
                saveCustomers();
                cout << "Saving data and exiting...\n";
                break;
            default: cout << "Invalid choice!\n"; pressEnterToContinue();
        }
    } while (choice != 5);

    return 0;
}
