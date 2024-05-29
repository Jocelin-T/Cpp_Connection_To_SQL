/*****************************************************************//**
 * @file   Employee.h
 * @brief  Employee Class with the same attributes of SQL "employee" table
 *
 * @author ThJo
 * @date   2 May 2024
 *********************************************************************/
#pragma once
#include <string>


class Employee{
public:
	// Constructors
	Employee() = default;

	// Parameterized Constructor
	Employee(const int employee_id, 
		const std::string emp_last_name, 
		const std::string emp_first_name,
		const std::string emp_email,
		const std::string emp_password
		);

	/** ***************************************** Constructor Employee *****************************************
	 * @brief : With only the employee_id pass, will get all is data from the DB.
	 *
	 * @param employee_id : int => ID of the employee
	 */
	Employee(const int employee_id);

	Employee(const std::string email, const std::string password);

private:
	int m_employee_id{ -1 };
	std::string m_last_name{ "Empty last_name" };
	std::string m_first_name{ "Empty first_name" };
	std::string m_email{ "emp@email.com" };
	std::string m_password{ "emp_password" };

public:
	// Getter
	int getEmployeeId() const { return m_employee_id; };
	std::string getLastName() const { return m_last_name;};
	std::string getFirstName() const { return m_first_name;};
	std::string getEmail() const { return m_email;};
	std::string getPassword() const { return m_password;};

	// Setter
	void setEmployeeId(int employee_id) { m_employee_id = employee_id; };
	void setLastName(std::string employee_last_name) { m_last_name = employee_last_name; };
	void setFirstName(std::string employee_first_name) { m_first_name = employee_first_name; };
	void setEmail(std::string employee_email) { m_email = employee_email; };
	void setPassword(std::string employee_password) { m_password = employee_password; };
};

