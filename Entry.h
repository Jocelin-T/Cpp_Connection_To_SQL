/*****************************************************************//**
 * @file   Entry.h
 * @brief  Class for every entries
 * 
 * @author ThJo
 * @date   7 May 2024
 *********************************************************************/
#pragma once
#include <sstream>
#include <cmath>
#include <string>


class Entry {
public: 
	// Default Constructor
	Entry() = default;

	// Parameterized Constructor
	Entry(const int employee_id, const std::string& entry_date,
		const std::string& entry_start, const std::string& entry_end,
		const int entry_id, const int working_hours);

	Entry(const int employee_id, const std::string& entry_date);

private:
	int m_entry_id{ -1 };
	std::string m_entry_date{ "1970-01-01" };
	std::string m_entry_start{ "00:00:00" };
	std::string m_entry_end{ "00:00:00" };
	int m_employee_id{ -1 };
	int m_working_hours{ 0 };

	/** ***************************************** Calculate working hours *****************************************
	* @brief : Calculate the number of hours from an employee and update the original Entry object.
	* @param entry : Entry&, will take entry_start and entry_end from the object
	*/
	void calculateDailyHours(Entry& entry);


	//int calculateWeeklyHours(const int employee_id, std::string entry_date);


	//int calculateMonthlyHours(const int employee_id, std::string entry_date);

	/** ***************************************** Convert time *****************************************
	* @brief : Convert time from std::string to int minutes.
	*
	* @param time : std::string&, time in format(HH:MM)
	* @return  : int, number of minutes
	*/
	int parseTimeToMinutes(const std::string& time);

	/** ***************************************** Populate Entry object *****************************************
	 * @brief : Populate Entry object with the data found in the DB.
	 *
	 * @param entry : Entry&, with employee_id, entry_date
	 */
	void completEntry(Entry& entry);

public:
	// Getter
	int getEntryId() const { return m_entry_id; };
	std::string getEntryDate() const { return m_entry_date; };
	std::string getEntryStart() const { return m_entry_start; };
	std::string getEntryEnd() const { return m_entry_end; };
	int getEmployeeId() const { return m_employee_id; };
	int getWorkingHours() const { return m_working_hours; };

	// Setter
	void setEntryID(int entry_id) { m_entry_id = entry_id; };
	void setEntryDate(std::string entry_date) { m_entry_date = entry_date; };
	void setEntryStart(std::string entry_start) { m_entry_start = entry_start; };
	void setEntryEnd(std::string entry_end) { m_entry_end = entry_end; };
	void setEmployeeId(int employee_id) { m_employee_id = employee_id; };
	void setEntryWorkingHours(int working_hours) { m_working_hours = working_hours; };

};
