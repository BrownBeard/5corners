// Fl_5C_Trap_Window.h
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

#ifndef _5C_FL_5C_TRAP_WINDOW_H
#define _5C_FL_5C_TRAP_WINDOW_H

#include <FL/Fl_Window.H>

// class Fl_5C_Trap_Window {{{
class Fl_5C_Trap_Window : public Fl_Window
{
public:
    // constructor
    Fl_5C_Trap_Window(int x, int y, int w, int h, const char* l = 0)
    : Fl_Window(x, y, w, h, l) {}

    // subclasses implement this and call Fl_5C_Trap_Window::handle()
    // to trap the mouse
    int handle(int event) = 0;
};
// }}}

#endif  // _5C_FL_5C_TRAP_WINDOW_H
