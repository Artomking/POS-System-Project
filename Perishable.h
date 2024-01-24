/* Citation and Sources...
Final Project Milestone 5
Module: Perishable
Filename: Perishable.h
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

#ifndef OOP_PROJECT_PERISHABLE_H
#define OOP_PROJECT_PERISHABLE_H

#include "Item.h"
#include "Date.h"
namespace sdds {

    class Perishable : public Item {
        Date m_expiryDate;
    public:
        char itemType() const;



        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
        std::ofstream& save(std::ofstream& ofs) const;
        std::ifstream& load(std::ifstream& ifs);
    };

} // sdds

#endif //OOP_PROJECT_PERISHABLE_H
