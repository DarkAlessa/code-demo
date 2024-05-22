#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString&, const wxPoint&, const wxSize&);
};

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("BoxSizer and Panel", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxPanel *panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel_top->SetBackgroundColour(wxColor(100, 100, 200));
    [[maybe_unused]] wxButton* bt_a = new wxButton(panel_top, wxID_ANY, "LISA", wxPoint(10, 10), wxDefaultSize, wxBORDER_NONE);

    wxPanel *panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel_bottom->SetBackgroundColour(wxColor(100, 200, 100));
    [[maybe_unused]] wxButton* bt_b = new wxButton(panel_bottom, wxID_ANY, "ELSA", wxPoint(10, 10), wxDefaultSize, wxBORDER_NONE);

    wxPanel *panel_center = new wxPanel(panel_bottom, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel_center->SetBackgroundColour(wxColor(200, 200, 100));
    [[maybe_unused]] wxButton* bt_c = new wxButton(panel_center, wxID_ANY, "OK", wxPoint(10, 10), wxDefaultSize, wxBORDER_NONE);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->SetMinSize(wxSize(640, 480));
    sizer->Add(panel_top, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    sizer->Add(panel_bottom, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer *sizer_bottom    = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *sizer_centering = new wxBoxSizer(wxHORIZONTAL);
    sizer_centering->Add(panel_center, 0, wxALIGN_CENTER);
    sizer_bottom->Add(sizer_centering, 1, wxALIGN_CENTER);

    panel_bottom->SetSizerAndFit(sizer_bottom);

    this->SetSizerAndFit(sizer);
}