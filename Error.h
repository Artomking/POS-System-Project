/* Citation and Sources...
Final Project Milestone 5
Module: Error
Filename: Error.h
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

#ifndef OOP_PROJECT_ERROR_H
#define OOP_PROJECT_ERROR_H

#include <iostream>
#include <cstring>

namespace sdds {

    class Error {
        char* desc = nullptr;

    public:
        Error();
        Error(const char* errorMessage);
        Error(const Error &err);
        ~Error();

        operator bool() const;
        Error& operator=(const char* errorMessage);
        Error& operator=(const Error& err);

        Error& clear();

        void display(std::ostream& ostr) const;
    };

    std::ostream& operator<<(std::ostream& ostr, const Error &err);


} // sdds

#endif //OOP_PROJECT_ERROR_H
