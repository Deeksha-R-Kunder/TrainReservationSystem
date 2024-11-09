#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>  // for rand()
#include <limits>   // for input validation

using namespace std;

const string ADMIN_PASSWORD = "PASSWORD";  // Hard-coded admin password for simplicity

class Train {
private:
    int trainno, nofafseat, nofasseat, noffsseat, nofacseat, nofssseat;
    char trainname[60], startingpoint[60], destination[60];
public:
    Train() {
        trainno = 0;
        nofafseat = nofasseat = noffsseat = nofacseat = nofssseat = 0;
        strcpy(trainname, "");
        strcpy(startingpoint, "");
        strcpy(destination, "");
    }

    void input();
    void display() const;
    int returnTrainNo() const { return trainno; }
    void updateSeats(int af, int as, int fs, int ac, int ss);
};

void Train::input() {
    cout << "Enter Train Number: ";
    cin >> trainno;
    cout << "Enter Train Name: ";
    cin.ignore();
    cin.getline(trainname, 60);
    cout << "Enter Starting Point: ";
    cin.getline(startingpoint, 60);
    cout << "Enter Destination: ";
    cin.getline(destination, 60);
    cout << "Enter Number of A/C First Class Seats: ";
    cin >> nofafseat;
    cout << "Enter Number of A/C Second Class Seats: ";
    cin >> nofasseat;
    cout << "Enter Number of First Class Sleeper Seats: ";
    cin >> noffsseat;
    cout << "Enter Number of A/C Chair Car Seats: ";
    cin >> nofacseat;
    cout << "Enter Number of Second Class Sleeper Seats: ";
    cin >> nofssseat;
}

void Train::display() const {
    cout << "Train Number: " << trainno << endl;
    cout << "Train Name: " << trainname << endl;
    cout << "Starting Point: " << startingpoint << endl;
    cout << "Destination: " << destination << endl;
    cout << "Available A/C First Class Seats: " << nofafseat << endl;
    cout << "Available A/C Second Class Seats: " << nofasseat << endl;
    cout << "Available First Class Sleeper Seats: " << noffsseat << endl;
    cout << "Available A/C Chair Car Seats: " << nofacseat << endl;
    cout << "Available Second Class Sleeper Seats: " << nofssseat << endl;
}

void Train::updateSeats(int af, int as, int fs, int ac, int ss) {
    nofafseat -= af;
    nofasseat -= as;
    noffsseat -= fs;
    nofacseat -= ac;
    nofssseat -= ss;
}

class Ticket {
private:
    int resNo, trainNo, age;
    char passengerName[60], status[40], classType[20];
public:
    Ticket() : resNo(0), trainNo(0), age(0) {
        strcpy(passengerName, "");
        strcpy(status, "Booked");
        strcpy(classType, "");
    }

    void bookTicket(int tNo);
    void display() const;
    int getReservationNo() const { return resNo; }
};

void Ticket::bookTicket(int tNo) {
    resNo = rand() % 10000 + 1000;
    trainNo = tNo;
    cout << "Enter Passenger Name: ";
    cin.ignore();
    cin.getline(passengerName, 60);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Class Type (A/C First Class, A/C Second Class, Sleeper, Chair Car, Second Class Sleeper): ";
    cin.ignore();
    cin.getline(classType, 20);
    strcpy(status, "Booked");
    cout << "Ticket booked successfully! Your reservation number is " << resNo << endl;
}

void Ticket::display() const {
    cout << "Reservation Number: " << resNo << endl;
    cout << "Passenger Name: " << passengerName << endl;
    cout << "Age: " << age << endl;
    cout << "Train Number: " << trainNo << endl;
    cout << "Class Type: " << classType << endl;
    cout << "Status: " << status << endl;
}


class User {
private:
    char username[60];
    char password[60];
public:
    void signup();
    bool login();
    void changePassword();
    bool isUsernameExists(const char* uname);
};

bool User::isUsernameExists(const char* uname) {
    ifstream userFile("users.dat", ios::binary);
    User user;
    while (userFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        if (strcmp(user.username, uname) == 0) {
            userFile.close();
            return true;
        }
    }
    userFile.close();
    return false;
}

void User::signup() {
    cout << "Enter a username: ";
    cin.ignore();
    cin.getline(username, 60);

    if (isUsernameExists(username)) {
        cout << "Username already exists. Please choose a different username.\n";
        cout << "Press Enter to return to the main menu.";
        cin.get();
        return;
    }

    cout << "Enter a password: ";
    cin.getline(password, 60);

    ofstream userFile("users.dat", ios::binary | ios::app);
    userFile.write(reinterpret_cast<char*>(this), sizeof(User));
    userFile.close();
    cout << "Signup successful! You can now log in.\n";
    cout << "Press Enter to return to the main menu.";
    cin.get();
}

