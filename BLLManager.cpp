/*****************************************************************//**
 * @file   BLLManager.cpp
 * @brief  All call of dal::SqlQuery will be in this Class
 * 
 * @author ThJo
 * @entry_date   21 May 2024
 *********************************************************************/
#include "BLLManager.h"
#include "Entry.h"
#include "Employee.h"

namespace bll {
	/** ***************************************** Complet entry with mySQL *****************************************
	* @brief : Complet an object Entry with the data found in mySQL.
	*
	* @param entry : Entry& => employee_id, entry_date are required
	*/
	void completEntryWithEmployeeIdAndDate(Entry& entry) {
		dal::SqlQuery sql_connection;
		if (sql_connection.connectToDB()) {
			sql_connection.getEntryWithEmployeeIdAndDate(entry);
		}
	}

	/** ***************************************** Complet employee with mySQL *****************************************
	* @brief : Complet an object Employee with the data found in mySQL.
	*
	* @param employee : Employee& => employee_id is required
	*/
	void completEmployeeWithId(Employee& employee) {
		dal::SqlQuery sql_connection;
		if (sql_connection.connectToDB()) {
			sql_connection.getEmployeeWithId(employee);
		}
	}

	/** ***************************************** Complet employee with mySQL *****************************************
	 * @brief : Complet an object Employee with the data found in mySQL.
	 *
	 * @param employee : Employee& => email and password are required
	 */
	void completEmployeeWithEmailAndPw(Employee& employee) {
		dal::SqlQuery sql_connection;
		if (sql_connection.connectToDB()) {
			sql_connection.completEmployeeWithEmailAndPw(employee);
		}
	}

	/** ***************************************** Create new entry *****************************************
	 * @brief : Create a new entry inside the DB with the given parameters, all are required.
	 *
	 * @param employee_id : int => id of the employee
	 * @param entry_date : std::string& => date of the entry in format YYYY-MM-DD
	 * @param entry_start : std::string& => start hour of the entry in format HH:MM
	 * @param entry_end : std::string& => end hour of the entry in format HH:MM
	 * @return : boolean => true if the creation is a succes
	 */
	bool createNewEntry(const int employee_id, const std::string& entry_date, const std::string& entry_start, const std::string& entry_end) {
		dal::SqlQuery sql_connection;
		if (sql_connection.connectToDB()) {
			Entry entry;
			entry.setEmployeeId(employee_id);
			entry.setEntryDate(entry_date);
			entry.setEntryStart(entry_start);
			entry.setEntryEnd(entry_end);

			sql_connection.insertNewEntry(entry);
			return sql_connection.creation_success;
		}
		else {
			return false;
		}
	}

	/** ***************************************** Create Employee *****************************************
	 * @brief : Create a new employee inside the DB with the given parameters, all are required.
	 *
	 * @param emp_last_name : std::string& => employee last name
	 * @param emp_first_name : std::string& => employee first name
	 * @param emp_email : std::string& => employee email
	 * @param emp_password : std::string& => employee password
	 * @return  : boolean => true if the creation is a succes
	 */
	bool createNewEmployee(const std::string& emp_last_name, const std::string& emp_first_name, const std::string& emp_email, const std::string& emp_password) {
		dal::SqlQuery sql_connection;
		if (sql_connection.connectToDB()) {
			Employee employee;
			employee.setLastName(emp_last_name);
			employee.setFirstName(emp_first_name);
			employee.setEmail(emp_email);
			employee.setPassword(emp_password);

			sql_connection.insertNewEmployee(employee);
			return sql_connection.creation_success;
		}
		else {
			return false;
		}
	}

	/** ***************************************** Get vector of Employees from mySQL *****************************************
	* @brief : Fetches a vector with objects of type Employee from mySQL.
	*
	* @return : std::vector<Employee> => a vector of Employee objects
	*/
	std::vector<Employee> getVectorWithEmployees() {
		std::vector<Employee> vector_employees;

		dal::SqlQuery sql_connection;
		if (sql_connection.connectToDB()) {
			sql_connection.getAllEmployees(vector_employees);
		}
		return vector_employees;
	}

	/** ***************************************** Admin connection *****************************************
	 * @brief : Check if the given parameters are egal to the admin data in the DB.
	 *
	 * @param email : std::string => email of the admin
	 * @param password : std::string => password of the admin
	 * @return  : bool => true if exist in DB, false in any other cases
	 */
	bool checkAdminConnection(const std::string& email, const std::string& password) {
		Employee employee;
		employee.setEmail(email);
		employee.setPassword(password);

		dal::SqlQuery sql_connection;
		if (sql_connection.connectToDB()) {
			if (sql_connection.connectAdmin(employee)) {
				return true;
			}
		}
		return false;
	}

	/** ***************************************** Employee connection *****************************************
	 * @brief : Check if the given parameters are egal to the employee data in the DB.
	 *
	 * @param email : std::string => email of the employee
	 * @param password : std::string => password of the employee
	 * @return  : bool => true if exist in DB, false in any other cases
	 */
	bool checkEmployeeConnection(const std::string& email, const std::string& password) {
		Employee employee;
		employee.setEmail(email);
		employee.setPassword(password);

		dal::SqlQuery sql_connection;
		 if (sql_connection.connectToDB()) {
			 if (sql_connection.checkEmployee(employee)) {
				 return true;
			 }
		 }
		 return false;
	}

	/** ***************************************** Get Employee *****************************************
	 * @brief : Return an object Employee with all is data fetch from the DB.
	 *
	 * @param email : std::string => email of the employee
	 * @param password : std::string => password of the employee
	 * @return  : Employee => with email, last name, first name, employee ID
	 */
	 Employee getEmployeeWithEmailAndPw(const std::string& email, const std::string& password) {
		Employee employee(email, password);

		return Employee(employee);
	}

} // namespace bll
