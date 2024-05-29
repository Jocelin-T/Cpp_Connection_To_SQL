/*****************************************************************//**
 * @file   Main.cpp
 * @brief  Une PME aimerait avoir une application de gestion de son personnel. Vous devez
 *	d�velopper une application qui g�re les horaires des diff�rents employ�s et qui
 *	permettra de calculer le salaire en fonction des horaires mensuelles effectu�s.
 *	L�analyse des besoins de la PME est d�crite comme suit :
 *	� Chaque employ� pourra se logger sur l�application avec un employee_email et un mot
 *	de passe afin d�y entrer une heure d�arriv�e et son heure de d�part (on ne
 *	tiendra pas compte des pauses).
 *	� D�pendamment du nombre d�heures effectu�es, l�application pourra calculer
 *	et affichez le nombre d�heures effectu� par jour, par semaine et par mois.
 *	� L�application pourra calculer et afficher le salaire brut de chaque employ� par
 *	mois sachant qu�une heure de travail est fix�e � 38 CHF
 *	� Il sera possible en fin d�ann�e d�avoir la liste de tous les salaires annuels des
 *	employ�s
 *	Mod�lisez et concevez une base de donn�es � acc�s restreinte pour
 *	r�pondre � la probl�matique de cette PME, puis d�velopper une application
 *	que vous connecterez � votre base de donn�es.
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
