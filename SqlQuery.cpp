/*****************************************************************//**
 * @file   SqlQuery.cpp
 * @brief  Class for all SQL DataBase connection and query (App)
 *
 * @author ThJo
 * @date   29 April 2024
 *********************************************************************/
#include "SqlQuery.h"
#include "Entry.h"
#include "Employee.h"


// Default Constructor
SqlQuery::SqlQuery()
	:m_pDriver(nullptr), m_pSql_connection(nullptr), m_pStatement(nullptr), m_pPrep_statement(nullptr)
{}

 /** ####################################### Employees ##################################### */
/** ***************************************** Connect as an employee *****************************************
 * @brief : Check if the user exist in the table [Employees].
 * 
 * @param employee : bll::Employee& => (Required to set his employee_email and employee_password)
 * @return  : Boolean => True if the input exist and matches || False in any other cases
 */
bool SqlQuery::checkEmployee(bll::Employee& employee) {
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
			m_pSql_connection->prepareStatement(
				"SELECT emp_password " 
				" FROM " + m_TBL_EMPLOYEES + 
				" WHERE emp_email = ?;" 
			)); // "?" is a placeholder and can stop SQL injection

		// Bind the employee_email parameter
		m_pPrep_statement->setString(1, employee.getEmail());

		// Execute the query
		std::unique_ptr<sql::ResultSet> result(m_pPrep_statement->executeQuery());
		
		// Check the result
		if (result->next()) { // check if the row is available
			std::string storedPassword = result->getString("emp_password");
			if (storedPassword == employee.getPassword()) {
				return true; // Password is correct
			}
			else {
				return false; // Password is Incorrect
			}
		}
		return false; // No user with that employee_email
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::checkEmployee", e);
		return false; // Error
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::checkEmployee", e);
		return false; // Error
	}
}

/** ***************************************** Complet data of an employee *****************************************
 * @brief : Complet the data of the given employee with the DB.
 * 
 * @param employee : bll::Employee&, emp_email and emp_password are required
 */
void SqlQuery::completEmployeeWithEmailAndPw(bll::Employee& employee){
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		// Prepare SQL query to fetch employee details with is employee_email and pw
		std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
			m_pSql_connection->prepareStatement(
				"SELECT id_emp, "
				"emp_last_name, "
				"emp_first_name "
				"FROM employees "
				"WHERE emp_email = ? AND emp_password = ?;"
			));

		// Insert inside the placeholder (!SQL injection)
		m_pPrep_statement->setString(1, employee.getEmail());
		m_pPrep_statement->setString(2, employee.getPassword());

		// Execute the query
		std::unique_ptr<sql::ResultSet> result(m_pPrep_statement->executeQuery());

		// Check if the results are found
		if (result->next()) {
			// Extract data from "result" and set them to the employee object
			employee.setEmployeeId(result->getInt("id_emp"));
			employee.setLastName(result->getString("emp_last_name"));
			employee.setFirstName(result->getString("emp_first_name"));
		}
		else {
			throw std::runtime_error("No employee found");
		}
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::completEmployeeWithEmailAndPw", e);
		throw;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::completEmployeeWithEmailAndPw", e);
		throw;
	}
}

/** ***************************************** Extract info of an employee *****************************************
 * @brief : Extract the info of the current connected employee from the DB.
 * 
 * @param employeeId : Employee, with is emp_id
 * @return  : Employee, with is emp_id, emp_last_name, emp_first_name, emp_email
 */
void SqlQuery::getEmployeeWithId(bll::Employee& employee) {
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		// Prepare SQL query to fetch employee details with is emp_id
		std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
			m_pSql_connection->prepareStatement("SELECT id_emp, "
				"emp_last_name, "
				"emp_first_name, "
				"emp_email "
				"FROM employees "
				"WHERE id_emp = ?;"));

		// Insert inside the placeholder (!SQL injection)
		m_pPrep_statement->setInt(1, employee.getEmployeeId());

		// Execute the query
		std::unique_ptr<sql::ResultSet> result(m_pPrep_statement->executeQuery());

		// Check if the results are found
		if (result->next()) {
			// Extract data from "result" and set them to the employee object
			employee.setEmployeeId(result->getInt("id_emp"));
			employee.setLastName(result->getString("emp_last_name"));
			employee.setFirstName(result->getString("emp_first_name"));
			employee.setEmail(result->getString("emp_email"));
		}
		else {
			throw std::runtime_error("No employee found with the specified ID.");
		}
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::getEmployeeWithId", e);
		throw;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::getEmployeeWithId", e);
		throw;
	}
}


