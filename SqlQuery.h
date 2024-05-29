/*****************************************************************//**
 * @file   SQL_Query.h
 * @brief  Class (header) for all SQL DataBase connection and query (App)
 *
 * @author ThJo
 * @date   29 April 2024
 *********************************************************************/
#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>
#include <iomanip>

// SQL libraries
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>

// Class (header)
#include "MainFrame.h"
#include "ErrorHandling.h"

// Forward declaration
namespace bll {
	class Entry;
	class Employee;
}


class SqlQuery {
public:
	// Constructor
	SqlQuery();

	// Destructor
	~SqlQuery();

private:
	// SQL connection
	const std::string m_DB_SERVER = "tcp://127.0.0.1:3306";
	const std::string m_DB_USERNAME = "root";
	const std::string m_DB_PASSWORD = ""; // Never save a password in code
	const std::string m_DATABASE = "orif_ex_connect_to_cpp";

	sql::Driver* m_pDriver;
	sql::Connection* m_pSql_connection;
	sql::Statement* m_pStatement;
	sql::PreparedStatement* m_pPrep_statement;

	// Tables name
	const std::string m_TBL_ENTRIES = "entries";
	const std::string m_TBL_EMPLOYEES = "employees";


	/** ***************************************** SQL Connection *****************************************
	* @brief : Throw a std::runtime_error message in case the connection with mySQL is not open.
	*
	*/
	void checkSQLConnection();

public:
	// Global variable for a check if any creation was a success
	bool creation_success{ false };


	// [Employees] Table
	/** ***************************************** Connect as an employee *****************************************
	 * @brief : Check if the user exist in the table [Employees].
	 *
	 * @param employee : bll::Employee& => (Required to set his employee_email and employee_password)
	 * @return  : Boolean => True if the input exist and matches || False in any other cases
	 */
	bool checkEmployee(bll::Employee& employee);

	/** ***************************************** Complet data of an employee *****************************************
	 * @brief : Complet the data of the given employee with the DB.
	 *
	 * @param employee : bll::Employee&, emp_email and emp_password are required
	 */
	void completEmployeeWithEmailAndPw(bll::Employee& employee);

	/** ***************************************** Extract info of an employee *****************************************
	 * @brief : Extract the info of the current connected employee from the DB.
	 *
	 * @param employeeId : Employee, with is emp_id
	 * @return  : Employee, with is emp_id, emp_last_name, emp_first_name, emp_email
	 */
	void getEmployeeWithId(bll::Employee& employee);


	// [Entries] Table
	/** ***************************************** Insert datas in Entries Table *****************************************
	 * @brief : Insert a new entry in the [Entries "table,
	 *	need to be call after SqlQuery::connectToDB().
	 *
	 * @param employee_details : A reference of a object Employee (Required to set is ID, last name, first name, employee_email, employee_password)
	 * @param entry : A reference of a object Entry (Required to set is date, entry hour, exit hour)
	 */
	void insertNewEntry(const bll::Entry& entry);

	/** ***************************************** Extract info of an entry *****************************************
	* @brief : Extract the info of the entry with the selected Employee and date from the DB.
	*
	* @param employee_ID : int, ID of the employee
	* @param entry : std::string, the date of the entry (Format: YYYY-MM-DD)
	* @return  : Entry, with the id_entry, entry_date, entry_start, entry_end, employee_ID
	*/
	void getEntryWithEmployeeIdAndDate(bll::Entry& entry);


	// DB Management
	/** ***************************************** Connect to SQL DataBase *****************************************
	 * @brief : Make the connection with the mySQL Database.
	 *
	 * @return  : Boolean, true if connection is successful || false if any error is catch
	 */
	bool connectToDB();

	/* ***************************************** Drop all SQL tables (Debug) ****************************************
	*	Order matter (Foreign key) start by dropping the last table created
	*/	
	void dropAllTables();

	/* ***************************************** Create all SQL tables (Debug) *****************************************
	*	Order matter (Foreign key) start with the table who doesn't have Foreign key.
	*	In the string concatenation be CARFUL to the space after the comma
	*/	
	void createAllTables();


	// Admin
	/** ***************************************** Connect as an Admin *****************************************
	 * @brief : Will connect to the AdminPanel if the required inputs are correct,
	 *	the ID of the admin NEED to be "1" in the table [Employees].
	 *
	 * @param employee_admin : A reference of a object Employee (Required to set is employee_email and employee_password)
	 * @return  : Boolean, True if the employee_email and employee_password match with the ID "1" of the table [Employees] | False in the other cases
	 */
	bool connectAdmin(bll::Employee& employee_admin);

	/** ***************************************** Create a new employee *****************************************
	* @brief : Create an entry in the [employees] table need to be call
	*	after SqlQuery::connectToDB().
	*
	* @param employee : An object employee (need to set is last name, first name, employee_email, employee_password)
	*/
	void insertNewEmployee(bll::Employee& employee);

	// ***************************************** Update an employee *****************************************
	void updateEmployee(bll::Employee& employee);

	// ***************************************** Delete an employee *****************************************
	void deleteEmployee();

	/** ***************************************** Get all employees *****************************************
	 * @brief : Complete the passed vector with all Employees existing in the DB.
	 *
	 * @param vector_employees : std::vector<Employee>& => a vector
	 */
	void getAllEmployees(std::vector<bll::Employee>& vector_employees);
};

