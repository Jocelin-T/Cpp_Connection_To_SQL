/*****************************************************************//**
 * @file   PanelConnection.cpp
 * @brief  Panel where Employee and Admin can connect
 *
 * @author ThJo
 * @date   3 May 2024
 *********************************************************************/
#include "PanelConnection.h"

namespace gui{
	PanelConnection::PanelConnection(wxWindow* pParent, wxFrame* pMain_frame)
		: Panel(pParent, pMain_frame) {
		initializeComponents();
		bindEventHandlers();
	}

	/**  ####################################### GUI #####################################
	 * @brief : GUI for this panel.
	 *	"this" make reference to Panel class too
	 */
	void PanelConnection::initializeComponents() {
		// Main sizer for the entire panel
		wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

		// Title of the panel
		m_pTitle_page = new wxStaticText(this, wxID_ANY, "Connect to your session");
		m_pTitle_page->SetFont(global_title_font);
		pMain_sizer->Add(m_pTitle_page, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 40);

		// Helper function to create label and text control pairs
		auto addLabelAndTextControl = [&](const wxString& label, long style = 0) -> wxTextCtrl* {
			wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
			wxStaticText* pLabel_text = new wxStaticText(this, wxID_ANY, label);
			wxTextCtrl* pText_ctrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, style);
			pSizer->Add(pLabel_text, 0, wxBOTTOM, 5);  // Add some space below the label
			pSizer->Add(pText_ctrl, 1, wxEXPAND); // Expand to fill available horizontal space
			pMain_sizer->Add(pSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 40);
			return pText_ctrl;
		};

		// Add label and text control pairs
		m_pEmail = addLabelAndTextControl("Email:");
		m_pPassword = addLabelAndTextControl("Password:", wxTE_PASSWORD);

		// Add a flexible spacer to push the buttons to the bottom
		pMain_sizer->AddStretchSpacer(1); // This adds a stretchable space that expands

		// Buttons at the bottom
		wxBoxSizer* pButton_sizer = new wxBoxSizer(wxHORIZONTAL);
		m_pButton_exit = new wxButton(this, wxID_ANY, "Exit");
		m_pButton_connect = new wxButton(this, wxID_ANY, "Connect");
		pButton_sizer->Add(m_pButton_exit, 0, wxRIGHT, 250);
		pButton_sizer->Add(m_pButton_connect, 0, wxLEFT, 250);

		// Add buttons without top space pushing down
		pMain_sizer->Add(pButton_sizer, 0, wxALIGN_CENTER | wxALL, 10);

		// Set the main sizer for the panel to arrange the sub-widgets
		this->SetSizer(pMain_sizer);
		this->Layout();
	}

	/** ####################################### Buttons ##################################### */
	/** ***************************************** Bind Handler *****************************************
	 * @brief : Handle all the buttons bind of this panel.
	 *
	 */
	void PanelConnection::bindEventHandlers() {
		m_pButton_exit->Bind(wxEVT_BUTTON, &PanelConnection::onExitButtonClicked, this);
		m_pButton_connect->Bind(wxEVT_BUTTON, &PanelConnection::onConnectButtonClicked, this);
	}
	/** ***************************************** Enter key *****************************************
	 */
	void PanelConnection::onEnterKeyPressed() {
		connectUser();
	}

	/** ***************************************** Connect Button *****************************************
	 * @brief : Connect button.
	 * 
	 * @param evt :
	 */
	void PanelConnection::onConnectButtonClicked(wxCommandEvent& evt) {
		connectUser();
	}

	/** ***************************************** Exit Button *****************************************
	 * @brief : This button close the program after confimation from the user
	 * 
	 * @param evt :
	 */
	void PanelConnection::onExitButtonClicked(wxCommandEvent& evt) {
		if (confirmMessageBox("Do you want to quit the program ?", "Exit Program")) {
			if (pMain_frame) {
				pMain_frame->Close(true);
			}
		}
	}

	/** ####################################### Utilities ##################################### */
	/** ***************************************** Try to connect the User *****************************************
	 * @brief : If the fields are filled, check if they are corresponding to a employee inside the DB.
	 * 
	 */
	void PanelConnection::connectUser()	{
		// Fetch data from text controls
		wxString email = getEmail();
		wxString password = getPassword();

		// Check if the fields are empty and send an error message
		if (email.empty() || password.empty()) {
			wxMessageBox("Missing entry", "Error", wxOK | wxICON_ERROR);
			return;
		}

		if (email == wxString(ADMIN_EMAIL)) { // If the user try to connect as Admin
			if (bll::checkAdminConnection(email.ToStdString(), password.ToStdString())) {
				MainFrame* mainFrame = dynamic_cast<MainFrame*>(pMain_frame); // Safe casting
				if (mainFrame) { // Connect him in the (PanelAdmin)
					mainFrame->toPanel_Admin();
				}
			}
			else {
				wxMessageBox("Invalid email or password", "Login Failed", wxOK | wxICON_ERROR);
			}
		}
		else if (bll::checkEmployeeConnection(email.ToStdString(), password.ToStdString())) { // if it's an Employee
			MainFrame* mainFrame = dynamic_cast<MainFrame*>(pMain_frame); // Safe casting
			if (mainFrame) { // Connect him in the (PanelEmployee_Hours)
				bll::Employee employee_details = bll::getEmployeeWithEmailAndPw(email.ToStdString(), password.ToStdString());
				mainFrame->toPanel_Employee_Hours(employee_details);
			}
		}
		else {
			wxMessageBox("Invalid email or password", "Login Failed", wxOK | wxICON_ERROR);
		}
	}




	/** ####################################### Getter ##################################### */
	wxString PanelConnection::getEmail() {
		return wxString(m_pEmail->GetValue());
	}
	wxString PanelConnection::getPassword() {
		return wxString(m_pPassword->GetValue());
	}

} // namespace gui
