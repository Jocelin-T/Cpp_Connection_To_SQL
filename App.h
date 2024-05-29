/*****************************************************************//**
 * @file   App.h
 * @brief  GUI part of the application
 * 
 * @author ThJo
 * @date   29 April 2024
 *********************************************************************/
#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>
#include <wx/wx.h>

// Class
#include "AppGlobals.h"
#include "MainFrame.h"
//#include "SqlQuery.h" // For App use

 /* ####################################### Class App (Header) #######################################
 *	This class is the entry point of the program (like main)
 *	@param :
 */
class App : public wxApp {

public:
	bool OnInit();
};

