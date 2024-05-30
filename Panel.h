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
#include <vector>

#include "AppGlobals.h"
#include "MainFrame.h"
#include "BLLManager.h"


namespace gui {
	class Panel : public wxPanel {
	public:
		// constructor initializes the Panel with a parent window 
		// and optionally with a pointer to the main frame (nullptr = optional in this case)
		Panel(wxWindow* pParent, wxFrame* pMain_frame = nullptr);

	protected:
		const std::regex M_DATE_PATTERN{ R"(^\d{4}-\d{2}-\d{2}$)" }; // YYYY-MM-DD
		const std::regex M_HOUR_PATTERN{ R"(^([01]\d|2[0-3]):([0-5]\d)$)" }; // HH:MM
		const std::regex M_NAME_PATTERN{ R"(^[A-Za-z\s-]+$)" }; // Alphabetic characters, spaces, and hyphens
		const std::regex M_EMAIL_PATTERN{ R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)" };
		const std::regex M_PASSWORD_PATTERN_DEBUG{ R"(^.{4,}$)" }; // At least 4 characters
		const std::regex M_PASSWORD_PATTERN_STRONG{
			R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{12,})" 
		};// at least 12 characters, including at least one uppercase letter,
		// one lowercase letter, one number, and one special character

		wxFrame* m_pMain_frame; // Pointer to the main frame

		// Vector for the footer buttons
		std::vector<wxButton*> vector_buttons_footer = {};
		std::vector<wxString> vector_labels_footer = {};
		std::vector<wxObjectEventFunction> vector_method_footer = {};


		/** ***************************************** Add title to Panel *****************************************
		 * @brief : Will add the title to the current Panel.
		 *
		 * @param current_panel : wxPanel* => panel where the title is display (probably this)
		 * @param box_sizer : wxBoxSizer* => box sizer holding the title
		 * @param title : wxString& => title
		 */
		void addPanelTitle(wxBoxSizer* box_sizer,const wxString& title);

		/** ***************************************** Label and Text Control *****************************************
		 * @brief : Create a label with is text control under.
		 *
		 * @param box_sizer : wxBoxSizer* => box wizer where this will be display
		 * @param label : wxString& => label of the text control
		 * @param default_value :	wxString& => value of the text control, empty by default
		 * @param style : long => 0 by default
		 * @return  : wxTextCtrl* => a label with is text control
		 */
		wxTextCtrl* pAddLabelAndTextControl(wxBoxSizer* box_sizer, const wxString& label,
			const wxString& default_value = "",
			long style = 0);

		// Should work ?
		void addFooterButtons(wxBoxSizer* main_sizer,
			std::vector<wxButton*>& buttons,
			const std::vector<wxString>& labels);

		/** ***************************************** Footer Buttons *****************************************
		 * @brief : Construct and insert a sizer with the number of choosed buttons and display them evenly.
		 *
		 * @param main_sizer : wxBoxSizer* => where this sizer gonna be insert
		 * @param buttons : std::vector<wxButton*>& => vector holding all buttons
		 * @param labels : std::vector<wxString>& => vector holding all label of the buttons
		 * @param method : std::vector<wxObjectEventFunction> => vector holding all methods
		 *				"wxCommandEventHandler(Class::method)"
		 */
		void addFooterButtons(wxBoxSizer* main_sizer, 
			std::vector<wxButton*>& buttons,
			const std::vector<wxString>& labels,
			std::vector<wxObjectEventFunction> method);

		/** ***************************************** to Panel Admin *****************************************
		 * @brief : When call switch to the Panel Admin.
		 *
		 */
		void toPanelAdmin();

		/** ***************************************** to Panel Connection *****************************************
		 * @brief : When call switch to the Panel Connection after a confirmation from the User.
		 *
		 */
		void toPanelConnection();

		/** ***************************************** Enter key *****************************************
		 * @brief : Default implementation does nothing.
		 * 
		 */
		virtual void onEnterKeyPressed();
		
		// for enter key
		void onKeyDown(wxKeyEvent& event);

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
		virtual bool isValidHour(const std::string& hour);

		/** ***************************************** check Name Format *****************************************
		 * @brief : Check if the given Name is in Alphabetic characters, spaces, and hyphens
		 *
		 * @param name : std::string& name
		 * @return  : boolean
		 */
		virtual bool isValidName(const std::string& name);

		/** ***************************************** check Email Format *****************************************
		 * @brief : Check if the given email is in a correct format.
		 *
		 * @param email : std::string& email
		 * @return  : boolean
		 */
		virtual bool isValidEmail(const std::string& email);

		/** ***************************************** check Debug Password Format *****************************************
		 * @brief : Check if the given password as at least 4 characters.
		 *
		 * @param password : std::string& password
		 * @return  : boolean
		 */
		virtual bool isValidPasswordDebug(const std::string& password);

		/** ***************************************** check Debug Password Format *****************************************
		 * @brief : Check if the given password is in a correct format:
		 * at least 12 characters, including at least one uppercase letter,
		 * one lowercase letter, one number, and one special character
		 *
		 * @param password : std::string& password
		 * @return  : boolean
		 */
		virtual bool isValidPasswordStrong(const std::string& password);

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