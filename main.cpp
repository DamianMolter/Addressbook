#include <iostream>
#include <string>
#include <windows.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

struct Friend {
    int id;
    string name, surname, phoneNumber, address, mail;
};

struct User {
    int id;
    string login, password;
};

string loadLine() {
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

vector <Friend> loadData(int loggedUserId) {
    Friend singleContact;
    vector <Friend> friends;
    string line;
    int fragmentNumber = 1;
    int ownerOfContactId;

    fstream addressBook;
    addressBook.open("addressBook.txt", ios::in | ios::app);
    while(getline(addressBook, line)) {
        while(!line.empty()) {
            int verticalBarPosition = line.find('|');
            string lineFragment = line.substr(0, verticalBarPosition);
            switch(fragmentNumber) {
            case 1:
                singleContact.id = stoi(lineFragment);
                break;
            case 2:
                ownerOfContactId = stoi(lineFragment);
                break;
            case 3:
                singleContact.name = lineFragment;
                break;
            case 4:
                singleContact.surname = lineFragment;
                break;
            case 5:
                singleContact.phoneNumber = lineFragment;
                break;
            case 6:
                singleContact.address = lineFragment;
                break;
            case 7:
                singleContact.mail = line.substr(0, line.find('|'));
                line.clear();
                fragmentNumber = 0;
                if(ownerOfContactId == loggedUserId) {
                    friends.push_back(singleContact);
                }
                break;
            }
            line.erase(0, verticalBarPosition + 1);
            fragmentNumber++;
        }
    }
    addressBook.close();
    return friends;
}

int countAllContacts() {

    fstream addressBook;
    string line;
    size_t verticalBarPosition;
    int contactCount = 0;
    addressBook.open("addressBook.txt", ios::in);
    while(getline(addressBook, line)) {
        verticalBarPosition = line.find('|');
        contactCount = stoi(line.substr(0, verticalBarPosition));
    }
    addressBook.close();

    return contactCount;
}

void addContactToAddressbook(vector <Friend> &friends, int loggedUserId, int contactCount) {
    Friend singleContact;
    fstream addressBook;

    cout << "Podaj imie: " << endl;
    singleContact.name = loadLine();
    cout << "Podaj nazwisko: " << endl;
    singleContact.surname = loadLine();
    cout << "Podaj numer telefonu: " << endl;
    singleContact.phoneNumber = loadLine();
    cout << "Podaj adres zamieszkania: " << endl;
    singleContact.address = loadLine();
    cout << "Podaj adres e-mail: " << endl;
    singleContact.mail = loadLine();
    singleContact.id = countAllContacts() + 1;

    addressBook.open("addressBook.txt", ios::out | ios::app);
    addressBook << singleContact.id << '|' << loggedUserId << '|' << singleContact.name << '|' << singleContact.surname << '|';
    addressBook << singleContact.phoneNumber << '|' << singleContact.address << '|' << singleContact.mail  << "|" << endl;
    addressBook.close();

    friends.push_back(singleContact);

    cout << "Kontakt pomyslnie dodany. ";
    sleep(1);
}

void displayContact(size_t contactPosition, vector <Friend> &friends) {
    cout << "Id: "<< friends[contactPosition].id << endl;
    cout << "Imie: " << friends[contactPosition].name << endl;
    cout << "Nazwisko: " << friends[contactPosition].surname << endl;
    cout << "Numer telefonu: " << friends[contactPosition].phoneNumber << endl;
    cout << "Adres zamieszkania: " << friends[contactPosition].address << endl;
    cout << "Adres e-mail: " << friends[contactPosition].mail << endl << endl;
}

void displayAllContacts(vector <Friend> friends) {

    for(size_t i = 0; i < friends.size(); i++) {
        displayContact(i, friends);
    }
    cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego." << endl;
    system("pause");
}

void searchContactByName(vector <Friend> &friends) {
    cout << "Wpisz wyszukiwana fraza:" << endl;
    string nameToFindInAddressbook = loadLine();
    cout << endl;
    for(size_t i = 0; i < friends.size(); i++) {
        if(friends[i].name == nameToFindInAddressbook) {
            displayContact(i, friends);
        }
    }
    cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego." << endl;
    system("pause");
}

void searchContactBySurname(vector <Friend> &friends) {
    cout << "Wpisz wyszukiwana fraza:" << endl;
    string surnameToFindInAddressbook = loadLine();
    cout << endl;
    for(size_t i = 0; i < friends.size(); i++) {
        if(friends[i].surname == surnameToFindInAddressbook) {
            displayContact(i, friends);
        }
    }
    cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego." << endl;
    system("pause");
}

int findWantedID (vector <Friend> &friends) {

    int wantedID;
    bool existenceInAddressbook = 0;
    cin >> wantedID;
    for(size_t i = 0; i < friends.size(); i++) {

        if(friends[i].id == wantedID) {
            wantedID = i;
            existenceInAddressbook = 1;
            break;
        }
    }

    if (!existenceInAddressbook) {
        cout << "Adresat o podanym ID nie istnieje." << endl;
        cout << "Wcisnij dowolny przycisk, aby powrocic do menu glownego." << endl;
        system("pause");
        return -1;
    }
    return wantedID;
}

void displayEditMenu() {

    cout << "Ktora informacje chcesz zmienic?" << endl;
    cout << "1. Imie." << endl;
    cout << "2. Nazwisko." << endl;
    cout << "3. Numer telefonu." << endl;
    cout << "4. Adres zamieszkania." << endl;
    cout << "5. Adres email." << endl;
    cout << "6. Powrot do menu." << endl;
}

void changeData (int contactPosition, vector <Friend> &friends) {

    int optionNumberToChange;
    cin >> optionNumberToChange;
    cout << "Podaj nowa wartosc." << endl;
    switch(optionNumberToChange) {
    case 1:
        friends[contactPosition].name = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 2:
        friends[contactPosition].surname = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 3:
        friends[contactPosition].phoneNumber = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 4:
        friends[contactPosition].address = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 5:
        friends[contactPosition].mail = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 6:
        break;
    default:
        cout << "Wybierz wlasciwa pozycje menu!" << endl;
        sleep(1);
        break;
    }
}

void editAddressbookFile (vector <Friend> friends, int contactPosition, int loggedUserId) {

    fstream newAddressBook, oldAddressBook;
    string line;
    oldAddressBook.open("addressBook.txt", ios::in);
    newAddressBook.open("addressBook_new.txt", ios::out);
    while(getline(oldAddressBook, line)) {
        size_t firstVerticalBarPosition = line.find('|');
        int contactId = stoi(line.substr(0, firstVerticalBarPosition));
        if(friends[contactPosition].id == contactId) {
            newAddressBook << friends[contactPosition].id << '|' << loggedUserId << '|'<< friends[contactPosition].name << '|';
            newAddressBook << friends[contactPosition].surname << '|' << friends[contactPosition].phoneNumber << '|';
            newAddressBook << friends[contactPosition].address << '|' << friends[contactPosition].mail << endl;
        } else {
            newAddressBook << line << endl;
        }
    }
    oldAddressBook.close();
    newAddressBook.close();
    remove("addressBook.txt");
    rename("addressBook_new.txt", "addressBook.txt");
}

void editContact(vector <Friend> &friends, int loggedUserId) {

    cout << "Wybierz ID adresata: ";
    int contactPosition = findWantedID (friends);
    if(contactPosition >= 0) {
        displayContact(contactPosition, friends);
        displayEditMenu();
        changeData (contactPosition, friends);
        editAddressbookFile (friends, contactPosition, loggedUserId);
    }
}

void deleteFromAddressbookFile (vector <Friend> friends, int contactPosition, int loggedUserId) {

    fstream newAddressBook, oldAddressBook;
    string line;
    oldAddressBook.open("addressBook.txt", ios::in);
    newAddressBook.open("addressBook_new.txt", ios::out | ios::trunc);
    while(getline(oldAddressBook, line)) {
        size_t firstVerticalBarPosition = line.find('|');
        int contactId = stoi(line.substr(0, firstVerticalBarPosition));
        if(friends[contactPosition].id != contactId) {
            newAddressBook << line << endl;
        }
    }
    oldAddressBook.close();
    newAddressBook.close();
    remove("addressBook.txt");
    rename("addressBook_new.txt", "addressBook.txt");
}

void deleteContact(vector <Friend> &friends, int loggedUserId) {

    cout << "Wpisz ID uzytkownika:" << endl;
    int contactPosition = findWantedID (friends);
    if(contactPosition >= 0) {
        displayContact(contactPosition, friends);
        cout << "Czy jestes pewien, ze chcesz usunac wybrany kontakt?" << endl;
        char decision;
        cin >> decision;
        switch(decision) {
        case 't':
            deleteFromAddressbookFile (friends,contactPosition, loggedUserId);
            friends.erase(friends.begin() + contactPosition);
            cout << "Kontakt pomyslnie usuniety" << endl;
            system("pause");
            break;
        case 'n':
            break;
        }
    }
}

vector <User> loadAllUsers() {

    User user;
    vector <User> users;
    fstream usersList;
    string line;
    int fragmentNumber = 1;
    usersList.open("users.txt", ios::in);
    while(getline(usersList, line)) {
        while(!line.empty()) {
            int verticalBarPosition = line.find('|');
            string lineFragment = line.substr(0, verticalBarPosition);
            switch(fragmentNumber) {
            case 1:
                user.id = stoi(lineFragment);
                break;
            case 2:
                user.login = lineFragment;
                break;
            case 3:
                user.password = line;
                line.clear();
                fragmentNumber = 0;
                users.push_back(user);
                break;
            }
            line.erase(0, verticalBarPosition + 1);
            fragmentNumber++;
        }
    }
    usersList.close();
    return users;
}

bool checkRepeatingLogin(vector <User> users, string login) {
    bool decision;
    for (size_t i = 0; i < users.size(); i++) {
        if(users[i].login == login) {
            decision = true;
            break;
        } else {
            decision = false;
        }
    }
    return decision;
}

void saveNewUserInFile(size_t userId, string login, string password){
    fstream usersList;
    usersList.open("users.txt", ios::app);
    usersList << userId << "|" << login << "|" << password << endl;
    usersList.close();
}

void registerNewUser() {
    size_t userId;
    string login, password;
    User user;
    vector <User> users = loadAllUsers();
    system("cls");
    cout << "KSIAZKA ADRESOWA by MOLTER IT SOLUTIONS " << endl;
    cout << "Podaj login:" << endl;
    cin >> login;
    while(checkRepeatingLogin(users, login)) {
        cout << "Podany login jest juz zajety, podaj inny!" << endl;
        cin >> login;
    }
    cout << "Podaj haslo:" << endl;
    cin >> password;
    cout << "Konto zostalo pomyslnie zalozone" << endl;
    users.size() != 0 ? userId = users[users.size() - 1].id + 1 : userId = 1;
    system("pause");
    saveNewUserInFile(userId, login, password);
}

int checkCorrectLoginAndPassword(vector <User> users,string login,string password) {
    int loggedUserId;
    for(size_t i = 0; i < users.size(); i++) {
        if(users[i].login == login && users[i].password == password) {
            loggedUserId = users[i].id;
            break;
        } else {
            loggedUserId = -1;
        }
    }
    return loggedUserId;
}

int loginToAddressbook (vector <User> users) {
    string login, password;
    int loggedUserId = -1;
    do {
        cout << "Podaj login (Wpisz 0 aby wrocic do glownego menu.):" << endl;
        cin >> login;
        if(login == "0") {
            break;
        }
        cout << "Podaj haslo:" << endl;
        cin >> password;
        cout << "Dane logowania niepoprawne! Sproboj ponownie!" << endl;
        loggedUserId = checkCorrectLoginAndPassword(users, login, password);
    } while(loggedUserId < 0);
    return loggedUserId;
}

int findUserPosition (vector <User> users, int loggedUserId) {
    bool existenceInUsersList = 0;
    for(size_t i = 0; i < users.size(); i++) {
        if(users[i].id == loggedUserId) {
            loggedUserId = i;
            existenceInUsersList = 1;
            break;
        }
    }
    if (!existenceInUsersList) {
        cout << "Uzytkownik o podanym ID nie istnieje." << endl;
        cout << "Wcisnij dowolny przycisk, aby powrocic do menu glownego." << endl;
        system("pause");
        return -1;
    }
    return loggedUserId;
}

void overwriteUsersList (vector <User> users) {
    fstream userList;
    userList.open("users.txt", ios::out | ios::trunc);
    for(size_t i = 0; i < users.size(); i++) {
        userList << users[i].id << '|' << users[i].login << '|' << users[i].password << endl;
    }
    userList.close();
}

void changePassword (int loggedUserId) {
    vector <User> users = loadAllUsers();
    int userPosition = findUserPosition(users, loggedUserId);
    string newPassword;
    cout << "Podaj nowe haslo" << endl;
    cin >> newPassword;
    users[userPosition].password = newPassword;
    cout << "Haslo zostalo zmienione!" << endl;
    overwriteUsersList(users);
    system("pause");

}

int addressBookMainMenu(int loggedUserId) {
    int contactCount = countAllContacts();
    int addressBookOptionNumber;
    vector <Friend> friends = loadData(loggedUserId);
    while(1) {
        system("cls");
        cout << "KSIAZKA ADRESOWA by MOLTER IT SOLUTIONS " << endl;
        cout << "Id zalogowanego uzytkownika: " << loggedUserId << endl;
        cout << "Witaj w ksiazce adresowej! Powiedz Przyjacielu i wejdz!!" << endl;
        cout << "1. Dodaj kontakt." << endl;
        cout << "2. Wyszukaj po imieniu." << endl;
        cout << "3. Wyszukaj po nazwisku." << endl;
        cout << "4. Wyswietl wszystkie kontakty." << endl;
        cout << "5. Usun adresata." << endl;
        cout << "6. Edytuj adresata." << endl;
        cout << "7. Zmien haslo." << endl;
        cout << "8. Wyloguj sie." << endl << endl;

        cin >> addressBookOptionNumber;
        cout << endl;

        switch(addressBookOptionNumber) {
        case 1:
            addContactToAddressbook(friends, loggedUserId, contactCount);
            break;

        case 2:
            searchContactByName(friends);
            break;

        case 3:
            searchContactBySurname(friends);
            break;

        case 4:
            displayAllContacts(friends);
            break;

        case 5:
            deleteContact(friends, loggedUserId);
            break;

        case 6:
            editContact(friends, loggedUserId);
            break;

        case 7:
            changePassword(loggedUserId);
            break;

        case 8:
            cout << "Pomyslnie sie wylogowales. Do zobaczenia :)" << endl;
            return 0;

        default:
            cout << "Wybierz wlasciwa pozycje menu!" << endl;
            sleep(1);
            break;
        }
    }

}


int main() {

    int loginMenuOptionNumber;
    int loggedUserId = -1;
    vector <User> users = loadAllUsers();

    while(1) {
        system("cls");
        cout << "KSIAZKA ADRESOWA by MOLTER IT SOLUTIONS " << endl;
        cout << "Witaj w ksiazce adresowej! Powiedz Przyjacielu i wejdz!" << endl;
        cout << "1. Logowanie." << endl;
        cout << "2. Rejestracja." << endl;
        cout << "3. Wyjdz z programu." << endl;

        cin >> loginMenuOptionNumber;
        switch(loginMenuOptionNumber) {

        case 1:
            loggedUserId = loginToAddressbook(users);
            if(loggedUserId > 0) {
                addressBookMainMenu(loggedUserId);
            };
            break;
        case 2:
            registerNewUser();
            break;
        case 3:
            cout << "Do zobaczenia wkrotce :)" << endl;
            return 0;
        default:
            cout << "Wybierz wlasciwa pozycje menu!" << endl;
            sleep(1);
            break;
        }
    }
}
