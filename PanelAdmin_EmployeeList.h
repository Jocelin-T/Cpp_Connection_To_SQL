/*****************************************************************//**
 * @file   PanelAdminEmployeeList.h
 * @brief  This panel will let's the admin select a employee and 
 *	display his hours per day, week, month and make is montly salary
 * 
 * @author ThJo
 * @date   8 May 2024
 *********************************************************************/
#pragma once

#include "Panel.h"

// Forward declaration
namespace bll {
    class Salary;
}

namespace gui {
    class PanelAdminEmployeeList : public Panel {
    public:
        // Constructor
        PanelAdminEmployeeList(wxWindow* pParent, wxFrame* pMain_frame);

    private:
        // Drop down list (wxChoice)
        wxChoice* m_pEmployee_choice;

        // Radio Box
        wxArrayString m_hours_choices; // Array of Choices
        wxRadioBox* m_pRadio_choices; // Radio of Choices

        // Panel display employee hours
        wxPanel* m_pPanel_hours;
        wxPanel* m_pCurrent_panel;
        wxBoxSizer* m_pHours_sizer;

        // Date selection
        wxTextCtrl* m_pDate;

        // Buttons
        wxButton* m_pButton_back;
        wxButton* m_pButton_submit;

        /** ***************************************** Date validation [override] *****************************************
        * @brief : Override the method from the base Class, for ignoring the wxMessageBox.
        *
        * @param date : std::string& => date
        * @return  : boolean
        */
        bool isValidDate(const std::string& date) override;

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

        /** ***************************************** Back Button *****************************************
         * @brief : When the button disconnect is press,
         *	will return to (PanelAdmin).
         *
         * @param evt :
         */
        void onBackButtonClicked(wxCommandEvent& evt);

        /** ***************************************** Send request *****************************************
         * @brief : Send a request on any change of employee selected, date, period.
         * 
         * @param evt :
         */
        void onSubmitButtonClicked(wxCommandEvent& evt);
        void onEmployeeChoiceChanged(wxCommandEvent& evt);
        void onHoursSelectionChanged(wxCommandEvent& evt);
        void onDateChanged(wxCommandEvent& evt);

        /** ***************************************** Populate list with Employees *****************************************
        * @brief : Will populate the drop down list (wxChoice) with the employee in the DB.
        *	Ignore the employee Admin
        *
        */
        void PopulateEmployees();

        /** ***************************************** Panel hours *****************************************
         * @brief : Update the displayed panel of the informations from the selected employee.
         *
         */
        void UpdatePanelHours();

    public:
        // Getter
        int getRadioBoxId();
        int getChoiceEmployeeId();
        wxString getDate();
    };
} // namespace gui