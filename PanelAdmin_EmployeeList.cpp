/*****************************************************************//**
 * @file   PanelAdminEmployeeList.cpp
 * @brief  This panel will let's the admin select a employee and 
 *	display his hours per day, week, month and make is montly salary
 * 
 * @namespace gui
 * 
 * @author ThJo
 * @date   8 May 2024
 *********************************************************************/
#include "PanelAdmin_EmployeeList.h"
#include "Salary.h"


namespace gui {
PanelAdminEmployeeList::PanelAdminEmployeeList(wxWindow* pParent, wxFrame* pMain_frame)
	: Panel(pParent, pMain_frame){
	InitializeComponents();
	BindEventHandlers();
	PopulateEmployees();
	UpdatePanelSalaries();
}

/** ####################################### GUI #####################################
* @brief : GUI for the panel hours management.
*	"this" make reference to Panel class too
*/
void PanelAdminEmployeeList::InitializeComponents(){
	wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

	// Title of the panel
	addPanelTitle(pMain_sizer, "List of employees");

	// Drop down list
	m_pEmployee_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1));
	pMain_sizer->Add(m_pEmployee_choice, 0, wxALIGN_CENTER | wxALL, 10);

	// Radio Box
	m_hours_choices.Add("A Day");
	m_hours_choices.Add("A Week");
	m_hours_choices.Add("A Month");
	m_pRadio_choices = new wxRadioBox(this, wxID_ANY, "Number of hours for:", wxDefaultPosition, wxDefaultSize, m_hours_choices);
	pMain_sizer->Add(m_pRadio_choices, 0, wxALIGN_CENTER);

	// Date selection
	wxStaticText* pLabel_date_selection = new wxStaticText(this, wxID_ANY, "Select the Date: (YYYY-MM-DD)");
	pMain_sizer->Add(pLabel_date_selection, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
	m_pDate = new wxTextCtrl(this, wxID_ANY, getCurrentDate(), wxDefaultPosition, wxSize(200, -1));
	pMain_sizer->Add(m_pDate, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
	

	// Panel and Sizer holding all the Employee data, hours and wages
	m_pSalary_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 350));
	m_pSalary_panel->SetBackgroundColour(*wxLIGHT_GREY);
	m_pContent_sizer = new wxBoxSizer(wxVERTICAL);

	// Employee data sizer (top)
	m_pEmployee_sizer = new wxBoxSizer(wxVERTICAL);
	m_pContent_sizer->Add(m_pEmployee_sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxEXPAND | wxBOTTOM, 5);

	// Scrolled window for the number of hours of the selected employee
	m_pScrolled_window = new wxScrolledWindow(m_pSalary_panel, wxID_ANY, wxDefaultPosition, wxSize(600, 200));
	m_pScrolled_window->SetScrollRate(5, 5);
	m_pHours_sizer = new wxBoxSizer(wxVERTICAL);
	m_pScrolled_window->SetSizer(m_pHours_sizer);
	m_pContent_sizer->Add(m_pScrolled_window, 1, wxEXPAND | wxLEFT | wxRIGHT, 20);

	// Total wages sizer (bottom)
	m_pTotal_wages_sizer = new wxBoxSizer(wxVERTICAL);
	m_pContent_sizer->Add(m_pTotal_wages_sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxEXPAND | wxTOP, 5);
	m_pSalary_panel->SetSizer(m_pContent_sizer);

	pMain_sizer->Add(m_pSalary_panel, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);


	// Add a flexible spacer to push the buttons to the bottom
	pMain_sizer->AddStretchSpacer(1);

	// Buttons at the bottom
	m_vector_buttons_footer = { m_pButton_back };
	m_vector_labels_footer = { "<< Back" };
	m_vector_method_footer = {
		wxCommandEventHandler(PanelAdminEmployeeList::onBackButtonClicked)
	};

	addFooterButtons(pMain_sizer, m_vector_buttons_footer, m_vector_labels_footer, m_vector_method_footer);


	// Set the main sizer for the panel to arrange the sub-widgets
	this->SetSizer(pMain_sizer);
	this->Layout();

	m_pEmployee_choice->SetFocus();
}
/** ####################################### Buttons ##################################### */
/** ***************************************** Bind Handler *****************************************
* @brief : Handle all the buttons bind of this panel.
*
*/
void PanelAdminEmployeeList::BindEventHandlers(){
	// Bind change events
	m_pEmployee_choice->Bind(wxEVT_CHOICE, &PanelAdminEmployeeList::onEmployeeChoiceChanged, this);
	m_pRadio_choices->Bind(wxEVT_RADIOBOX, &PanelAdminEmployeeList::onHoursSelectionChanged, this);
	m_pDate->Bind(wxEVT_TEXT, &PanelAdminEmployeeList::onDateChanged, this);
}

