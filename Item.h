/* Citation and Sources...
Final Project Milestone 5
Module: Item
Filename: Item.h
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

#ifndef OOP_PROJECT_ITEM_H
#define OOP_PROJECT_ITEM_H

#include "POS.h"
#include "PosIO.h"
#include "Error.h"
#include <iostream>
#include <fstream>


namespace sdds {

    class Item : public PosIO{
        char m_sku[MAX_SKU_LEN+1];
        char* m_name = nullptr;
        double m_price;
        bool m_taxed;
        int m_quantity;

    protected:
        int m_displayType;
        Error error;
    public:
        virtual char itemType() const = 0;
        Item();
        Item(const Item &item);
        ~Item();

        Item& operator=(const Item& item);

        bool operator==(const Item& item);
        bool operator==(const char* tempSku);
        bool operator>(const Item* item);

        int operator+=(int value);
        int operator-=(int value);

        operator bool() const;

        Item& displayType(int posType);
        double cost() const;
        int quantity() const;
        Item& clear();

        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
        std::ofstream& save(std::ofstream& ofs) const;
        std::ifstream& load(std::ifstream& ifs);

        std::ostream& bprint(std::ostream& os) const;
    };

    double operator+=(double& left, const Item& right);


} // sdds

#endif //OOP_PROJECT_ITEM_H
