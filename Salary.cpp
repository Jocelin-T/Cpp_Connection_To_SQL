/*****************************************************************//**
 * @file   Salary.cpp
 * @brief  Make all calculation for the salaries and hours
 * 
 * @author ThJo
 * @date   7 May 2024
 *********************************************************************/
#include "Salary.h"
#include <wx/wx.h>

namespace bll {
	Salary::Salary(const int employee_id, const std::string& entry_date, const int salary_per_hour)
		: m_salary_per_hour{ salary_per_hour }
	{
		createDailySalary(employee_id, entry_date);
	}

	/** ***************************************** Creation of a new daily salary *****************************************
	 * @brief : Create a salary for the given employee id and date with
	 *	a pointer for the Entry, a pointer for the Employee and the wages according to the Entry found.
	 * 
	 * @param employee_id : int => ID of the employee
	 * @param entry_date : std::string => Date of the entry
	 */
	void Salary::createDailySalary(const int employee_id, const std::string& entry_date){
		// New Entry object
		m_pEntry_details = new Entry(employee_id, entry_date);
		// New Employee object
		m_pEmployee_details = new Employee(employee_id);

		// Wages according to the Entry choosed
		m_wages = calculateWages(getWorkingHours(), m_salary_per_hour);
	}


	void Salary::createYearlySalary(const int employee_id, const std::string& date)	{
		// New Employee object
		m_pEmployee_details = new Employee(employee_id);


	}

	/** ***************************************** Calculate Wages *****************************************
	 * @brief : Calculate the wages with working_hours(only) and salary per hour.
	 *
	 * @param working_hours : int => number of working hours
	 * @param salary_per_hour : int => salary per hour
	 * @return  : int => wages
	 */
	int Salary::calculateWages(const int working_hours, const int salary_per_hour) {
		return working_hours * salary_per_hour;
	}


	// Manual Destructor
	void Salary::destroySalary(){
		if (m_pEntry_details) {
			delete m_pEntry_details;
			m_pEntry_details = nullptr;
		}
		if (m_pEmployee_details) {
			delete m_pEmployee_details;
			m_pEmployee_details = nullptr;
		}
	}
} // namespace bll