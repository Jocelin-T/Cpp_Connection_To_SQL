/*****************************************************************//**
 * @file   MultiThreading.h
 * @brief  All multithreading code will be here
 * 
 * @author ThJo
 * @date   10 June 2024
 *********************************************************************/
#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <chrono>
#include <ctime>
#include <map>
#include <queue>
 // Threads
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
// Error handling
#include <exception>
#include <stdexcept>
// Logging
#include <fstream>

#include "Salary.h"

// Forward declaration
class Employee;
class Entry;

namespace bll {
	/** ***************************************** Yearly wages *****************************************
	 * @brief : When call will get Wages of the selected year for all Employees (not the admin).
	 *
	 * @param year : std::string& => Year in format YYYY
	 * @return  : std::map<int, int> => <employee_id, yearly_wages>
	 */
	std::map<int, int> getYearlyWagesOfAllEmployees(const std::string& year);

} // namespace bll