/** ####################################### Entries ##################################### */
/** ***************************************** Insert datas in [Entries] Table *****************************************
 * @brief : Insert a new entry in the [Entries] table,
 *
 * @param entry : A reference of a object Entry (Required to set is date, entry hour, exit hour, employee ID)
 */
void SqlQuery::insertNewEntry(const bll::Entry& entry) {

	creation_success = false;
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		// Unique pointer for the SQL query insert into [entries] table
		std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
			m_pSql_connection->prepareStatement(
				"INSERT INTO " + m_TBL_ENTRIES +
				"(entry_date, entry_start, entry_end, id_emp) "
				"VALUES (?, ?, ?, ?)"
			));

		// Bind data to parameters (it's egale to the [?] inside VALUES)
		m_pPrep_statement->setString(1, std::string(entry.getEntryDate()));
		m_pPrep_statement->setString(2, std::string(entry.getEntryStart()));
		m_pPrep_statement->setString(3, std::string(entry.getEntryEnd()));
		m_pPrep_statement->setInt(4, int(entry.getEmployeeId()));

		// Execute the statement
		m_pPrep_statement->executeUpdate();
		wxMessageBox("Creation of the entry done!", "Success",
			wxOK | wxICON_INFORMATION);
		creation_success = true;
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::insertNewEntry", e);
		creation_success = false;
		throw;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::insertNewEntry", e);
		creation_success = false;
		throw;
	}
}

/** ***************************************** Extract data of an entry *****************************************
 * @brief : Complete the object Entry with the data in the DB.
 * 
 * @param entry : bll::Entry&, with the employee_ID, entry_date
 */
void SqlQuery::getEntryWithEmployeeIdAndDate(bll::Entry& entry){
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();
		
		// Prepare SQL query to fetch entry details with is id_emp and entry_date
		std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
			m_pSql_connection->prepareStatement(
				"SELECT id_entry, entry_start, entry_end"
				" FROM " + m_TBL_ENTRIES +
				" WHERE id_emp = ? AND entry_date = ?;"
			));

		// Insert inside the placeholder (Prevent SQL injection)
		m_pPrep_statement->setInt(1, entry.getEmployeeId());
		m_pPrep_statement->setString(2, entry.getEntryDate());

		// Execute the query
		std::unique_ptr<sql::ResultSet> result(m_pPrep_statement->executeQuery());

		// Check if the results are found
		if (result->next()) {
			// Extract data from "result" and set them to the entry object
			entry.setEntryStart(result->getString("entry_start"));
			entry.setEntryEnd(result->getString("entry_end"));
			entry.setEntryID(result->getInt("id_entry"));
		}
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::getEntryWithEmployeeIdAndDate", e);
		throw;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::getEntryWithEmployeeIdAndDate", e);
		throw;
	}
}


/** ####################################### DB Management ##################################### */
/** ***************************************** Connect to SQL DataBase *****************************************
 * @brief : Make the connection with mySQL Database.
 * 
 * @return  : Boolean, true if connection is successful || false if any error is catch
 */
bool SqlQuery::connectToDB() {
	try {
		// Variables are in the class header: SQL_Management.h
		m_pDriver = get_driver_instance();
		m_pSql_connection = m_pDriver->connect(m_DB_SERVER, m_DB_USERNAME, m_DB_PASSWORD);
		m_pSql_connection->setSchema(m_DATABASE);

		wxLogStatus(wxString::Format("Connected to server: %s || As: %s || To DB: %s",
			m_DB_SERVER,
			m_DB_USERNAME,
			m_DATABASE));

		return true;
	}
	catch (const sql::SQLException& e) {
		m_pSql_connection = nullptr;
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::connectToDB", e);
		return false;
	}
	catch (const std::runtime_error& e) {
		m_pSql_connection = nullptr;
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::connectToDB", e);
		return false;
	}
}

