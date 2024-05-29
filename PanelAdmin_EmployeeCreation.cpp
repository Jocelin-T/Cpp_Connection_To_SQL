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
		BindEventHandlers();
	}

	/** ####################################### GUI #####################################
	 * @brief : GUI for this panel.
	 *	"this" make reference to Panel class too
	 */
	void PanelAdmin_EmployeeCreation::InitializeComponents() {
		// Main sizer for the entire panel
		wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

		// Title of the panel
		m_pTitle_page = new wxStaticText(this, wxID_ANY, "Creation of a new employee");
		m_pTitle_page->SetFont(global_title_font);
		pMain_sizer->Add(m_pTitle_page, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 40);

		// Helper function to create label and text control pairs
		auto addLabelAndTextControl = [&](const wxString& label, long style = 0) -> wxTextCtrl* {
			wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
			wxStaticText* pLabel_text = new wxStaticText(this, wxID_ANY, label);
			wxTextCtrl* pText_ctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, style);
			pSizer->Add(pLabel_text, 0, wxBOTTOM, 5);  // Add some space below the label
			pSizer->Add(pText_ctrl, 1, wxEXPAND);
			pMain_sizer->Add(pSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 40);
			return pText_ctrl;
		};

		// Add label and text control pairs
		m_pLast_name = addLabelAndTextControl("Last Name:");
		m_pFirst_name = addLabelAndTextControl("First Name:");
		m_pEmail = addLabelAndTextControl("Email:");
		m_pPassword = addLabelAndTextControl("Password:", wxTE_PASSWORD);

		// Add a flexible spacer to push the buttons to the bottom
		pMain_sizer->AddStretchSpacer(1);

		// Buttons at the bottom
		wxBoxSizer* pButton_sizer = new wxBoxSizer(wxHORIZONTAL);
		m_pButton_back = new wxButton(this, wxID_ANY, "<< Back");
		m_pButton_add = new wxButton(this, wxID_ANY, "Create Employee");
		pButton_sizer->Add(m_pButton_back, 0, wxRIGHT, 250);
		pButton_sizer->Add(m_pButton_add, 0, wxLEFT, 250);

		pMain_sizer->Add(pButton_sizer, 0, wxALIGN_CENTER | wxALL, 10);

		// Set the main sizer for the panel to arrange the sub-widgets
		this->SetSizer(pMain_sizer);
		this->Layout();

		m_pLast_name->SetFocus(); // Focus on this wxTextCtrl
	}

	/** ####################################### Buttons ##################################### */
	/** ***************************************** Bind Handler *****************************************
	 * @brief : Handle all the buttons bind of this panel.
	 * 
	 */
	void PanelAdmin_EmployeeCreation::BindEventHandlers() {
		m_pButton_add->Bind(wxEVT_BUTTON, &PanelAdmin_EmployeeCreation::onAddButtonClicked, this);
		m_pButton_back->Bind(wxEVT_BUTTON, &PanelAdmin_EmployeeCreation::onBackButtonClicked, this);
	}

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
	 * @brief : When the button disconnect is press,
	 *	will return to (PanelAdmin).
	 * 
	 * @param evt :
	 */
	void PanelAdmin_EmployeeCreation::onBackButtonClicked(wxCommandEvent& evt){
		// "dynamic_cast" need to be used, because the method "toPanel_Admin()" only exist in MainFrame, not in wxFrame
		MainFrame* pMain_frame_dynamic = dynamic_cast<MainFrame*>(pMain_frame); // Safe casting to derived class
		if (pMain_frame_dynamic) {
			pMain_frame_dynamic->toPanel_Admin(); // Call the method to switch panels
		}
		else {
			wxMessageBox("Failed to cast MainFrame", "Error", wxOK | wxICON_ERROR);
		}
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

