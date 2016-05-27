#include <bits/stdc++.h>
#include <wx/string.h>
#include <wx/utils.h>
#include <wx/wx.h>
using namespace std;
class Simple : public wxFrame {
public:
    Simple(const wxString &title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(0, 0),
                  wxFULL_REPAINT_ON_RESIZE) {
        Centre();
    }
};
class wxImagePanel : public wxPanel {
    wxBitmap image;
    int x_start, y_start, x_end, y_end;

public:
    wxImagePanel(wxFrame *parent, wxString file, wxBitmapType format) : wxPanel(parent) {
        image.LoadFile(file, format);
        cout << "There" << endl;
    };

    void paintEvent(wxPaintEvent &evt) {
        wxPaintDC dc(this);
        render(dc);
    };
    void paintNow() {
        wxClientDC dc(this);
        render(dc);
    };
    void mouseEvents(wxMouseEvent &event) {
        const wxPoint pt = wxGetMousePosition();
        cout << pt.x << " " << pt.y << endl;
    };
    void mouseUp(wxMouseEvent &event) {
        const wxPoint pt = wxGetMousePosition();
        x_end = pt.x;
        y_end = pt.y;
        const wxRect &rect = wxRect(wxPoint(x_start, y_start), wxPoint(x_end, y_end));
        extern wxImagePanel *drawPane;
        const wxBitmap output = (drawPane->image).GetSubBitmap(rect);
        assert(output.SaveFile(wxT("/tmp/tmp3.png"), wxBITMAP_TYPE_PNG));
        cout << "Rectangle formed" << endl;
    };
    void mouseDown(wxMouseEvent &event) {
        const wxPoint pt = wxGetMousePosition();
        x_start = pt.x;
        y_start = pt.y;
    };
    void render(wxDC &dc) { dc.DrawBitmap(image, 0, 0, false); };
    DECLARE_EVENT_TABLE()
};
wxImagePanel *drawPane;

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
EVT_LEFT_DOWN(wxImagePanel::mouseDown)
EVT_LEFT_UP(wxImagePanel::mouseUp)
EVT_MIDDLE_DOWN(wxImagePanel::mouseEvents)
EVT_RIGHT_DOWN(wxImagePanel::mouseEvents)
// EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
// EVT_MOUSE_EVENTS(wxImagePanel::mouseEvents)
EVT_PAINT(wxImagePanel::paintEvent)
END_EVENT_TABLE()

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        wxInitAllImageHandlers();
        Simple *simple = new Simple(wxT("Simple"));
        wxShell(wxT("scrot /tmp/tmp2.png"));
        drawPane = new wxImagePanel(simple, wxT("/tmp/tmp2.png"), wxBITMAP_TYPE_PNG);
        simple->Show(true);
        simple->ShowFullScreen(true);
        return true;
    };
};

IMPLEMENT_APP(MyApp)
