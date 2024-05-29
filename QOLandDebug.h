/*****************************************************************//**
 * @file   QOLandDebug.h
 * @brief  This class will have all "quality of life" and debug methods
 * 
 * @author ThJo
 * @date   26 April 2024
 *********************************************************************/
 // ####################################### Import #######################################
#pragma once
#include <iostream>
#include <stdlib.h> // required for system()

class QOLandDebug {
public:
	// Constructor
	QOLandDebug() = default;

	/* ####################################### Pause and Clear #######################################
	*	Method for readability in the console.
	*	Make a pause then clear the console for the next part
	*/
	void pauseAndClear();
};

