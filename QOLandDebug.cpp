/*****************************************************************//**
 * @file   QOLandDebug.cpp
 * @brief  This class will have all "quality of life" and debug methods
 * 
 * @author ThJo
 * @date   26 April 2024
 *********************************************************************/
 // ####################################### Import #######################################
#include <iostream>
#include <stdlib.h> // required for system()

// Class (header)
#include "QOLandDebug.h"
#include "MainFrame.h"



/* ####################################### Pause and Clear #######################################
*	Function for readability in the console.
*	Make a pause then clear the console for the next part
*/
void QOLandDebug::pauseAndClear() {
	std::cout << "\n";
	system("pause");
	system("cls");
}