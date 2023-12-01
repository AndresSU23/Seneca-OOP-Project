/***********************************************************************
// Final project Milestone 5
// Module: Menu
// File: Menu.h
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
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {
	class Menu {
		char* m_content{};

	public:
		Menu(const char* content);
		~Menu();
		unsigned int run(int size = 33) const;
		void printSelection(unsigned int selection);
	};
}

#endif // !SDDS_MENU_H
