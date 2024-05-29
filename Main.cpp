/*****************************************************************//**
 * @file   Main.cpp
 * @brief  Une PME aimerait avoir une application de gestion de son personnel. Vous devez
 *	développer une application qui gère les horaires des différents employés et qui
 *	permettra de calculer le salaire en fonction des horaires mensuelles effectués.
 *	L’analyse des besoins de la PME est décrite comme suit :
 *	• Chaque employé pourra se logger sur l’application avec un employee_email et un mot
 *	de passe afin d’y entrer une heure d’arrivée et son heure de départ (on ne
 *	tiendra pas compte des pauses).
 *	• Dépendamment du nombre d’heures effectuées, l’application pourra calculer
 *	et affichez le nombre d’heures effectué par jour, par semaine et par mois.
 *	• L’application pourra calculer et afficher le salaire brut de chaque employé par
 *	mois sachant qu’une heure de travail est fixée à 38 CHF
 *	• Il sera possible en fin d’année d’avoir la liste de tous les salaires annuels des
 *	employés
 *	Modélisez et concevez une base de données à accès restreinte pour
 *	répondre à la problématique de cette PME, puis développer une application
 *	que vous connecterez à votre base de données.
 * 
 * @author ThJo
 * @date   22 April 2024
 *********************************************************************/
#include "App.h"

/* ####################################### Main (App) #######################################
*	This class is the entry point of the program (like main)
*	OnInit() function is override and application will start here
*/
wxIMPLEMENT_APP(App); // Needed for wxWidget (start the program)
bool App::OnInit() {
	// Creation of the main frame
	gui::MainFrame* pMain_frame = new gui::MainFrame("Gestionnaire d'heure");
	pMain_frame->SetClientSize(800, 600);
	pMain_frame->SetMinClientSize(wxSize(800, 600));
	pMain_frame->Center();
	pMain_frame->Show();


	return true;
}













// ####################################### Main (Console) #######################################
//int main(){
//	system("cls");
//	 //Object for the connection to the DB
//	SQL_Management sql_connection;
//
//	// Object for the console format management and debug
//	QOLandDebug console;
//
//	sql_connection.connectToDB();
//	//sql_connection.dropAllTables(); // DEBUG
//	//sql_connection.createAllTables(); // DEBUG
//	//sql_connection.showAllTables();
//	//sql_connection.createEmployee();
//	//sql_connection.userSelectTableToShow();
//
//
//	system("pause");
//	return 0;
//}
