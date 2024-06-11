/*****************************************************************//**
 * @file   MultiThreading.cpp
 * @brief  All multithreading code will be here
 * 
 * @author ThJo
 * @date   10 June 2024
 *********************************************************************/
#include "MultiThreading.h"
#include "BLLManager.h"


namespace bll {
	// Global variables
	std::mutex mtx;
	std::mutex log_mutex;// Global mutex for thread-safe logging
	std::condition_variable cv;
	std::queue<std::vector<bll::Salary>> salaries_queue;
	bool done{ false };
	std::exception_ptr thread_exception = nullptr;
	int active_threads{ 0 };

	/************************************************** Dynamic Threads ************************************************/
	// Logging function for debbug
	void logMessage(const std::string& message) {
		static std::ofstream log_file("application.log", std::ios_base::app);
		std::lock_guard<std::mutex> guard(log_mutex);
		if (log_file.is_open()) {
			log_file << message << std::endl;
		}
		else {
			std::cerr << "Unable to open log file!" << std::endl;
		}
	}

	/** ***************************************** Get Yearly wages *****************************************
	 * @brief : When call will get Wages of the passed year for all Employees (not the admin).
	 * 
	 * @param year : std::string& => Year in format YYYY
	 * @return  : std::map<int, int> => <employee_id, yearly_wages>
	 */
	std::map<int, int> getYearlyWagesOfAllEmployees(const std::string& year) {
		done = false;
		active_threads = 0;
		std::map<int, int> employee_wages_map; // <employee_id, yearly wages>
		std::vector<Employee> vector_employees = getVectorWithEmployees();
		std::vector<std::thread> vector_threads;

		// Determine the number of hardware threads available
		unsigned int num_threads = std::thread::hardware_concurrency();
		num_threads = num_threads > 0 ? num_threads : 1; // Ensure at least one thread

		// Calculate chunk size for each thread
		size_t chunk_size = vector_employees.size() / num_threads;

		try {
			// Set the counter of working threads
			{
				std::lock_guard<std::mutex> lock(mtx);
				active_threads = num_threads;
			}

			// Launch threads to process subsets of employees
			for (unsigned int i = 0; i < num_threads; ++i) {
				size_t start = i * chunk_size;
				size_t end = (i == num_threads - 1) ? vector_employees.size() : start + chunk_size;
				vector_threads.emplace_back(&bll::getYearlySalariesOfOneEmployee, year, std::cref(vector_employees), start, end);
			}

			// Launch a thread to calculate yearly wages
			std::thread t_wages(&bll::calculateYearlyWages, std::ref(employee_wages_map));

			// Join all threads
			for (std::thread& t_sql : vector_threads) {
				if (t_sql.joinable()) {
					t_sql.join();
				}
			}

			if (t_wages.joinable()) {
				t_wages.join();
			}

			if (thread_exception) {
				std::rethrow_exception(thread_exception);
			}
		}
		catch (const std::exception& e) {
			logMessage(std::string("Exception caught: ") + e.what());
		}

		return employee_wages_map;
	}



