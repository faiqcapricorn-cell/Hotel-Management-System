// ======================================================
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
