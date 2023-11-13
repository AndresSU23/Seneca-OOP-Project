/***********************************************************************
// Final project Milestone 2
// Module: AidMan
// File: AidMan.cpp
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
#include <iomanip>
#include <cstring>

#include "AidMan.h"
#include "Utils.h"


using namespace std;

namespace sdds {
	unsigned int AidMan::menu() const {
		int year, month, day;
		ut.getSystemDate(&year, &month, &day);
		cout << "Aid Management System Prototype" << endl << "Date: ";
		cout << setfill('0') << setw(4) << year << " / "
			<< setw(2) << month << " / "
			<< setw(2) << day << endl;
		cout << "Data file : " << ((m_fileName) ? m_fileName : "No file") << endl;
		cout << "---------------------------------" << endl;

		return m_menu.run();
	}
	AidMan::AidMan(const char* fileName) {
		if (fileName) {
			m_fileName = new char[strlen(fileName) + 1];
			strcpy(m_fileName, fileName);
		}
		else {
			m_fileName = nullptr;
		}
	}
	AidMan::~AidMan() {
		delete[] m_fileName;
		m_fileName = nullptr;
	}
	void AidMan::run() {
		unsigned int input{};
		do {
			input = menu();
			if (input == 0) cout << "Exiting Program!" << endl;
			else {
				cout << endl << "****"; 
				m_menu.printSelection(input);
				cout <<"****" << endl << endl;
			}
		} while (input != 0);
	}
}