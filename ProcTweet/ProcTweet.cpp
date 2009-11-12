// ProcTweet.cpp : main project file.

#include "stdafx.h"
#include "MainWin.h"

using namespace ProcTweet;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
        // Enabling Windows XP visual effects before any controls are created
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false); 

        // Create the main window and run it
        Application::Run(gcnew MainWin());
        return 0;
}

