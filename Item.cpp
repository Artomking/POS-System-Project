/* Citation and Sources...
Final Project Milestone 5
Module: Item
Filename: Item.cpp
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

#include "Item.h"


namespace sdds {
    Item::Item() : PosIO(){
        m_sku[0] = '\0';
        m_name = nullptr;
        m_price = 0;
        m_taxed = false;
        m_quantity = 0;
        m_displayType = 1;
    }

    Item::Item(const Item &item) : PosIO(){
        if (this != &item && &item != nullptr) {
            delete[] m_name;
            std::copy(item.m_sku, item.m_sku + MAX_SKU_LEN, m_sku);
            if (strlen(item.m_name) < 40) m_name = new char[strlen(item.m_name)+1];
            else m_name = new char[MAX_NAME_LEN+1];
            strcpy(m_name, item.m_name);
            m_price = item.m_price;
            m_taxed = item.m_taxed;
            m_quantity = item.m_quantity;
            m_displayType = item.m_displayType;
            error = item.error;
        }
    }

    Item::~Item() {
        delete[] m_name;
        m_name = nullptr;
    }

    Item &Item::operator=(const Item &item) {
        if (this != &item && &item != nullptr && item.m_name != nullptr) {
            delete[] m_name;
            std::copy(item.m_sku, item.m_sku + MAX_SKU_LEN, m_sku);
            m_name = new char[MAX_NAME_LEN+1];
            strcpy(m_name, item.m_name);
            m_price = item.m_price;
            m_taxed = item.m_taxed;
            m_quantity = item.m_quantity;
            m_displayType = item.m_displayType;
            error = item.error;

        }
        return *this;
    }

    bool Item::operator==(const Item &item) {
        return strcmp(m_sku, item.m_sku) == 0;
    }

    bool Item::operator==(const char* tempSku) {
        return strcmp(m_sku, tempSku) == 0;
    }

    bool Item::operator>(const Item* item) {
        return strcmp(m_name, item->m_name) > 0;
    }

    int Item::operator+=(int value) {
        m_quantity += value;
        if (m_quantity > MAX_STOCK_NUMBER){
            error = ERROR_POS_QTY;
            m_quantity = MAX_STOCK_NUMBER;
        }
        return m_quantity;
    }

    int Item::operator-=(int value) {
        m_quantity -= value;
        if (m_quantity < 0){
            error = ERROR_POS_STOCK;
            m_quantity = 0;
        }
        return m_quantity;
    }

    Item::operator bool() const {
        return !error;
    }

    Item& Item::displayType(int posType) {
        if (posType == 1 || posType == 2) m_displayType = posType;
        return *this;
    }

    double Item::cost() const {
        return m_price*(1+m_taxed*TAX);
    }

    int Item::quantity() const {
        return m_quantity;
    }

    Item &Item::clear() {
        error.clear();
        return *this;
    }

    std::ostream &Item::write(std::ostream &os) const {
        if (*this) {
            if (m_displayType == POS_LIST) {
                os.width(7);

                os << std::left << m_sku << "|";
                if (m_name != nullptr) {
                    for (unsigned int i = 0; i < 20; i++) {
                        if (i >= strlen(m_name)) {
                            os << " ";
                        } else {
                            os << m_name[i];
                        }
                    }
                }
                os << "|";
                os.width(7);
                os.precision(2);
                os.setf(std::ios::fixed);
                os.setf(std::ios::right);
                os << m_price << "| ";
                if (m_taxed) {
                    os << "X |";
                } else {
                    os << "  |";
                }
                os.width(4);
                os  << m_quantity << "|";

                os.width(9);
                os << cost() * m_quantity << "|";
                os.unsetf(std::ios::fixed);
                os.unsetf(std::ios::right);
            } else if (m_displayType == POS_FORM) {
                os << "=============v\n";
                os.precision(2);
                os.setf(std::ios::fixed);
                os.setf(std::ios::left);
                os.width(13);
                os << "Name:";
                os << m_name << std::endl;

                os.width(13);
                os << "Sku:";
                os << m_sku << std::endl;

                os.width(13);

                os << "Price:" << m_price << std::endl;
                os.width(13);
                os << "Price + tax:";
                if (m_taxed) os << cost();
                else os << "N/A";
                os << std::endl;
                os.unsetf(std::ios::fixed);
                os.width(13);
                os << "Stock Qty:";
                os << m_quantity << std::endl;
                os.unsetf(std::ios::left);
            }
        } else os << error;

        return os;
    }

    std::ofstream& Item::save(std::ofstream& ofs) const{
        ofs.precision(2);
        ofs.setf(std::ios::fixed);
        if (*this){
            ofs << itemType() << "," << m_sku << "," << m_name << ",";
            ofs << m_price << "," << m_taxed << "," << m_quantity;
        } else std::cerr << error;
        ofs.unsetf(std::ios::fixed);
        return ofs;
    }

    std::istream &Item::read(std::istream &is) {
        char tempSku[MAX_SKU_LEN*4];
        char tempName[MAX_NAME_LEN*4];
        char choice[MAX_NAME_LEN] = {};
        double tempPrice;
        int tempQuantity = -1;

        m_sku[0] = '\0';
        std::cout << "Sku";
        while (m_sku[0] == '\0') {
            std::cout << "\n> ";
            is.getline(tempSku, 90);
            if (is.fail() || strlen(tempSku) > MAX_SKU_LEN) std::cout << ERROR_POS_SKU;
            else strcpy(m_sku, tempSku);

            if (is.fail()) is.clear();
        }


        delete[] m_name;
        m_name = nullptr;
        std::cout << "Name";
        while (m_name == nullptr) {
            std::cout << "\n> ";
            is.getline(tempName, 90);
            if (is.fail() || strlen(tempName) > MAX_NAME_LEN) std::cout << ERROR_POS_NAME;
            else {
                m_name = new char[strlen(tempName)+1];
                strcpy(m_name, tempName);
            }

            if (is.fail()) is.clear();
        }
        m_price = -1;
        std::cout << "Price";
        while (m_price == -1) {
            std::cout << "\n> ";
            is >> tempPrice;

            if (is.fail()){
                is.clear();
                is.ignore(10000, '\n');
                std::cout << ERROR_POS_PRICE;
            }
            else if (tempPrice < 0) std::cout << ERROR_POS_PRICE;
            else m_price = tempPrice;

        }

        std::cout << "Taxed?\n(Y)es/(N)o";
        while (strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0){
            std::cout << ": ";
            is >> choice;
            if (strcmp(choice, "y") == 0) choice[0] = 'Y';
            if (strcmp(choice, "n") == 0) choice[0] = 'N';

            if (strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0) {
                std::cout << "Only 'y' and 'n' are acceptable";
                is.clear();
                is.ignore(100, '\n');
            } else m_taxed = choice[0] == 'Y';
        }


        m_quantity = -1;
        std::cout << "Quantity";
        while (m_quantity <= 0 || m_quantity > MAX_STOCK_NUMBER) {
            std::cout << "\n> ";
            is >> tempQuantity;

            if (is.fail()){
                is.clear();
                is.ignore(10000, '\n');
                std::cout << ERROR_POS_QTY;
            }
            else if (tempQuantity <= 0 || tempQuantity > MAX_STOCK_NUMBER) std::cout << ERROR_POS_QTY;
            else m_quantity = tempQuantity;

        }

        return is;
    }


    std::ifstream &Item::load(std::ifstream &ifs) {
        char tempSku[MAX_SKU_LEN*4+1] = {};
        char tempName[MAX_NAME_LEN*4+1] = {};
        double tempPrice;
        int tempTaxed;
        int tempQuantity;

        clear();
        ifs.getline(tempSku, MAX_SKU_LEN*4, ',');
        ifs.getline(tempName, MAX_NAME_LEN*4, ',');
        ifs >> tempPrice;
        ifs.get();
        ifs >> tempTaxed;
        ifs.get();
        ifs >> tempQuantity;

        if (!ifs.fail()){
        if (strlen(tempSku) > MAX_SKU_LEN) if (!error) error = ERROR_POS_SKU;
        if (strlen(tempName) > MAX_NAME_LEN) if (!error) error = ERROR_POS_NAME;
        if (tempPrice < 0) if (!error) error = ERROR_POS_PRICE;
        if (tempTaxed != 0 && tempTaxed != 1) if (!error) error = ERROR_POS_TAX;
        if (tempQuantity <= 0 || tempQuantity > MAX_STOCK_NUMBER) if (!error) error = ERROR_POS_QTY;
        }

        if (!error){
            strcpy(m_sku, tempSku);
            delete[] m_name;
            m_name = new char[strlen(tempName)+1];
            strcpy(m_name, tempName);
            m_price = tempPrice;
            m_taxed = tempTaxed;
            m_quantity = tempQuantity;
        }
        return ifs;
    }

    std::ostream &Item::bprint(std::ostream &os) const {
        os << "| ";
        for (unsigned int i = 0; i < 20; i++) {
            if (i >= strlen(m_name)) {
                os << " ";
            } else {
                os << m_name[i];
            }
        }
        os << "|";
        os.width(10);
        os.precision(2);
        os.setf(std::ios::fixed);
        os << std::right << cost();
        os << " |";
        os << "  ";

        if (m_taxed) os << "T  |";
        else os << "   |";

        os << std::endl;
        return os;
    }

    double operator+=(double& left, const Item& right){
        left += right.cost() * right.quantity();
        return left;
    }
} // sdds