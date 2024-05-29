/*****************************************************************//**
 * @file   Employee.cpp
 * @brief  Employee Class with the same attributes of SQL "employee" table
 * 
 * @author ThJo
 * @date   2 May 2024
 *********************************************************************/
#include "Employee.h"
#include "BLLManager.h"


namespace bll {
// Parameterized Constructor
Employee::Employee(const int employee_id, const std::string emp_last_name,
	const std::string emp_first_name, const std::string emp_email, const std::string emp_password)
	: m_employee_id{ employee_id }, m_last_name{ emp_last_name },
	m_first_name{ emp_first_name }, m_email{ emp_email }, m_password{ emp_password }
{}

/** ***************************************** Constructor Employee *****************************************
 * @brief : With only the employee_id pass, will get all is data from the DB.
 * 
 * @param employee_id : int => ID of the employee
 */
Employee::Employee(const int employee_id)
	: m_employee_id{ employee_id }
{
	// Complet the Employee object with the data found in the DB
	bll::completEmployeeWithId(*this);
}

Employee::Employee(const std::string email, const std::string password)
	: m_email{ email }, m_password{ password }
{
	// Complet the Employee object with the data found in the DB
	bll::completEmployeeWithEmailAndPw(*this);
}
} // namespace bll

