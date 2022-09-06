#include <wx/wx.h>
#include <fstream>
#include <iostream>
// #include <regex> // for regex_replace when looking services, easy but adds too much weight to the app for my taste
// #include <iostream>
// #include <string> // For strings
// #include <stdio.h>; // For popen, no
// #include <wx/process.h> // for c++ process use
// #include <wx/utils.h> // For wxExecute
// #include <wx/arrstr.h> // IMPORTANT to use wxCstring for converting wxArrayString to wxString
#include "guifile_postgresql_enabler_stopper.cpp"

// It's necessary to include taskbar.h for "minimize to tray"
// functionality
#include <wx/taskbar.h>

using namespace std;


////////////////////////////////////////////////////////////////////
////// Derived classes that inherits wxFormBuilder ones ////////////
////////////////////////////////////////////////////////////////////

// The main frame inherits the "class" "MyFrame1" 
class main_frame : public MyFrame1
{
public:
    //  The public method for initilizing windows will inherit copy de MyFrame1 method.
    // THIS METHOD MUST BE CALLED WITH THE SAME NAME AS THE CLASS to compile
    // main_frame( wxWindow* parent ): MyFrame1(parent){};
    main_frame( wxWindow* parent );
    // And it's corresponding destructor
    virtual ~main_frame();
 
protected:
    // A function with the same name MUST be specificied (at least with empty brackets) outside this class in order for the code to compile.
    //Otherwise compiler will give an "undefined reference to 'vtable for main_frame'"
    // each function takes parameter it's shortened "handler"
    // e.g wxCommandActivateHandler uses parameter wxCommandActivate& event
    // void OnExit(wxCommandEvent& event);
    // void OnAbout(wxCommandEvent& event);
    virtual void wx_on_activate_actions(wxShowEvent& event);
    virtual void wx_check_status(wxCommandEvent& event);
    virtual void wx_start_sql(wxCommandEvent& event);
    virtual void wx_stop_sql(wxCommandEvent& event);
    virtual void wx_search_service(wxCommandEvent& event);
    virtual void wx_save_custom_service(wxCommandEvent& event);

    // Objects NOT created by wxFormBuilder HERE
    virtual void wx_minimizar( wxIconizeEvent& event );
    wxTaskBarIcon* m_taskBarIcon;
    // I'll use a bitmap for the taskbaricon and not a wxIcon because
    // "wxIcon" won't work well with embedded resources.
    wxBitmap* icn;
    void wx_taskbaricon_lclick (wxTaskBarIconEvent& event);

};

// Next we have to add the NEW elements we want to add to main_frame
// that are not present on MyFrame1
main_frame::main_frame( wxWindow* parent ): MyFrame1(parent)
{
    //////////////// ADING TASKBARICON HERE /////////////
    // quite important to define it here
    // or we won't have any access to it later
    // Also initiliaze appropiate image handler first (always need)
    // BMP plus PNG if defining bitmaps!
    wxImage::AddHandler(new wxBMPHandler);
    wxImage::AddHandler(new wxPNGHandler);
    // wxInitAllImageHandlers(); //This loads all the handlers easily but we need only one in general.

    //Be careful, the following variables are pointers previously defined on the
    // protected section of the class mainframe, that's why we use "new"
    m_taskBarIcon = new wxTaskBarIcon(wxTBI_DEFAULT_TYPE);
    // wxIcon icon( wxICON( wxT(pruebuchi) ) );
    // *icn = icon;
    // Proper portable way to load bitmaps, using the variable name
    // automatically detects if the image commes from a variable
    // or from resource (same with wxIcon but it won't work here)
    // don't get confused with capital letters!
    icn = new wxBitmap(wxBITMAP_PNG(taskbar_icon_resource));
    // If using LoadFile ALSO SPECIFY THE IMAGE TYPE OR IT WON'T LOAD EITHER
    // USE A SMALL SIZE ICON or it will lag when iconizing!
    // icn->LoadFile( "pruebita.png", wxBITMAP_TYPE_PNG );
    m_taskBarIcon->Connect( wxEVT_TASKBAR_LEFT_DCLICK, wxTaskBarIconEventHandler( main_frame::wx_taskbaricon_lclick ), NULL, this );
    /////////////////////////////////////////////////////
}

// We create the proper destructor for connect events

main_frame::~main_frame()
{
    m_taskBarIcon->Disconnect( wxEVT_TASKBAR_LEFT_DCLICK, wxTaskBarIconEventHandler( main_frame::wx_taskbaricon_lclick ), NULL, this );
}

class app_main : public wxApp
{
    public:
        // The public method constructor MUST have the same name AS THE CLASS
        app_main() : wxApp() {};
        ~app_main();
        virtual bool OnInit();
    private:
        // Frames MUST BE DEFINED HERE in the wxApp, and modified after on OnInit
        // otherwise it will not compile (at least as a pointer)
        main_frame *littlewindow;
         // void   OnTaskbarRightDown          (wxTaskBarIconEvent& event);

