/***********************************************************************
// Final project Milestone 4
// Module: Perishable
// File: Perishable.h
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
#pragma once
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>

#include "Item.h"
#include "Date.h"

namespace sdds {
	class Perishable : public Item {
		Date m_expiry{};
		char* m_handling{};

	public:
		Perishable() = default;
		Perishable(const Perishable& src);
		~Perishable();
		Perishable& operator =(const Perishable& src);
		const Date& expiry() const;
		virtual int readSku(std::istream& istr) override;
		virtual std::ofstream& save(std::ofstream& ofstr) const override;
		virtual std::ifstream& load(std::ifstream& ifstr) override;
		virtual std::ostream& display(std::ostream& ostr) const override;
		virtual std::istream& read(std::istream& istr) override;
	};
}

#endif // !SDDS_PERISHABLR_H
