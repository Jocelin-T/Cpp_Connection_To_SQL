/*****************************************************************//**
 * @file   PanelConnection.h
 * @brief  Panel where Employee and Admin can connect
 *
 * @author ThJo
 * @date   3 May 2024
 *********************************************************************/
#pragma once
#include "Panel.h"
#include "Employee.h"
#include "SqlQuery.h"
#include "BLLManager.h"


namespace gui {
	class PanelConnection : public Panel {
	public:
		// Constructor
		PanelConnection(wxWindow* pParent, wxFrame* pMain_frame);

		// Override the onEnterKeyPressed method
		void onEnterKeyPressed() override;

	private:
		// Text fields
		wxTextCtrl* m_pEmail;
		wxTextCtrl* m_pPassword;

		// Buttons
		wxButton* m_pButton_exit;
		wxButton* m_pButton_connect;


		/**  ####################################### GUI #####################################
		 * @brief : GUI for this panel.
		 *	"this" make reference to Panel class too
		 */
		void initializeComponents();

		/** ***************************************** Connect Button *****************************************
		 * @brief : Connect button.
		 *
		 * @param evt :
		 */
		void onConnectButtonClicked(wxCommandEvent& evt);

		/** ***************************************** Exit Button *****************************************
		 * @brief : This button close the program after confimation from the user
		 *
		 * @param evt :
		 */
		void onExitButtonClicked(wxCommandEvent& evt);

		/** ***************************************** Try to connect the User *****************************************
		 * @brief : If the fields are filled, check if they are corresponding to a employee inside the DB.
		 *
		 */
		void connectUser();

		// Getter
		wxString getEmail();
		wxString getPassword();

	};
} // namespace gui

