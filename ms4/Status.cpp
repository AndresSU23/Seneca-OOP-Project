/***********************************************************************
// Final project Milestone 1
// Module: Status
// File: Status.cpp
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

#include "Status.h"
#include "Utils.h"

using namespace std;
namespace sdds {

	Status::Status(const char* desc) {
		m_code = 0;

		m_desc = nullptr;

		if (desc) ut.alocpy(m_desc, desc);
		
	}
	Status::~Status() {
		clear();
	}
	Status& Status::operator=(const Status& stat)
	{
		if (this != &stat)
		{
			clear();
			m_code = stat.m_code;
			ut.alocpy(m_desc, stat.m_desc);
		}

		return *this;
	}
	Status& Status::operator=(const char* desc) {
		delete[] m_desc;
		m_desc = nullptr;
		ut.alocpy(m_desc, desc);
		return *this;
	}
	Status& Status::operator=(int code) {
		m_code = code;
		return *this;
	}
	Status::operator int() const {
		return m_code;
	}
	Status::operator const char* () const {
		return m_desc;
	}
	Status::operator bool() const {
		return !m_desc;
	}
	Status& Status::clear() {
		delete[] m_desc;
		m_desc = nullptr;
		m_code = 0;
		return *this;
	}
	std::ostream& operator<<(std::ostream& ostr, const Status& status)
	{
		if (!status) {
			if ((int)status) {
				ostr << "ERR#" << (int)status << ": ";
			}
			ostr << (const char*)status;
		}
		return ostr;
	}
}


