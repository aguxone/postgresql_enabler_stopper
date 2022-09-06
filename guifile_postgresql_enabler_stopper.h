///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxButton* m_button4;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrl3;
		wxButton* m_button5;
		wxButton* m_button3;
		wxButton* m_button1;
		wxButton* m_button2;
		wxTextCtrl* m_textCtrl1;

		// Virtual event handlers, override them in your derived class
		virtual void wx_minimizar( wxIconizeEvent& event ) { event.Skip(); }
		virtual void wx_on_activate_actions( wxShowEvent& event ) { event.Skip(); }
		virtual void wx_search_service( wxCommandEvent& event ) { event.Skip(); }
		virtual void wx_save_custom_service( wxCommandEvent& event ) { event.Skip(); }
		virtual void wx_check_status( wxCommandEvent& event ) { event.Skip(); }
		virtual void wx_start_sql( wxCommandEvent& event ) { event.Skip(); }
		virtual void wx_stop_sql( wxCommandEvent& event ) { event.Skip(); }


	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PostgreSQL server Enabler/Stopper"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1293,648 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame1();

};

