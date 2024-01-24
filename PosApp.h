/* Citation and Sources...
Final Project Milestone 5
Module: PosApp
Filename: PosApp.h
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

#ifndef OOP_PROJECT_POSAPP_H
#define OOP_PROJECT_POSAPP_H

#include <iostream>
#include <cstring>
#include "POS.h"
#include "Item.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Bill.h"
namespace sdds {
    class PosApp{
        char* m_filename;
        Item* m_items[MAX_NO_ITEMS] = {};
        int m_numItems;
    public:

        PosApp(const char* string);
        ~PosApp();

        void menu();
        void addItem();
        void removeItem();
        void stockItem();
        int listItems(bool);
        void pos();
        Item& search(const char*);
        void saveRecs();
        void loadRecs();
        void run();
        void sort();
        void actionTitle(const char* string);
    };
}
#endif //OOP_PROJECT_POSAPP_H
