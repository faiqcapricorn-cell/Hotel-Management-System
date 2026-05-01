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

