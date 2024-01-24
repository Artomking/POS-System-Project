/* Citation and Sources...
Final Project Milestone 5
Module: Date
Filename: Date.h
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

#ifndef OOP_PROJECT_DATE_H
#define OOP_PROJECT_DATE_H

#include "Error.h"
namespace sdds {

    class Date {
        int year{};
        int month{};
        int day{};
        int hour{};
        int minute{};
        bool dateOnlyFlag;
        Error dateError;
    public:
        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour, int minute=0);

        void validation();
        int compare() const;
        void read(std::istream& istr);

        Date& dateOnly(bool);
        const Error& error() const;
        bool dateStatus() const;
        void printDate(std::ostream& ostr) const;
        void printHours(std::ostream& ostr) const;
        void resetDate();

        operator bool() const;
        bool operator==(const Date& date) const;
        bool operator!=(const Date& date) const;
        bool operator<(const Date& date) const;
        bool operator>(const Date& date) const;
        bool operator<=(const Date& date) const;
        bool operator>=(const Date& date) const;
    };

    void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
    int uniqueDateValue(int year, int mon, int day, int hour, int min);
    int daysOfMonth(int year, int month);

    std::ostream& operator<<(std::ostream& ostr, const Date &date);
    std::istream& operator>>(std::istream& istr, Date &date);


} // sdds

#endif //OOP_PROJECT_DATE_H
