/***********************************************************************
// Final project Milestone
// Module: Perishable
// File: Perishable.cpp
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

#include "Perishable.h"
#include "Utils.h"

namespace sdds {
	Perishable::Perishable(const Perishable& src) {
		(*this) = src;
	}

	Perishable::~Perishable() {
		delete[] m_handling;
	}

	Perishable& Perishable::operator=(const Perishable& src)
	{
		Item::operator= (src);
		m_expiry = src.m_expiry;
		ut.alocpy(m_handling, src.m_handling);
		return *this;
	}

	const Date& Perishable::expiry() const {
		return m_expiry;
	}

	int Perishable::readSku(std::istream& istr) {
		m_sku = ut.getint(10000, 39999, "SKU: ");
		istr.clear();
		istr.ignore();
		return m_sku;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const {
		if (Item::operator bool()) {
			Item::save(ofstr) << '\t';
			if (m_handling && strlen(m_handling)) ofstr << m_handling;
			const_cast<Date&>(m_expiry).formatted(false);
			ofstr << '\t' << m_expiry;
		}
		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr){
		Item::load(ifstr);

		delete[] m_handling;
		m_handling = nullptr;

		char temp[1000]{};
		ifstr.getline(temp, 1000, '\t');
		ut.alocpy(m_handling, temp);


		ifstr >> m_expiry;
		ifstr.ignore();


		if (ifstr.fail()) {
			m_status = "Input file stream read (perishable) failed!";
			delete[] m_handling;
			m_handling = nullptr;
		}
		else {
			m_status.clear();
		}

		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const {
		if (m_status) {
			const_cast<Date&>(m_expiry).formatted(true);
			if (linear()) {
				Item::display(ostr) << ((m_handling && strlen(m_handling)) ? "*" : " ") << m_expiry;
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: " << m_expiry << std::endl;
				if (m_handling && strlen(m_handling)) {
					ostr << "Handling Instructions: " << m_handling << std::endl;
				}
			}
		}
		else {
			ostr << m_status;
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		delete[] m_handling;
		m_handling = nullptr;
		
		std::cout << "Expiry date (YYMMDD): ";
		istr >> m_expiry;
		istr.clear();
		istr.ignore();

		std::cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek() != '\n') {
			char temp[1000]{ '\0' };
			istr.getline(temp, 1000, '\n');
			ut.alocpy(m_handling, temp);
		}

		if (istr.fail()) Item::m_status = "Perishable console date entry failed!";
		else { Item::m_status.clear(); }

		return istr;
	}




}