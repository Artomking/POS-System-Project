/* Citation and Sources...
Final Project Milestone 5
Module: Error
Filename: Error.cpp
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

#include "Error.h"
#include <cstring>

namespace sdds {
    Error::Error(){
        desc = nullptr;
    }

    Error::Error(const char* errorMessage){
        if (errorMessage != nullptr) {
            desc = new char[strlen(errorMessage) + 1];
            strcpy(desc, errorMessage);
        }
    }

    Error::Error(const Error &err){
        if (*this != err&& err.desc != nullptr) {
            delete[] desc;
            desc = new char[strlen(err.desc) + 1];
            strcpy(desc, err.desc);
        }
    }

    Error& Error::operator=(const char* errorMessage) {
        delete[] desc;

        if (errorMessage != nullptr){
            desc = new char[strlen(errorMessage) + 1];
            strcpy(desc, errorMessage);
        } else {
            desc = nullptr;
        }
        return *this;
    }

    Error& Error::operator=(const Error& err){
        if (this != &err) {
            delete[] desc;
            if (err.desc != nullptr) {
                desc = new char[strlen(err.desc) + 1];
                strcpy(desc, err.desc);
            } else {
                desc = nullptr;
            }
        }
        return *this;
    }

    Error::~Error(){
        delete[] desc;
        desc = nullptr;
    }

    Error::operator bool() const {
        return desc != nullptr;
    }

    Error& Error::clear(){
        delete[] desc;
        desc = nullptr;
        return *this;
    }


    void Error::display(std::ostream& ostr) const{
        ostr << desc;
    }

    std::ostream& operator<<(std::ostream& ostr, const Error& err){
        if (err){
            err.display(ostr);
        }
        return ostr;
    }
} // sdds