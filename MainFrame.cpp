/*****************************************************************//**
 * @file   MainFrame.cpp
 * @brief  Create the Main Frame and manage the panel when changing page
 *
 * @author ThJo
 * @date   29 April 2024
 *********************************************************************/
#include "MainFrame.h"

#include "Panel.h"
#include "PanelConnection.h"
#include "PanelEmployee_Hours.h"
#include "PanelAdmin.h"
#include "PanelAdmin_EmployeeCreation.h"
#include "PanelAdmin_EmployeeUpdate.h"
#include "PanelAdmin_EmployeeList.h"

namespace gui {
	MainFrame::MainFrame(const wxString& title) 
		: wxFrame(nullptr, wxID_ANY, title) {

		//SwitchPanel(new PanelAdmin(this, this)); // DEBUG to Admin panel
		SwitchPanel(new PanelConnection(this, this)); // Program start with this Panel
		CreateStatusBar(); // Display a Status Bar in the lower part of the frame
		Show(true);
	}

	/** ####################################### Employee ##################################### */
	/**  ***************************************** Switch to (PanelEmployee_Hours) *****************************************
	 * @brief : Will change the panel to (PanelEmployee_Hours).
	 * 
	 * @param employee_details : Employee, with the full details (employee_ID, employee_last_name, employee_first_name, employee_email)
	 */
	void MainFrame::toPanel_Employee_Hours(bll::Employee& employee_details) {
		SwitchPanel(new PanelEmployee_Hours(this, this, employee_details));
	}

	/**  ***************************************** Switch to (PanelConnection) *****************************************
	 * @brief : Will change the panel to (PanelConnection).
	 * 
	 */
	void MainFrame::toPanel_Connection(){
		SwitchPanel(new PanelConnection(this, this));
	}

	/** ####################################### Admin ##################################### */
	/** ***************************************** Switch to (PanelAdmin) *****************************************
	 * @brief : Will change the panel to (PanelAdmin).
	 * 
	 */
	void MainFrame::toPanelAdmin(){
		SwitchPanel(new PanelAdmin(this, this));
	}

	/** ***************************************** Switch to (PanelAdmin_EmployeeCreation) *****************************************
	 * @brief : Will change the panel to (PanelAdmin_EmployeeCreation).
	 * 
	 */
	void MainFrame::toPanel_Admin_AddEmployee(){
		SwitchPanel(new PanelAdmin_EmployeeCreation(this, this));
	}

	/** ***************************************** Switch to (PanelAdmin_EmployeeUpdate) *****************************************
	 * @brief : Will change the panel to (PanelAdmin_EmployeeUpdate).
	 * 
	 */
	void MainFrame::toPanel_Admin_UpdateEmployee(){
		//SwitchPanel(new PanelAdmin_EmployeeUpdate(this, this));
	}

	/** ***************************************** Switch to (PanelAdminEmployeeList) *****************************************
	 * @brief : Will change the panel to (PanelAdminEmployeeList).
	 * 
	 */
	void MainFrame::toPanel_Admin_ListEmployee(){
		SwitchPanel(new PanelAdminEmployeeList(this, this));
	}


	/** ####################################### Utilities ##################################### */
	/** ***************************************** Switch Panel *****************************************
	 * @brief : Destroy the current panel if there is one and create the new one.
	 *
	 * @param newPanel : wxPanel*, the panel to create inside the frame
	 */
	void MainFrame::SwitchPanel(wxPanel* newPanel) {
		if (m_pCurrent_panel) {
			m_pCurrent_panel->Destroy();  // Remove the current panel
		}
		m_pCurrent_panel = newPanel;
		this->SetSizer(new wxBoxSizer(wxVERTICAL));  // Ensure the frame has a sizer
		this->GetSizer()->Add(m_pCurrent_panel, 1, wxEXPAND | wxALL);
		this->Layout();
		this->Fit();
	}
} // namespace gui

