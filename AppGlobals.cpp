/*****************************************************************//**
 * @file   AppGlobals.cpp
 * @brief  Global Variables for the Application
 *
 * @author ThJo
 * @date   3 May 2024
 *********************************************************************/
/* ####################################### INFOS ####################################### 
* **************************************** delete on wxWidget control *****************************************
* wxWidget manage the destruction of all is control(frames, panels, buttons, text, ...)
* that why there is no need to use the "delete" method on the "new" control 
* ("new" operator: allocate memory from the heap, who is dynamic memory)
* 
* **************************************** Out of Scope explication *****************************************
* Local Scope: When an object is defined within a block of code (like inside a function or a loop),
* it goes out of scope once the execution leaves that block. For example:
void function() {
    int localVariable = 10;  // localVariable comes into scope
    // localVariable is accessible here
}  // localVariable goes out of scope and is destroyed here
* """"""""""""""""""""""""""""""""""

Nested Scope: When you have nested blocks, each block can have its own scope. 
Variables defined in an inner block are destroyed once the block is exited:
void function() {
    {
        int innerVariable = 5; // Starts scope
        // Code that uses innerVariable
    }  // innerVariable goes out of scope and is destroyed here
    // Cannot use innerVariable here, it's out of scope
}
* """"""""""""""""""""""""""""""""""

Control Structures: Within control structures like loops or conditionals, 
if you define an object, it will go out of scope when the control structure block ends, 
unless the scope of the object is outside the control structure:
for (int i = 0; i < 10; ++i) {
    int loopVariable = i;  // loopVariable is created and destroyed with each iteration
}
* """"""""""""""""""""""""""""""""""

Static Local Variables: Unlike regular local variables, 
static local variables do not go out of scope when the function exits; 
they are only destroyed when the program ends. 
They persist in memory across multiple calls to the function:
void function() {
    static int staticVar = 10;  // Only initialized once, and persists between calls
    // staticVar does not go out of scope here
}  // function ends but staticVar is not destroyed
* """"""""""""""""""""""""""""""""""

Class Members: If an object is an instance of a class, 
its lifespan is tied to the lifespan of the containing object.
When the parent object is destroyed, all its member objects go out of scope and are destroyed:
class Example {
    int memberVariable;  // Scope is tied to the lifetime of an Example object instance
};

void function() {
    Example obj;  // obj is created
    // obj.memberVariable is accessible
}  // obj goes out of scope and obj.memberVariable is destroyed
* """"""""""""""""""""""""""""""""""

Dynamically Allocated Memory: Objects allocated with new do not go out of scope in the same way; 
they persist until delete is explicitly called on them. 
These objects live in heap memory and their scope is manually managed:

Example* dynamicObj = new Example();  // dynamicObj itself is a pointer and has its scope, 
                                      // but the object it points to must be manually managed
delete dynamicObj;  // The dynamically allocated Example object is destroyed
*
* In case a object goes out of scope, using delete or a destructor is required for avoid memory leak!
* 
* ****************************************  *****************************************
*
* 
*/


#include "AppGlobals.h"

// Initialize global font
wxFont global_title_font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
const std::string ADMIN_EMAIL{ "adm" };

