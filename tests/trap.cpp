// trap.cpp
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

#include <FL/Fl.H>
#include "../src/Fl_5C_Trap_Window.h"
using namespace std;

// because Fl_5Corners_Trap_Window is abstract, we need this class
class MyTrapWindow : public Fl_5C_Trap_Window
{
public:
    MyTrapWindow(int x, int y, int w, int h, const char* l)
    : Fl_5C_Trap_Window(x, y, w, h, l) {}

    int handle(int event) { return Fl_5C_Trap_Window::handle(event); }
};

int main(int argc, char* argv[])
{
    // test trapping the mouse inside a window
    MyTrapWindow window(0, 0, 640, 480, "Trap Test");
    window.show(argc, argv);
    Fl::run();
}