bool User::login() {
    char inputUsername[60], inputPassword[60];
    cout << "Enter your username: ";
    cin.ignore();
    cin.getline(inputUsername, 60);
    cout << "Enter your password: ";
    cin.getline(inputPassword, 60);

    ifstream userFile("users.dat", ios::binary);
    User user;
    while (userFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        if (strcmp(user.username, inputUsername) == 0 && strcmp(user.password, inputPassword) == 0) {
            cout << "Login successful!\n";
            return true;
        }
    }
    userFile.close();
    cout << "Invalid credentials. Returning to the main menu.\n";
    cout << "Press Enter to return to the main menu.";
    cin.get();
    return false;
}

void User::changePassword() {
    char inputUsername[60], oldPassword[60], newPassword[60];
    cout << "Enter your username: ";
    cin.ignore();
    cin.getline(inputUsername, 60);
    cout << "Enter your current password: ";
    cin.getline(oldPassword, 60);

    fstream userFile("users.dat", ios::binary | ios::in | ios::out);
    User user;
    bool found = false;
    int pos;
    while (userFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        pos = userFile.tellg();
        if (strcmp(user.username, inputUsername) == 0 && strcmp(user.password, oldPassword) == 0) {
            found = true;
            cout << "Enter your new password: ";
            cin.getline(newPassword, 60);
            strcpy(user.password, newPassword);
            userFile.seekp(pos - sizeof(User));
            userFile.write(reinterpret_cast<char*>(&user), sizeof(User));
            cout << "Password changed successfully!\n";
            break;
        }
    }
    if (!found) {
        cout << "Username or current password is incorrect.\n";
    }
    userFile.close();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void addTrain() {
    Train tr;
    ofstream file("trains.dat", ios::binary | ios::app);
    tr.input();
    file.write(reinterpret_cast<char*>(&tr), sizeof(tr));
    file.close();
    cout << "Train added successfully!\n";
}

void showTrains() {
    Train tr;
    ifstream file("trains.dat", ios::binary);
    if (!file) {
        cout << "No trains found!\n";
        return;
    }
    while (file.read(reinterpret_cast<char*>(&tr), sizeof(tr))) {
        tr.display();
        cout << "-----------------------------\n";
    }
    file.close();

    cout << "Press Enter to return to the admin menu.";
    cin.ignore();
    cin.get();
}

void bookTicket() {
    int trainNo;
    cout << "Enter Train Number for Booking: ";
    cin >> trainNo;

    ifstream file("trains.dat", ios::binary);
    Train tr;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&tr), sizeof(tr))) {
        if (tr.returnTrainNo() == trainNo) {
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Train not found!\n";
        return;
    }

    Ticket ticket;
    ticket.bookTicket(trainNo);

    ofstream tFile("tickets.dat", ios::binary | ios::app);
    tFile.write(reinterpret_cast<char*>(&ticket), sizeof(ticket));
    tFile.close();
}

void viewTicket() {
    int resNo;
    cout << "Enter Reservation Number: ";
    cin >> resNo;

    Ticket ticket;
    ifstream file("tickets.dat", ios::binary);
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&ticket), sizeof(ticket))) {
        if (ticket.getReservationNo() == resNo) {
            ticket.display();
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Ticket not found!\n";
    }
}

int main() {
    int choice;
    do {
        //clearScreen();
        cout << "TRAIN RESERVATION SYSTEM\n";
        cout << "1. Admin Login\n";
        cout << "2. Passenger Signup\n";
        cout << "3. Passenger Login\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string password;
            cout << "Enter Admin Password: ";
            cin >> password;
            if (password == ADMIN_PASSWORD) {
                int adminChoice;
                do {
                    clearScreen();
                    cout << "ADMIN MENU\n";
                    cout << "1. Add Train\n";
                    cout << "2. View All Trains\n";
                    cout << "3. Back\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1: addTrain(); break;
                    case 2: showTrains(); break;
                    case 3: break;
                    default: cout << "Invalid choice.\n";
                    }
                } while (adminChoice != 3);
            } else {
                cout << "Incorrect password.\n";
            }
            break;
        }
        case 2: {
            User user;
            user.signup();
            break;
        }
        case 3: {
            User user;
            if (user.login()) {
                int userChoice;
                do {
                    //clearScreen();
                    cout << "PASSENGER MENU\n";
                    cout << "1. Book Ticket\n";
                    cout << "2. View Ticket\n";
                    cout << "3. Change Password\n";
                    cout << "4. Back\n";
                    cout << "Enter your choice: ";
                    cin >> userChoice;

                    switch (userChoice) {
                    case 1: bookTicket(); break;
                    case 2: viewTicket(); break;
                    case 3: user.changePassword(); break;
                    case 4: break;
                    default: cout << "Invalid choice.\n";
                    }
                } while (userChoice != 4);
            }
            break;
        }
        case 4: cout << "Thank you for using the Train Reservation System.\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}