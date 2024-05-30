/*****************************************************************//**
 * @file   PanelEmployee_Hours.cpp
 * @brief  Panel where Employee can enter there entry time and exit time
 *
 * @author ThJo
 * @date   3 May 2024
 *********************************************************************/
#include "PanelEmployee_Hours.h"


namespace gui {
	PanelEmployee_Hours::PanelEmployee_Hours(wxWindow* pParent, wxFrame* pMain_frame, const bll::Employee& employee)
		: Panel{ pParent, pMain_frame }, m_employee{ employee }
	{
		initializeComponents();
	}

	/** ####################################### GUI #####################################
	 * @brief : GUI for the panel hours management.
	 *	"this" make reference to Panel class too
	 */
	void PanelEmployee_Hours::initializeComponents() {
		// Main sizer for the entire panel
		wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

		// Title of the panel
		addPanelTitle(pMain_sizer, "Hours manager");

		// Display infos of the current employee connected (convert from std::string to wxString)
		m_pLast_name = new wxStaticText(this, wxID_ANY, wxString(m_employee.getLastName()));
		m_pFirst_name = new wxStaticText(this, wxID_ANY, wxString(m_employee.getFirstName()));
		pMain_sizer->Add(m_pLast_name, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);
		pMain_sizer->Add(m_pFirst_name, 0, wxALIGN_CENTER_HORIZONTAL);

		// Add label and text control pairs
		m_pEntry_date = pAddLabelAndTextControl(pMain_sizer,"Date: (YYYY-MM-DD)", getCurrentDate());
		m_pEntry_hour = pAddLabelAndTextControl(pMain_sizer,"Entry hour: (HH:MM)"); // Focus on this one
		m_pExit_hour = pAddLabelAndTextControl(pMain_sizer,"Exit hour : (HH:MM)");

		// Add a flexible spacer to push the buttons to the bottom
		pMain_sizer->AddStretchSpacer(1); // This adds a stretchable space that expands

		// Add footer button
		vector_buttons_footer = { m_pButton_disconnect, m_pButton_confirm };
		vector_labels_footer = { "Disconnect", "Confirm Entry" };
		vector_method_footer = {
			wxCommandEventHandler(PanelEmployee_Hours::onDisconnectButtonClicked),
			wxCommandEventHandler(PanelEmployee_Hours::onConfirmButtonClicked)
		};

		addFooterButtons(pMain_sizer, vector_buttons_footer, vector_labels_footer, vector_method_footer);

		// Set the main sizer for the panel to arrange the sub-widgets
		this->SetSizer(pMain_sizer);
		this->Layout();

		m_pEntry_hour->SetFocus(); // Focus on this wxTextCtrl
	}

	/** ####################################### Buttons ##################################### */
	/** ***************************************** Enter key *****************************************
	 */
	void PanelEmployee_Hours::onEnterKeyPressed() {
		sendData();
	}

	/** ***************************************** Disconnect Button *****************************************
	 * @param evt :
	 */
	void PanelEmployee_Hours::onDisconnectButtonClicked(wxCommandEvent& evt) {
		toPanelConnection();
	}

	/** ***************************************** Confirm Button *****************************************
	 * @param evt :
	 */
	void PanelEmployee_Hours::onConfirmButtonClicked(wxCommandEvent& evt) {
		sendData();
	}

	/** ####################################### Utilities ##################################### */
	/** ***************************************** Send Data *****************************************
	 * @brief : Send the data to the BllManager.
	 *
	 */
	void PanelEmployee_Hours::sendData() {
		// Validation of the fields (not empty)
		if (!validateInput()) {
			return;
		}

		// Fetch data from text controls
		wxString entry_date = getDate();
		wxString start_hour = getEntryHour();
		wxString end_hour = getExitHour();

		// Display a message dialog box and wait for confirmation
		wxString title = "Confirm your entry";
		wxString message = wxString::Format(
			title 
			+ ":\n\nDate: " + entry_date 
			+ "\nEntry hour: " + start_hour 
			+ "\nExit hout: " + end_hour
		);

		// Program will continue only if [Yes] is press by the user
		if (confirmMessageBox(message, title)) {
			if (bll::createNewEntry(
				m_employee.getEmployeeId(),
				entry_date.ToStdString(),
				start_hour.ToStdString(),
				end_hour.ToStdString()
			)) { 
				clearFields(); // if the entry is a succes clear the fields
			}
		}
	}

	/** ***************************************** TextControl validation *****************************************
	 * @brief : Validate the field of the hours manager.
	 *
	 * @return  : Boolean => false if any field is empty || true if all field are filled
	 */
	bool PanelEmployee_Hours::validateInput(){
		if (getDate().IsEmpty()
			|| getEntryHour().IsEmpty()
			|| getExitHour().IsEmpty()) {
			wxMessageBox("Please fill in all fields.", "Missing Information", wxOK | wxICON_WARNING);
			return false;
		}
		if (!isValidDate(getDate().ToStdString())) {
			return false;
		}
		if (!isValidHour(getEntryHour().ToStdString()) 
			|| !isValidHour(getExitHour().ToStdString())) {
			return false;
		}
		return true;
	}

	/** ***************************************** Clear the fields *****************************************
	 * @brief : Clear all fields (Not "m_pEntry_date") of the PanelEmployee_Hours.
	 * 
	 */
	void PanelEmployee_Hours::clearFields(){
		//m_pEntry_date->SetValue(""); // not needed
		m_pEntry_hour->SetValue("");
		m_pExit_hour->SetValue("");
	}


	/** ####################################### Getter ##################################### */
	wxString PanelEmployee_Hours::getDate(){
		return wxString(m_pEntry_date->GetValue());
	}
	wxString PanelEmployee_Hours::getEntryHour() {
		return wxString(m_pEntry_hour->GetValue());
	}
	wxString PanelEmployee_Hours::getExitHour() {
		return wxString(m_pExit_hour->GetValue());
	}
} // namespace gui

