/* Citation and Sources...
Final Project Milestone 5
Module: PosIO
Filename: PosIO.h
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

#ifndef OOP_PROJECT_POSIO_H
#define OOP_PROJECT_POSIO_H

#include <iostream>

namespace sdds {

    class PosIO {
    public:
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual std::ofstream& save(std::ofstream& ofs) const = 0;
        virtual std::ifstream& load(std::ifstream& ifs) = 0;

        virtual ~PosIO(){};
    };

    std::ostream& operator<<(std::ostream& os, PosIO& pos);
    std::istream& operator>>(std::istream& is, PosIO& pos);
    std::ofstream& operator<<(std::ofstream& ofs, PosIO& pos);
    std::ifstream& operator>>(std::ifstream& ifs, PosIO& pos);


} // sdds

#endif //OOP_PROJECT_POSIO_H
