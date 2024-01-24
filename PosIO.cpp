/* Citation and Sources...
Final Project Milestone 5
Module: PosIO
Filename: PosIO.cpp
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

#include "PosIO.h"

namespace sdds {

    std::ostream& operator<<(std::ostream& os, PosIO& pos){
        pos.write(os);
        return os;
    }
    std::istream& operator>>(std::istream& is, PosIO& pos){
        pos.read(is);
        return is;
    }

    std::ofstream& operator<<(std::ofstream& ofs, PosIO& pos){
        pos.save(ofs);
        return ofs;
    }
    std::ifstream& operator>>(std::ifstream& ifs, PosIO& pos){
        pos.load(ifs);
        return ifs;
    }

} // sdds