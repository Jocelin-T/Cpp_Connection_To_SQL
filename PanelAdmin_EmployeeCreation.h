/*****************************************************************//**
 * @file   PanelAdmin_EmployeeCreation.h
 * @brief  Panel access by the admin role only,
 *  he can add a new employee to the DB
 *
 * @author ThJo
 * @date   2 May 2024
 *********************************************************************/
#pragma once
#include <wx/wx.h>

//#include "AppGlobals.h"
#include "Panel.h"
//#include "Employee.h"
//#include "SqlQuery.h"

namespace gui{
    class PanelAdmin_EmployeeCreation : public Panel {
    public:
        // Constructor initializes the Panel with the parent window and Main Frame
        PanelAdmin_EmployeeCreation(wxWindow* parent, wxFrame* pMain_frame);

    private:
        // Text Fields
        wxTextCtrl* m_pLast_name;
        wxTextCtrl* m_pFirst_name;
        wxTextCtrl* m_pEmail;
        wxTextCtrl* m_pPassword;

        // Buttons
        wxButton* m_pButton_add;
        wxButton* m_pButton_back;

        // Override the onEnterKeyPressed method
        void onEnterKeyPressed() override;

        /** ####################################### GUI #####################################
         * @brief : GUI for the panel hours management.
         *	"this" make reference to Panel class too
         */
        void InitializeComponents();

        /** ***************************************** Bind Handler *****************************************
         * @brief : Handle all the buttons bind of this panel.
         *
         */
        void BindEventHandlers();

        /** ***************************************** Add Button *****************************************
         * @brief : The button "Create Employee" will display in a message box
         *	the info of the employee created and after confirmation from the user,
         *	insert the employee in the table [Employees]
         *
         * @param evt :
         */
        void onAddButtonClicked(wxCommandEvent& evt);

        /** ***************************************** Back Button *****************************************
         * @brief : When the button disconnect is press,
         *	will return to (PanelAdmin).
         *
         * @param evt :
         */
        void onBackButtonClicked(wxCommandEvent& evt);

        /**
         * @brief : Validate the field of the employee creation.
         *
         * @return  : Boolean, false if any field is empty || true if all field are filled
         */
        bool validateInput();

        /**
         * @brief : Clear all fields of the PanelAdmin_EmployeeCreation.
         *
         */
        void clearFields();

        /** ***************************************** Create Employee *****************************************
        * @brief : Create a new employee inside the DB with the given parameters, all are required.
        *
        * @param emp_last_name : std::string& => employee last name
        * @param emp_first_name : std::string& => employee first name
        * @param emp_email : std::string& => employee email
        * @param emp_password : std::string& => employee password
        * @return  : boolean => true if the creation is a succes
        */
        void createEmployee();

        // Getter
        wxString getLastName();
        wxString getFirstName();
        wxString getEmail();
        wxString getPassword();
    };
} // namespace gui
