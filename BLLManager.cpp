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
#include "Salary.h"

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

	/** ***************************************** Create new Employee *****************************************
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
			employee.setLastName(formatLastName(emp_last_name));
			employee.setFirstName(formatFirstName(emp_first_name));
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

	/** ***************************************** Get Salaries *****************************************
	 * @brief : Crate a vector with all Salary, depending the period choosed. NEED to destroy the vector after use.
	 * 
	 * @param employee_id : int => ID of the employee
	 * @param entry_date : std::string& => first date for weeks and month
	 * @param period : int => period choosed
	 * @param salary_per_hour : int => salary per hour
	 * @return  : std::vector<Salary>
	 */
	std::vector<Salary> getSalaries(const int employee_id, const std::string& entry_date, const int period, const int salary_per_hour) {
		std::vector<Salary> list_salaries;
		switch (period) {
		case 0: // Daily
			list_salaries.emplace_back(Salary(employee_id, entry_date, salary_per_hour));
			break;
		case 1: // Weekly
			// Calculate the start and end dates of the week
			for (int i = 0; i < 7; ++i) {
				// Adjust entry_date to get each day of the week
				std::string day_date = getAdjustedDate(entry_date, i);
				list_salaries.emplace_back(Salary(employee_id, day_date, salary_per_hour));
			}
			break;
		case 2: // Monthly
			// Calculate the start and end dates of the month
			for (int i = 0; i < 30; ++i) {
				// Adjust entry_date to get each day of the month
				std::string day_date = getAdjustedDate(entry_date, i);
				list_salaries.emplace_back(Salary(employee_id, day_date, salary_per_hour));
			}
			break;
		default:
			break;
		}		
		return list_salaries;
	}

	/** ***************************************** Manual Destroyer *****************************************
	 * @brief : NEED to be call when done with getSalary() for avoiding memory leak.
	 * 
	 * @param vector_salaries : std::vector<Salary>& => vector to clear
	 */
	void destroySalaries(std::vector<Salary>& vector_salaries) {
		if (!vector_salaries.empty()) {
			std::reverse(vector_salaries.begin(), vector_salaries.end());
			for (Salary& salary : vector_salaries) {
				salary.destroySalary();
			}
			vector_salaries.clear();
		}
	}

	/** ***************************************** Get total wages *****************************************
	 * @brief : Calculate the total wages from all Salary.
	 * 
	 * @param vector_salaries : std::vector<Salary>& => vector holding salaries
	 * @return  : int
	 */
	int getTotalWages(const std::vector<Salary>& vector_salaries) {
		int total{ 0 };
		for (const Salary& salary : vector_salaries) {
			total += salary.getWages();
		}
		return total;
	}


	/** ***************************************** Adjust the date *****************************************
	 * @brief : Adjust the date depending the month.
	 * 
	 * @param base_date : std::string& => the first date
	 * @param days_offset : int => the current iteration
	 * @return  : std::string => the date in YYYY-MM_DD
	 */
	std::string getAdjustedDate(const std::string& base_date, int days_offset) {
		// Parse base_date into a std::tm structure
		std::tm tm = {};
		std::istringstream ss(base_date);
		ss >> std::get_time(&tm, "%Y-%m-%d");

		// Add days_offset to the date
		std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
		tp += std::chrono::hours(days_offset * 24);

		// Convert back to std::tm
		std::time_t time = std::chrono::system_clock::to_time_t(tp);
		std::tm* new_tm = std::localtime(&time);

		// Format the new date as a string
		char buffer[11];
		std::strftime(buffer, 11, "%Y-%m-%d", new_tm);

		return std::string(buffer);
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

	 /** ***************************************** First Name Format *****************************************
	  * @brief : Transform the std::string received in this format: (Examplename) or (Example-Name).
	  * 
	  * @param first_name : std::string& => first name
	  * @return  : std::string
	  */
	 std::string formatFirstName(const std::string& first_name) {
		 std::string formatted_name;
		 bool new_segment = true; // To track the start of a new segment after a hyphen

		 for (char c : first_name) {
			 if (new_segment) {
				 formatted_name += std::toupper(c);
				 new_segment = false;
			 }
			 else {
				 formatted_name += std::tolower(c);
			 }

			 if (c == '-') {
				 new_segment = true; // Reset for new segment
			 }
		 }
		 return formatted_name;
	 }

	 /** ***************************************** Last Name Format *****************************************
	  * @brief : Transform the std::string received in this format: (EXAMPLENAME) or (EXAMPLE-NAME) or (EXEMPLE NAME).
	  * 
	  * @param last_name : std::string& => last name
	  * @return  : std::string
	  */
	 std::string formatLastName(const std::string& last_name) {
		 std::string formatted_name;
		 for (char c : last_name) {
			 if (c == '-' || c == ' ') {
				 formatted_name += c; // Preserve hyphens and spaces
			 }
			 else {
				 formatted_name += std::toupper(c);
			 }
		 }
		 return formatted_name;
	 }

} // namespace bll
