/*****************************************************************//**
 * @file   PanelAdminAllSalaries.cpp
 * @brief  Panel where all salaries are displayed, for each Employee
 * 
 * @author ThJo
 * @date   3 June 2024
 *********************************************************************/
#include "PanelAdmin_AllSalaries.h"


namespace gui {
	PanelAdminAllSalaries::PanelAdminAllSalaries(wxWindow* pParent, wxFrame* pMain_frame)
		: Panel(pParent, pMain_frame) {
			InitializeComponents();
			BindEventHandlers();
			updatePanelSalaries();
	}

	/** ####################################### GUI #####################################
	* @brief : GUI for the panel hours management.
	*	"this" make reference to Panel class too
	*/
	void PanelAdminAllSalaries::InitializeComponents() {
		wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);
		
		// Title of the panel
		addPanelTitle(pMain_sizer, "Salaries for a full year");

		// Date selection
		wxStaticText* pLabel_date_selection = new wxStaticText(this, wxID_ANY, "Select the year: (YYYY)");
		pMain_sizer->Add(pLabel_date_selection, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
		m_pYear = new wxTextCtrl(this, wxID_ANY, getCurrentYear(), wxDefaultPosition, wxSize(100, -1));
		pMain_sizer->Add(m_pYear, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);

		// Panel and Sizer holding all salaries
		m_pSalary_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 350));
		m_pSalary_panel->SetBackgroundColour(*wxLIGHT_GREY);

		// Scrolled window for the number of hours of the selected employee
		m_pScrolled_window = new wxScrolledWindow(m_pSalary_panel, wxID_ANY, wxDefaultPosition, wxSize(600, 200));
		m_pScrolled_window->SetScrollRate(5, 5);
		m_pSalaries_sizer = new wxBoxSizer(wxVERTICAL);
		m_pScrolled_window->SetSizer(m_pSalaries_sizer);


		// Add the scrolled window to the salary panel's sizer
		wxBoxSizer* salary_panel_sizer = new wxBoxSizer(wxVERTICAL);
		salary_panel_sizer->Add(m_pScrolled_window, 1, wxEXPAND);
		m_pSalary_panel->SetSizer(salary_panel_sizer);

		// Add the salary panel to the main sizer
		pMain_sizer->Add(m_pSalary_panel, 0, wxEXPAND | wxALL, 10);


		// Add a flexible spacer to push the buttons to the bottom
		pMain_sizer->AddStretchSpacer(1);

		// Buttons at the bottom
		m_vector_buttons_footer = { m_pButton_back };
		m_vector_labels_footer = { "<< Back" };
		m_vector_method_footer = {
			wxCommandEventHandler(PanelAdminAllSalaries::onBackButtonClicked)
		};

		addFooterButtons(pMain_sizer, m_vector_buttons_footer, m_vector_labels_footer, m_vector_method_footer);

		// Set the main sizer for the panel to arrange the sub-widgets
		this->SetSizer(pMain_sizer);
		this->Layout();

		m_pYear->SetFocus();
	}

	/** ####################################### Buttons ##################################### */
	void PanelAdminAllSalaries::BindEventHandlers() {
		m_pYear->Bind(wxEVT_TEXT, &PanelAdminAllSalaries::onYearChanged, this);

	}

	/** ***************************************** Back Button *****************************************
	* @brief : When the button disconnect is press,
	*	will return to (PanelAdmin).
	*
	* @param evt :
	*/
	void PanelAdminAllSalaries::onBackButtonClicked(wxCommandEvent& evt) {
		toPanelAdmin();
	}

	void PanelAdminAllSalaries::onYearChanged(wxCommandEvent& evt) {
		updatePanelSalaries();
	}

	/** ####################################### Utilities ##################################### */
	/** ***************************************** Date validation [override] *****************************************
	 * @brief : Override the method from the base Class, for ignoring the wxMessageBox.
	 *
	 * @param date : std::string& => year
	 * @return  : boolean
	 */
	bool PanelAdminAllSalaries::isValidYear(const std::string& year) {
		if (std::regex_match(year, M_YEAR_PATTERN)) {
			return true;
		}
		return false;
	}

	/** ***************************************** Update salaries *****************************************
	 * @brief : When call update all salaries.
	 *
	 */
	void PanelAdminAllSalaries::updatePanelSalaries() {
		if (m_pScrolled_window) {
			m_pScrolled_window->DestroyChildren();
			m_pSalaries_sizer->Clear(true);  // Clear the sizer contents as well
		}

		//wxString selected_year = m_pYear->GetValue();
		std::string selected_year = m_pYear->GetValue().ToStdString();

		// Stop in case the value in m_pYear isn't in format YYYY
		if (!isValidYear(selected_year)) {
			wxStaticText* invalid_year = new wxStaticText(m_pScrolled_window, wxID_ANY,
				"Invalid year format. Please enter the year as YYYY.", wxDefaultPosition, wxDefaultSize, 0);
			m_pSalaries_sizer->Add(invalid_year, 0, wxALL | wxEXPAND, 5);
			return;  // Exit if year format is incorrect
		}

		// Creation of a vector of Employees
		std::vector<bll::Employee> list_employees = bll::getVectorWithEmployees();
		// Creation of a map, holding employee_id, yearly_wages
		std::map<int, int> map = bll::getYearlyWagesOfAllEmployees(selected_year);

		// Display all employees in a wxScrolledWindow
		for (const bll::Employee& employee : list_employees) {
			if (employee.getFirstName() != "Admin" && employee.getEmployeeId() != 1) { // Ignore the Employee Admin
				int yearly_wages = map[employee.getEmployeeId()];
				wxStaticText* pSalary_text = new wxStaticText(m_pScrolled_window, wxID_ANY,
					wxString::Format(
						"%d - %s %s: %d CHF",
						employee.getEmployeeId(),
						employee.getFirstName(),
						employee.getLastName(),
						yearly_wages
					));
				m_pSalaries_sizer->Add(pSalary_text, 0, wxALL | wxEXPAND, 5);
			}
		}

		m_pSalary_panel->Layout();  // Re-layout the panel
	}
} // namespace gui