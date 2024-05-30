/*****************************************************************//**
 * @file   Panel.cpp
 * @brief  Base class for all the panel, will contain public method
 * 
 * @author ThJo
 * @date   02 May 2024
 *********************************************************************/
#include "Panel.h"


namespace gui{
	// Constructor initializes the Panel with a parent window 
	// and optionally with a pointer to the main frame
	Panel::Panel(wxWindow* pParent, wxFrame* pMain_frame) 
		: wxPanel(pParent), m_pMain_frame(pMain_frame)
	{
		// Use wxEVT_CHAR_HOOK to catch all key events including Enter
		this->Bind(wxEVT_CHAR_HOOK, &Panel::onKeyDown, this);
	}

	/** ***************************************** Add title to Panel *****************************************
	 * @brief : Will add the title to the current Panel.
	 * 
	 * @param current_panel : wxPanel* => panel where the title is display (probably this)
	 * @param box_sizer : wxBoxSizer* => box sizer holding the title
	 * @param title : wxString& => title
	 */
	void Panel::addPanelTitle(wxBoxSizer* box_sizer, const wxString& title){
		wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
		wxStaticText* pTitle_page = new wxStaticText(this, wxID_ANY, title);
		pTitle_page->SetFont(global_title_font);
		box_sizer->Add(pTitle_page, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 40);
	}

	/** ***************************************** Label and Text Control *****************************************
	 * @brief : Create a label with is text control under.
	 * 
	 * @param box_sizer : wxBoxSizer* => box wizer where this will be display
	 * @param label : wxString& => label of the text control
	 * @param default_value :	wxString& => value of the text control, empty by default
	 * @param style : long => style if the wxTextCtrl, no style by default
	 * @return  : wxTextCtrl* => a label with is text control
	 */
	wxTextCtrl* Panel::pAddLabelAndTextControl(wxBoxSizer* box_sizer, const wxString& label, const wxString& default_value, long style) {
		wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
		wxStaticText* pLabel_text = new wxStaticText(this, wxID_ANY, label);
		wxTextCtrl* pText_ctrl = new wxTextCtrl(this, wxID_ANY, default_value, wxDefaultPosition, wxDefaultSize, style);
		pSizer->Add(pLabel_text, 0, wxBOTTOM, 5);  // Add some space below the label
		pSizer->Add(pText_ctrl, 1, wxEXPAND); // Expand to fill available horizontal space
		box_sizer->Add(pSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 40);
		return pText_ctrl;
	}

	// *********************************************************** Should Work ***********************************************************
	void Panel::addFooterButtons(wxBoxSizer* main_sizer, std::vector<wxButton*>& buttons, const std::vector<wxString>& labels){
		wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);

		size_t button_count = labels.size();
		buttons.resize(button_count);

