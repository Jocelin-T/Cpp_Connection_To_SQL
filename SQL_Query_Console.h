/*****************************************************************//**
 * @file   SQL_Query_Console.h
 * @brief  Class (header) for all SQL DataBase connection and management  (Console)
 * 
 * @author ThJo
 * @date   24 April 2024
 *********************************************************************/
#pragma once
// ####################################### Import #######################################
#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>

// SQL libraries
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

// ####################################### Class SQL_Query_Console (Header) #######################################
class SQL_Query_Console {
public:
	// ***************************************** Public Attributes *****************************************
	const std::string DB_SERVER = "tcp://127.0.0.1:3306";
	const std::string DB_USERNAME = "root";
	const std::string DB_PASSWORD = ""; // Never save employee_password in code
	const std::string DATABASE = "orif_ex_connect_to_cpp";

	// Tables name
	const std::string TBL_ENTRIES = "entries";
	const std::string TBL_EMPLOYEES = "employees";

	sql::Driver* pDriver;
	sql::Connection* pSql_connection;
	sql::Statement* pStatement;
	sql::PreparedStatement* pPrep_statement;

	// Constructor
	SQL_Query_Console() : pDriver(nullptr), pSql_connection(nullptr), pStatement(nullptr), pPrep_statement(nullptr) {}

	// ***************************************** Connect to SQL DataBase *****************************************
	void connectToDB();

	// ***************************************** Drop all SQL tables (Debug) *****************************************
	void dropAllTables();

	// ***************************************** Create all SQL tables (Debug) *****************************************
	void createAllTables();

	// ***************************************** Show all SQL tables *****************************************
	void showAllTables();

	/** ***************************************** Show 1 table *****************************************
	 * @brief : This method will display in console all data from the selected table.
	 *
	 * @param table_name : The table you want to display
	 */
	void showTable(std::string table_name);

	// ***************************************** Create a new employee *****************************************
	void createEmployee();

	// ***************************************** Update a employee *****************************************
	void updateEmployee();

	// ***************************************** Delete a employee *****************************************
	void deleteEmployee();

	// ***************************************** Connect as an employee *****************************************
	void connectAsEmployee();



	// ***************************************** User select 1 table to show *****************************************
	void userSelectTableToShow();




	// Destructor (for a clean memory management)
	~SQL_Query_Console() {
		delete pSql_connection;
		delete pStatement;
		delete pPrep_statement;
		// Don't need to delete the driver (driver manager does the work)
	}
};

