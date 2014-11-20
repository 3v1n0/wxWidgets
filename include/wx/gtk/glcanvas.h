/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/glcanvas.h
// Purpose:     wxGLCanvas, for using OpenGL/Mesa with wxWidgets and GTK
// Author:      Robert Roebling
// Modified by:
// Created:     17/8/98
// Copyright:   (c) Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GLCANVAS_H_
#define _WX_GLCANVAS_H_

#include <gtk/gtk.h>

#if !GTK_CHECK_VERSION(3,15,0)

#include "wx/unix/glx11.h"

//---------------------------------------------------------------------------
// wxGLCanvas
//---------------------------------------------------------------------------

class WXDLLIMPEXP_GL wxGLCanvas : public wxGLCanvasX11
{
public:
    wxGLCanvas(wxWindow *parent,
               wxWindowID id = wxID_ANY,
               const int *attribList = NULL,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const wxPalette& palette = wxNullPalette);

    bool Create(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxGLCanvasName,
                const int *attribList = NULL,
                const wxPalette& palette = wxNullPalette);

    virtual bool SetBackgroundStyle(wxBackgroundStyle style) wxOVERRIDE;

    // implement wxGLCanvasX11 methods
    // --------------------------------

    virtual Window GetXWindow() const wxOVERRIDE;


    // deprecated methods
    // ------------------

#if WXWIN_COMPATIBILITY_2_8
    wxDEPRECATED(
    wxGLCanvas(wxWindow *parent,
               wxWindowID id = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const int *attribList = NULL,
               const wxPalette& palette = wxNullPalette)
    );

    wxDEPRECATED(
    wxGLCanvas(wxWindow *parent,
               const wxGLContext *shared,
               wxWindowID id = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const int *attribList = NULL,
               const wxPalette& palette = wxNullPalette)
    );

    wxDEPRECATED(
    wxGLCanvas(wxWindow *parent,
               const wxGLCanvas *shared,
               wxWindowID id = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const int *attribList = NULL,
               const wxPalette& palette = wxNullPalette)
    );

    // called from "realized" callback to create the implicit context if needed
    void GTKInitImplicitContext();
#endif // WXWIN_COMPATIBILITY_2_8

    // implementation from now on
    void OnInternalIdle() wxOVERRIDE;

    bool              m_exposed;
#ifdef __WXGTK3__
    cairo_t* m_cairoPaintContext;
#endif

#if WXWIN_COMPATIBILITY_2_8
    wxGLContext      *m_sharedContext;
    wxGLCanvas       *m_sharedContextOf;
    const bool        m_createImplicitContext;
#endif // WXWIN_COMPATIBILITY_2_8

private:
    DECLARE_CLASS(wxGLCanvas)
};

#else // if GTK_CHECK_VERSION(3,16,0)

#include <GL/gl.h>

class WXDLLIMPEXP_GL wxGLContext : public wxGLContextBase
{
public:
    wxGLContext(wxGLCanvas *win, const wxGLContext* other = NULL);

    virtual bool SetCurrent(const wxGLCanvas& win) const wxOVERRIDE;

private:
    GdkGLContext *m_glContext;

    DECLARE_CLASS(wxGLContext)
};

// ----------------------------------------------------------------------------
// wxGLCanvas: OpenGL output window
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_GL wxGLCanvas : public wxGLCanvasBase
{
public:
    wxGLCanvas(wxWindow *parent,
               wxWindowID id = wxID_ANY,
               const int *attribList = NULL,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const wxPalette& palette = wxNullPalette);

    bool Create(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxGLCanvasName,
                const int *attribList = NULL,
                const wxPalette& palette = wxNullPalette);

    virtual bool SwapBuffers() wxOVERRIDE;

    // static bool ConvertWXAttrsToQtGL(const int *wxattrs, QGLFormat &format);

    GtkGLArea *GetGLArea() const { return GTK_GL_AREA(m_glArea); }

private:
    GtkWidget *m_glArea;

    DECLARE_CLASS(wxGLCanvas)
};

#endif // !GTK_CHECK_VERSION(3,16,0)

#endif // _WX_GLCANVAS_H_

