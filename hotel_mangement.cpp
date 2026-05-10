#include <iostream>
#include <fstream>
#include <string>
#include <exception>
using namespace std;

// ======================================================
// MEMBER 1 START: 
// Structs, Person (Abstract), Customer, Room, Booking
// Object Arrays, Searching, and Sorting
// ======================================================

// Use of Structures
struct Date {
    int day;
    int month;
    int year;
};

class Person {
protected:
    string name;
    int id;
    string phone;

public:
    Person() {
        name = "Unknown";
        id = 0;
        phone = "N/A";
    }

    Person(string name, int id, string phone) {
        this->name = name;
        this->id = id;
        this->phone = phone;
    }

    Person(const Person& p) {
        name = p.name;
        id = p.id;
        phone = p.phone;
    }

    virtual void display() = 0; // Pure virtual function

    virtual ~Person() {}

    int getID() {
        return id;
    }
};

class Customer : public Person {
private:
    int roomBooked;
    int daysStay;
    string paymentMethod;
    string paymentStatus;

public:
    Customer() : Person() {
        roomBooked = 0;
        daysStay = 0;
        paymentMethod = "Not Selected";
        paymentStatus = "Pending";
    }

    Customer(string name, int id, string phone, int roomBooked, int daysStay, string paymentMethod, string paymentStatus)
        : Person(name, id, phone) {
        this->roomBooked = roomBooked;
        this->daysStay = daysStay;
        this->paymentMethod = paymentMethod;
        this->paymentStatus = paymentStatus;
    }

    Customer(const Customer& c) : Person(c) {
        roomBooked = c.roomBooked;
        daysStay = c.daysStay;
        paymentMethod = c.paymentMethod;
        paymentStatus = c.paymentStatus;
    }

    void addCustomer() {
        cin.ignore();
        cout << "\nEnter Customer Name: ";
        getline(cin, name);
        cout << "Enter Customer ID: ";
        cin >> id;
        cout << "Enter Phone Number: ";
        cin >> phone;
        cout << "Enter Room Number: ";
        cin >> roomBooked;
        cout << "Enter Number of Days Stay: ";
        cin >> daysStay;
        cout << "Enter Payment Method (Cash/Bank/Online): ";
        cin >> paymentMethod;
        cout << "Enter Payment Status (Paid/Pending): ";
        cin >> paymentStatus;
    }

    void display() override {
        cout << "\n--- Customer Details ---\n";
        cout << "Name: " << name << ", ID: " << id << ", Phone: " << phone << endl;
        cout << "Room: " << roomBooked << ", Days Stay: " << daysStay << endl;
        cout << "Payment: " << paymentMethod << " (" << paymentStatus << ")\n";
    }
};

class Room {
private:
    int roomNumber;
    string roomType;
    float price;
    bool isAvailable;

public:
    static int totalRooms;

    Room() {
        roomNumber = 0;
        roomType = "Standard";
        price = 0;
        isAvailable = true;
        totalRooms++;
    }

    Room(int roomNumber, string roomType, float price, bool isAvailable) {
        this->roomNumber = roomNumber;
        this->roomType = roomType;
        this->price = price;
        this->isAvailable = isAvailable;
        totalRooms++;
    }

    float operator+(Room r) {
        return this->price + r.price;
    }

    void displayRoom() {
        cout << "Room Number: " << roomNumber << " (" << roomType << ") - Rs." << price << " - " << (isAvailable ? "Available" : "Booked") << endl;
    }

    float getPrice() {
        return price;
    }
};

int Room::totalRooms = 0;

class Booking {
private:
    Customer customer;
    Room room;
    Date checkIn;  // Using struct inside class
    Date checkOut;

public:
    void createBooking(Customer c, Room r) {
        customer = c;
        room = r;

        cout << "Enter Check-In Date (DD MM YYYY format): ";
        cin >> checkIn.day >> checkIn.month >> checkIn.year;

        cout << "Enter Check-Out Date (DD MM YYYY format): ";
        cin >> checkOut.day >> checkOut.month >> checkOut.year;

        cout << "\nBooking Created Successfully!\n";
    }

    void displayBooking() {
        cout << "\n===== Booking Details =====\n";
        customer.display();
        room.displayRoom();
        cout << "Check-In: " << checkIn.day << "/" << checkIn.month << "/" << checkIn.year << endl;
        cout << "Check-Out: " << checkOut.day << "/" << checkOut.month << "/" << checkOut.year << endl;
    }
};

// Searching object in an array - Returning Object from Function
Customer searchCustomer(Customer arr[], int size, int searchId) {
    for (int i = 0; i < size; i++) {
        if (arr[i].getID() == searchId) {
            return arr[i]; 
        }
    }
    return Customer("Not Found", 0, "", 0, 0, "", "");
}