/** ***************************************** Back Button *****************************************
* @brief : When the button disconnect is press,
*	will return to (PanelAdmin).
*
* @param evt :
*/
void PanelAdminEmployeeList::onBackButtonClicked(wxCommandEvent& evt){
	toPanelAdmin();
}

void PanelAdminEmployeeList::onEmployeeChoiceChanged(wxCommandEvent& evt){
	UpdatePanelSalaries();
}

void PanelAdminEmployeeList::onHoursSelectionChanged(wxCommandEvent& evt){
	UpdatePanelSalaries();
}

void PanelAdminEmployeeList::onDateChanged(wxCommandEvent& evt){
	UpdatePanelSalaries();
}

/** ####################################### Utilities ##################################### */
/** ***************************************** Date validation [override] *****************************************
 * @brief : Override the method from the base Class, for ignoring the wxMessageBox.
 * 
 * @param date : std::string& => date
 * @return  : boolean
 */
bool PanelAdminEmployeeList::isValidDate(const std::string& date) {
	if (std::regex_match(date, M_DATE_PATTERN)) {
		return true;
	}
	return false;
}

/** ***************************************** Populate list with Employees *****************************************
 * @brief : Will populate the drop down list (wxChoice) with the employee in the DB.
 *	Ignore the employee Admin
 * 
 */
void PanelAdminEmployeeList::PopulateEmployees() {
	// Creation and population of a vector of Employee
	std::vector<bll::Employee> list_employees = bll::getVectorWithEmployees();

	// Display all employees in a wxChoices
	for (bll::Employee& employee : list_employees) {
		if (employee.getFirstName() != "Admin" && employee.getEmployeeId() != 1) { // Ignore the Employee Admin
			wxString item_label = wxString::Format(wxT("%d - %s %s"),
				employee.getEmployeeId(),
				employee.getFirstName(),
				employee.getLastName()
			);
			void* client_id = reinterpret_cast<void*>(static_cast<intptr_t>(employee.getEmployeeId()));
			m_pEmployee_choice->Append(item_label, client_id);
		}
	}
	// Select the first employee from the wxChoice if not empty
	if (!list_employees.empty()) {
		m_pEmployee_choice->Select(0); 
	}
}

/** ***************************************** Panel hours *****************************************
 * @brief : Update the displayed panel of the informations from the selected employee.
 * 
 */
