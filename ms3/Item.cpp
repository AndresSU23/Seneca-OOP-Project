/***********************************************************************
// Final project Milestone 3
// Module: Item
// File: Item.cpp
// Version 1.0
// Author
// Description
//			Name      : David Andres Sanchez Umbarila
//			Student ID: 140273228
//			Email     : dasanchez-umbarila@myseneca.ca
/			Date      :
//
//			I have done all the coding by myself and only copied the code
//			 that my professor provided to complete my workshops and
//			 assignments.
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

#include "Item.h"
#include "Utils.h"

namespace sdds {

	Item::Item() {
		m_price = 0.0;
		m_qty = 0;
		m_qtyNeeded = 0;
		m_description = nullptr;
		m_linear = false;
        m_sku = 0;
	}

	bool Item::linear() const
	{
		return m_linear;
	}
    Item::~Item() {
        delete[] m_description;
        m_status.clear();
    }

    int Item::qtyNeeded() const {
        return m_qty;
    }

    int Item::qty() const {
        return m_qtyNeeded;
    }

    Item::operator double() const {
        return m_price;
    }

    Item::operator bool() const {
        return m_status;
    }

    int Item::operator-=(int qty) {
        return m_qty -= qty;
    }

    int Item::operator+=(int qty) {
        return m_qty += qty;
    }

    void Item::linear(bool isLinear) {
        m_linear = isLinear;
    }

    void Item::clear() {
        m_status.clear();
    }

    bool Item::operator==(int sku) const {
        return m_sku == sku;
    }

    bool Item::operator==(const char* description) const {
        if (m_description && description) {
            return std::strstr(m_description, description) != nullptr;
        }
        return false;
    }
    std::ofstream& Item::save(std::ofstream& ofstr) const {
        if (m_status) {
            ofstr << m_sku << '\t' << m_description << '\t'
                << m_qty << '\t' << m_qtyNeeded << '\t'
                << std::fixed << std::setprecision(2) << m_price;
        }
        return ofstr;
    }
    std::ifstream& Item::load(std::ifstream& ifstr) {
        delete[] m_description;
        m_description = nullptr;

        ifstr >> m_sku;
        ifstr.ignore();
        char temp[1000]{};
        ifstr.getline(temp, 1000, '\t');
        ut.alocpy(m_description, temp);


        ifstr >> m_qty;
        ifstr.ignore();
        ifstr >> m_qtyNeeded;
        ifstr.ignore();
        ifstr>> m_price;
        ifstr.ignore();

        if (ifstr.fail()) {
            m_status = "Input file stream read failed!";
            delete[] m_description;
            m_description = nullptr;
        }
        else {
           clear();
        };

        return ifstr;
    }
    std::ostream& Item::display(std::ostream& ostr) const {
        if (m_status) {
            if (linear()) {
                char buffer[36]{ '\0' };

                ostr << std::setw(5) << std::setfill('0') << m_sku << " | ";

                if (m_description) {
                    std::strncpy(buffer, m_description, 35);
                    buffer[35] = '\0';
                    ostr << std::setw(35) << std::left << std::setfill(' ') << buffer << " | ";
                }

                ostr << std::setw(4) << std::right << m_qty << " | "
                    << std::setw(4) << m_qtyNeeded << " | "
                    << std::setw(7) << std::fixed << std::setprecision(2) << m_price << " |";
            }
            else {
                ostr << "AMA Item :" << std::endl;
                ostr << m_sku << ": " << m_description << std::endl;
                ostr << "Quantity Needed : " << m_qtyNeeded << std::endl;
                ostr << "Quantity Available : " << m_qty << std::endl;
                ostr << "Unit Price : $" << std::fixed << std::setprecision(2) << m_price << std::endl;
                ostr << "Needed Purchase Fund : $" << std::fixed << std::setprecision(2) << (m_price * (m_qtyNeeded - m_qty)) << std::endl;
            }
        } 
        else {
            ostr << m_status;
        }
        return ostr;
    }
    int Item::readSku(std::istream& istr) {
        m_sku = ut.getint(40000, 99999, "SKU: ");
        return m_sku;
    }
    std::istream& Item::read(std::istream& istr) {
        std::cout << "AMA Item:" << std::endl;
        std::cout << "SKU: " << m_sku << std::endl;

        char temp[1000]{ '\0' };
        std::cout << "Description: ";
        istr >> temp;
        ut.alocpy(m_description, temp);

        m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
        m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");
        m_price = ut.getdouble(0.0, 9999.0, "Unit Price: $");
        

        return istr;
    }
}