        // Also i'll define the taskbaricon icon, we'll initialize it
        // later on start.
        // wxTaskBarIcon* m_taskBarIcon;
};

// Implement app goes FIRST, here all frames, dialogs etc are defined!
// FreeConsole();

// DECLARE_APP(app_main);
wxIMPLEMENT_APP(app_main);


//////////////////////////////////////
/// OnInit changes
/////////////////////////////////////

bool app_main::OnInit()
{
    // A pointer to the main_frame was already defined (as littlewindow)
    // but not really initialized.
    // So we'll tune it up in this OnInit method which defines what happens when app starts an initilizes everything.
    // Now the old defined pointer is getting initialized with type and parameters
    // that it needs (the one we'll leave as null for having the defaults)
    // and memory for it is allocated.
    littlewindow = new main_frame{nullptr};

    ////////////////////////////////////////////////////////////
    ////// Setting up the APP's frame ICON//////////////////////
    // It is quite complicated since i could not load a resource directly to
    // a wxIcon, and also wxIcon won't construct from something that is not
    // a .ico file, so we load a bitmap_png an assign it to an icon after
    wxImage::AddHandler(new wxBMPHandler);
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap app_icon_bitmap_resource(wxBITMAP_PNG(taskbar_icon_resource));
    wxIcon app_icon;
    app_icon.CopyFromBitmap(app_icon_bitmap_resource);
    littlewindow->SetIcon(app_icon);
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    //// Setting up adequate SIZE ////////////////////////////////////////
    // First we extract the current display size with wxWidgets functions

    static int width;
    static int height;
    wxDisplaySize(&width, &height);
    cout << width << "\n";
    cout << height;

    // Now we'll change this object size and position with wxWidgets methods
    littlewindow->SetClientSize(littlewindow->FromDIP(wxSize(width/6,height/5)));
    // littlewindow->SetSize( wxSize(width/3.1,height/2.2) );
    // For SetPosition wxPoint
    //width bigger denominator--> more left
    //height bigger denominator--> more up
    littlewindow->SetPosition( wxPoint(width/3.2, height/3.2) );
    // As the last step we make it show itself
    littlewindow->Show(true);

    // littlewindow->width_exp();
    ///////////////////////////////////////////////////////////////////////

    return true;
}

app_main::~app_main()
{
    delete littlewindow;
}

//////////////////////////////////////////////////////////////
////// External Functions for GUI elements //////////////////
/////////////////////////////////////////////////////////////


string read_service_file()
{
    static fstream service_name_file;
    service_name_file.open("service_name_file.ini", ios::in);
    if (service_name_file.is_open()) //is_open es un método de fstream que justamente si está abierto y devuelve booleano true o false.
    {
        string service_to_write;
        getline( service_name_file, service_to_write);
        service_name_file.close();
        return service_to_write;
    }
    // Very important to close it to avoid problems!
    return "no_service_on_ini_file";
}

fstream * open_service_file()
// Returning a pointer because cannot return easily the whole fstream
// but an fstream pointer is easy enough to manipulate.
{
    // The fstream NEEDS to be static, if not we'll save the pointer
    // in memory but the stream itself is deleted after running the function!
    static fstream service_name_file;
    // We open the file with flags "out" (write mode) and "trunc" (discards
    // the content of stream when opening)
    service_name_file.open("service_name_file.ini", ios::out | ios::trunc);
    // service_name_file.clear();
    fstream * service_name_file_pointer = & service_name_file;
    // service_name_file << "HOLA";
    return service_name_file_pointer;
}

string write_service_file( fstream * service_name_file  , string input_service )
{
    if (service_name_file->is_open()) //is_open es un método de fstream que justamente si está abierto y devuelve booleano true o false.
    {
        *service_name_file << input_service;
        // Close fstream or it won't be written and causes many headaches
        service_name_file->close();
        return input_service;
    }
    return "fail";
}

