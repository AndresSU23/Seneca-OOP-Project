/***********************************************************************
// Final project Milestone 4
// Module: Date
// File: Date.cpp
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

#include <iostream>
#include <cstring>
#include <iomanip>

#include "Date.h"
#include "Utils.h"

using namespace std;

namespace sdds {

	bool Date::validate()  {
		bool flag{};

		if (m_year < currentYear || m_year > MaxYearValue)
		{
			m_state = "Invalid year in date";
			m_state = 1;
			flag = false;
		}
		else if (m_month < 1 || m_month > 12){
			m_state = "Invalid month in date";
			m_state = 2;
			flag = false;
		}
		else if (m_day < 1 || m_day > ut.daysOfMon(m_month, m_year)) {
			m_state = "Invalid day in date";
			m_state = 3;
			flag = false;
		}
		else {
			m_state.clear();
			flag = true;
		}
		return flag;
	}
	int Date::uniqueDataValue() const {
		return m_year * 372 + m_month * 31 + m_day;
	}
	Date::Date() {
		ut.getSystemDate(&m_year, &m_month, &m_day);
	}
	Date::~Date() {
		m_state.clear();
	}
	Date::Date(int year, int month, int day) {
		m_year = year;
		m_month = month;
		m_day = day;
	}
	bool Date::operator==(const Date cmp) const {
		return uniqueDataValue() == cmp.uniqueDataValue();
	}
	bool Date::operator!=(const Date cmp) const {
		return uniqueDataValue() != cmp.uniqueDataValue();
	}
	bool Date::operator<(const Date cmp) const {
		return uniqueDataValue() < cmp.uniqueDataValue();
	}
	bool Date::operator>(const Date cmp) const {
		return uniqueDataValue() > cmp.uniqueDataValue();
	}
	bool Date::operator<=(const Date cmp) const {
		return uniqueDataValue() <= cmp.uniqueDataValue();
	}
	bool Date::operator>=(const Date cmp) const {
		return uniqueDataValue() >= cmp.uniqueDataValue();
	}
	const Status& Date::state() const {
		return m_state;
	}
	Date& Date::formatted(bool format) {
		m_formatted = format;
		return *this;
	}
	Date::operator bool() const {
		return m_state;
	}
	std::ostream& Date::write(std::ostream& ostr) const {
		if (m_formatted) {
			ostr << setfill('0') << setw(4) << m_year << '/'
				<< setw(2) << m_month << '/'
				<< setw(2) << m_day;
		}
		else {
			ostr << setfill('0') << setw(2) << (m_year%100)
				<< setw(2) << m_month
				<< setw(2) << m_day;
		}

		return ostr;
	}
	std::istream& Date::read(std::istream& istr) {
		int inputDate{};
		istr >> inputDate;

		if (istr)
		{
			if (inputDate >= 1 && inputDate <= 9999) {
				m_year = currentYear;
				m_month = inputDate / 100;
				m_day = inputDate % 100;
			}
			else if (inputDate >= 100000 && inputDate <= 999999) {
				m_year = inputDate / 10000 + 2000;
				inputDate %= 10000;
				m_month = inputDate / 100;
				m_day = inputDate % 100;

			}


			if (!validate()) istr.setstate(std::ios::badbit);
		}
		else {
			m_state = "Invalid date value";
		}
		return istr;
	}
	std::ifstream& Date::read(std::ifstream& istr) {
		int inputDate{};
		istr >> inputDate;

		if (istr)
		{
			if (inputDate >= 1 && inputDate <= 9999) {
				m_year = currentYear;
				m_month = inputDate / 100;
				m_day = inputDate % 100;
			}
			else if (inputDate >= 100000 && inputDate <= 999999) {
				m_year = inputDate / 10000 + 2000;
				inputDate %= 10000;
				m_month = inputDate / 100;
				m_day = inputDate % 100;
			}

			if (!validate()) istr.setstate(std::ios::badbit);
		}
		else {
			m_state = "Invalid date value";
		}
		return istr;
	}
	std::ostream& operator<<(std::ostream& ostr,const Date& date) {
		return date.write(ostr);
	}
	std::istream& operator>>(std::istream& istr, Date& date) {
		return date.read(istr);
	}
	std::ifstream& operator>>(std::ifstream& istr, Date& date) {
		return date.read(istr);
	}
}