/***************************************************************
 * Name:      TestDebug_wxApp.cpp
 * Purpose:   Test and Debug wxWidgets differences between 3.0.4 and 3.1.2
 * Author:    Parduz
 * Created:   2019-11-25
 **************************************************************/

#include "wx/wx.h"
#include <wx/aboutdlg.h>


#include <wx/taskbar.h>

//-----------------------------------------------------------------------------
class TestDebug_wxApp : public wxApp
{
    public:
        virtual bool OnInit();
};
//-----------------------------------------------------------------------------

//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
class MainFrameBaseClass : public wxFrame
{
protected:
    wxMenuBar*      m_MainMenu;
    wxMenu*         m_mFile;
    wxMenuItem*     m_mFile_Exit;

    // TEST MENU ------------------------------------------
	wxMenu*			m_mnuPopUp;
	wxMenuItem*		m_mnuZoomIn;
	wxMenuItem*		m_mnuZoomOut;
	wxMenu*			m_mnuQuality;
	wxMenuItem*		m_mnuPUQuality0;
	wxMenuItem*		m_mnuPUQuality1;
	wxMenuItem*		m_mnuPUQuality2;
	wxMenuItem*		m_mnuPUQuality3;
	wxMenuItem*		m_mnuPUQuality4;

	wxTaskBarIcon*	m_taskBarIcon;
    // TEST MENU ------------------------------------------

    wxMenu*         m_mAbout;

protected:

    virtual void    OnExit                      ();
    virtual void    OnAbout                     ();

    virtual void    OnMenu_mFile_Exit_Sel       (wxCommandEvent& event)     { OnExit();  event.Skip(); }
    virtual void    OnMenu_mAbout_Open          (wxMenuEvent& event)        { OnAbout(); event.Skip(); }

    wxString        strAbout;


    // TEST MENU ------------------------------------------
    virtual void    OnMenuPopUp					(wxCommandEvent& event)			{ event.Skip(); }
    virtual void	OnTaskbarRightDown			(wxTaskBarIconEvent& event)		{ event.Skip(); }
    // TEST MENU ------------------------------------------

public:

	enum {
        wxID_MNUQUALITY0 = 10001,
        wxID_MNUQUALITY1 = 10002,
        wxID_MNUQUALITY2 = 10003,
        wxID_MNUQUALITY3 = 10004,
        wxID_MNUQUALITY4 = 10005,
        wxID_MNUZOOMOUT  = 10006,
        wxID_MNUZOOMIN   = 10007
	};


