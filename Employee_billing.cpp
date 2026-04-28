
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
using namespace std;

// ======================================================

// ======================================================

// Employee Classes, Bill (Friend), Exception Handling
// File Manager, Admin, Nested Class, Dynamic Memory
// ======================================================

// -------------------------------------------------------
// c. i.  Inheritance (Single) — Employee inherits Person
//    ii. Function Overriding   — display() overridden
// a. iii. Access Specifiers    — 'protected' salary/designation
//         so subclasses (Receptionist, Manager) can inherit them
// -------------------------------------------------------
class Employee : public Person {    // c.i. Single Inheritance
protected:                          // a.iii. Access Specifier: protected
    string designation;
    float salary;

public:
    // b. i.  Default Constructor
    //    v.  Initialization List
    Employee() : Person() {         // b.v. Initialization List
        designation = "None";
        salary = 0;
    }

    // b. i.  Parameterized Constructor
    //    v.  Initialization List — passes name/id/phone to Person
    Employee(string name, int id, string phone, string designation, float salary)
        : Person(name, id, phone) { // b.v. Initialization List
        this->designation = designation;    // e.v. 'this' pointer
        this->salary = salary;
    }

    // c. ii. Function Overriding — overrides Person::display()
    void display() override {
        cout << "\n--- Employee Details ---\n";
        cout << "Name: " << name << ", ID: " << id << ", Phone: " << phone << endl;
        cout << "Designation: " << designation << ", Salary: Rs." << salary << endl;
    }
};

// -------------------------------------------------------
// c. i. Inheritance (Multilevel) — Receptionist → Employee → Person
//        Three levels deep: grandchild inherits grandparent's members
// -------------------------------------------------------
class Receptionist : public Employee {  // c.i. Multilevel Inheritance (level 3)
public:
    // b. i. Default Constructor — delegates to Employee's parameterized ctor
    Receptionist()
        : Employee("Receptionist Staff", 201, "0300000000", "Receptionist", 30000) {}
};

// -------------------------------------------------------
// c. i. Inheritance (Multilevel) — Manager → Employee → Person
// -------------------------------------------------------
class Manager : public Employee {       // c.i. Multilevel Inheritance (level 3)
public:
    Manager()
        : Employee("Hotel Manager", 301, "0311111111", "Manager", 80000) {}
};

// -------------------------------------------------------
// h. Exception Handling in OOP
//    iv. Custom Exception Classes — InvalidBillException
//        inherits std::exception and overrides what()
//    iii. Standard Exceptions — uses exception base class
// -------------------------------------------------------
class InvalidBillException : public exception {     // h.iv. Custom Exception
public:
    // h. i. try, Catch, Throw — what() is called inside catch block
    const char* what() const noexcept override {
        return "Invalid Bill Amount! Cannot be negative.";
    }
};

// -------------------------------------------------------
// a.  i.   Classes and Objects — Bill encapsulates charge data
//     iv.  Encapsulation — all charge fields are private
// d.  i.   Friend Functions — generateBill() declared as friend,
//          granting it direct access to private members
//     iv.  Inline Member Functions — calculateTotal() is inline
// -------------------------------------------------------
class Bill {
private:                            // a.iii. Access Specifier: private
    float roomCharges;
    float foodCharges;
    float serviceCharges;

public:
    // b. i. Default Constructor
    Bill() {
        roomCharges = foodCharges = serviceCharges = 0;
    }

    // -------------------------------------------------------
    // b. i.  Parameterized Constructor
    // h. i.  throw — throws custom exception if any value < 0
    // -------------------------------------------------------
    Bill(float r, float f, float s) {
        if (r < 0 || f < 0 || s < 0)
            throw InvalidBillException();   // h.i. throw custom exception

        roomCharges = r;
        foodCharges = f;
        serviceCharges = s;
    }

    // d. iv. Inline Member Function — 'inline' suggests compiler
    //        substitute the function body at call site (avoids
    //        function-call overhead for small, frequently used fn)
    inline float calculateTotal() {
        return roomCharges + foodCharges + serviceCharges;
    }

