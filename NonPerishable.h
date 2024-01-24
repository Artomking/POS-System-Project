/* Citation and Sources...
Final Project Milestone 5
Module: NonPerishable
Filename: NonPerishable.h
Version 1.0
Author Artom Zabihi
Revision History
Revision History
-----------------------------------------------------------
 Preliminary release: April 6th, 2023
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#ifndef OOP_PROJECT_NONPERISHABLE_H
#define OOP_PROJECT_NONPERISHABLE_H

#include "Item.h"
namespace sdds {

    class NonPerishable : public Item{
    public:
        char itemType() const;
        std::ostream& write(std::ostream& os) const;
    };

} // sdds

#endif //OOP_PROJECT_NONPERISHABLE_H
