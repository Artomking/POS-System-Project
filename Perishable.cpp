/* Citation and Sources...
Final Project Milestone 5
Module: Perishable
Filename: Perishable.cpp
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

#include "Perishable.h"

namespace sdds {
    char Perishable::itemType() const {
        return 'P';
    }

    std::ostream &Perishable::write(std::ostream &os) const {
        Item::write(os);

        if (*this && os.good()){
            if (m_displayType == POS_LIST) os << "  " << m_expiryDate << " |";
            else if (m_displayType == POS_FORM) os << "Expiry date: " << m_expiryDate << "\n=============^\n";
        }

        return os;
    }

    std::istream &Perishable::read(std::istream &is) {
        Item::read(is);

        if (*this && is.good()){
            Date date;
            date.dateOnly(true);
            std::cout << "Expiry date (YYYY/MM/DD)\n> ";
            is >> date;
            if (date) m_expiryDate = date;
            else error = date.error();
        }

        return is;
    }

    std::ofstream &Perishable::save(std::ofstream &ofs) const {
        Item::save(ofs);

        if (*this) ofs << "," << m_expiryDate;

        return ofs;
    }

    std::ifstream &Perishable::load(std::ifstream &ifs) {
        Item::load(ifs);
        if (*this && ifs.good()){
            Date date;
            date.dateOnly(true);
            ifs.ignore(1);

            ifs >> date;

            if (date) m_expiryDate = date;
            else error = date.error();
        }
        return ifs;
    }

} // sdds