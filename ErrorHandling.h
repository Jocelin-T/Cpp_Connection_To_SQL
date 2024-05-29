/*****************************************************************//**
 * @file   ErrorHandling.h
 * @brief  Manage all the error from the try-catch blocks, 
 *	most method will be static
 * 
 * @author ThJo
 * @date   22 May 2024
 *********************************************************************/
#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <stdexcept>
#include <cppconn/exception.h>

#include "wx/wx.h"

class ErrorHandling{
public:
	// Constructors
	ErrorHandling() = default;

	/** ***************************************** Error: Run Time Error *****************************************
	* @brief : Display a wxMessageBox with the run time error receive.
	*
	* @param e : std::runtime_error& => exeption (should be "e")
	*/
	static void displayMessageBoxRunTimeError(const std::string what_method, const std::runtime_error& e);

	/** ***************************************** SQL Exception *****************************************
	 * @brief : Display a wxMessageBox with the SQL Exception received.
	 *
	 * @param e : sql::SQLException& => exception (should be "e")
	 */
	static void displayMessageBoxSqlError(const std::string what_method, const sql::SQLException& e);

};

#endif // ERRORHANDLING_H