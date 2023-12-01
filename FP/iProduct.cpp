/***********************************************************************
// Final project Milestone 4
// Module: iProduct
// File: iProduct.cpp
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

#include "iProduct.h"

std::ostream& sdds::operator<<(std::ostream& ostr, const iProduct& product)
{
	return product.display(ostr);
}

std::istream& sdds::operator>>(std::istream& istr, iProduct& product)
{
	return product.read(istr);
}
