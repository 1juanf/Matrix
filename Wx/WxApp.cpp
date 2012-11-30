/*!
	@file		WxApp.cpp

	@brief		A skeleton code for defining the top-level GUI application.
				To use in your project:
				1)	Find and Replace "" with "YourProject",
				2)	Find and Replace "MATRIX_TEST_" with "YOUR_PROJECT_",
				3)	See details in Events.h, MainFrame.h/cpp, Core.h/cpp
					and QWxEvent.h

	@author		Tom Allen
	@date		06-02-2007
*/

// For compilers that supports precompilation , includes “wx/wx.h”
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif
#include "wx/msgdlg.h"
#include <cctype>
#include <string>

// ===========================================================================================
// Memory debugging (need Visual Leak Detector installed. See QDocs/QDeveloperGuidelines.pdf.
//#include <vld.h>
// ===========================================================================================

//  Wx includes
#include "WxApp.h"
#include "../Wx/MatrixPanel.h"
#include <windows.h>

IMPLEMENT_APP( WxApp )

bool WxApp::OnInit()
{
	// Get the size of the display area
	wxRect dispRect = ::wxGetClientDisplayRect();

	bool displaySettings = false, previewMode = false;
	if( argc > 1 )
	{
		std::ostringstream str;
		str << argv[1];
		std::string argString = str.str().substr(0,2);
		for( std::size_t i=0; i<argString.size(); ++i )
		{
			argString[i] = tolower(argString[i]);
		}
		if( argString == "/c" )
		{
			displaySettings = true;
		}
		else if(argString == "/p" )
		{
			previewMode = true;
		}
		else
		{
			previewMode = false;
			displaySettings = false;
		}
	}

	// Make the main frame based on this size (ie: a maximised window)
	wxFrame * parent = new wxFrame( (wxFrame*)NULL, -1, "The Matrix", wxPoint(dispRect.x, dispRect.y), wxSize(dispRect.width, dispRect.height), wxDEFAULT_FRAME_STYLE | wxFRAME_NO_TASKBAR | wxFRAME_TOOL_WINDOW );
	MatrixPanel * mainFrame = new MatrixPanel( parent, wxPoint(dispRect.x, dispRect.y), wxSize(dispRect.width, dispRect.height) );
	SetTopWindow( parent ); // Tell wxWidgets it is the Top Level Window.

	if( displaySettings == false && previewMode == false )
	{
		parent->ShowFullScreen( true, wxFULLSCREEN_ALL ); // Show it fullscreen.
	}
	else if( displaySettings == true )
	{
		wxMessageDialog dlg( parent, wxT("Matrix Screensaver, by Tom Allen"), wxT("What is the Matrix?"), wxOK|wxICON_INFORMATION, wxDefaultPosition );
		if( dlg.ShowModal() == wxID_OK )
		{
			parent->Close();
			return false;
		}
	}
	else if( previewMode == true )
	{
		parent->Close();
		return false;
	}
	return true;
}

int WxApp::OnExit()
{
	return 0;
}

