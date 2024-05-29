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
	UpdatePanelHours();
}

/** ####################################### GUI #####################################
* @brief : GUI for the panel hours management.
*	"this" make reference to Panel class too
*/
void PanelAdminEmployeeList::InitializeComponents(){
	wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

	// Title of the panel
	m_pTitle_page = new wxStaticText(this, wxID_ANY, "List of employees");
	m_pTitle_page->SetFont(global_title_font);
	pMain_sizer->Add(m_pTitle_page, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 40);

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


	// Panel with the number of hours of the selected employee
	m_pPanel_hours = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 200));
	m_pPanel_hours->SetBackgroundColour(*wxLIGHT_GREY);
	m_pHours_sizer = new wxBoxSizer(wxVERTICAL);

	
	// Set the sizer for m_pPanel_hours
	m_pPanel_hours->SetSizer(m_pHours_sizer);
	pMain_sizer->Add(m_pPanel_hours, 1, wxEXPAND | wxALL, 20);

	// Add a flexible spacer to push the buttons to the bottom
	pMain_sizer->AddStretchSpacer(1);

	// Buttons at the bottom
	wxBoxSizer* pButton_sizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButton_back = new wxButton(this, wxID_ANY, "<< Back");
	m_pButton_submit = new wxButton(this, wxID_ANY, "Get data");
	pButton_sizer->Add(m_pButton_back, 0, wxRIGHT, 250);
	pButton_sizer->Add(m_pButton_submit, 0, wxLEFT, 250);

	pMain_sizer->Add(pButton_sizer, 0, wxALIGN_CENTER | wxALL, 10);

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

	m_pButton_back->Bind(wxEVT_BUTTON, &PanelAdminEmployeeList::onBackButtonClicked, this);
	m_pButton_submit->Bind(wxEVT_BUTTON, &PanelAdminEmployeeList::onSubmitButtonClicked, this);

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
	// "dynamic_cast" need to be used, because the method "toPanel_Admin()" only exist in MainFrame, not in wxFrame
	MainFrame* pMain_frame_dynamic = dynamic_cast<MainFrame*>(pMain_frame); // Safe casting to derived class
	if (pMain_frame_dynamic) {
		pMain_frame_dynamic->toPanel_Admin(); // Call the method to switch panels
	}
	else {
		wxMessageBox("Failed to cast MainFrame", "Error", wxOK | wxICON_ERROR);
	}
}

void PanelAdminEmployeeList::onSubmitButtonClicked(wxCommandEvent& evt){
	UpdatePanelHours();
}

void PanelAdminEmployeeList::onEmployeeChoiceChanged(wxCommandEvent& evt){
	UpdatePanelHours();
}

void PanelAdminEmployeeList::onHoursSelectionChanged(wxCommandEvent& evt){
	UpdatePanelHours();
}

void PanelAdminEmployeeList::onDateChanged(wxCommandEvent& evt){
	UpdatePanelHours();
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
void PanelAdminEmployeeList::UpdatePanelHours(){
	// Clear existing content in m_pPanel_hours
	if (m_pPanel_hours) {
		m_pPanel_hours->DestroyChildren();
		m_pHours_sizer->Clear(true);  // Clear the sizer contents as well
	}

	// Add new content based on the current selections
	wxString selected_employee = m_pEmployee_choice->GetStringSelection();
	int selected_employee_id = getChoiceEmployeeId();
	wxString selected_period = m_pRadio_choices->GetStringSelection();
	wxString selected_date = m_pDate->GetValue();

	// Check if the given date is in the correct format
	if (!isValidDate(selected_date.ToStdString())) {
		wxStaticText* invalid_date = new wxStaticText(m_pPanel_hours, wxID_ANY, 
			"Invalid date format. Please enter the date as YYYY-MM-DD.", wxDefaultPosition, wxDefaultSize, 0);
		m_pHours_sizer->Add(invalid_date, 0, wxALL | wxEXPAND, 5);
		return;  // Exit if date format is incorrect
	}

	// Display the updated information
	wxStaticText* pText_employee = new wxStaticText(m_pPanel_hours, wxID_ANY,
		"Employee: " + selected_employee +
		" | Period: " + selected_period +
		" | Date: " + selected_date, wxDefaultPosition, wxDefaultSize, 0);
	m_pHours_sizer->Add(pText_employee, 0, wxALL | wxEXPAND, 5);

	// Pointer of a new Salary object
	bll::Salary* pSalary_details = new bll::Salary(selected_employee_id, selected_date.ToStdString());

	// GUI
	wxStaticText* pSalary_text = new wxStaticText(m_pPanel_hours, wxID_ANY,
		wxString::Format("Employee: %d - %s %s\n"
			"Entry N° %d Date: %s\n"
			"From %s to %s : %d Hours\n"
			"Wages: %d CHF (%d CHF/Hour)",
			pSalary_details->getEmployeeId(),
			pSalary_details->getEmployeeLastName(),
			pSalary_details->getEmployeeFirstName(),

			pSalary_details->getIdEntry(),
			pSalary_details->getEntryDate(),

			pSalary_details->getEntryStart(),
			pSalary_details->getEntryEnd(),
			pSalary_details->getWorkingHours(),

			pSalary_details->getWages(),
			pSalary_details->getSalaryPerHour()
		));

	if (pSalary_details) {
		delete pSalary_details;
		pSalary_details = nullptr;
	}

	m_pHours_sizer->Add(pSalary_text, 0, wxALL | wxEXPAND, 5);

	m_pPanel_hours->SetSizer(m_pHours_sizer);  // Ensure the panel has its sizer set
	m_pPanel_hours->Layout();  // Re-layout the panel
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