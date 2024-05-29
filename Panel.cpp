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
		: wxPanel(pParent), pMain_frame(pMain_frame)
	{
		// Use wxEVT_CHAR_HOOK to catch all key events including Enter
		this->Bind(wxEVT_CHAR_HOOK, &Panel::onKeyDown, this);
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
			//wxLogStatus("Yes");
			return true;
		case wxID_NO:
			//wxLogStatus("No");
			return false;
		case wxID_CANCEL:
			//wxLogStatus("Cancel");
			return false;
		default:
			//wxLogStatus("Default");
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