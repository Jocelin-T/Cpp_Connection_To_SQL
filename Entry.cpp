/*****************************************************************//**
 * @file   Entry.cpp
 * @brief  Class for every entries
 *
 * @author ThJo
 * @date   7 May 2024
 *********************************************************************/
#include "Entry.h"
#include "BLLManager.h"

namespace bll {
 // Parameterized Constructor
Entry::Entry(const int employee_id, const std::string& entry_date,
	const std::string& entry_start, const std::string& entry_end,
	const int entry_id, const int working_hours)
	: m_employee_id{ employee_id }, m_entry_date{ entry_date },
	m_entry_start{ entry_start }, m_entry_end{ entry_end },
	m_entry_id{ entry_id }, m_working_hours{ working_hours }
{}

Entry::Entry(const int employee_id, const std::string& entry_date)
	: m_employee_id{ employee_id }, m_entry_date{ entry_date }
{
	completEntry(*this);
}

/** ***************************************** Populate Entry object *****************************************
 * @brief : Populate Entry object with the data found in the DB.
 * 
 * @param entry : Entry&, with employee_id, entry_date
 */
void Entry::completEntry(Entry& entry) {
	// get data from DB
	bll::completEntryWithEmployeeIdAndDate(entry);
	calculateDailyHours(*this);
}

/** ***************************************** Calculate working hours *****************************************
* @brief : Calculate the number of hours from an employee and update the original Entry object.
* @param entry : Entry&, will take entry_start and entry_end from the object
*/
void Entry::calculateDailyHours(Entry& entry) {
	const std::string& START_HOUR = entry.getEntryStart();
	const std::string& END_HOUR = entry.getEntryEnd();

	// Set 0 and return if the hours are "00:00"
	if (START_HOUR == "00:00:00" && END_HOUR == "00:00:00") {
		entry.setEntryWorkingHours(0);
		return;
	}

	// Parse the std::string to int minutes
	const int START_MINUTES = parseTimeToMinutes(START_HOUR);
	const int END_MINUTES = parseTimeToMinutes(END_HOUR);

	// Calculate the difference
	const int DAILY_HOURS = (END_MINUTES - START_MINUTES) / 60;

	// Set the modification
	entry.setEntryWorkingHours(DAILY_HOURS);
}

/** ***************************************** Convert time *****************************************
 * @brief : Convert time from std::string to int minutes.
 *
 * @param time : std::string&, time in format(HH:MM)
 * @return  : int, number of minutes
 */
int Entry::parseTimeToMinutes(const std::string& time) {
	std::istringstream timeStream(time);
	int hours, minutes;
	char colon;

	timeStream >> hours >> colon >> minutes;

	return hours * 60 + minutes;
}
} // namespace bll