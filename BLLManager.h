/*****************************************************************//**
 * @file   BLLManager.h
 * @brief  All call of SqlQuery will be in this Class
 * 
 * @author ThJo
 * @date   21 May 2024
 *********************************************************************/
#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <map>
#include <queue>


#include "SqlQuery.h"
#include "Salary.h"

// Forward declaration
class Entry;
class Employee;

namespace bll {
	/** ***************************************** Complet entry with mySQL *****************************************
	 * @brief : complet an object Entry with the data find in mySQL.
	 *
	 * @param entry : Entry& -> employee_id, entry_date are required
	 */
	void completEntryWithEmployeeIdAndDate(Entry& entry);

	/** ***************************************** Complet employee with mySQL *****************************************
	 * @brief : Complet an object Employee with the data found in mySQL.
	 *
	 * @param employee : Employee& => employee_id is required
	 */
	void completEmployeeWithId(Employee& employee);

	/** ***************************************** Complet employee with mySQL *****************************************
	* @brief : Complet an object Employee with the data found in mySQL.
	*
	* @param employee : Employee& => email and password are required
	*/
	void completEmployeeWithEmailAndPw(Employee& employee);

	/** ***************************************** Create new entry *****************************************
	 * @brief : Create a new entry inside the DB with the given parameters, all are required.
	 *
	 * @param employee_id : int => id of the employee
	 * @param entry_date : std::string& => date of the entry in format YYYY-MM-DD
	 * @param entry_start : std::string& => start hour of the entry in format HH:MM
	 * @param entry_end : std::string& => end hour of the entry in format HH:MM
	 * @return : boolean => true if the creation is a succes
	 */
	bool createNewEntry(const int employee_id, const std::string& entry_date, const std::string& entry_start, const std::string& entry_end);

	/** ***************************************** TO DO *****************************************
	 * @brief : Create a new employee inside the DB with the given parameters, all are required.
	 *
	 * @param emp_last_name : std::string& => employee last name
	 * @param emp_first_name : std::string& => employee first name
	 * @param emp_email : std::string& => employee email
	 * @param emp_password : std::string& => employee password
	 * @return  : boolean => true if the creation is a succes
	 */
	bool createNewEmployee(const std::string& emp_last_name, const std::string& emp_first_name, const std::string& emp_email, const std::string& emp_password);

	/** ***************************************** Get vector of Employees from mySQL *****************************************
	* @brief : Fetches a vector with objects of type Employee from mySQL.
	*
	* @return : std::vector<Employee> => a vector of Employee objects
	*/
	std::vector<Employee> getVectorWithEmployees();

	/** ***************************************** Get Salaries of one Employee *****************************************
	 * @brief : Create a vector with all Salaries of 1 employee, depending the period choosed.
	 *  NEED to destroy the vector after use.
	 *
	 * @param employee_id : int => ID of the employee
	 * @param entry_date : std::string& => first date for weeks and month
	 * @param period : int => period choosed
	 * @param salary_per_hour : int => salary per hour
	 * @return  : std::vector<Salary>
	 */
	std::vector<Salary> getSalariesOfOneEmployee(const int employee_id, const std::string& entry_date, const int period, const int salary_per_hour);

	/** ***************************************** Get yearly wages of all Employees *****************************************
	 * @brief : Create a map with all the employee_id and yearly wages.
	 *
	 * @param year : std::string& => the choosen year
	 * @return  : std::map<int, int> => employee_id, yearly wages
	 */
	std::map<int, int> getYearlyWagesOfAllEmployees(const std::string& year);


	void getYearlySalariesOfOneEmployee(const std::string& year, const std::vector<Employee>& vector_employees, size_t start, size_t end);


	void calculateYearlyWages(std::map<int, int>& map);

	/** ***************************************** Manual Destroyer *****************************************
	 * @brief : NEED to be call when done with getSalary() for avoiding memory leak.
	 *
	 * @param vector_salaries : std::vector<Salary>& => vector to clear
	 */
	void destroySalaries(std::vector<Salary>& vector_salaries);

	/** ***************************************** Get total wages *****************************************
	 * @brief : Calculate the total wages from all Salary.
	 *
	 * @param vector_salaries : std::vector<Salary>& => vector holding salaries
	 * @return  : int
	 */
	int getTotalWages(const std::vector<Salary>& vector_salaries);

	/** ***************************************** Adjust the date *****************************************
	 * @brief : Adjust the date depending the month.
	 *
	 * @param base_date : std::string& => the first date
	 * @param days_offset : int => the current iteration
	 * @return  : std::string => the date in YYYY-MM_DD
	 */
	std::string getAdjustedDate(const std::string& base_date, int days_offset);

	/** ***************************************** Admin connection *****************************************
	 * @brief : Check if the given parameters are egal to the admin data in the DB.
	 *
	 * @param email : std::string => email of the admin
	 * @param password : std::string => password of the admin
	 * @return  : bool => true if exist in DB, false in any other cases
	 */
	bool checkAdminConnection(const std::string& email, const std::string& password);

	/** ***************************************** Employee connection *****************************************
	 * @brief : Check if the given parameters are egal to the employee data in the DB.
	 *
	 * @param email : std::string => email of the employee
	 * @param password : std::string => password of the employee
	 * @return  : bool => true if exist in DB, false in any other cases
	 */
	bool checkEmployeeConnection(const std::string& email, const std::string& password);

	/** ***************************************** Get Employee *****************************************
	 * @brief : Return an object Employee with all is data fetch from the DB.
	 *
	 * @param email : std::string => email of the employee
	 * @param password : std::string => password of the employee
	 * @return  : Employee => with email, last name, first name, employee ID
	 */
	Employee getEmployeeWithEmailAndPw(const std::string& email, const std::string& password);

	/** ***************************************** First Name Format *****************************************
	 * @brief : Transform the std::string received in this format: (Examplename) or (Example-Name).
	 *
	 * @param first_name : std::string& => first name
	 * @return  : std::string
	 */
	std::string formatFirstName(const std::string& first_name);

	/** ***************************************** Last Name Format *****************************************
	 * @brief : Transform the std::string received in this format: (EXAMPLENAME) or (EXAMPLE-NAME) or (EXEMPLE NAME).
	 *
	 * @param last_name : std::string& => last name
	 * @return  : std::string
	 */
	std::string formatLastName(const std::string& last_name);

} // namespace BLL
