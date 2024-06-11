/*****************************************************************//**
 * @file   PanelAdmin.h
 * @brief  Panel where the admin have options to get datas and update the DB
 * 
 * @author ThJo
 * @date   7 May 2024
 *********************************************************************/
#pragma once
#include "Panel.h"

namespace gui {
	class PanelAdmin : public Panel {
	public:
		// Constructor
		PanelAdmin(wxWindow* pParent, wxFrame* pMain_frame);

	private:
		const wxSize m_button_size{ wxSize(170, 50) };

		// Buttons
		wxButton* m_pButton_add_employee;
		wxButton* m_pButton_update_employee;
		wxButton* m_pButton_list_employee;
		wxButton* m_pButton_all_salaries;

		wxButton* m_pButton_disconnect;
		wxButton* m_pButton_placeholder;

		/** ####################################### GUI #####################################
		 * @brief : GUI for the panel admin.
		 *	"this" make reference to Panel class too
		 */
		void initializeComponents();

		/** ***************************************** Bind Handler *****************************************
		 * @brief : Handle all the buttons bind of this panel.
		 *
		 */
		void bindEventHandlers();

		/** ***************************************** Button Add Employee *****************************************
		 * @brief : Create the panel for adding a new employee (PanelAdmin_EmployeeCreation).
		 *
		 * @param evt :
		 */
		void onAddEmployeeClicked(wxCommandEvent& evt);

		/** ***************************************** Button Update Employee *****************************************
		 * @brief : Create the panel for updating a employee informations (PanelAdmin_EmployeeUpdate).
		 *
		 * @param evt :
		 */
		void onUpdateEmployeeClicked(wxCommandEvent& evt);

		/** ***************************************** Button List Employee *****************************************
		 * @brief : Create the panel for display the list of employee and
		 *	display there hours and salaries (PanelAdminEmployeeList).
		 *
		 * @param evt :
		 */
		void onListEmployeeClicked(wxCommandEvent& evt);

		/** ***************************************** Button All Salaries *****************************************
		 * @brief : Create the panel for display the list of employee and
		 *	display there hours and salaries (toPanel_Admin_AllSalaries).
		 *
		 * @param evt :
		 */
		void onAllSalariesClicked(wxCommandEvent& evt);

		/** ***************************************** Disconnect Button *****************************************
		 * @brief : When the button disconnect is press,
		 *	will return to the main page (PanelConnection), after confirmation from the user.
		 *
		 * @param evt :
		 */
		void onDisconnectButtonClicked(wxCommandEvent& evt);

	};
} // namespace gui
