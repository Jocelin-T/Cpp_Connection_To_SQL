/*****************************************************************//**
 * @file   PanelAdmin_EmployeeCreation.cpp
 * @brief  Panel access by the admin role only, 
 *	he can add a new employee to the DB
 * 
 * @author ThJo
 * @date   2 May 2024
 *********************************************************************/
#include "PanelAdmin_EmployeeCreation.h"

namespace gui{
	PanelAdmin_EmployeeCreation::PanelAdmin_EmployeeCreation(wxWindow* parent, wxFrame* pMain_frame)
		: Panel(parent, pMain_frame){
		InitializeComponents();
	}

	/** ####################################### GUI #####################################
	 * @brief : GUI for this panel.
	 *	"this" make reference to Panel class too
	 */
	void PanelAdmin_EmployeeCreation::InitializeComponents() {
		// Main sizer for the entire panel
		wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

		// Title of the panel
		addPanelTitle(pMain_sizer, "Creation of a new employee");

		// Add label and text control pairs
		m_pLast_name = pAddLabelAndTextControl(pMain_sizer,"Last Name:");
		m_pFirst_name = pAddLabelAndTextControl(pMain_sizer,"First Name:");
		m_pEmail = pAddLabelAndTextControl(pMain_sizer,"Email:");
		m_pPassword = pAddLabelAndTextControl(pMain_sizer,"Password:", "", wxTE_PASSWORD);

		// Add a flexible spacer to push the buttons to the bottom
		pMain_sizer->AddStretchSpacer(1);

		// Add footer button
		m_vector_buttons_footer = { m_pButton_back, m_pButton_add };
		m_vector_labels_footer = { "<< Back", "Create Employee" };
		m_vector_method_footer = {
			wxCommandEventHandler(PanelAdmin_EmployeeCreation::onBackButtonClicked),
			wxCommandEventHandler(PanelAdmin_EmployeeCreation::onAddButtonClicked)
		};

		addFooterButtons(pMain_sizer, m_vector_buttons_footer, m_vector_labels_footer, m_vector_method_footer);

		// Set the main sizer for the panel to arrange the sub-widgets
		this->SetSizer(pMain_sizer);
		this->Layout();

		m_pLast_name->SetFocus(); // Focus on this wxTextCtrl
	}

	/** ####################################### Buttons ##################################### */
	/** ***************************************** Entrer key *****************************************
	 */
	void PanelAdmin_EmployeeCreation::onEnterKeyPressed() {
		createEmployee();
	}

	/** ***************************************** Add Button *****************************************
	 * @param evt :
	 */
	void PanelAdmin_EmployeeCreation::onAddButtonClicked(wxCommandEvent& evt){
		createEmployee();
	}

	/** ***************************************** Back Button *****************************************
	 * @param evt :
	 */
	void PanelAdmin_EmployeeCreation::onBackButtonClicked(wxCommandEvent& evt){
		toPanelAdmin();
	}

	/** ####################################### Utilities ##################################### */
	void PanelAdmin_EmployeeCreation::createEmployee() {
		// Validation of the fields
		if (!validateInput()) {
			return;
		}

		// Fetch data from text controls
		wxString employee_last_name = getLastName();
		wxString employee_first_name = getFirstName();
		wxString employee_email = getEmail();
		wxString employee_password = getPassword();

		// Display a message dialog box and wait for confirmation
		wxString title = "Confirm employee creation";
		wxString message = wxString::Format(title +
			":\n\nLast Name: " + employee_last_name +
			"\nFirst Name: " + employee_first_name +
			"\nEmail: " + employee_email +
			"\nPassword: " + employee_password);

		// Program will continue only if [Yes] is press by the user
		if (confirmMessageBox(message, title)) {
			if (bll::createNewEmployee(
				employee_last_name.ToStdString(),
				employee_first_name.ToStdString(),
				employee_email.ToStdString(),
				employee_password.ToStdString()))
			{
				clearFields();
			}
		}
	}

	/** ***************************************** Validate fields *****************************************
	 * @brief : Validate all fields of the employee creation.
	 * 
	 * @return  : boolean
	 */
	bool PanelAdmin_EmployeeCreation::validateInput() {
		if (getLastName().IsEmpty() 
			|| getFirstName().IsEmpty()
			|| getEmail().IsEmpty()
			|| getPassword().IsEmpty()) {
			wxMessageBox("Please fill in all fields.", "Missing Information", wxOK | wxICON_WARNING);
			return false; // NOT all fields are filled
		}
		if (!isValidName(getLastName().ToStdString())
			|| !isValidName(getFirstName().ToStdString())) {
			return false;
		}
		if (!isValidEmail(getEmail().ToStdString())) {
			return false;
		}
		if (!isValidPasswordDebug(getPassword().ToStdString())) {
			return false;
		}
		return true; // All fields are correct
	}

	/** ***************************************** Clear fields *****************************************
	 * @brief : Clear all fields of the PanelAdmin_EmployeeCreation.
	 * 
	 */
	void PanelAdmin_EmployeeCreation::clearFields() {
		m_pLast_name->SetValue("");
		m_pFirst_name->SetValue("");
		m_pEmail->SetValue("");
		m_pPassword->SetValue("");
	}

	/** ####################################### Getter ##################################### */
	wxString PanelAdmin_EmployeeCreation::getLastName() {
		return wxString(m_pLast_name->GetValue());
	}
	wxString PanelAdmin_EmployeeCreation::getFirstName() {
		return wxString(m_pFirst_name->GetValue());
	}
	wxString PanelAdmin_EmployeeCreation::getEmail() {
		return wxString(m_pEmail->GetValue());
	}
	wxString PanelAdmin_EmployeeCreation::getPassword() {
		return wxString(m_pPassword->GetValue());
	}

} // namespace gui

