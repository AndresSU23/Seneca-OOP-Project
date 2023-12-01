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
#include <fstream>

#include "AidMan.h"
#include "Perishable.h"
#include "Item.h"
#include "Utils.h"

using namespace std;

namespace sdds {
	unsigned int AidMan::menu() const {
		Date date{};
		date.formatted(true); //Changing the date format
		cout << "Aid Management System" << endl << "Date: ";
		cout << date << endl; //Printing Date
		cout << "Data file: " << ((m_fileName) ? m_fileName : "No file") << endl; //Printing the chosen file

		return m_menu.run();
	}
	void AidMan::save() {
		if (m_fileName) { //Checking if theres is a filename
			ofstream file(m_fileName, ios::app); //Opening file
			for (int i = 0; i < m_noItems; i++) {
				m_items[i]->save(file); //Calling the save function of each item
			}
			file.close(); //Closing the file
		}
	}
	void AidMan::deallocate() {
		for (int i = 0; i < m_noItems; i++) {
			delete[] m_items[i]; //Cleaning the classes
			m_items[i] = nullptr;
		}
		m_noItems = 0; //Reseting the number of items
	}
	bool AidMan::load() {
		save(); //Saving old Records
		deallocate(); //Deletin all records
		cin.ignore(); //Remove Garbage from the buffer

		//Check for file existence and create if necessary

		if (m_fileName) { //Checking if the file exists
			ifstream file(m_fileName); //Opening check for existence
			if (file.is_open()) { //Check if the file was openned correctly
				cout << "Failed to open " << m_fileName << " for reading!" << endl;
				cout << "Would you like to create a new data file?" << endl;
				cout << "1- Yes!" << endl << "0 - Exit" << endl << "> ";
				if (ut.getint(0,1)) { //Getting User menu input
					char temp[1000]{ '\0' };
					cin.getline(temp, 1000, '\n'); //Getting file in temporary var
					delete[] m_fileName;
					m_fileName = nullptr;
					ut.alocpy(m_fileName, temp); //Dynamically allocating the file name
					ofstream outputFile(m_fileName); //Creating the new file
					outputFile << "";
					outputFile.close();
				}
				else cout << "Exiting Program!" << endl; 
			}
			file.close(); //Securely closing the checking file
		}
		else { //If file name is not declared
			cout << "Enter file name: ";
			char temp[1000]{ '\0' };
			cin.getline(temp, 1000, '\n'); //Get file name is temporary var
			ut.alocpy(m_fileName, temp); //Dinamically allocating the file name
		}
		
		//Readinf from the verified file 

		ifstream file(m_fileName); //Opening the reading file
		for (int i = 0; i < sdds_max_num_items; i++) {
			int peek = file.peek(); //Looking in ASCII the next char
			
			if (peek >= 49 && peek <= 51) { //If its between 1 and 3 inclusively
				m_items[i] = &Perishable(); 
				if (m_items[i]->load(file)) m_noItems++; //If loaded correctly increment the number of items
				else {									 //If not delete the created Perishable
					delete[] m_items[i];
					m_items[i] = nullptr;
				}
			}
			else if (peek >= 52 && peek <= 57) { //If its between 4 and 9 inclusively
				m_items[i] = &Item();
				if (m_items[i]->load(file)) m_noItems++; //If loaded correctly increment the number of items
				else { 									 //If not delete the created Item
					delete[] m_items[i];
					m_items[i] = nullptr;
				}
			}
			else file.setstate(std::ios::failbit);	//If its different set the state of the file to fail
		}
		cout << m_noItems << " records loaded!" << endl; //Report the loaded records
		file.close(); //Safely close 
		return m_noItems;
	}
	int AidMan::list(const char* sub_desc) {
		int counter{0};
		cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		for (int i = 0; i < m_noItems; i++)
		{
			if (!sub_desc) { //Check if the substring is given
				m_items[i]->linear(true); //Changes the format of the product
				cout << std::setw(4) << std::setfill(' ') << std::right << (i + 1) << " | "; //Prints row number
				m_items[i]->display(cout) << endl; //Prints Product
				counter++;
			}
			else {
				if (m_items[i]->subString(sub_desc)) { //Check if the substring is present
					m_items[i]->linear(false);
					cout << std::setw(4) << std::setfill(' ') << std::right << (i + 1) << " |";
					m_items[i]->display(cout) << endl;
					counter++;
				}
			}
		}
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		return counter;
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
				if (m_fileName) { //Check if filename is given
					m_menu.printSelection(input);
					switch (input)
					{
					case 1:
						listItems();
						break;
					case 2:
						addItem();
						break;
					case 3:
						removeItem();
						break;
					case 4:
						updateQuantity();
						break;
					case 5:
						sort();
						break;
					case 6:
						shipItems();
						break;
					case 7:
						loadDatabase();
						break;
					default:
						break;
					}
				}
				else { //Forces the users to load a file
					m_menu.printSelection(7);
					loadDatabase();
				}
				cout << endl;
			}
		} while (input != 0);
		
	}

	void AidMan::listItems() {
		if (list()) {
			cin.ignore();
			cout << "Enter row number to display details or <ENTER> to continue:" << endl << "> ";
			if (cin.peek() != '\n') {
				int row = ut.getint();
				m_items[row - 1]->linear(false);
				m_items[row - 1]->display(cout);
			}
			else {
				cin.ignore();
			}
		}
	}

	void AidMan::addItem() {
	}

	void AidMan::removeItem() {
	}

	void AidMan::updateQuantity() {
	}

	void AidMan::sort() {
	}

	void AidMan::shipItems() {
	}

	void AidMan::loadDatabase() {
		load();
	}
}