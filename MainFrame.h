/*****************************************************************//**
 * @file   MainFrame.h
 * @brief  Create the Main Frame and manage the panel when changing page
 *
 * @author ThJo
 * @date   29 April 2024
 *********************************************************************/
#pragma once
#include <wx/wx.h>

#include "Employee.h"

class Employee;
class Panel;
class PanelConnection;
class PanelEmployee_Hours;
class PanelAdmin;
class PanelAdmin_EmployeeCreation;
class PanelAdmin_EmployeeUpdate;
class PanelAdmin_EmployeeList;

namespace gui {
    class MainFrame : public wxFrame{
    public:
        /** ####################################### Class Main Frame #####################################
         * @brief : Class who gonna be the Main Frame(Window).
         *
         * @param title : wxString, Title of the Frame(Window)
         */
        MainFrame(const wxString& title);

        /** ***************************************** Switch Panel *****************************************
         * @brief : Destroy the current panel if there is one and
         *	create the new one.
         *
         * @param newPanel : wxPanel*, the panel to create inside the frame
         */
        void SwitchPanel(wxPanel* newPanel);

        /**  ***************************************** Switch to (PanelEmployee_Hours) *****************************************
         * @brief : Will change the panel to (PanelEmployee_Hours).
         *
         * @param employee_details : Employee, with the full details (employee_ID, employee_last_name, employee_first_name, employee_email)
         */
        void toPanel_Employee_Hours(Employee& employee_details);

        /**  ***************************************** Switch to (PanelConnection) *****************************************
         * @brief : Will change the panel to (PanelConnection).
         *
         */
        void toPanel_Connection();

        /** ***************************************** Switch to (PanelAdmin) *****************************************
         * @brief : Will change the panel to (PanelAdmin).
         *
         */
        void toPanel_Admin();

        /** ***************************************** Switch to (PanelAdmin_EmployeeCreation) *****************************************
         * @brief : Will change the panel to (PanelAdmin_EmployeeCreation).
         *
         */
        void toPanel_Admin_AddEmployee();

        /** ***************************************** Switch to (PanelAdmin_EmployeeUpdate) *****************************************
         * @brief : Will change the panel to (PanelAdmin_EmployeeUpdate).
         *
         */
        void toPanel_Admin_UpdateEmployee();

        /** ***************************************** Switch to (PanelAdminEmployeeList) *****************************************
         * @brief : Will change the panel to (PanelAdminEmployeeList).
         *
         */
        void toPanel_Admin_ListEmployee();


    private:
        wxPanel* m_pCurrent_panel;  // Pointer to keep track of the current panel
        Employee employee_details; // Current logged-in user
    };
} // namespace gui
