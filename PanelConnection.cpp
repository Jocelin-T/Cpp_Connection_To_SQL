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
	}

	/**  ####################################### GUI #####################################
	 * @brief : GUI for this panel.
	 *	"this" make reference to Panel class too
	 */
	void PanelConnection::initializeComponents() {
		// Main sizer for the entire panel
		wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

		// Title of the panel
		addPanelTitle(pMain_sizer, "Connect to your session");

		// Add label and text control pairs
		m_pEmail = pAddLabelAndTextControl(pMain_sizer, "Email:");
		m_pPassword = pAddLabelAndTextControl(pMain_sizer, "Password:", "", wxTE_PASSWORD);

		// Add a flexible spacer to push the buttons to the bottom
		pMain_sizer->AddStretchSpacer(1); // This adds a stretchable space that expands

		// Add footer button
		vector_buttons_footer = { m_pButton_exit, m_pButton_connect };
		vector_labels_footer = { "Exit", "Connect" };
		vector_method_footer = { 
			wxCommandEventHandler(PanelConnection::onExitButtonClicked), 
			wxCommandEventHandler(PanelConnection::onConnectButtonClicked) 
		};

		addFooterButtons(pMain_sizer, vector_buttons_footer, vector_labels_footer, vector_method_footer);

		// Set the main sizer for the panel to arrange the sub-widgets
		this->SetSizer(pMain_sizer);
		this->Layout();
	}

	/** ####################################### Buttons ##################################### */
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
			if (m_pMain_frame) {
				m_pMain_frame->Close(true);
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
			wxMessageBox("Missing entry", "Error", wxOK | wxICON_WARNING);
			return;
		}

		if (email == wxString(ADMIN_EMAIL)) { // If the user try to connect as Admin
			if (bll::checkAdminConnection(email.ToStdString(), password.ToStdString())) {
				MainFrame* mainFrame = dynamic_cast<MainFrame*>(m_pMain_frame); // Safe casting
				if (mainFrame) { // Connect him in the (PanelAdmin)
					mainFrame->toPanelAdmin();
				}
			}
			else {
				wxMessageBox("Invalid email or password", "Login Failed", wxOK | wxICON_WARNING);
			}
		}
		else if (bll::checkEmployeeConnection(email.ToStdString(), password.ToStdString())) { // if it's an Employee
			MainFrame* mainFrame = dynamic_cast<MainFrame*>(m_pMain_frame); // Safe casting
			if (mainFrame) { // Connect him in the (PanelEmployee_Hours)
				bll::Employee employee_details = bll::getEmployeeWithEmailAndPw(email.ToStdString(), password.ToStdString());
				mainFrame->toPanel_Employee_Hours(employee_details);
			}
		}
		else {
			wxMessageBox("Invalid email or password", "Login Failed", wxOK | wxICON_WARNING);
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