/* ***************************************** Drop all SQL tables (Debug) ****************************************
*	Order matter (Foreign key) start by dropping the last table created
*/
void SqlQuery::dropAllTables() {
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		// Unique pointer for the connection management
		std::unique_ptr<sql::Statement> statement(m_pSql_connection->createStatement());

		// Drop table [entries] if it already exist
		statement->execute("DROP TABLE IF EXISTS " + m_TBL_ENTRIES);
		std::cout << "Dropping table [" + m_TBL_ENTRIES + "] if exists\n";

		// Drop table [employees] if it already exist
		statement->execute("DROP TABLE IF EXISTS " + m_TBL_EMPLOYEES);
		std::cout << "Dropping table [" + m_TBL_EMPLOYEES + "] if exists\n";
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::dropAllTables", e);
		throw;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::dropAllTables", e);
		throw;
	}
}

/* ***************************************** Create all SQL tables (Debug) *****************************************
*	Order matter (Foreign key) start with the table who doesn't have Foreign key.
*	In the string concatenation be CARFUL to the space after the comma
*/
void SqlQuery::createAllTables() {
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		// Unique pointer for the connection management
		std::unique_ptr<sql::Statement> statement(m_pSql_connection->createStatement());

		// """"""""""""""""""" Table [employees] """""""""""""""""""
		std::string sqlCreateEmployeesTbl = "CREATE TABLE " + m_TBL_EMPLOYEES + " ("
			"id_emp INT PRIMARY KEY AUTO_INCREMENT, "
			"emp_last_name VARCHAR(32), "
			"emp_first_name VARCHAR(32), "
			"emp_email VARCHAR(50), "
			"emp_password VARCHAR(18)); ";
		statement->execute(sqlCreateEmployeesTbl);

		// """"""""""""""""""" Table [entries] """""""""""""""""""
		std::string sqlCreateEntriesTbl = "CREATE TABLE " + m_TBL_ENTRIES + "  ("
			"id_entry INT PRIMARY KEY AUTO_INCREMENT, "
			"entry_date DATE, "
			"entry_start DATETIME, "
			"entry_end DATETIME, "
			"id_emp INT, "
			"FOREIGN KEY(id_emp) REFERENCES " + m_TBL_EMPLOYEES + "(id_emp));";
		statement->execute(sqlCreateEntriesTbl);

		// """"""""""""""""""" Insert the Admin in index "1" of table [Employees] """""""""""""""""""
		SqlQuery sql_connection;
		if (sql_connection.connectToDB()) {
			// Unique pointer for the SQL query insert into [employees] table
			std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
				m_pSql_connection->prepareStatement("INSERT INTO " + m_TBL_EMPLOYEES +
					"(emp_last_name, emp_first_name, emp_email, emp_password) "
					"VALUES (?, ?, ?, ?)"));

			// Bind data to parameters (it's egale to the [?] inside VALUES)
			m_pPrep_statement->setString(1, std::string("Admin"));
			m_pPrep_statement->setString(2, std::string("Admin"));
			m_pPrep_statement->setString(3, std::string("adm")); // Email
			m_pPrep_statement->setString(4, std::string("admin")); // Password

			// Execute the statement
			m_pPrep_statement->executeUpdate();
			wxMessageBox("Creation of the Admin done!", "Success",
				wxOK | wxICON_INFORMATION);
		}
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::createAllTables", e);
		throw;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::createAllTables", e);
		throw;
	}
}



/** ####################################### Admin ##################################### */
/** ***************************************** Connect as an Admin *****************************************
 * @brief : Will connect to the AdminPanel if the required inputs are correct,
 *	the ID of the admin NEED to be "1" in the table [Employees].
 * 
 * @param employee_admin : A reference of a object Employee (Required to set is employee_email and employee_password)
 * @return  : Boolean, True if the employee_email and employee_password match with the ID "1" of the table [Employees] |
 *					 False in the other cases
 */
bool SqlQuery::connectAdmin(bll::Employee& employee_admin){
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
			m_pSql_connection->prepareStatement("SELECT emp_password, id_emp FROM " + m_TBL_EMPLOYEES +
				" WHERE emp_email = ?;")); // "?" is a placeholder and can stop SQL injection

		// Bind the employee_email parameter
		m_pPrep_statement->setString(1, employee_admin.getEmail());

		// Execute the query
		std::unique_ptr<sql::ResultSet> result(m_pPrep_statement->executeQuery());

		// Check the result
		if (result->next()) { // check if the row is available
			std::string storedPassword = result->getString("emp_password");
			int storedID = result->getInt("id_emp");
			if (storedPassword == employee_admin.getPassword() && storedID == 1) {
				return true; // Password is correct and ID are correct
			}
			else {
				return false; // Password is Incorrect
			}
		}
		return false; // No user with that employee_email
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::connectAdmin", e);
		return false;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::connectAdmin", e);
		return false;
	}
}

