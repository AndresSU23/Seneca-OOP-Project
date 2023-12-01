/***********************************************************************
// Final project Milestone 5
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
		cout << "---------------------------------" << endl;
		return m_menu.run();
	}
	void AidMan::save() {
		if (m_fileName) { //Checking if theres is a filename
			ofstream file(m_fileName); //Opening file
			for (int i = 0; i < m_noItems; i++) {
				m_items[i]->save(file) << endl; //Calling the save function of each item
			}
			file.close(); //Closing the file
		}
	}
	void AidMan::deallocate() {
		for (int i = 0; i < m_noItems; i++) {
			delete m_items[i]; //Cleaning the classes
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
				Menu menu("1- Yes!");
				if (menu.run(false)) { //Getting User menu input
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
		int i;
		for (i = 0; i < sdds_max_num_items; i++) {
			int peek = file.peek(); //Looking in ASCII the next char
			
			if (peek >= 49 && peek <= 51) { //If its between 1 and 3 inclusively
				m_items[i] = new Perishable; 
				if (m_items[i]->load(file)) m_noItems++; //If loaded correctly increment the number of items
				else {									 //If not delete the created Perishable
					delete m_items[i];
					m_items[i] = nullptr;
				}
			}
			else if (peek >= 52 && peek <= 57) { //If its between 4 and 9 inclusively
				m_items[i] = new Item;
				if (m_items[i]->load(file)) m_noItems++; //If loaded correctly increment the number of items
				else { 									 //If not delete the created Item
					delete m_items[i];
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
					m_items[i]->linear(true);
					cout << std::setw(4) << std::setfill(' ') << std::right << (i + 1) << " | ";
					m_items[i]->display(cout) << endl;
					counter++;
				}
			}
		}
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		return counter;
	}
	int AidMan::search(int sku) const {
		//Returns the index of the matching item, or -1 in case is not found
		for (int i = 0; i < m_noItems; i++)
		{
			if (m_items[i]->operator== (sku)) return i;
		}
		return -1;
	}
	void AidMan::remove(int index) {
		//Removex the object in the index
		delete m_items[index];
		m_items[index] = nullptr;
		//Moves the other objest to the left 
		for (int i = index; i < m_noItems - 1; i++) {
			m_items[i] = m_items[i + 1];
		}
		m_items[--m_noItems] = nullptr;		//Reduces the amount of items and puts nullptr on the last one
	}
	bool AidMan::smallerDiffQty(const iProduct* p1, const iProduct* p2) const {
		return (p1->qtyNeeded() - p1->qty()) < (p2->qtyNeeded() - p2->qty());
	}
	void AidMan::swap(iProduct*& a, iProduct*& b) {
		iProduct* temp = a;		//Creates a copy of the pointer
		a = b;	//Changes the position of the pointers
		b = temp;
	}

	void AidMan::descendingSort(iProduct* arr[], int size) {
		for (int i = 0; i < size - 1; ++i) {
			for (int j = 0; j < size - i - 1; ++j) {
				// Compare using the comparator function
				if (smallerDiffQty(arr[j], arr[j + 1])) {
					swap(arr[j], arr[j + 1]);
				}
			}
		}
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
		deallocate();
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
					cin.ignore();
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
			cout << "Enter row number to display details or <ENTER> to continue:" << endl << "> ";
			if (cin.peek() != '\n') {
				int row = ut.getint();
				m_items[row - 1]->linear(false);
				m_items[row - 1]->display(cout) << endl;
			}
			else {
				cin.ignore();
			}
		}
	}

	void AidMan::addItem() {
		if (m_noItems >= sdds_max_num_items) cout << "Database full!" << endl;
		else {
			Menu itemMenu("Perishable\tNon-Perishable");	//Creates a menu item with the item optionss
			int input = itemMenu.run(17);
			if (input) {	//Checks input is not 0
				if (input == 1) m_items[m_noItems] = new Perishable;	//If 1 creates a Perishable object in the last avialable position 
				else m_items[m_noItems] = new Item;		//If 2 creates an Non-Perishable object in the last avialable position
				int sku = m_items[m_noItems]->readSku(cin);		//Reads and saves the sku
				if (search(sku) < 0) {	//If the sku doesnt exist
					m_items[m_noItems]->read(cin);	//Reads the rest of info 
					if (m_items[m_noItems]->operator bool()) { //If it loaded correclty the size is incremented
						ofstream file(m_fileName, ios::app);
						m_items[m_noItems]->save(file);
						file << '\n';
						file.close();
						m_noItems++;
					}
					else {
						delete m_items[m_noItems];	//If not remove safely the created object
						m_items[m_noItems] = nullptr;
					}
				}
				else {	//If the sku exist
					cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl;
					delete m_items[m_noItems];	//Removes the created safely the created object
					m_items[m_noItems] = nullptr;
				}
			}
			else { //If user selection is 0
				cout << "Aborted" << endl;
			}
		}
	}

	void AidMan::removeItem() {
		cout << "Item description: ";
		char input[1000]{ '\0' };
		cin.getline(input, 1000, '\n'); //Gets User description
		if (list(input)) {
			int sku = ut.getint("Enter SKU: ");
			int index = search(sku); //Searches for the given sku
			if (index >= 0) {
				cout << "Following item will be removed: " << endl;
				m_items[index]->linear(false);
				m_items[index]->display(cout) << endl;
				
				cout << "Are you sure?" << endl;
				Menu menu("Yes!");
				if (menu.run(0)) {
					remove(index); //Removes the index and Saves the items
					save();
					cout << "Item removed!" << endl;
				} else cout << "Aborted!" << endl;
			} else cout << "SKU not found!" << endl;
		} else cout << "No matches found!" << endl;
	}

	void AidMan::updateQuantity() {
		cout << "Item description: ";
		char input[1000]{ '\0' };
		cin.getline(input, 1000, '\n');		 //Gets User description
		if (list(input)) {
			int sku = ut.getint("Enter SKU: ");
			int index = search(sku);	 //Searches for the given sku
			if (index >= 0) {
				Menu menu("Add\tReduce");
				switch(menu.run(0)) {
				case 1:
					if (m_items[index]->qty() == m_items[index]->qtyNeeded()) {		//If requirement have been met
						cout << "Quantity Needed already fulfilled!" << endl;
					}
					else {
						int added = ut.getint(1, m_items[index]->qtyNeeded(), "Quantity to add: ");	 //Get the user addition
						m_items[index]->operator+= (added);		//Updates the class
						cout << added << " items added!" << endl;
						save();
					}
					break;
				case 2:
					if (m_items[index]->qty() == 0) {	//If the quantity is empty
						cout << "There are no Items to reduce!" << endl;
					}
					else {
						int reduced = ut.getint(1, m_items[index]->qty(), "Quantity to reduce: ");  //Get the user reduction
						m_items[index]->operator-= (reduced);	//Updates the class
						cout << reduced << " items removed!" << endl;
						save();
					}
					break;
				case 0:
				default:
					cout << "Aborted!" << endl;
					break;
				}
			} else cout << "SKU not found!" << endl;
		} else cout << "No matches found!" << endl;
	}

	void AidMan::sort() {
		descendingSort(m_items, m_noItems);
		save();	//Saving the sorted list
		cout << "Sort completed!" << endl;
	}

	void AidMan::shipItems() {
		ofstream shipFile("shippingOrder.txt");
		Date date{};
		date.formatted(true);
		shipFile << "Shipping Order, Date: " << date << endl;
		shipFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		shipFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		int counter{ 0 };
		for (int i = 0; i < m_noItems; i++)	{
			if (m_items[i]->qty() == m_items[i]->qtyNeeded()) {
				m_items[i]->linear(true);
				shipFile << std::setw(4) << std::setfill(' ') << std::right << (++counter) << " | ";	//Formats Row and Increments counter
				m_items[i]->display(shipFile) << endl;	//Prints in file item info
				remove(i); //Removes the index and Saves the items
				i--;	//Rewinds the index to count for the deleted item
			}
		}
		shipFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		save();
		cout << "Shipping Order for " << counter << " times saved!" << endl;
	}

	void AidMan::loadDatabase() {
		load(); //Executes the File load
	}
}