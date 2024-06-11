/*****************************************************************//**
 * @file   PanelAdminAllSalaries.h
 * @brief  Panel where all salaries are displayed, for each Employee
 * 
 * @author ThJo
 * @date   3 June 2024
 *********************************************************************/
#pragma once
#include "Panel.h"



namespace gui {
	class PanelAdminAllSalaries : public Panel {
	public:
		// Constructor
		PanelAdminAllSalaries(wxWindow* pParent, wxFrame* pMain_frame);

	private:
		// Date selection
		wxTextCtrl* m_pYear;

		// Display all salaries data
		wxPanel* m_pSalary_panel;
		wxScrolledWindow* m_pScrolled_window;
		wxBoxSizer* m_pSalaries_sizer;

		// Buttons
		wxButton* m_pButton_back;

		void InitializeComponents();

		void BindEventHandlers();

		void onBackButtonClicked(wxCommandEvent& evt);

		void onYearChanged(wxCommandEvent& evt);

		/** ***************************************** Year validation [override] *****************************************
		 * @brief : Override the method from the base Class, for ignoring the wxMessageBox.
		 *
		 * @param date : std::string& => year
		 * @return  : boolean
		 */
		bool isValidYear(const std::string& year) override;

		/** ***************************************** Update salaries *****************************************
		 * @brief : When call update all salaries.
		 *
		 */
		void updatePanelSalaries();

	};
} // namespace gui