void PanelAdminEmployeeList::UpdatePanelSalaries(){
	// Clear existing content in m_pScrolled_window
	if (m_pScrolled_window) {
		m_pScrolled_window->DestroyChildren();
		m_pHours_sizer->Clear(true);  // Clear the sizer contents as well
		m_pEmployee_sizer->Clear(true);
		m_pTotal_wages_sizer->Clear(true);
	}

	// Add new content based on the current selections
	wxString selected_employee = m_pEmployee_choice->GetStringSelection();
	int selected_employee_id = getChoiceEmployeeId();
	wxString selected_period = m_pRadio_choices->GetStringSelection();
	wxString selected_date = m_pDate->GetValue();
	
	//m_pSalaryPerHour = pAddLabelAndTextControl(m_pHours_sizer, "Salary per hour", "38");
	//// Convert text 
	//long selected_salary;
	//wxString str_salary = m_pSalaryPerHour->GetValue();
	//if (str_salary.ToLong(&selected_salary)) {
	//	int salary = static_cast<int>(selected_salary);
	//	wxLogMessage("Selected Salary: %d", salary);
	//}
	//else {
	//	wxLogError("The input value is not a valid number.");
	//}

	// Check if the given date is in the correct format
	if (!isValidDate(selected_date.ToStdString())) {
		wxStaticText* invalid_date = new wxStaticText(m_pScrolled_window, wxID_ANY,
			"Invalid date format. Please enter the date as YYYY-MM-DD.", wxDefaultPosition, wxDefaultSize, 0);
		m_pHours_sizer->Add(invalid_date, 0, wxALL | wxEXPAND, 5);
		return;  // Exit if date format is incorrect
	}

	list_salaries = bll::getSalariesOfOneEmployee(
		selected_employee_id,
		selected_date.ToStdString(),
		m_pRadio_choices->GetSelection(),
		38);

	updateDisplayedEmployeeData();
	updateDisplayedSalaries();
	updateDisplayedTotalWages();

	// Manual Destroy for avoiding memory leak
	bll::destroySalaries(list_salaries);

	m_pSalary_panel->Layout();  // Re-layout the panel
}

/** ***************************************** Employee data *****************************************
 * @brief : Dynamic Display of the Employee data from the selected employee.
 */
void PanelAdminEmployeeList::updateDisplayedEmployeeData(){
	wxStaticText* pEmployee_data_text = new wxStaticText(m_pSalary_panel, wxID_ANY,
		wxString::Format("Employee: %d - %s %s",
			list_salaries[0].getEmployeeId(),
			list_salaries[0].getEmployeeLastName(),
			list_salaries[0].getEmployeeFirstName()
		), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	m_pEmployee_sizer->Add(pEmployee_data_text, 0, wxALL | wxALIGN_CENTER, 5);
}

/** ***************************************** Hours *****************************************
 * @brief : Dynamic Display of the Hours from the selected employee.
 */
void PanelAdminEmployeeList::updateDisplayedSalaries(){
	for (const bll::Salary& salary : list_salaries) {
		wxStaticText* pSalary_text = new wxStaticText(m_pScrolled_window, wxID_ANY,
			wxString::Format(
				"------------------- %s -------------------\n"
				"Entry N° %d\n"
				"From %s to %s : %d Hours\n"
				"Wages: %d CHF (%d CHF/Hour)\n",
				salary.getEntryDate(),
				salary.getEntryId(),
				salary.getEntryStart(),
				salary.getEntryEnd(),
				salary.getWorkingHours(),
				salary.getWages(),
				salary.getSalaryPerHour()
			));
		m_pHours_sizer->Add(pSalary_text, 0, wxALL | wxEXPAND, 5);
	}
}

/** ***************************************** Total wages *****************************************
 * @brief : Dynamic Display of the Total Wages from the selected employee.
 */
void PanelAdminEmployeeList::updateDisplayedTotalWages(){
	wxStaticText* pTotal_wages = new wxStaticText(m_pSalary_panel, wxID_ANY,
		wxString::Format("Total: %d CHF",
			bll::getTotalWages(list_salaries)
		));
	m_pTotal_wages_sizer->Add(pTotal_wages, 0, wxALL | wxALIGN_RIGHT, 5);
}


/** ####################################### Getter ##################################### */
/**
 * @brief : Rien pigé, Return the ID of the selected employee.
 * 
 * @return  : int => ID of the selected employee from the wxChoice (drop down list)
 */
int PanelAdminEmployeeList::getChoiceEmployeeId() {
	int selection = m_pEmployee_choice->GetSelection();
	if (selection != wxNOT_FOUND) {
		return reinterpret_cast<intptr_t>(m_pEmployee_choice->GetClientData(selection));
	}
	return -1; // Return an invalid ID if not found
}

int PanelAdminEmployeeList::getRadioBoxId() {
	return m_pRadio_choices->GetSelection();
}
wxString PanelAdminEmployeeList::getDate() {
	return wxString(m_pDate->GetValue());
}

} // namespace gui