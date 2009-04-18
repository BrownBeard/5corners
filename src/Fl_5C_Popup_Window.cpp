// Fl_5C_Popup_Window.cpp
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

#include <cstdio>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "Fl_5C_Popup_Window.h"
//#include "Fl_5C_Tree.h"
using namespace std;

// struct Fl_5C_Popup_Window::Impl {{{
struct Fl_5C_Popup_Window::Impl
{
    Fl_5C_Tree* tree;
    Fl_5C_Item* selection;
};
// }}}
// Fl_5C_Popup_Window::Fl_5C_Popup_Window(x, y, w, h, l) {{{
Fl_5C_Popup_Window::Fl_5C_Popup_Window(int x, int y, int w, int h,
                                       const char* l)
: Fl_5C_Trap_Window(x, y, w, h, l)
{
    impl = new Impl;
    impl->tree = 0;
    impl->selection = 0;
}
// }}}
// Fl_5C_Popup_Window::~Fl_5C_Popup_Window() {{{
Fl_5C_Popup_Window::~Fl_5C_Popup_Window()
{
    delete impl;
}
// }}}
// Fl_5C_Popup_Window::clearTree() {{{
void Fl_5C_Popup_Window::clearTree()
{
    impl->tree = 0;
}
// }}}
// Fl_5C_Popup_Window::getTree() {{{
Fl_5C_Tree* Fl_5C_Popup_Window::getTree()
{
    return impl->tree;
}
// }}}
// Fl_5C_Popup_Window::draw() {{{
void Fl_5C_Popup_Window::draw()
{
    // draw the outline
    fl_color(FL_WHITE);
    fl_rectf(0, 0, w(), h());
    fl_color(FL_BLACK);
    fl_rect(0,       0,       w() / 2, h() / 2);
    fl_rect(w() / 2, 0,       w() / 2, h() / 2);
    fl_rect(0,       h() / 2, w() / 2, h() / 2);
    fl_rect(w() / 2, h() / 2, w() / 2, h() / 2);
}
// }}}
// Fl_5C_Popup_Window::handle(event) {{{
int Fl_5C_Popup_Window::handle(int event)
{
    // let Fl_5C_Trap_Window trap the pointer
    if (Fl_5C_Trap_Window::handle(event)) return 1;



    return 0;
}
// }}}
// Fl_5C_Popup_Window::popup() {{{
Fl_5C_Item* Fl_5C_Popup_Window::popup()
{
    border(0);
    hotspot(this);
    show();
    while (shown()){
        Fl::wait();
    }
    return impl->selection;
}
// }}}
// Fl_5C_Popup_Window::setTree() {{{
void Fl_5C_Popup_Window::setTree(Fl_5C_Tree* tree)
{
    impl->tree = tree;
}
// }}}

// fl_popup_5c_window(tree) {{{
Fl_5C_Item* fl_popup_5c_window(Fl_5C_Tree* tree)
{
    Fl_5C_Popup_Window window(0, 0, 320, 240, "5Corners");
    window.setTree(tree);
    return window.popup();
}
// }}}
