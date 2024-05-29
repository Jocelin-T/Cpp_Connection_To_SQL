/*****************************************************************//**
 * @file   Panel.h
 * @brief  Base class for all the panel, will contain public method
 *
 * @author ThJo
 * @date   02 April 2024
 *********************************************************************/
#pragma once
#include <wx/wx.h>
#include <regex>

#include "AppGlobals.h"
#include "MainFrame.h"
#include "BLLManager.h"


namespace gui {
	class Panel : public wxPanel {
	public:
		// constructor initializes the Panel with a parent window 
		// and optionally with a pointer to the main frame (nullptr = optional in this case)
		Panel(wxWindow* pParent, wxFrame* pMain_frame = nullptr);

		/** ***************************************** Enter key *****************************************
		 * @brief : Default implementation does nothing.
		 * 
		 */
		virtual void onEnterKeyPressed();

		void onKeyDown(wxKeyEvent& event);
	

	protected:
		const std::regex M_DATE_PATTERN{ R"(^\d{4}-\d{2}-\d{2}$)" }; // YYYY-MM-DD
		const std::regex M_HOUR_PATTERN{ R"(^([01]\d|2[0-3]):([0-5]\d)$)" }; // HH:MM
		const std::regex M_NAME_PATTERN{ R"(^[A-Za-z\s-]+$)" }; // Alphabetic characters, spaces, and hyphens
		const std::regex M_EMAIL_PATTERN{ R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)" };
		const std::regex M_PASSWORD_PATTERN_DEBUG{ R"(^.{4,}$)" }; // At least 4 characters
		const std::regex M_PASSWORD_PATTERN_STRONG{
			R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{12,})" 
		};// at least 12 characters, including at least one uppercase letter,
		//one lowercase letter, one number, and one special character

		wxFrame* pMain_frame; // Pointer to the main frame

		/** ***************************************** check Date Format *****************************************
		 * @brief : Check if the given date is in the format YYYY-MM-DD.
		 *
		 * @param date : std::string& => date
		 * @return  : boolean
		 */
		virtual bool isValidDate(const std::string& date);

		/** ***************************************** check Hour Format *****************************************
		 * @brief : Check if the given hour is in the format HH:MM.
		 *
		 * @param hour : std::string& => hour
		 * @return  : boolean
		 */
		bool isValidHour(const std::string& hour);

		/** ***************************************** check Name Format *****************************************
		 * @brief : Check if the given Name is in Alphabetic characters, spaces, and hyphens
		 *
		 * @param name : std::string& name
		 * @return  : boolean
		 */
		bool isValidName(const std::string& name);

		/** ***************************************** check Email Format *****************************************
		 * @brief : Check if the given email is in a correct format.
		 *
		 * @param email : std::string& email
		 * @return  : boolean
		 */
		bool isValidEmail(const std::string& email);

		/** ***************************************** check Debug Password Format *****************************************
		 * @brief : Check if the given password as at least 4 characters.
		 *
		 * @param password : std::string& password
		 * @return  : boolean
		 */
		bool isValidPasswordDebug(const std::string& password);

		/** ***************************************** check Debug Password Format *****************************************
		 * @brief : Check if the given password is in a correct format:
		 * at least 12 characters, including at least one uppercase letter,
		 * one lowercase letter, one number, and one special character
		 *
		 * @param password : std::string& password
		 * @return  : boolean
		 */
		bool isValidPasswordStrong(const std::string& password);

		/** ***************************************** Confirm Message Box *****************************************
		 * @brief : Display a message dialog with the info of the created employee
		 *	and ask a confirmation with YES, NO, CANCEL.
		 *
		 * @param message : wxString, it's the message display inside the message dialog
		 * @param title : wxString, it's the title of the message dialog
		 * @return  : Boolean
		 */
		bool confirmMessageBox(const wxString message, const wxString title);

		/** ***************************************** Give the current date *****************************************
		 * @brief : Get the current date of the system.
		 *
		 * @return  : wxString, date in format YYYY-MM-DD
		 */
		wxString getCurrentDate();

	};
} // namespace gui