    // d. i. Friend Function Declaration — generateBill() is not
    //       a member but is granted access to private members
    friend void generateBill(Bill b);
};

// -------------------------------------------------------
// d. i. Friend Function — defined outside the class but can
//       access Bill's private members (roomCharges, etc.)
//       directly via the object parameter
// -------------------------------------------------------
void generateBill(Bill b) {
    cout << "\n===== FINAL BILL =====\n";
    cout << "Total Bill = Rs." << b.calculateTotal() << endl;
}

// -------------------------------------------------------
// g. File Handling with OOP
//    i.   File Streams — ofstream (write/append), ifstream (read)
//    ii.  Reading and Writing Objects to Files
//    iv.  File-based Object Persistence — data survives restarts
// -------------------------------------------------------
class FileManager {
public:
    // g. i. ofstream — output file stream opened in append mode
    void saveData(string text) {
        ofstream file("hotel_data.txt", ios::app);  // g.i. ofstream
        if (file.is_open()) {
            file << text << endl;           // g.ii. Writing data to file
            file.close();
            cout << "\nData Saved Successfully!\n";
        }
    }

    // g. i. ifstream — input file stream for reading
    void readData() {
        ifstream file("hotel_data.txt");    // g.i. ifstream
        string line;

        cout << "\n===== FILE DATA =====\n";
        if (file.is_open()) {
            while (getline(file, line)) {   // g.ii. Reading line by line
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "No saved data found.\n";
        }
    }
};

// a. i. Classes and Objects — standalone Admin utility class
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

// -------------------------------------------------------
// d. v. Nested Classes — FoodService is declared inside Hotel,
//       logically grouping it as part of the Hotel concept.
//       Accessed externally as Hotel::FoodService.
// -------------------------------------------------------
class Hotel {
public:
    class FoodService {             // d.v. Nested Class
    public:
        void showMenu() {
            cout << "\n===== FOOD MENU =====\n";
            cout << "Breakfast = Rs.500\n";
            cout << "Lunch = Rs.800\n";
            cout << "Dinner = Rs.1200\n";
        }
    };
};

// -------------------------------------------------------
// e. iii. Pointers to Objects — Employee* base pointer holds
//          a Receptionist (derived) object
//    iv.  Dynamic Memory Allocation — 'new' allocates on heap;
//         'delete' releases it to prevent memory leaks
// c. iii. Runtime Polymorphism — emp->display() calls
//         Receptionist::display() (resolved at runtime)
//    iv.  Dynamic Binding — correct vtable entry used at runtime
// -------------------------------------------------------
void dynamicMemoryDemo() {
    Employee* emp = new Receptionist(); // e.iii. Pointer to Object
                                        // e.iv.  'new' — heap allocation
                                        // c.iii. Runtime Polymorphism

    cout << "\n===== Dynamic Memory Demo =====\n";
    emp->display();                     // c.iv. Dynamic Binding — Receptionist::display()

    delete emp;                         // e.iv. 'delete' — heap deallocation
                                        // b.iv. Destructor called automatically
}

// ======================================================
// MAIN FUNCTION (Integrated Menu)
// ======================================================

// -------------------------------------------------------
// a. v. Objects as Variables and Memory Representation
//       — all objects below are stack-allocated
// f. i. Array of Objects — customerArr[] and roomArr[]
//    ii. Objects as Array Elements
// -------------------------------------------------------
int main() {
    int choice;

    // f. i. Array of Objects — holds up to 5 Customer objects on the stack
    Customer customerArr[5];        // f.i. Array of Objects
    int customerCount = 0;

    // f. i. & ii. Array of Room Objects initialized with parameterized constructors
    Room roomArr[3] = {
        Room(101, "Suite", 8000, true),
        Room(102, "Standard", 3000, true),
        Room(103, "Deluxe", 5000, true)
    };

    
