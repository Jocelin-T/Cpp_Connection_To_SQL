/*****************************************************************//**
 * @file   Salary.h
 * @brief  Make all calculation for the salaries and hours
 * 
 * @author ThJo
 * @date   7 May 2024
 *********************************************************************/
#pragma once
#include <vector>
#include <string>

#include "Employee.h"
#include "Entry.h"



namespace bll {
	class Salary{
	public:
		// Constructors
		Salary() = default;

		Salary(const int employee_id,
			const std::string& entry_date, 
			const int salary_per_hour = 38); // Default salary per hour

		std::vector<Salary> getSalaries(
			const int employee_id,
			const std::string& entry_date,
			const int period,
			const int salary_per_hour = 38);

		// Destructor
		~Salary();

	private:
		// Members
		int m_salary_per_hour{ 0 };
		int m_wages{ 0 };

		// Objects Ptr
		const Entry* m_pEntry_details;
		const Employee* m_pEmployee_details;

		/** ***************************************** Creation of a new daily salary *****************************************
		 * @brief : Create a salary for the given employee id and date with
		 *	a pointer for the Entry, a pointer for the Employee and the wages according to the Entry found.
		 *
		 * @param employee_id : int => ID of the employee
		 * @param entry_date : std::string => Date of the entry
		 */
		void createDailySalary(const int employee_id, const std::string& entry_date);

		//void createWeeklySalary(const int employee_id, const std::string& entry_date);
	
		//void createMonthlySalary(const int employee_id, const std::string& entry_date);

		/** ***************************************** Calculate Wages *****************************************
		 * @brief : Calculate the wages with working_hours(only) and salary per hour.
		 *
		 * @param working_hours : int => number of working_hours
		 * @param salary_per_hour : int => salary per hour
		 * @return  : int => wages
		 */
		int calculateWages(const int hours, const int salary_per_hour);

	public:
		// Getters
		int getEmployeeId() const {
			return m_pEmployee_details != nullptr ? m_pEmployee_details->getEmployeeId() : -1;
		}
		std::string getEmployeeLastName() const {
			return m_pEmployee_details != nullptr ? m_pEmployee_details->getLastName() : "";
		}
		std::string getEmployeeFirstName() const {
			return m_pEmployee_details != nullptr ? m_pEmployee_details->getFirstName() : "";
		}
		int getIdEntry() const {
			return m_pEntry_details != nullptr ? m_pEntry_details->getEntryId() : -1;
		}
		std::string getEntryDate() const {
			return m_pEntry_details != nullptr ? m_pEntry_details->getEntryDate() : "";
		}
		std::string getEntryStart() const {
			return m_pEntry_details != nullptr ? m_pEntry_details->getEntryStart() : "";
		}
		std::string getEntryEnd() const {
			return m_pEntry_details != nullptr ? m_pEntry_details->getEntryEnd() : "";
		}
		int getWorkingHours() const {
			return m_pEntry_details != nullptr ? m_pEntry_details->getWorkingHours() : 0;
		}
		int getSalaryPerHour() const { return m_salary_per_hour; };
		int getWages() const { return m_wages; };

		// Setters
		void setSalaryPerHour(int salary_per_hour) { m_salary_per_hour = salary_per_hour; };
		void setWages(int wages) { m_wages = wages; };

	};

} // namespace bll