// Sorting Objects in an array (Bubble Sort without built-in functions)
void sortRoomsByPrice(Room arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].getPrice() > arr[j + 1].getPrice()) {
                Room temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ======================================================
// MEMBER 2 START:
// Employee Classes, Bill (Friend), Exception Handling
// File Manager, Admin, Nested Class, Dynamic Memory
// ======================================================

class Employee : public Person {
protected:
    string designation;
    float salary;

public:
    Employee() : Person() {
        designation = "None";
        salary = 0;
    }

    Employee(string name, int id, string phone, string designation, float salary)
        : Person(name, id, phone) {
        this->designation = designation;
        this->salary = salary;
    }

    void display() override {
        cout << "\n--- Employee Details ---\n";
        cout << "Name: " << name << ", ID: " << id << ", Phone: " << phone << endl;
        cout << "Designation: " << designation << ", Salary: Rs." << salary << endl;
    }
};

class Receptionist : public Employee {
public:
    Receptionist()
        : Employee("Receptionist Staff", 201, "0300000000", "Receptionist", 30000) {}
};

class Manager : public Employee {
public:
    Manager()
        : Employee("Hotel Manager", 301, "0311111111", "Manager", 80000) {}
};

class InvalidBillException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid Bill Amount! Cannot be negative.";
    }
};

class Bill {
private:
    float roomCharges;
    float foodCharges;
    float serviceCharges;

public:
    Bill() {
        roomCharges = foodCharges = serviceCharges = 0;
    }

    Bill(float r, float f, float s) {
        if (r < 0 || f < 0 || s < 0)
            throw InvalidBillException();

        roomCharges = r;
        foodCharges = f;
        serviceCharges = s;
    }

    inline float calculateTotal() {
        return roomCharges + foodCharges + serviceCharges;
    }

    friend void generateBill(Bill b);
};

void generateBill(Bill b) {
    cout << "\n===== FINAL BILL =====\n";
    cout << "Total Bill = Rs." << b.calculateTotal() << endl;
}

class FileManager {
public:
    void saveData(string text) {
        ofstream file("hotel_data.txt", ios::app);
        if (file.is_open()) {
            file << text << endl;
            file.close();
            cout << "\nData Saved Successfully!\n";
        }
    }

    void readData() {
        ifstream file("hotel_data.txt");
        string line;

        cout << "\n===== FILE DATA =====\n";
        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "No saved data found.\n";
        }
    }
};

class Admin {
public:
    void adminPanel() {
        cout << "\n===== ADMIN PANEL =====\n";
        cout << "1. View Reports\n";
        cout << "2. Delete Records\n";
        cout << "3. Manage Staff\n";
        cout << "(Admin features under construction)\n";
    }
};

class Hotel {
public:
    class FoodService { // Nested Class
    public:
        void showMenu() {
            cout << "\n===== FOOD MENU =====\n";
            cout << "Breakfast = Rs.500\n";
            cout << "Lunch = Rs.800\n";
            cout << "Dinner = Rs.1200\n";
        }
    };
};

void dynamicMemoryDemo() {
    Employee* emp = new Receptionist();
    cout << "\n===== Dynamic Memory Demo =====\n";
    emp->display();
    delete emp;
}

// ======================================================
// MAIN FUNCTION (Integrated Menu)
// ======================================================

int main() {
    int choice;
    
    // Arrays of Objects
    Customer customerArr[5]; 
    int customerCount = 0;

    Room roomArr[3] = {
        Room(101, "Suite", 8000, true),
        Room(102, "Standard", 3000, true),
        Room(103, "Deluxe", 5000, true)
    };

    Receptionist receptionist;
    Manager manager;
    FileManager fileManager;
    Admin admin;
    Hotel::FoodService food;

    do {
        cout << "\n====================================\n";
        cout << "    HOTEL MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Customer (Array)\n";
        cout << "2. Search Customer by ID\n";
        cout << "3. View & Sort Rooms by Price\n";
        cout << "4. View Staff Details\n";
        cout << "5. Generate Bill (Exception Handling)\n";
        cout << "6. Save / Read File\n";
        cout << "7. Food Menu (Nested Class)\n";
        cout << "8. Admin Panel & Dynamic Memory\n";
        cout << "9. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (customerCount < 5) {
                customerArr[customerCount].addCustomer();
                customerCount++;
                cout << "Customer successfully added to system array.\n";
            } else {
                cout << "Customer storage is full!\n";
            }
            break;

        case 2: {
            int searchId;
            cout << "Enter Customer ID to search: ";
            cin >> searchId;
            Customer found = searchCustomer(customerArr, customerCount, searchId);
            found.display();
            break;
        }

        case 3:
            cout << "\n--- Rooms Before Sorting ---\n";
            for(int i = 0; i < 3; i++) roomArr[i].displayRoom();
            
            sortRoomsByPrice(roomArr, 3);
            
            cout << "\n--- Rooms After Sorting ---\n";
            for(int i = 0; i < 3; i++) roomArr[i].displayRoom();
            break;

        case 4:
            manager.display();
            receptionist.display();
            break;

        case 5:
            try {
                float r, f, s;
                cout << "Enter Room Charges: ";
                cin >> r;
                cout << "Enter Food Charges: ";
                cin >> f;
                cout << "Enter Service Charges: ";
                cin >> s;

                Bill b(r, f, s);
                generateBill(b);
            }
            catch (exception& e) {
                cout << "ERROR: " << e.what() << endl;
            }
            break;

        case 6:
            fileManager.saveData("System Accessed.");
            fileManager.readData();
            break;

        case 7:
            food.showMenu();
            break;

        case 8:
            admin.adminPanel();
            dynamicMemoryDemo();
            break;

        case 9:
            cout << "\nProgram Closed.\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 9);

    return 0;
}