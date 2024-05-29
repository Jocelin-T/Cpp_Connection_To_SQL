/*****************************************************************//**
 * @file   PanelAdmin.cpp
 * @brief  Panel where the admin have options to get datas and update the DB
 * 
 * @author ThJo
 * @date   7 May 2024
 *********************************************************************/
#include "PanelAdmin.h"

namespace gui {
	PanelAdmin::PanelAdmin(wxWindow* pParent, wxFrame* pMain_frame)
		: Panel(pParent, pMain_frame) {
		initializeComponents();
		bindEventHandlers();
	}

	/** ####################################### GUI #####################################
	 * @brief : GUI for the panel admin.
	 *	"this" make reference to Panel class too
	 */
	void PanelAdmin::initializeComponents(){
		// Main sizer for the entire panel
		wxBoxSizer* pMain_sizer = new wxBoxSizer(wxVERTICAL);

		// Title of the panel
		m_pTitle_page = new wxStaticText(this, wxID_ANY, "Admin Manager");
		m_pTitle_page->SetFont(global_title_font);
		pMain_sizer->Add(m_pTitle_page, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 40);

		// Buttons of admin options
		wxBoxSizer* pOption_sizer = new wxBoxSizer(wxVERTICAL);
		pButton_add_employee = new wxButton(this, wxID_ANY, "Add a new employee", wxDefaultPosition, button_size);
		pOption_sizer->Add(pButton_add_employee, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);

		pButton_update_employee = new wxButton(this, wxID_ANY, "Update a employee", wxDefaultPosition, button_size);
		pOption_sizer->Add(pButton_update_employee, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);

		pButton_list_employee = new wxButton(this, wxID_ANY, "Show list of employee", wxDefaultPosition, button_size);
		pOption_sizer->Add(pButton_list_employee, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);


		pMain_sizer->Add(pOption_sizer, 0, wxALIGN_CENTER);

		// Add a flexible spacer to push the buttons to the bottom
		pMain_sizer->AddStretchSpacer(1); // This adds a stretchable space that expands

		// Buttons at the bottom
		wxBoxSizer* pButton_sizer = new wxBoxSizer(wxHORIZONTAL);
		pButton_disconnect = new wxButton(this, wxID_ANY, "Disconnect");
		pButton_placeholder = new wxButton(this, wxID_ANY, ""); // not visible
		pButton_placeholder->Show(false); 
		pButton_sizer->Add(pButton_disconnect, 0, wxRIGHT, 550);
		pButton_sizer->Add(pButton_placeholder, 0, wxLEFT, 250);

		// Add buttons without top space pushing down
		pMain_sizer->Add(pButton_sizer, 0, wxALIGN_CENTER | wxALL, 10);

		// Set the main sizer for the panel to arrange the sub-widgets
		this->SetSizer(pMain_sizer);
		this->Layout();

		pButton_add_employee->SetFocus();
	}
	/** ####################################### Buttons ##################################### */
	/** ***************************************** Bind Handler *****************************************
	 * @brief : Handle all the buttons bind of this panel.
	 *
	 */
	void PanelAdmin::bindEventHandlers(){
		pButton_add_employee->Bind(wxEVT_BUTTON, &PanelAdmin::onAddEmployeeClicked, this);
		pButton_update_employee->Bind(wxEVT_BUTTON, &PanelAdmin::onUpdateEmployeeClicked, this);
		pButton_list_employee->Bind(wxEVT_BUTTON, &PanelAdmin::onListEmployeeClicked, this);

		pButton_disconnect->Bind(wxEVT_BUTTON, &PanelAdmin::onDisconnectButtonClicked, this);
	}

	/** ***************************************** Button Add Employee *****************************************
	 * @brief : Create the panel for adding a new employee (PanelAdmin_EmployeeCreation).
	 * 
	 * @param evt :
	 */
	void PanelAdmin::onAddEmployeeClicked(wxCommandEvent& evt){
		// "dynamic_cast" need to be used, because the method "toPanel_Admin_AddEmployee()" only exist in MainFrame, not in wxFrame
		MainFrame* pMain_frame_dynamic = dynamic_cast<MainFrame*>(pMain_frame); // Safe casting to derived class
		if (pMain_frame_dynamic) {
			pMain_frame_dynamic->toPanel_Admin_AddEmployee(); // Call the method to switch panels
		}
		else {
			wxMessageBox("Failed to cast MainFrame", "Error", wxOK | wxICON_ERROR);
		}
	}

	/** ***************************************** Button Update Employee *****************************************
	 * @brief : Create the panel for updating a employee informations (PanelAdmin_EmployeeUpdate).
	 * 
	 * @param evt :
	 */
	void PanelAdmin::onUpdateEmployeeClicked(wxCommandEvent& evt){
		// "dynamic_cast" need to be used, because the method "toPanel_Admin_UpdateEmployee()" only exist in MainFrame, not in wxFrame
		MainFrame* pMain_frame_dynamic = dynamic_cast<MainFrame*>(pMain_frame); // Safe casting to derived class
		if (pMain_frame_dynamic) {
			pMain_frame_dynamic->toPanel_Admin_UpdateEmployee(); // Call the method to switch panels
		}
		else {
			wxMessageBox("Failed to cast MainFrame", "Error", wxOK | wxICON_ERROR);
		}
	}

	/** ***************************************** Button List Employee *****************************************
	 * @brief : Create the panel for display the list of employee and 
	 *	display there hours and salaries (PanelAdminEmployeeList).
	 * 
	 * @param evt :
	 */
	void PanelAdmin::onListEmployeeClicked(wxCommandEvent& evt){
		// "dynamic_cast" need to be used, because the method "toPanel_Admin_ListEmployee()" only exist in MainFrame, not in wxFrame
		MainFrame* pMain_frame_dynamic = dynamic_cast<MainFrame*>(pMain_frame); // Safe casting to derived class
		if (pMain_frame_dynamic) {
			pMain_frame_dynamic->toPanel_Admin_ListEmployee(); // Call the method to switch panels
		}
		else {
			wxMessageBox("Failed to cast MainFrame", "Error", wxOK | wxICON_ERROR);
		}
	}

	/** ***************************************** Disconnect Button *****************************************
	 * @brief : When the button disconnect is press,
	 *	will return to the main page (PanelConnection), after confirmation from the user.
	 *
	 * @param evt :
	 */
	void PanelAdmin::onDisconnectButtonClicked(wxCommandEvent& evt) {
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
} // namespace gui


