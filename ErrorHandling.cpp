/*****************************************************************//**
 * @file   ErrorHandling.cpp
 * @brief  Manage all the error from the try-catch blocks
 * most method will be static
 * 
 * @author ThJo
 * @date   22 May 2024
 *********************************************************************/
#include "ErrorHandling.h"


/** ***************************************** Run Time Error *****************************************
* @brief : Display a wxMessageBox with the run time error received.
*
* @param e : std::runtime_error& => exception (should be "e")
*/
void ErrorHandling::displayMessageBoxRunTimeError(const std::string what_method, const std::runtime_error& e) {
	wxMessageBox(wxString::Format("Run Time Error: %s\nIn method: %s",
		e.what(),
		what_method),
		"Error", wxOK | wxICON_ERROR);
}

/** ***************************************** SQL Exception *****************************************
 * @brief : Display a wxMessageBox with the SQL Exception received.
 *
 * @param e : sql::SQLException& => exception (should be "e")
 */
void ErrorHandling::displayMessageBoxSqlError(const std::string what_method, const sql::SQLException& e){
	wxMessageBox(wxString::Format("SQL Exception: %s\nError Code: %d\nSQL State: %s\nIn method: %s",
		e.what(),
		e.getErrorCode(),
		e.getSQLState().c_str(),
		what_method.c_str()),
		"Error", wxOK | wxICON_ERROR);
}
