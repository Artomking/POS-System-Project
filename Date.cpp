/* Citation and Sources...
Final Project Milestone 5
Module: Date
Filename: Date.cpp
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

#include "Date.h"
#include "POS.h"
#include <ctime>

namespace sdds {
    Date::Date() {
        dateOnlyFlag = false;
        getSystemDate(year, month, day, hour, minute, dateOnlyFlag);
    }

    Date::Date(int year, int month, int day) {
        dateOnlyFlag = true;
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = 0;
        this->minute = 0;
        validation();
    }

    Date::Date(int year, int month, int day, int hour, int minute) {
        dateOnlyFlag = false;
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        validation();
    }

    void Date::validation() {
        if (!dateError) {
            if (year < MIN_YEAR || year > MAX_YEAR) dateError = "Invalid Year";
            else if (month < MIN_MONTH || month > MAX_MONTH) dateError = "Invalid Month";
            else if (day < MIN_DAY || day > daysOfMonth(year, month)) dateError = "Invalid Day";
            else if (hour < MIN_HOUR || hour > MAX_HOUR) dateError = "Invalid Hour";
            else if (minute < MIN_MINUTE || minute > MAX_MINUTE) dateError = "Invlid Minute";
        }
    }

    Date& Date::dateOnly(bool setFlag) {
        if (setFlag){
            hour = 0;
            minute = 0;
        }
        dateOnlyFlag = setFlag;
        return *this;
    }

    const Error& Date::error() const{
        return dateError;
    }

    int Date::compare() const{
        return uniqueDateValue(year, month, day, hour, minute);
    }

    bool Date::dateStatus() const{
        return dateOnlyFlag;
    }

    void Date::printDate(std::ostream &ostr) const {
        ostr << year << "/";
        if (month < 10) ostr << "0";
        ostr << month << "/";
        if (day < 10) ostr << "0";
        ostr << day;
    }

    void Date::printHours(std::ostream &ostr) const {
        ostr << ", ";
        if (hour < 10) ostr << "0";
        ostr << hour << ":";
        if (minute < 10) ostr << "0";
        ostr << minute;
    }

    Date::operator bool() const {
        return !dateError;
    }

    bool Date::operator==(const Date &date) const {
        return compare() == date.compare();
    }

    bool Date::operator!=(const Date &date) const {
        return compare() != date.compare();
    }

    bool Date::operator<(const Date &date) const {
        return compare() < date.compare();
    }

    bool Date::operator>(const Date &date) const {
        return compare() > date.compare();
    }

    bool Date::operator<=(const Date &date) const {
        return compare() <= date.compare();
    }

    bool Date::operator>=(const Date &date) const {
        return compare() >= date.compare();
    }

    void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly) {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if(dateOnly) {
            hour = min = 0;
        } else {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    int uniqueDateValue(int year, int mon, int day, int hour, int min) {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    int daysOfMonth(int year, int month){
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    void Date::resetDate(){
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
    }

    void Date::read(std::istream& istr){
        bool exit = false;
        dateError.clear();
        resetDate();

        istr >> year;
        if (istr.fail()){
            dateError = "Cannot read year entry";
            exit = true;
        }
        istr.get();
        istr >> month;
        if (istr.fail() && !exit){
            dateError = "Cannot read month entry";
            exit = true;
        }
        istr.get();
        istr >> day;
        if (istr.fail() && !exit){
            dateError = "Cannot read day entry";
            exit = true;
        }

        if (!dateOnlyFlag) {
            istr.get();
            istr >> hour;
            if (istr.fail() && !exit){
                dateError = "Cannot read hour entry";
                exit = true;
            }
            istr.get();
            istr >> minute;
            if (istr.fail() && !exit){
                dateError = "Cannot read minute entry";
                exit = true;
            }
        }
        if (exit) istr.clear();
        validation();
    }


    std::ostream& operator<<(std::ostream& ostr, const Date &date){
        if (date){
            date.printDate(ostr);
            if (!date.dateStatus()) date.printHours(ostr);
        } else {
            ostr << date.error() <<"(";
            date.printDate(ostr);
            if (!date.dateStatus()) date.printHours(ostr);
            ostr << ")";
        }
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, Date &date){
        date.read(istr);
        return istr;
    }
} // sdds