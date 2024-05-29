/*****************************************************************//**
 * @file   PanelEmployee_Hours.cpp
 * @brief  Panel where Employee can enter there entry time and exit time
 *
 * @author ThJo
 * @date   3 May 2024
 *********************************************************************/
#include "PanelEmployee_Hours.h"


namespace gui {
	PanelEmployee_Hours::PanelEmployee_Hours(wxWindow* pParent, wxFrame* pMain_frame, const Employee& employee)
		: Panel{ pParent, pMain_frame }, m_employee{ employee }
	{
		initializeComponents();
		bindEventHandlers();
	}

	/** ####################################### GUI #####################################
	 * @brief : GUI for the panel hours management.
	 *	"this" make reference to Panel class too
	 */
	void PanelEmployee_Hours::initializeComponents() {
		// Main sizer for the entire panel
		wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

		// Title of the panel
		m_pTitle_page = new wxStaticText(this, wxID_ANY, "Hours manager");
		m_pTitle_page->SetFont(global_title_font);
		pMain_sizer->Add(m_pTitle_page, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 40);

		// Display infos of the current employee connected (convert from std::string to wxString)
		m_pLast_name = new wxStaticText(this, wxID_ANY, wxString(m_employee.getLastName()));
		m_pFirst_name = new wxStaticText(this, wxID_ANY, wxString(m_employee.getFirstName()));
		pMain_sizer->Add(m_pLast_name, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);
		pMain_sizer->Add(m_pFirst_name, 0, wxALIGN_CENTER_HORIZONTAL);

		// Helper function to create label and text control pairs
		auto addLabelAndTextControl = [&](const wxString& label,
			const wxString& defaultValue = "",
			long style = 0) -> wxTextCtrl* {
				wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
				wxStaticText* pLabel_text = new wxStaticText(this, wxID_ANY, label);
				wxTextCtrl* pText_ctrl = new wxTextCtrl(this, wxID_ANY, defaultValue, wxDefaultPosition, wxDefaultSize, style);
				pSizer->Add(pLabel_text, 0, wxBOTTOM, 5);  // Add some space below the label
				pSizer->Add(pText_ctrl, 1, wxEXPAND); // Expand to fill available horizontal space
				pMain_sizer->Add(pSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 40);
				return pText_ctrl;
			};

		// Add label and text control pairs
		m_pEntry_date = addLabelAndTextControl("Date: (YYYY-MM-DD)", getCurrentDate());
		m_pEntry_hour = addLabelAndTextControl("Entry hour: (HH:MM)"); // Focus on this one
		m_pExit_hour = addLabelAndTextControl("Exit hour: (HH:MM)");

		// Add a flexible spacer to push the buttons to the bottom
		pMain_sizer->AddStretchSpacer(1); // This adds a stretchable space that expands

		// Buttons at the bottom
		wxBoxSizer* pButton_sizer = new wxBoxSizer(wxHORIZONTAL);
		m_pButton_disconnect = new wxButton(this, wxID_ANY, "Disconnect");
		m_pButton_confirm = new wxButton(this, wxID_ANY, "Confirm Entry");
		pButton_sizer->Add(m_pButton_disconnect, 0, wxRIGHT, 250);
		pButton_sizer->Add(m_pButton_confirm, 0, wxLEFT, 250);

		// Add buttons without top space pushing down
		pMain_sizer->Add(pButton_sizer, 0, wxALIGN_CENTER | wxALL, 10);

		// Set the main sizer for the panel to arrange the sub-widgets
		this->SetSizer(pMain_sizer);
		this->Layout();

		m_pEntry_hour->SetFocus(); // Focus on this wxTextCtrl
	}

	/** ####################################### Buttons ##################################### */
	/** ***************************************** Bind Handler *****************************************
	 * @brief : Handle all the buttons bind of this panel.
	 *
	 */
	void PanelEmployee_Hours::bindEventHandlers() {
		m_pButton_disconnect->Bind(wxEVT_BUTTON, &PanelEmployee_Hours::onDisconnectButtonClicked, this);
		m_pButton_confirm->Bind(wxEVT_BUTTON, &PanelEmployee_Hours::onConfirmButtonClicked, this);
	}

	void PanelEmployee_Hours::onEnterKeyPressed() {
		sendData();
	}

	/** ***************************************** Disconnect Button *****************************************
	 * @brief : When the button disconnect is press,
	 *	will return to (PanelConnection), after confirmation from the user.
	 *
	 * @param evt :
	 */
	void PanelEmployee_Hours::onDisconnectButtonClicked(wxCommandEvent& evt) {
		if (confirmMessageBox("Do you want to disconnect from your session ?", "Disconnect")) {
			// "dynamic_cast" need to be used, because the method "toPanel_Connection()" only exist in MainFrame, not in wxFrame
			MainFrame* pMain_frame_dynamic = dynamic_cast<MainFrame*>(pMain_frame); // Safe casting to derived class
			if (pMain_frame_dynamic) {
				pMain_frame_dynamic->toPanel_Connection(); // Call the method to switch panels
			}
			else {
				wxMessageBox("Failed to cast MainFrame", "Error", wxOK | wxICON_ERROR);
			}
		}
	}

	/** ***************************************** Confirm Button *****************************************
	 * @brief : Confirm Button
	 *
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

