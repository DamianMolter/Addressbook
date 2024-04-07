#include <iostream>
#include <string>
#include <windows.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Friend {
    int id;
    string name, surname, phoneNumber, address, mail;
};

string loadLine() {
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

void loadData(vector <Friend> &friends) {
    Friend singleContact;
    string line;
    int fragmentNumber = 1;

    fstream addressBook;
    addressBook.open("addressBook.txt", ios::in | ios::app);
    while(getline(addressBook, line)) {
        while(!line.empty()) {
            int borderPosition = line.find('|');
            string lineFragment = line.substr(0, borderPosition);

            switch(fragmentNumber) {
            case 1:
                singleContact.id = stoi(lineFragment);
                break;
            case 2:
                singleContact.name = lineFragment;
                break;
            case 3:
                singleContact.surname = lineFragment;
                break;
            case 4:
                singleContact.phoneNumber = lineFragment;
                break;
            case 5:
                singleContact.address = lineFragment;
                break;
            case 6:
                singleContact.mail = line;
                line.clear();
                fragmentNumber = 0;
                friends.push_back(singleContact);
                break;
            }
            line.erase(0, borderPosition + 1);
            fragmentNumber++;
        }
    }
    addressBook.close();
}

void addContactToAddressbook(vector <Friend> &friends) {
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

    friends.size() != 0 ? singleContact.id = friends[friends.size() - 1].id + 1 : singleContact.id = 1;

    addressBook.open("addressBook.txt", ios::out | ios::app);
    addressBook << singleContact.id << '|' << singleContact.name << '|' << singleContact.surname << '|';
    addressBook << singleContact.phoneNumber << '|' << singleContact.address << '|' << singleContact.mail << endl;
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
        cout << "Uzytkownik o podanym ID nie istnieje." << endl;
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
    switch(optionNumberToChange) {
    case 1:
        cout << "Podaj nowa wartosc." << endl;
        friends[contactPosition].name = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 2:
        cout << "Podaj nowa wartosc." << endl;
        friends[contactPosition].surname = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 3:
        cout << "Podaj nowa wartosc." << endl;
        friends[contactPosition].phoneNumber = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 4:
        cout << "Podaj nowa wartosc." << endl;
        friends[contactPosition].address = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 5:
        cout << "Podaj nowa wartosc." << endl;
        friends[contactPosition].mail = loadLine();
        cout << "Dane zostaly pomyslnie zmienione." << endl;
        break;
    case 6:
        break;
    }
}

void overwriteAddressbookFile (vector <Friend> friends) {

    fstream addressBook;
    addressBook.open("addressBook.txt", ios::out | ios::trunc);

    for(size_t i = 0; i < friends.size(); i++) {
        addressBook << friends[i].id << '|' << friends[i].name << '|' << friends[i].surname << '|';
        addressBook << friends[i].phoneNumber << '|' << friends[i].address << '|' << friends[i].mail << endl;
    }
    addressBook.close();
}

void editContact(vector <Friend> &friends) {

    cout << "Wybierz ID adresata: ";
    int contactPosition = findWantedID (friends);
    if(contactPosition >= 0) {
        displayContact(contactPosition, friends);
        displayEditMenu();
        changeData (contactPosition, friends);
        overwriteAddressbookFile (friends);
    }
}

void deleteContact(vector <Friend> &friends) {

    cout << "Wpisz ID uzytkownika:" << endl;
    int contactPosition = findWantedID (friends);
    if(contactPosition >= 0) {
        displayContact(contactPosition, friends);
        cout << "Czy jestes pewien, ze chcesz usunac wybrany kontakt?" << endl;
        char decision;
        cin >> decision;
        switch(decision) {
        case 't':
            friends.erase(friends.begin() + contactPosition);
            cout << "Kontakt pomyslnie usuniety" << endl;
            system("pause");
            break;
        case 'n':
            break;
        }
        overwriteAddressbookFile (friends);
    }
}

int main() {
    int menuOptionNumber;
    vector <Friend> friends;
    loadData(friends);

    while(1) {
        system("cls");
        cout << "KSIAZKA ADRESOWA by MOLTER IT SOLUTIONS " << endl;
        cout << "Witaj w ksiazce adresowej Przyjacielu! Wybierz madrze!" << endl;
        cout << "1. Dodaj kontakt." << endl;
        cout << "2. Wyszukaj po imieniu." << endl;
        cout << "3. Wyszukaj po nazwisku." << endl;
        cout << "4. Wyswietl wszystkie kontakty." << endl;
        cout << "5. Usun adresata." << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zakoncz program." << endl << endl;

        cin >> menuOptionNumber;
        cout << endl;

        switch(menuOptionNumber) {
        case 1:
            addContactToAddressbook(friends);
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
            deleteContact(friends);
            break;

        case 6:
            editContact(friends);
            break;

        case 7:
            cout << "Pomyslnie sie wylogowales. Do zobaczenia :)" << endl;
            return 0;

        default:
            cout << "Wybierz wlasciwa pozycje menu!" << endl;
            sleep(1);
            break;
        }
    }
}
