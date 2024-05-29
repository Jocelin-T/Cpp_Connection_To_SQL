/*****************************************************************//**
 * @file   SQL_Management.cpp
 * @brief  Class for all SQL DataBase connection and management (Console)
 * 
 * @author ThJo
 * @date   24 April 2024
 *********************************************************************/
// ####################################### Import #######################################
#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>
#include <iomanip>

// SQL libraries
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>

// Class (header)
#include "SQL_Query_Console.h"
#include "QOLandDebug.h"
#include "MainFrame.h"

// ***************************************** Connect to SQL DataBase *****************************************
void SQL_Query_Console::connectToDB() {
		wxString msg;
	try {
		// Variables are in the class header: SQL_Management.h
		pDriver = get_driver_instance();
		pSql_connection = pDriver->connect(DB_SERVER, DB_USERNAME, DB_PASSWORD);
		pSql_connection->setSchema(DATABASE);
		std::cout << "Connected to server: " << DB_SERVER << "\nAs: " << DB_USERNAME << "\nTo DB: " << DATABASE << "\n";
	}
	catch (sql::SQLException e) { // In case of an Error: Display a message and stop the programm
		std::cout << "Could not connect to server. Error message: " << e.what() << "\n";

		system("pause");
		exit(1);
	}
	QOLandDebug console;
	console.pauseAndClear();
}

/* ***************************************** Drop all SQL tables (Debug) ****************************************
*	Order matter (Foreign key) start by dropping the last table created
*/
void SQL_Query_Console::dropAllTables() {
	try {
		// Unique pointer for the connection management
		std::unique_ptr<sql::Statement> statement(pSql_connection->createStatement());

		// Drop table [entries] if it already exist
		statement->execute("DROP TABLE IF EXISTS " + TBL_ENTRIES);
		std::cout << "Dropping table [" + TBL_ENTRIES + "] if exists\n";

		// Drop table [employees] if it already exist
		statement->execute("DROP TABLE IF EXISTS " + TBL_EMPLOYEES);
		std::cout << "Dropping table [" + TBL_EMPLOYEES + "] if exists\n";
	}
	catch (sql::SQLException& e) {
		std::cout << "Drop table failed:\n" << "SQL Error: " << e.what() << "\n";
	}
}

/* ***************************************** Create all SQL tables (Debug) *****************************************
*	Order matter (Foreign key) start with the table who doesn't have Foreign key.
*	In the string concatenation be CARFUL to the space after the comma
*/
void SQL_Query_Console::createAllTables() {
	try {
		// Unique pointer for the connection management
		std::unique_ptr<sql::Statement> statement(pSql_connection->createStatement());

		// """"""""""""""""""" Table [employees] """""""""""""""""""
		std::string sqlCreateEmployeesTbl = "CREATE TABLE " + TBL_EMPLOYEES + " ("
			"id_emp INT PRIMARY KEY AUTO_INCREMENT, "
			"emp_last_name VARCHAR(32), "
			"emp_first_name VARCHAR(32), "
			"emp_email VARCHAR(50), "
			"emp_password VARCHAR(18)); ";
		statement->execute(sqlCreateEmployeesTbl);
		std::cout << "Table [" + TBL_EMPLOYEES + "] created\n";

		// """"""""""""""""""" Table [entries] """""""""""""""""""
		std::string sqlCreateEntriesTbl = "CREATE TABLE " + TBL_ENTRIES + "  ("
			"id_day INT PRIMARY KEY AUTO_INCREMENT, "
			"day_current DATE, "
			"day_start DATETIME, "
			"day_end DATETIME, "
			"id_emp INT, "
			"FOREIGN KEY(id_emp) REFERENCES " + TBL_EMPLOYEES + "(id_emp));";
		statement->execute(sqlCreateEntriesTbl);
		std::cout << "Table [" + TBL_ENTRIES + "] created\n";
	}
	catch (sql::SQLException& e) {
		std::cout << "Tables creation failed:\n" << "SQL Error: " << e.what() << "\n";
	}
}

