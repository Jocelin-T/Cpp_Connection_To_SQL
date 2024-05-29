/*****************************************************************//**
 * @file   PanelEmployee_Hours.h
 * @brief  Panel where Employee can enter there entry time and exit time
 *
 * @author ThJo
 * @date   3 May 2024
 *********************************************************************/
#pragma once
#include "Panel.h"

namespace gui {
	class PanelEmployee_Hours : public Panel{
	public:
		// Constructor
		PanelEmployee_Hours(wxWindow* pParent, wxFrame* pMain_frame, const bll::Employee& employee);

		// Getter
		wxString getDate();
		wxString getEntryHour();
		wxString getExitHour();

	private:
		// Static Text
		wxStaticText* m_pLast_name;
		wxStaticText* m_pFirst_name;

		// Text fields
		wxTextCtrl* m_pEntry_date;
		wxTextCtrl* m_pEntry_hour;
		wxTextCtrl* m_pExit_hour;

		// Buttons
		wxButton* m_pButton_disconnect;
		wxButton* m_pButton_confirm;

		// Current employee connected
		const bll::Employee m_employee;

		// Override the onEnterKeyPressed method
		void onEnterKeyPressed() override;

		/**
		 * @brief : GUI for this panel.
		 *	"this" make reference to Panel class too
		 */
		void initializeComponents();

		/** ***************************************** Bind Handler *****************************************
		 * @brief : Handle all the buttons bind of this panel.
		 *
		 */
		void bindEventHandlers();

		/** ***************************************** Disconnect Button *****************************************
		 * @brief : When the button disconnect is press,
		 *	will return to the main page (PanelConnection), after confirmation from the user.
		 *
		 * @param evt :
		 */
		void onDisconnectButtonClicked(wxCommandEvent& evt);

		/** ***************************************** Confirm Button *****************************************
		 * @brief : When the button "Confirm Entry" is press,
		 *	check if all fields are not empty,
		 *	wait the confirmation from the user,
		 *	add the inputs in the table [Entries].
		 *
		 * @param evt :
		 */
		void onConfirmButtonClicked(wxCommandEvent& evt);

		/** ***************************************** Send Data *****************************************
		 * @brief : Send the data to the BllManager.
		 *
		 */
		void sendData();

		/** ***************************************** TextControl validation *****************************************
		 * @brief : Validate the field of the hours manager.
		 *
		 * @return  : Boolean, false if any field is empty || true if all field are filled
		 */
		bool validateInput();

		/** ***************************************** Clear the fields *****************************************
		 * @brief : Clear all fields of the PanelEmployee_Hours.
		 *
		 */
		void clearFields();
	};
} // namespace gui


