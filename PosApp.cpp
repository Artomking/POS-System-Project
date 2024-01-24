/* Citation and Sources...
Final Project Milestone 5
Module: PosApp
Filename: PosApp.cpp
Version 1.0
Author Artom Zabihi
Revision History
-----------------------------------------------------------
 Preliminary release: April 6th, 2023
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#include "PosApp.h"
using namespace std;

namespace sdds {
    PosApp::PosApp(const char* string){
        if (strlen(string) <= MAX_FILENAME_LENGTH) {
            m_filename = new char[strlen(string) + 1];
            strcpy(m_filename, string);
        } else m_filename = nullptr;
        m_numItems = 0;
    };

    void PosApp::menu() {
        int choice = -1;
        bool exit = false;

        do {
            cout << "The Sene-Store" << endl;
            cout << "1- List items\n2- Add item\n3- Remove item\n4- Stock item\n5- POS\n0- exit program\n> ";

            do {
                if (!(cin >> choice)) {
                    choice = -1;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid Integer, try again: ";
                } else if (choice < 0 || choice > 5) {
                    cout << "[0<=value<=5], retry: > ";
                }
            } while (choice < 0 || choice > 5);

            switch (choice) {
                case 0:
                    exit = true;
                    break;
                case 1:
                    listItems(true);
                    break;
                case 2:
                    addItem();
                    break;
                case 3:
                    removeItem();
                    break;
                case 4:
                    stockItem();
                    break;
                case 5:
                    pos();
                    break;
            }
        } while (!exit);
    }

    int PosApp::listItems(bool listItem) {
        double total = 0;
        int choice = 0;
        if (!listItem){
            actionTitle("Item Selection by row number");
            cout << "Press <ENTER> to start....";
            cin.ignore(1000 ,'\n');
            while (cin.get() != '\n');
        }

        actionTitle("Listing Items");
        sort();

        cout.fill(' ');
        cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
        cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
        for (int i = 0; i < m_numItems; i++){
            cout.width(4);
            cout << right << i+1;
            cout << " | ";
            m_items[i]->displayType(POS_LIST);
            m_items[i]->write(cout);
            cout << endl;
            total = operator+=(total, *m_items[i]);
        }
        cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
        if (listItem) {
            cout << "                               Total Asset: $  |";
            cout.width(14);
            cout.setf(ios::right);
            cout.precision(2);
            cout << total;
            cout.unsetf(ios::right);
            cout << "|" << endl << "-----------------------------------------------^--------------^" << endl << endl;
        } else {
            cout << "Enter the row number: ";
            while (choice < 1 || choice > m_numItems) {
                if (!(cin >> choice)) {
                    choice = 0;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid Integer, try again: ";
                } else if (choice < 1 || choice > m_numItems) {
                    cout << "[1<=value<=" << m_numItems << "], retry: Enter the row number: ";
                }
            }
        }
        return choice;
    }

    void PosApp::sort() {
        for (int i = 0; i < m_numItems-1; i++){
            for (int j = 0; j < m_numItems-i-1; j++){
                if (m_items[j]->operator>(m_items[j+1])){
                    auto temp = m_items[j];
                    m_items[j] = m_items[j+1];
                    m_items[j+1] = temp;
                }
            }
        }
    }

    void PosApp::addItem() {
        actionTitle("Adding Item to the store");
        if (m_numItems >= MAX_NO_ITEMS) cout << "Inventory Full!";
        else {
            char choice = ' ';
            bool exitFlag = false;
            Item* newItem;
            cout << "Is the Item perishable? (Y)es/(N)o: ";
            while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
                cin >> choice;
                if (choice == 'y' || choice == 'Y') newItem = new Perishable;
                else if (choice == 'n' || choice == 'N') newItem = new NonPerishable;
            }
            cin.ignore(100, '\n');
            while (!exitFlag) {
                cin >> *newItem;
                if (*newItem) exitFlag = true;
                else {
                    cin.clear();
                    cin.ignore(1000);
                    cout << *newItem << ", try again...\n";
                }
            }
            m_items[m_numItems++] = newItem;

            actionTitle("DONE!");

        }
    }

    void PosApp::removeItem() {
        actionTitle("Remove Item");

        int index = listItems(false)-1;

        m_items[index]->displayType(POS_FORM);

        cout << "Removing...." << endl << *m_items[index];

        for (int i = index; i < m_numItems-1; i++){
            Item *temp = m_items[i];
            m_items[i] = m_items[i+1];
            m_items[i+1] = temp;
        }
        m_numItems--;
        delete m_items[m_numItems];
        m_items[m_numItems] = nullptr;

        actionTitle("DONE!");
    }

    void PosApp::stockItem() {
        int quantity = 0;
        actionTitle("Select an item to stock");
        int index = listItems(false)-1;

        m_items[index]->displayType(POS_FORM);
        cout << "Selected Item:" << endl << *m_items[index];
        cout << "Enter quantity to add: ";

        while (quantity < 1 || quantity > MAX_STOCK_NUMBER - m_items[index]->quantity()) {
            if (!(cin >> quantity)) {
                quantity = 0;
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid Integer, try again: ";
            } else if (quantity < 1 || quantity > MAX_STOCK_NUMBER - m_items[index]->quantity()) {
                cout << "[1<=value<=" << MAX_STOCK_NUMBER - m_items[index]->quantity()
                     << "], retry: Enter quantity to add: ";
            }
        }
        m_items[index]->operator+=(quantity);
        actionTitle("DONE!");
    }

    void PosApp::pos() {
        char tempSku[MAX_SKU_LEN+1]{};
        int index = -1;
        bool exitFlag = false;
        Bill bill;
        bill.clear();
        actionTitle("Starting Point of Sale");
        cin.clear();
        cin.ignore(1000, '\n');
        while (!exitFlag) {
            cout << "Enter SKU or <ENTER> only to end sale...\n> ";
            index = -1;
            if (!cin.getline(tempSku, MAX_SKU_LEN)) {
                cout << ERROR_POS_SKU;
                cin.clear();
                cin.ignore(1000, '\n');
                index = -1;
            }
            if (strlen(tempSku) == 0) exitFlag = true;
            for (int i = 0; i < m_numItems; i++) {
                if (m_items[i]->operator==(tempSku)) index = i;
            }

            if (!exitFlag) {
                if (index == -1) cout << "!!!!! Item Not Found !!!!!" << endl;
                else {
                    m_items[index]->operator-=(1);
                    if (m_items[index]->operator bool()) {
                        m_items[index]->displayType(POS_FORM);
                        bill.add(m_items[index]);
                        cout.fill(' ');
                        cout << *m_items[index] << endl << ">>>>> Added to bill" << endl
                             << ">>>>> Total: ";
                        cout.precision(2);
                        cout.setf(ios::fixed);
                        cout << bill.total() << endl;
                        cout.unsetf(ios::fixed);
                    } else{
                        cout << ERROR_POS_STOCK << endl;
                        m_items[index]->clear();
                    }
                }
            }
        }
        cout.precision(2);
        cout.setf(ios::fixed);
        bill.print(cout);
        cout.unsetf(ios::fixed);
    }

    void PosApp::saveRecs() {
        actionTitle("Saving Data");
        ofstream file(m_filename);
        for (int i = 0; i < m_numItems; i++){
            file << *m_items[i] << endl;
        }
    }

    void PosApp::loadRecs() {
        actionTitle("Loading Items");

        ifstream datafile(m_filename);
        if (!datafile){
            ofstream (m_filename);
        }

        for (int i = 0; i < m_numItems; i++){
            delete m_items[i];
            m_items[i] = nullptr;
        }
        m_numItems = 0;

        while (datafile.peek() != EOF && m_numItems < MAX_NO_ITEMS){
            char type = datafile.get();
            datafile.ignore(100,',');

            if (type == 'P') m_items[m_numItems] = new Perishable;
            else if (type == 'N') m_items[m_numItems] = new NonPerishable;

            if (m_items[m_numItems]){
                datafile >> *m_items[m_numItems];
                datafile.ignore(100,'\n');
                m_numItems++;
            }

        }
    }

    void PosApp::run() {
        loadRecs();
        menu();
        saveRecs();
        cout << "Goodbye!" << endl;
    }

    void PosApp::actionTitle(const char *string) {
        cout << ">>>> ";
        cout.width(72);
        cout.fill('.');
        cout << left << string << endl;
    }


    PosApp::~PosApp() {
        delete[] m_filename;
        for (int i = 0; i < MAX_NO_ITEMS; i++){
            delete m_items[i];
        }
    }



}