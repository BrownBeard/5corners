// editor.cpp
// Copyright (C) 2009 Sam Bateman, Adam Seyfarth
// samuel.bateman@gmail.com
// adam.seyfarth@gmail.com
//
// This file is part of 5 Corners.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Window.H>
#include "../src/Fl_5C_Popup_Window.h"
#include "../src/Fl_5C_Tree.h"
using namespace std;

class MyWindow;

// global variables
MyWindow* window;
Fl_5C_Tree* tree;
Fl_Text_Editor* editor;
Fl_Text_Buffer* buffer;
string current_file;

// class MyWindow {{{
class MyWindow : public Fl_Window
{
public:
    MyWindow(int x, int y, int w, int h, const char* l)
    : Fl_Window(x, y, w, h, l) {}

    int handle(int event);
};
// }}}
// MyWindow::handle(event) {{{
int MyWindow::handle(int event)
{
    // handle right clicks
    if (event == FL_PUSH && Fl::event_button() == 3){
        fl_popup_5c_window(tree);
        return 1;
    }

    // it's kind of weird that we need this...
    for (int i = 0; i < children(); ++i){
        if (child(i)->handle(event)) return 1;
    }
    return 0;
}
// }}}

// Callback functions {{{
// new_cb() {{{
void new_cb(Fl_Widget*, void*)
{
    buffer->remove(0, buffer->length());
}
// }}}
// open_cb() {{{
void open_cb(Fl_Widget*, void*)
{
    const char* chosen = fl_file_chooser("Open File", NULL, NULL);
    if (!chosen) return;
    if (buffer->loadfile(chosen) == 0) current_file = chosen;
    else fl_alert("%s", strerror(errno));
}
// }}}
// saveas_cb() {{{
void saveas_cb(Fl_Widget*, void*)
{
    const char* chosen = fl_file_chooser("Save File", NULL, NULL);
    if (!chosen) return;
    if (buffer->savefile(chosen) == 0) current_file = chosen;
    else fl_alert("%s", strerror(errno));
}
// }}}
// save_cb() {{{
void save_cb(Fl_Widget* w, void* d)
{
    if (current_file == "") saveas_cb(w, d);
    else if (buffer->savefile(current_file.c_str()) != 0){
        fl_alert("%s", strerror(errno));
    }
}
// }}}
// cut_cb() {{{
void cut_cb(Fl_Widget*, void*)
{
    Fl_Text_Editor::kf_cut(0, editor);
}
// }}}
// copy_cb() {{{
void copy_cb(Fl_Widget*, void*)
{
    Fl_Text_Editor::kf_copy(0, editor);
}
// }}}
// paste_cb() {{{
void paste_cb(Fl_Widget*, void*)
{
    Fl_Text_Editor::kf_paste(0, editor);
}
// }}}
// quit_cb() {{{
void quit_cb(Fl_Widget*, void*)
{
    exit(0);
}
// }}}
// }}}

// main(argc, argv) {{{
int main(int argc, char** argv)
{
    // create the 5 Corners tree
    Fl_5C_Item items[] =
    {
        {"File"},
            {"New",     0, FL_CTRL |            'n', new_cb,    0, true},
            {"Open",    0, FL_CTRL |            'o', open_cb,   0, true},
            {"Save",    0, FL_CTRL |            's', save_cb,   0, true},
            {"Save As", 0, FL_CTRL | FL_SHIFT | 's', saveas_cb, 0, true},
        {"Edit"},
            {"Cut",   0, FL_CTRL | 'x', cut_cb,   0, true},
            {"Copy",  0, FL_CTRL | 'c', copy_cb,  0, true},
            {"Paste", 0, FL_CTRL | 'v', paste_cb, 0, true},
            FL_5C_EMPTY_ITEM,
        FL_5C_EMPTY_ITEM,
        {"Quit", 0, FL_CTRL | 'q', quit_cb, 0, true},
    };
    tree = new Fl_5C_Tree(items);

    // create the editor
    buffer = new Fl_Text_Buffer;
    editor = new Fl_Text_Editor(0, 0, 640, 480);
    editor->buffer(buffer);
    editor->textfont(FL_COURIER);

    // create the window
    window = new MyWindow(0, 0, 640, 480, "5 Corners Text Editor");
    window->add(editor);
    window->end();
    window->resizable(editor);
    window->show(argc, argv);
    Fl::run();
}
// }}}
