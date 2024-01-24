/* Citation and Sources...
Final Project Milestone 5
Module: POS
Filename: POS.h
Version 1.3
Author Artom Zabihi
Revision History
-----------------------------------------------------------
 Preliminary release: April 6th, 2023
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#ifndef OOP_PROJECT_POS_H
#define OOP_PROJECT_POS_H

namespace sdds{
    const double TAX = 0.13;
    const int MAX_SKU_LEN = 7;

    const int MIN_YEAR = 2000;
    const int MAX_YEAR = 2030;

    const int MIN_MONTH = 1;
    const int MAX_MONTH = 12;

    const int MIN_DAY = 1;

    const int MIN_HOUR = 0;
    const int MAX_HOUR = 23;

    const int MIN_MINUTE = 0;
    const int MAX_MINUTE = 59;

    const int MAX_STOCK_NUMBER = 99;
    const int MAX_NO_ITEMS = 200;

    const int MAX_NAME_LEN = 40;

    const int POS_LIST = 1;
    const int POS_FORM = 2;

    const char ERROR_POS_SKU[] = "SKU too long";
    const char ERROR_POS_NAME[] = "Item name too long";
    const char ERROR_POS_PRICE[] = "Invalid price value";
    const char ERROR_POS_TAX[] = "Invalid tax status";
    const char ERROR_POS_QTY[] = "Invalid quantity value";
    const char ERROR_POS_STOCK[] = "Item out of stock";
    const char ERROR_POS_EMPTY[] = "Invalid Empty Item";

    const int MAX_FILENAME_LENGTH = 128;
}
#endif //OOP_PROJECT_POS_H
