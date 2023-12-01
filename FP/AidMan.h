/***********************************************************************
// Final project Milestone 5
// Module: AidMan
// File: AidMan.h
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
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"

namespace sdds {
	const int sdds_max_num_items = 100;
	class AidMan {
		char* m_fileName{nullptr};
		Menu m_menu{ "List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database" };
		iProduct* m_items[sdds_max_num_items]{nullptr};
		int m_noItems{0};

		unsigned int menu() const;
		void save();
		void deallocate();
		bool load();
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void remove(int index);
		bool smallerDiffQty(const iProduct* p1, const iProduct* p2) const;
		void swap(iProduct*& a, iProduct*& b);
		void descendingSort(iProduct* arr[], int size);
	public:
		AidMan() = default;
		AidMan(const char* fileName);
		~AidMan();
		void run();
		void listItems();
		void addItem();
		void removeItem();
		void updateQuantity();
		void sort();
		void shipItems();
		void loadDatabase();
	};
}

#endif // !SDDS_AIDMAN_H