    wxMenuBar* GetMainMenu() { return m_MainMenu; }
    MainFrameBaseClass(const wxString& title = _("Test_Debug Frame"));
    virtual ~MainFrameBaseClass();
};
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
MainFrameBaseClass::MainFrameBaseClass(const wxString& title):wxFrame(
        0L,
        wxID_ANY,
        title,
        wxDefaultPosition,
        wxSize(400,272),
        wxCAPTION|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLOSE_BOX
)
{
    m_MainMenu = new wxMenuBar(0);
    this->SetMenuBar(m_MainMenu);

    m_mFile = new wxMenu();
    m_MainMenu->Append(m_mFile, _("&File"));

    m_mFile_Exit = new wxMenuItem(m_mFile, wxID_ANY, _("&Exit"), wxT(""));
    m_mFile->Append(m_mFile_Exit);

    // TEST MENU ------------------------------------------
    m_mnuPopUp = new wxMenu();
    m_MainMenu->Append(m_mnuPopUp, _("Options"));

    m_mnuZoomIn = new wxMenuItem(m_mnuPopUp, wxID_MNUZOOMIN, _("Zoom In\tAlt++"), wxT(""), wxITEM_NORMAL);
    m_mnuPopUp->Append(m_mnuZoomIn);

    m_mnuZoomOut = new wxMenuItem(m_mnuPopUp, wxID_MNUZOOMOUT, _("Zoom Out\tAlt+-"), wxT(""), wxITEM_NORMAL);
    m_mnuPopUp->Append(m_mnuZoomOut);

    m_mnuPopUp->AppendSeparator();

    m_mnuQuality = new wxMenu();
    m_mnuPopUp->AppendSubMenu(m_mnuQuality, _("Zoom Quality"));

    m_mnuPUQuality0 = new wxMenuItem(m_mnuQuality, wxID_MNUQUALITY0, _("Faster"), wxT(""), wxITEM_RADIO);
    m_mnuQuality->Append(m_mnuPUQuality0);

    m_mnuPUQuality1 = new wxMenuItem(m_mnuQuality, wxID_MNUQUALITY1, _("Fast"), wxT(""), wxITEM_RADIO);
    m_mnuQuality->Append(m_mnuPUQuality1);

    m_mnuPUQuality2 = new wxMenuItem(m_mnuQuality, wxID_MNUQUALITY2, _("Average"), wxT(""), wxITEM_RADIO);
    m_mnuQuality->Append(m_mnuPUQuality2);

    m_mnuPUQuality3 = new wxMenuItem(m_mnuQuality, wxID_MNUQUALITY3, _("Better"), wxT(""), wxITEM_RADIO);
    m_mnuQuality->Append(m_mnuPUQuality3);

    m_mnuPUQuality4 = new wxMenuItem(m_mnuQuality, wxID_MNUQUALITY4, _("Best"), wxT(""), wxITEM_RADIO);
    m_mnuQuality->Append(m_mnuPUQuality4);
    // TEST MENU ------------------------------------------

    m_mAbout = new wxMenu();
    m_MainMenu->Append(m_mAbout, _("&About"));
    strAbout = _("Test wxTaskBarIcon popup menu behaviour");


    m_taskBarIcon = new wxTaskBarIcon(wxTBI_DEFAULT_TYPE);
    {
        wxIcon icn;
        icn.LoadFile("zoom-32.png");
        //icn.CopyFromBitmap(LoadBitmap("zoom-32.png"));
        m_taskBarIcon->SetIcon(icn, _("TEST - Options"));
    }




    SetName(wxT("MainFrameBaseClass"));
    SetMinClientSize(wxSize(400,272));
    SetSize(400,272);
    if (GetSizer()) {
         GetSizer()->Fit(this);
    }
    CentreOnScreen(wxBOTH);

    // Connect events
    this->Connect(m_mFile_Exit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenu_mFile_Exit_Sel), NULL, this);
    m_mAbout->Connect(wxEVT_MENU_OPEN, wxMenuEventHandler(MainFrameBaseClass::OnMenu_mAbout_Open), NULL, this);


    m_taskBarIcon->Connect(wxEVT_TASKBAR_RIGHT_DOWN, wxTaskBarIconEventHandler(MainFrameBaseClass::OnTaskbarRightDown), NULL, this);
    this->Connect(m_mnuZoomIn->GetId(), 	wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Connect(m_mnuZoomOut->GetId(),	wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Connect(m_mnuPUQuality0->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Connect(m_mnuPUQuality1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Connect(m_mnuPUQuality2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Connect(m_mnuPUQuality3->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Connect(m_mnuPUQuality4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
MainFrameBaseClass::~MainFrameBaseClass()
{
    this->Disconnect(m_mFile_Exit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenu_mFile_Exit_Sel), NULL, this);
    m_mAbout->Disconnect(wxEVT_MENU_OPEN, wxMenuEventHandler(MainFrameBaseClass::OnMenu_mAbout_Open), NULL, this);
    m_taskBarIcon->Disconnect(wxEVT_TASKBAR_RIGHT_DOWN, wxTaskBarIconEventHandler(MainFrameBaseClass::OnTaskbarRightDown), NULL, this);
    this->Disconnect(m_mnuZoomIn->GetId(), 	wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Disconnect(m_mnuZoomOut->GetId(),	wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Disconnect(m_mnuPUQuality0->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Disconnect(m_mnuPUQuality1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Disconnect(m_mnuPUQuality2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Disconnect(m_mnuPUQuality3->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
    this->Disconnect(m_mnuPUQuality4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnMenuPopUp), NULL, this);
}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
void MainFrameBaseClass::OnExit()
{
    Close();
}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
void MainFrameBaseClass::OnAbout()
{
    wxAboutDialogInfo info;
    info.SetCopyright(_("-"));
    info.SetLicence(_("--"));
    info.SetDescription(strAbout);
    ::wxAboutBox(info);
}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°





//#############################################################################
//#############################################################################
//#############################################################################
class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(const wxString& title);
    virtual ~MainFrame();
private:
    // TEST MENU ------------------------------------------
    void    OnMenuPopUp					(wxCommandEvent& event);
    void	OnTaskbarRightDown			(wxTaskBarIconEvent& event);
	wxMenu*	CreateMenuPopUp				();
    // TEST MENU ------------------------------------------
};
//#############################################################################
//#############################################################################
//#############################################################################







// ============================================================================
// ============================================================================
// ============================================================================
IMPLEMENT_APP(TestDebug_wxApp)
// ============================================================================
// implementation
// ============================================================================
bool TestDebug_wxApp::OnInit()
{
    MainFrame* frame = new MainFrame(_("wxWidgets Test PopUp menus"));

    frame->Show();
    return true;
}
// ============================================================================
// ============================================================================
// ============================================================================








//#############################################################################
//#############################################################################
//#############################################################################
MainFrame::~MainFrame()
{
}
//#############################################################################
MainFrame::MainFrame(const wxString& title) : MainFrameBaseClass(title)
{
}
//#############################################################################







    // TEST MENU ------------------------------------------
void MainFrame::OnTaskbarRightDown(wxTaskBarIconEvent& event)
{
	/*
	// tries tu use the already made Popup mend
	if (m_mnuPopUp->IsAttached()) {
		m_mnuPopUp->Detach();
	}
	m_taskBarIcon->PopupMenu(m_mnuPopUp);
	*/
	// tries to create a local menu and use it
	m_taskBarIcon->PopupMenu( CreateMenuPopUp() );
}
wxMenu* MainFrame::CreateMenuPopUp()
{
    wxMenu* mnuPopUp = new wxMenu();

    wxMenu* mnuPUZoom = new wxMenu();
    mnuPUZoom->Append(wxID_MNUZOOMIN, _("Zoom In\tAlt++"), wxT(""));
    mnuPUZoom->Append(wxID_MNUZOOMOUT, _("Zoom Out\tAlt+-"), wxT(""));

    mnuPUZoom->AppendSeparator();

    wxMenu* mnuQuality = new wxMenu();
    mnuQuality->AppendRadioItem(wxID_MNUQUALITY0, _("Faster"), wxT(""));
    mnuQuality->AppendRadioItem(wxID_MNUQUALITY1, _("Fast"), wxT(""));
    mnuQuality->AppendRadioItem(wxID_MNUQUALITY2, _("Average"), wxT(""));
    mnuQuality->AppendRadioItem(wxID_MNUQUALITY3, _("Better"), wxT(""));
    mnuQuality->AppendRadioItem(wxID_MNUQUALITY4, _("Best"), wxT(""));

    mnuPUZoom->AppendSubMenu(mnuQuality, _("Zoom Quality"));
    mnuPopUp->AppendSubMenu(mnuPUZoom, _("Zoom"));


    Connect(wxID_MNUZOOMIN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(OnMenuPopUp), NULL, this);
    Connect(wxID_MNUZOOMOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(OnMenuPopUp), NULL, this);
    Connect(wxID_MNUQUALITY0, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(OnMenuPopUp), NULL, this);
    Connect(wxID_MNUQUALITY1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(OnMenuPopUp), NULL, this);
    Connect(wxID_MNUQUALITY2, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(OnMenuPopUp), NULL, this);
    Connect(wxID_MNUQUALITY3, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(OnMenuPopUp), NULL, this);
    Connect(wxID_MNUQUALITY4, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(OnMenuPopUp), NULL, this);

	return mnuPopUp;
}
    // TEST MENU ------------------------------------------





void MainFrame::OnMenuPopUp(wxCommandEvent& event)
{
	wxMessageBox("PopUp menu!");
}
//#############################################################################
//#############################################################################
