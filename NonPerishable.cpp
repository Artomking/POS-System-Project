/* Citation and Sources...
Final Project Milestone 5
Module: NonPerishable
Filename: NonPerishable.cpp
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

#include "NonPerishable.h"

namespace sdds {
    char NonPerishable::itemType() const {
        return 'N';
    }

    std::ostream &NonPerishable::write(std::ostream &os) const {
        if (*this) {
            Item::write(os);
            if (m_displayType == POS_LIST) os << "     N / A   |";
            else os << "=============^" << std::endl;
        }
        return os;
    }
} // sdds