string extract_console_status_text ()
{
    // We define a wxArrayString which is an array of wxString basically
    // or pure string class IF ADDED (must initialize string first)
    wxArrayString status_text_wxas;

    // Then we read de ini file in order to know the know of the service
    // and we save the command to execute into a string
    string saved_service = read_service_file();
    string command_to_check_status = "cmd /c sc query " + saved_service + " | find /i  \"STATE\"";

    // wxExecute SYNTAX
    // wxExecute ( string_literal_cmd_command , console_output_as_wxArrayString, Execute_flags)
    // wxExecute likes wchar_t better so put an L before the quotes.
    // also it doesn't the commands sometimes but get's solved by opening
    // another instance with cmd /c
    wxExecute(command_to_check_status, status_text_wxas, wxEXEC_HIDE_CONSOLE | wxEXEC_SYNC);
    // wxExecute(L"cmd /c sc query postgresql-x64-14 | find /i  \"STATE\"", status_text_wxas, wxEXEC_HIDE_CONSOLE | wxEXEC_SYNC);
    // Powershell alternative
    // wxExecute(L"powershell get-service postgresql-x64-14 | select Status", status_text_wxas, wxEXEC_HIDE_CONSOLE | wxEXEC_SYNC);

    // We first get the number of array elements with a wxArrayString method
    int num = status_text_wxas.GetCount();
    // We define a normal string
    string status_text_str = "                       "; // 6 tabs
    // The we iterate through all items of the array, we want all the lines
    for (int i=0 ; i<num; i++)
    {
        // Method .Item(int) gets element of the array
        // cout << status_text_wxas.Item(i) + " ";
        status_text_str += status_text_wxas.Item(i);
        status_text_str += " ";
    }

    // We'll replace the str if no service was found with an if
    if (status_text_str != "                       ")
    // That extreme whitespace is what it ouputs if no service is found
    {} // do nothing
    else
    {
        status_text_str = "No service found with the name specified on ini file";
    }

    return status_text_str;
}

string search_service()
{
    wxArrayString service_name_wxas;
    // If cmd does not work we can add cmd /c
    wxExecute(L"cmd /c for /f \"tokens=2\" %s in ('sc query state^= all ^| find \"SERVICE_NAME: postgre\"') do @echo %s" , service_name_wxas, wxEXEC_HIDE_CONSOLE | wxEXEC_SYNC);
    // Powershell alternative
    // wxExecute(L"powershell Get-Service -Name \"postgre*\" | Select Name | Format-Wide" , service_name_wxas, wxEXEC_HIDE_CONSOLE | wxEXEC_SYNC);
    string service_name_str;
    // Ading the wxString to the string now
    service_name_str += service_name_wxas.Item(0);
    return service_name_str;
}

void start_sql()
{
    string service_to_run = read_service_file();
    string command_to_run = "sc start \"";
    command_to_run += service_to_run;
    command_to_run += "\"";
    // "sc start \"postgresql-x64-14\""
    wxExecute(command_to_run , wxEXEC_HIDE_CONSOLE | wxEXEC_SYNC);
}

void stop_sql()
{
    string service_to_stop = read_service_file();
    string command_to_run = "sc stop \"";
    command_to_run += service_to_stop;
    command_to_run += "\"";
    // "sc stop \"postgresql-x64-14\""
    wxExecute(command_to_run, wxEXEC_HIDE_CONSOLE | wxEXEC_SYNC);
}


//////////////////////////////////////////////////////////////
///////// Connect and Bind Events for GUI elements
/////////////////////////////////////////////////////////////

void main_frame::wx_taskbaricon_lclick( wxTaskBarIconEvent& event)
{
    this->Show(true);
    this->Maximize(false); //bool parameter=false restores the
    // window size instead of maximizing it to screen size.
    m_taskBarIcon->RemoveIcon();
}


void main_frame::wx_on_activate_actions( wxShowEvent& event)
{
    string string_to_write = read_service_file( );
    cout <<  string_to_write;
    cout << "activate PRUEBA";
    m_textCtrl3->SetValue(string_to_write);
    // m_taskBarIcon->RemoveIcon();
}

void main_frame::wx_minimizar(wxIconizeEvent& event)
{
    // cout << "PUTAZOS";
    this->Show(false);
    m_taskBarIcon->SetIcon(*icn, _("PostgreSQL Server Enabler"));
}

void main_frame::wx_check_status( wxCommandEvent& event )
{
    string saved_service_on_ini = read_service_file();
    string status_text_str = extract_console_status_text ();
    m_textCtrl3->SetValue(saved_service_on_ini);
    m_textCtrl1->SetValue(status_text_str);
}

void main_frame::wx_start_sql ( wxCommandEvent& event )
{
    start_sql();
    string status_text_str = extract_console_status_text ();
    m_textCtrl1->SetValue(status_text_str);
}

void main_frame::wx_stop_sql ( wxCommandEvent& event )
{
    stop_sql();
    string status_text_str = extract_console_status_text ();
    m_textCtrl1->SetValue(status_text_str);
}

void main_frame::wx_search_service ( wxCommandEvent& event )
{
    string service_name =  write_service_file( open_service_file() , search_service() );
    m_textCtrl3->SetValue(service_name);
}

void main_frame::wx_save_custom_service(wxCommandEvent& event)
{
    string string_to_save;
    string_to_save += m_textCtrl3->GetValue();
    write_service_file( open_service_file() , string_to_save );
}




