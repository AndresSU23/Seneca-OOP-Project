/***********************************************************************
// Final project Milestone 4
// Module: Item
// File: Item.h
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
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include <iostream>

#include "iProduct.h"
#include "Status.h"

namespace sdds {
	class Item : public iProduct {
		double m_price{};
		int m_qty{};
		int m_qtyNeeded{};
		char* m_description{};
		bool m_linear{};

	protected:
		Status m_status{};
		int m_sku{};

		bool linear() const;

	public:
		Item();
		Item(const Item& src);
		~Item();

		Item& operator =(const Item& src);

		int qtyNeeded() const override;
		int qty() const override;
		operator double() const override;
		operator bool() const override;

		int operator-=(int qty) override;
		int operator+=(int qty) override;
		void linear(bool isLinear) override;

		void clear();

		bool operator==(int sku) const override;
		bool operator==(const char* description) const override;

		virtual std::ofstream& save(std::ofstream& ofstr) const override;
		virtual std::ifstream& load(std::ifstream& ifstr) override;
		virtual std::ostream& display(std::ostream& ostr) const override;
		virtual int readSku(std::istream& istr) override;
		virtual std::istream& read(std::istream& istr) override;
	};
}

#endif // !SDDS_ITEM_H
