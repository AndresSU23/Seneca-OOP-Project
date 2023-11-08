/***********************************************************************
// Final project Milestone 1
// Module: Date
// File: Date.h
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

#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include <iostream>
#include "Status.h"

namespace sdds {
	const int MaxYearValue = 2030;
	const int currentYear = 2023;
	class Date {
		int m_year{};
		int m_month{};
		int m_day{};
		Status m_state{};
		bool m_formatted{true};

		bool validate();
		int uniqueDataValue() const;
		
	public:
		Date();
		Date(int year, int month, int day);
		bool operator ==(const Date cmp) const;
		bool operator !=(const Date cmp) const;
		bool operator <(const Date cmp) const;
		bool operator >(const Date cmp) const;
		bool operator <=(const Date cmp) const;
		bool operator >=(const Date cmp) const;
		const Status& state() const;
		Date& formatted(bool format);
		operator bool() const;
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};
	std::ostream& operator <<(std::ostream& ostr, const Date& date);
	std::istream& operator >>(std::istream& istr, Date& date);
}
#endif // !SDDS_DATE_H
