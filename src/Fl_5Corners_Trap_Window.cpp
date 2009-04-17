// Fl_5Corners_Trap_Window.cpp
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
#include <FL/Fl_Window.H>
#include <FL/x.H>
#include "Fl_5Corners_Trap_Window.h"
using namespace std;

// Fl_5Corners_Trap_Window::handle(event) {{{
int Fl_5Corners_Trap_Window::handle(int event)
{
    if (event == FL_ENTER){
        // hooray for simple solutions
        XGrabPointer(fl_display, fl_xid(this), True,
                     ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                     GrabModeAsync, GrabModeAsync, fl_xid(this),
                     None, CurrentTime);
        return 1;
    }
    return 0;
}
// }}}