		if (button_count == 1) {
			buttons[0] = new wxButton(this, wxID_ANY, labels[0]);
			button_sizer->Add(buttons[0], 0, wxRIGHT, 250);
			button_sizer->AddStretchSpacer(1);
		}
		else if (button_count == 2) {
			buttons[0] = new wxButton(this, wxID_ANY, labels[0]);
			buttons[1] = new wxButton(this, wxID_ANY, labels[1]);
			button_sizer->Add(buttons[0], 0, wxRIGHT, 250);
			button_sizer->AddStretchSpacer(1);
			button_sizer->Add(buttons[1], 0, wxLEFT, 250);
		}
		else {
			for (size_t i = 0; i < button_count; ++i) {
				buttons[i] = new wxButton(this, wxID_ANY, labels[i]);
				if (i > 0) {
					button_sizer->AddStretchSpacer(1); // Add spacer between buttons
				}
				button_sizer->Add(buttons[i], 0, wxLEFT | wxRIGHT, 10); // Add some padding around buttons
			}
		}
		main_sizer->Add(button_sizer, 0, wxEXPAND | wxALL, 10);
	}
	// *********************************************************** Should work ***********************************************************


	/** ***************************************** Buttons Footer *****************************************
	 * @brief : Construct and insert a sizer with the number of choosed buttons and display them evenly.
	 * 
	 * @param main_sizer : wxBoxSizer* => where this sizer gonna be insert
	 * @param buttons : std::vector<wxButton*>& => vector holding all buttons
	 * @param labels : std::vector<wxString>& => vector holding all label of the buttons
	 * @param method : std::vector<wxObjectEventFunction> => vector holding all methods "wxCommandEventHandler(Class::method)"
	 */
	void Panel::addFooterButtons(wxBoxSizer* main_sizer, std::vector<wxButton*>& buttons,
		const std::vector<wxString>& labels, std::vector<wxObjectEventFunction> method) {
		wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);

		size_t button_count = labels.size();
		buttons.resize(button_count);

		if (button_count == 1) {
			buttons[0] = new wxButton(this, wxID_ANY, labels[0]);
			button_sizer->Add(buttons[0], 0, wxRIGHT, 250);
			//button_sizer->AddStretchSpacer(1);
			buttons[0]->Bind(wxEVT_BUTTON, method[0], this);
		}
		else if (button_count == 2) {
			buttons[0] = new wxButton(this, wxID_ANY, labels[0]);
			buttons[1] = new wxButton(this, wxID_ANY, labels[1]);
			button_sizer->Add(buttons[0], 0, wxRIGHT, 250);
			//button_sizer->AddStretchSpacer(1);
			button_sizer->Add(buttons[1], 0, wxLEFT, 250);
			buttons[0]->Bind(wxEVT_BUTTON, method[0], this);
			buttons[1]->Bind(wxEVT_BUTTON, method[1], this);
		}
		else {
			for (size_t i = 0; i < button_count; ++i) {
				buttons[i] = new wxButton(this, wxID_ANY, labels[i]);
				if (i > 0) {
					button_sizer->AddStretchSpacer(1); // Add spacer between buttons
				}
				button_sizer->Add(buttons[i], 0, wxLEFT | wxRIGHT, 10); // Add some padding around buttons
				buttons[i]->Bind(wxEVT_BUTTON, method[i], this);
			}
		}
		main_sizer->Add(button_sizer, 0, wxEXPAND | wxALL, 10);
	}

	/** ***************************************** to Panel Admin *****************************************
	 * @brief : When call switch to the Panel Admin.
	 * 
	 */
	void Panel::toPanelAdmin() {
		// "dynamic_cast" need to be used, because the method "toPanelAdmin()" only exist in MainFrame, not in wxFrame
		MainFrame* pMain_frame_dynamic = dynamic_cast<MainFrame*>(m_pMain_frame); // Safe casting to derived class
		if (pMain_frame_dynamic) {
			pMain_frame_dynamic->toPanelAdmin(); // Call the method to switch panels
		}
		else {
			wxMessageBox("Failed to cast MainFrame", "Error", wxOK | wxICON_ERROR);
		}
	}

	/** ***************************************** to Panel Connection *****************************************
	 * @brief : When call switch to the Panel Connection after a confirmation from the User.
	 * 
	 */
	void Panel::toPanelConnection()	{
		if (confirmMessageBox("Do you want to disconnect from your session ?", "Disconnect")) {
			// "dynamic_cast" need to be used, because the method "toPanel_Connection()" only exist in MainFrame, not in wxFrame
			MainFrame* pMain_frame_dynamic = dynamic_cast<MainFrame*>(m_pMain_frame); // Safe casting to derived class
			if (pMain_frame_dynamic) {
				pMain_frame_dynamic->toPanel_Connection(); // Call the method to switch panels
			}
			else {
				wxMessageBox("Failed to cast MainFrame", "Error", wxOK | wxICON_ERROR);
			}
		}
	}

	/** ***************************************** Enter key *****************************************
	 * @brief : Default implementation does nothing.
	 *
	 */
	void Panel::onEnterKeyPressed(){
		// Default implementation does nothing
	}

	void Panel::onKeyDown(wxKeyEvent& event) {
		if (event.GetKeyCode() == WXK_RETURN) {
			onEnterKeyPressed();
		}
		else {
			event.Skip(); // Skip to allow other handlers to process the event
		}
	}


	/** ####################################### Utilities ##################################### */
	/** ***************************************** Confirm Message Box *****************************************
	 * @brief : Display a message dialog with the info of the created employee
	 *	and ask a confirmation with YES, NO, CANCEL.
	 *
	 * @param message : wxString => it's the message display inside the message dialog
	 * @param title : wxString => it's the title of the message dialog
	 * @return  : Boolean
	 */
	bool Panel::confirmMessageBox(wxString message, wxString title) {
		wxMessageDialog dialog(this, message, title, wxYES_NO | wxCANCEL | wxICON_INFORMATION);
		auto result = dialog.ShowModal();

		switch (result) {
		case wxID_YES:
			return true;
		case wxID_NO:
			return false;
		case wxID_CANCEL:
			return false;
		default:
			return false;
		}
	}

	/** ***************************************** Give the current date *****************************************
	 * @brief : Get the current date of the system.
	 * 
	 * @return  : wxString => date in format YYYY-MM-DD
	 */
	wxString Panel::getCurrentDate(){
		wxDateTime now = wxDateTime::Now();
		wxString formattedDate = now.FormatISODate();
		return formattedDate;
	}

	/** ####################################### Check Format Regex ##################################### */
	/** ***************************************** check Date Format *****************************************
	 * @brief : Check if the given date is in the format YYYY-MM-DD.
	 * 
	 * @param date : std::string& => date
	 * @return  : boolean
	 */
	bool Panel::isValidDate(const std::string& date) {
		if (std::regex_match(date, M_DATE_PATTERN)) {
			return true;
		}
		wxMessageBox("Date format is incorrect: YYYY-MM-DD", "Incorrect Format", wxOK | wxICON_WARNING);
		return false;
	}

	/** ***************************************** check Hour Format *****************************************
	 * @brief : Check if the given hour is in the format HH:MM.
	 * 
	 * @param hour : std::string& => hour
	 * @return  : boolean
	 */
	bool Panel::isValidHour(const std::string& hour) {
		if (std::regex_match(hour, M_HOUR_PATTERN)) {
			return true;
		}
		wxMessageBox("Hour format is incorrect: HH:MM", "Incorrect Format", wxOK | wxICON_WARNING);
		return false;
	}

	/** ***************************************** check Name Format *****************************************
	 * @brief : Check if the given Name is in Alphabetic characters, spaces, and hyphens
	 *
	 * @param name : std::string& name
	 * @return  : boolean
	 */
	bool Panel::isValidName(const std::string& name) {
		if (std::regex_match(name, M_NAME_PATTERN)) {
			return true;
		}
		wxMessageBox("Name format incorrect.", "Incorrect Format", wxOK | wxICON_WARNING);
		return false;
	}

	/** ***************************************** check Email Format *****************************************
	 * @brief : Check if the given email is in a correct format.
	 *
	 * @param email : std::string& email
	 * @return  : boolean
	 */
	bool Panel::isValidEmail(const std::string& email) {
		if (std::regex_match(email, M_EMAIL_PATTERN)) {
			return true;
		}
		wxMessageBox("Email format incorrect.", "Incorrect Format", wxOK | wxICON_WARNING);
		return false;
	}

	/** ***************************************** check Debug Password Format *****************************************
	 * @brief : Check if the given password as at least 4 characters.
	 *
	 * @param password : std::string& password
	 * @return  : boolean
	 */
	bool Panel::isValidPasswordDebug(const std::string& password) {
		if (std::regex_match(password, M_PASSWORD_PATTERN_DEBUG)) {
			return true;
		}
		wxMessageBox("Password format incorrect: At least 4 characters", "Incorrect Format", wxOK | wxICON_WARNING);
		return false;
	}

	/** ***************************************** check Strong Password Format *****************************************
	 * @brief : Check if the given password is in a correct format:
	 * at least 12 characters, including at least one uppercase letter,
	 * one lowercase letter, one number, and one special character
	 *
	 * @param password : std::string& password
	 * @return  : boolean
	 */
	bool Panel::isValidPasswordStrong(const std::string& password) {
		if (std::regex_match(password, M_PASSWORD_PATTERN_STRONG)) {
			return true;
		}
		wxMessageBox("Password format incorrect: "
			"At least 12 characters, including at least one uppercase letter "
			"one lowercase letter, one number, and one special character",
			"Incorrect Format", wxOK | wxICON_WARNING);
		return false;
	}
} // namespace gui