	void getYearlySalariesOfOneEmployee(
		const std::string& year,
		const std::vector<Employee>& vector_employees,
		size_t start,
		size_t end) {

		try {
			// Iterate over a subset of employees (from start to end index)
			for (size_t i = start; i < end; ++i) {
				const Employee& employee = vector_employees[i];

				if (employee.getEmployeeId() != 1) { // Ignore the admin
					// Log the start of processing for the employee
					logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id())) 
						+ " Done: " + std::to_string(done)
						+ " Start processing Employee ID: " + std::to_string(employee.getEmployeeId()));

					std::vector<Salary> yearly_salaries;

					// Generate monthly salaries for the whole year
					for (int month = 1; month <= 12; ++month) {
						std::string month_str = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
						std::string start_date = year + "-" + month_str + "-01";
						
						// Get salaries for the current month and add them to yearly_salaries
						std::vector<bll::Salary> monthly_salaries = getSalariesOfOneEmployee(employee.getEmployeeId(), start_date, 2, 38);
						yearly_salaries.insert(yearly_salaries.end(), monthly_salaries.begin(), monthly_salaries.end());
					}

					// Push the yearly salaries to the queue
					{
						logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id())) 
							+ " Done: " + std::to_string(done)
							+ " Lock");

						std::lock_guard<std::mutex> lock(mtx);
						salaries_queue.push(std::move(yearly_salaries));

						logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id())) 
							+ " Done: " + std::to_string(done)
							+ " Unlock");
					}

					// Notify the other thread that new data is available
					cv.notify_one();
					logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id()))
						+ " Done: " + std::to_string(done)
						+ " Notify finished processing Employee ID: " + std::to_string(employee.getEmployeeId()));
				}
			}
		}
		catch (const std::exception& e) {
			logMessage("Exception caught while processing employee subset: " + std::string(e.what()));
			{
				std::lock_guard<std::mutex> lock(mtx);
				thread_exception = std::current_exception();
			}
			cv.notify_all(); // Notify other threads to stop processing
		}

		// Mark as done and notify all threads in case this is the last subset
		{
			logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id()))
				+ " Done: " + std::to_string(done)
				+ " Lock");

			std::lock_guard<std::mutex> lock(mtx);
			if (--active_threads == 0) {
				done = true;
			}

			logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id()))
				+ " Done: " + std::to_string(done)
				+ " Unlock");
		}
		cv.notify_all();
	}


	void calculateYearlyWages(std::map<int, int>& map) {
		try {
			int total{ 0 };
			int emp_id{ 0 };

			// Keep running until done and the queue is empty
			while (true) {
				std::unique_lock<std::mutex> lock(mtx); // Used for condition variable "wait"

				// Wait for new data or until processing is done
				cv.wait(lock, [] { return !salaries_queue.empty() || done; });
				logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id()))
					+ " Done: " + std::to_string(done)
					+ " Unique Lock");

				// Process all salaries in the queue
				while (!salaries_queue.empty()) {
					std::vector<Salary> vector_salaries = std::move(salaries_queue.front());
					salaries_queue.pop();
					emp_id = vector_salaries[0].getEmployeeId();

					// Log the start of wage calculation for the employee
					logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id())) 
						+ " Done: " + std::to_string(done)
						+ " Start calculating wages for Employee ID: " + std::to_string(emp_id));

					total = getTotalWages(vector_salaries);

					// Destroy the salaries to free up memory
					destroySalaries(vector_salaries);

					// Store the total wages in the map
					map[emp_id] = total;

					// Log the end of wage calculation for the employee
					logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id())) 
						+ " Done: " + std::to_string(done)
						+ " Finished calculating wages for Employee ID: " + std::to_string(emp_id) + ", Total Wages: " + std::to_string(total));

					// Log map update
					std::stringstream ss;
					ss << "Thread " << std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id())) << " Map Update - Employee ID: " << emp_id << ", Total Wages: " << total;
					logMessage(ss.str());
				}

				// Break out of the loop if processing is done and the queue is empty
				if (done && salaries_queue.empty()) {
					logMessage("Thread " + std::to_string(std::hash<std::thread::id>()(std::this_thread::get_id())) 
						+ " Done: " + std::to_string(done)
						+ " Unique Unlock");
					break;
				}
			}
		}
		catch (const std::exception& e) {
			logMessage(std::string("Exception caught: ") + e.what());
			std::lock_guard<std::mutex> lock(mtx);
			thread_exception = std::current_exception();
			done = true;
			cv.notify_all();
		}
	}



} // namespace bll

/************************************************** 2 Threads ************************************************/
	///** ***************************************** Get yearly wages of all Employees *****************************************
	// * @brief : Create a map with all the employee_id and yearly wages.
	// * 
	// * @param year : std::string& => the choosen year
	// * @return  : std::map<int, int> => employee_id, yearly wages
	// */
	//std::map<int, int> getYearlyWagesOfAllEmployees(const std::string& year) {
	//	std::map<int, int> employee_wages_map; // <employee_id, yearly wages>
	//	std::vector<Employee> vector_employees = getVectorWithEmployees();

	//	std::thread t1(getYearlySalariesOfOneEmployee, year, std::cref(vector_employees)); // cref = const ref
	//	std::thread t2(calculateYearlyWages, std::ref(employee_wages_map));

	//	t1.join();
	//	t2.join();

	//	return employee_wages_map;
	//}


	//void getYearlySalariesOfOneEmployee(
	//	const std::string& year,
	//	const std::vector<Employee>& vector_employees) {

	//	for (const Employee& employee : vector_employees) {
	//		std::vector<Salary> yearly_salaries;
	//		for (int month = 1; month <= 12; ++month) {
	//			std::string month_str = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
	//			std::string start_date = year + "-" + month_str + "-01";
	//			//std::string end_date = year + "-" + month_str + "-31";

	//			auto monthly_salaries = getSalariesOfOneEmployee(employee.getEmployeeId(), start_date, 2, 38);
	//			yearly_salaries.insert(yearly_salaries.end(), monthly_salaries.begin(), monthly_salaries.end());
	//		}
	//		salaries_queue.push(std::move(yearly_salaries));
	//		cv.notify_one();
	//	}
	//	std::unique_lock<std::mutex> lock(mtx);
	//	done = true;
	//}


	//void calculateYearlyWages(std::map<int,int>& map) {

	//	int total{ 0 };
	//	int emp_id{ 0 };

	//	while (true) {
	//		std::unique_lock<std::mutex> lock(mtx);
	//		cv.wait(lock, [] {return !salaries_queue.empty() || done; });


	//		while (!salaries_queue.empty()) {
	//			std::vector<Salary> vector_salaries = std::move(salaries_queue.front());
	//			salaries_queue.pop();
	//			total += getTotalWages(vector_salaries);
	//			emp_id = vector_salaries[0].getEmployeeId();
	//			destroySalaries(vector_salaries);
	//		}
	//		if (done && salaries_queue.empty()) {
	//			break;
	//		}
	//		map[emp_id] = total;
	//	}
	//}