// ***************************************** Show all tables *****************************************
void SQL_Query_Console::showAllTables() {
	try {
		// Unique pointer for the connection management
		std::unique_ptr<sql::Statement> statement(pSql_connection->createStatement());
		// Execute query and store result
		std::unique_ptr<sql::ResultSet> res(statement->executeQuery("SHOW TABLES;"));

		std::cout << "Current tables in " << DATABASE << " database:\n";

		// Loop true the table name and show them in the console
		while (res->next()) {
			std::cout << res->getString(1) << "\n";
		}
	}
	catch (sql::SQLException& e) {
		std::cout << "Show all tables failed:\n" << "SQL Error: " << e.what() << "\n";
	}
}

/** ***************************************** Show 1 table *****************************************
 * @brief : This method will display in console all data from the selected table.
 * 
 * @param table_name : The table you want to display
 */
void SQL_Query_Console::showTable(std::string table_name) {
	try {
		// Unique pointer for the connection management
		std::unique_ptr<sql::Statement> statement(pSql_connection->createStatement());
		// Execute query and store result
		std::unique_ptr<sql::ResultSet> res(statement->executeQuery("SELECT * FROM " + table_name + ";"));
		// Get the number of columns with metadata (can't be unique_ptr because "getMetaData()" is a protected method)
		sql::ResultSetMetaData* meta = res->getMetaData();
		int numColumns = meta->getColumnCount();

		// Loop true the column and their names
		std::cout << "Data in " << table_name << " table:\n";
		for (int i = 1; i <= numColumns; i++) {
			std::cout << std::setw(20) << std::left << meta->getColumnName(i);
		}
		std::cout << "\n";

		// Loop true the rows and display the data
		while (res->next()) {
			for (int i = 1; i <= numColumns; i++) {
				std::cout << std::setw(20) << std::left << res->getString(i);
			}
			std::cout << "\n";
		}
	}
	catch (sql::SQLException& e) {
		std::cout << "Show table [" << table_name << "] failed:\n" << "SQL Error: " << e.what() << "\n";
	}
}


// ***************************************** Create a new employee *****************************************
void SQL_Query_Console::createEmployee() {
	std::string employee_last_name;
	std::string employee_first_name;
	std::string employee_email;
	std::string employee_password;
	std::string temp_conf;
	bool confirmed = false;
	try {
		// Unique pointer for the SQL query insert into [employees] table
		std::unique_ptr<sql::PreparedStatement> prep_statement(
			pSql_connection->prepareStatement("INSERT INTO " + TBL_EMPLOYEES + "(emp_last_name, emp_first_name, emp_email, emp_password) "
				"VALUES (?, ?, ?, ?)"));

		// Wait for the user confirmation
		while (!confirmed) {
			// User entries all values needed
			std::cout << "Creation of a new employee:\n\n";
			std::cout << "Enter the Last Name: ";
			std::cin >> employee_last_name;
			std::cout << "Enter the First Name: ";
			std::cin >> employee_first_name;
			std::cout << "Enter the Email: ";
			std::cin >> employee_email;
			std::cout << "Enter the Password: ";
			std::cin >> employee_password;
			system("cls");

			// Show the result of the added employee
			std::cout << "Employee created:\n" << "Last Name: " << employee_last_name << 
										"\nFirst Name: " << employee_first_name << 
										"\nEmail: " << employee_email << 
										"\nPassword: " << employee_password << "\n\n";
			// Ask for the confirmation
			std::cout << "You want to confirm this creation (Y/N)";
			std::cin >> temp_conf;
			temp_conf == "Y" || temp_conf == "y" ? confirmed = true : confirmed = false;
		}

		// Bind data to parameters (it's egale to the [?] of VALUES)
		prep_statement->setString(1, employee_last_name);
		prep_statement->setString(2, employee_first_name);
		prep_statement->setString(3, employee_email);
		prep_statement->setString(4, employee_password);

		// Execute the statement
		prep_statement->executeUpdate();
	}
	catch(sql::SQLException& e){
		std::cout << "Creation of an employee failed:\n" << "SQL Error: " << e.what() << "\n";
	}
}

// ***************************************** Update a employee *****************************************
void SQL_Query_Console::updateEmployee() {

}

// ***************************************** Delete a employee *****************************************
void SQL_Query_Console::deleteEmployee() {

}

// ***************************************** Connect as an employee *****************************************
void SQL_Query_Console::connectAsEmployee() {

}

// ***************************************** User select 1 table to show  *****************************************
void SQL_Query_Console::userSelectTableToShow() {
	std::string table_name;
	showAllTables();
	std::cout << "Enter the table you would like to see: ";
	std::cin >> table_name;
	showTable(table_name);
}