/** ***************************************** Insert a new employee *****************************************
 * @brief : Insert a new employee in the [employees] table,
 *  need to be call after SqlQuery::connectToDB().
 *
 * @param employee : A reference of a object Employee (Required to set is last name, first name, employee_email, employee_password)
 */
void SqlQuery::insertNewEmployee(bll::Employee& employee) {
	creation_success = false;
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		// Unique pointer for the SQL query insert into [employees] table
		std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
			m_pSql_connection->prepareStatement(
				"INSERT INTO " + m_TBL_EMPLOYEES +
				"(emp_last_name, emp_first_name, emp_email, emp_password) "
				"VALUES (?, ?, ?, ?)"));

		// Bind data to parameters (it's egale to the [?] inside VALUES)
		m_pPrep_statement->setString(1, std::string(employee.getLastName()));
		m_pPrep_statement->setString(2, std::string(employee.getFirstName()));
		m_pPrep_statement->setString(3, std::string(employee.getEmail()));
		m_pPrep_statement->setString(4, std::string(employee.getPassword()));

		// Execute the statement
		m_pPrep_statement->executeUpdate();
		wxMessageBox("Creation of the employee done!", "Success",
			wxOK | wxICON_INFORMATION);
		creation_success = true;
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::insertNewEmployee", e);
		creation_success = false;
		throw;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::insertNewEmployee", e);
		creation_success = false;
		throw;
	}
}

// ***************************************** Update a employee *****************************************
void SqlQuery::updateEmployee(bll::Employee& employee) {

}

// ***************************************** Delete a employee *****************************************
void SqlQuery::deleteEmployee() {

}

/** ***************************************** Get all employees *****************************************
 * @brief : Complete the passed vector with all Employees existing in the DB.
 * 
 * @param vector_employees : std::vector<Employee>& => a vector
 */
void SqlQuery::getAllEmployees(std::vector<bll::Employee>& vector_employees){
	try {
		// Ensure the SQL connection is open
		checkSQLConnection();

		// Prepare SQL query to fetch all employee details
		std::unique_ptr<sql::PreparedStatement> m_pPrep_statement(
			m_pSql_connection->prepareStatement(
				"SELECT id_emp, emp_last_name, emp_first_name, emp_email "
				"FROM " + m_TBL_EMPLOYEES + ";"
			));

		// Execute the query
		std::unique_ptr<sql::ResultSet> result(m_pPrep_statement->executeQuery());

		// Loop through the result and create a object Employee each time
		while (result->next()) {
			bll::Employee employee;
			employee.setEmployeeId(result->getInt("id_emp"));
			employee.setLastName(result->getString("emp_last_name"));
			employee.setFirstName(result->getString("emp_first_name"));
			employee.setEmail(result->getString("emp_email"));

			// Add the created Employee object to the vector
			vector_employees.push_back(employee);
		}
	}
	catch (const sql::SQLException& e) {
		ErrorHandling::displayMessageBoxSqlError("SqlQuery::getAllEmployees", e);
		throw;
	}
	catch (const std::runtime_error& e) {
		ErrorHandling::displayMessageBoxRunTimeError("SqlQuery::getAllEmployees", e);
		throw;
	}
}


/** ***************************************** SQL Connection *****************************************
 * @brief : Throw a std::runtime_error message in case the connection with mySQL is not open.
 * 
 */
void SqlQuery::checkSQLConnection() {
	// Ensure that the SQL connection is open
	if (!m_pSql_connection) {
		throw std::runtime_error("Database connection is not open.");
	}
}


/** ***************************************** Destructor *****************************************
 * @brief : Don't need to delete the driver (driver manager does the work).
 * 
 */
SqlQuery::~SqlQuery() {
	if (m_pSql_connection) {
		delete m_pSql_connection;
		m_pSql_connection = nullptr;  // Clear the pointer after deleting
	}
	if (m_pStatement) {
		delete m_pStatement;
		m_pStatement = nullptr;
	}
	if (m_pPrep_statement) {
		delete m_pPrep_statement;
		m_pPrep_statement = nullptr;
	}
}
