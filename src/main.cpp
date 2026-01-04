#include "fileHandling.h"

#include <iostream>
#include <filesystem>
#include <wx/wx.h>

class osmp : public wxApp{
public:
	bool OnInit() override;
};



class MyFrame : public wxFrame {
	public:
		MyFrame();
	
	private:
		void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
};

bool osmp::OnInit() {
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}

enum {
	ID_Hello = 1
};


// 
MyFrame::MyFrame()
	: wxFrame(nullptr, wxID_ANY, "OSMP Application") {
		wxMenu *menuFile = new wxMenu;
		menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
			"Help string shown in status bar for this menu item");
		
			menuFile->AppendSeparator();
		menuFile->Append(wxID_EXIT);

		wxMenu *menuHelp = new wxMenu;
		menuHelp->Append(wxID_ABOUT);
		
		wxMenuBar *menuBar = new wxMenuBar;
		menuBar ->Append(menuFile, "&File");
		menuBar ->Append(menuHelp, "&Help");

		SetMenuBar(menuBar);

		CreateStatusBar();
		SetStatusText("OSMP");


		//Bind events
		Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
		Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
		}


void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a OSMP. An open source music player, designed to run cross platform.",
                "About OSMP", wxOK | wxICON_INFORMATION);
}

// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(osmp);