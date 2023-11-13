/***********************************************************************
// Final project Milestone 2
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

namespace sdds {
	class AidMan {
		char* m_fileName{};
		Menu m_menu{ "List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSortShip Items New/Open Aid Database" };

		unsigned int menu() const;

	public:
		AidMan(const char* fileName);
		~AidMan();
		void run();
	};
}

#endif // !SDDS_AIDMAN_H
