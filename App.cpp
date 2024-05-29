///*****************************************************************//**
// * @file   App.cpp
// * @brief  GUI part of the application
// * 
// * @author ThJo
// * @date   29 April 2024
// *********************************************************************/
// /* ####################################### Import #######################################
// */
//#include <wx/wx.h>
//
// // Class (header)
//#include "App.h"
//#include "MainFrame.h"
//#include "SQL_Management.h"
//#include "QOLandDebug.h"
//
//wxIMPLEMENT_APP(App); // Needed for wxWidget (start the program)
//
///* ####################################### Class App #######################################
//*	This class is the entry point of the program (like main)
//*	OnInit() function is override and application will start here
//*/
//bool App::OnInit() {
//
//	MainFrame* pMainFrame = new MainFrame("Gestionnaire d'heure");
//	pMainFrame->SetClientSize(800, 600);
//	pMainFrame->Center();
//	pMainFrame->Show();
//
//	//Object for the connection to the DB
//	SQL_Management sql_connection;
//
//	//// Object for the console format management and debug
//	//QOLandDebug console;
//
//	try {
//		sql_connection.connectToDB();
//	}
//	catch (const std::exception& e) {
//		wxMessageBox("Failed to connect to the database: " + wxString(e.what()), "Database Error", wxOK | wxICON_ERROR);
//		return false;
//	}
//
//	return true;
//}
