// popup.cpp
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
#include "../src/Fl_5C_Popup_Window.h"
#include "../src/Fl_5C_Tree.h"
using namespace std;

class MyWindow : public Fl_Window
{
public:
    MyWindow(int x, int y, int w, int h, const char* l)
    : Fl_Window(x, y, w, h, l) {}

    int handle(int event);
};

void cb(Fl_Widget* w, void* data)
{
    printf("item = %s\n", (const char*)data);
}

Fl_5C_Item items[] =
{
    {"File"},
        {"New",  0, 0, cb, (void*)"New",  true},
        {"Open", 0, 0, cb, (void*)"Open", true},
        FL_5C_EMPTY_ITEM,
//      {"Save", 0, 0, cb, (void*)"Save", true},
        {"Exit", 0, 0, cb, (void*)"Exit", true},
    {"Edit", 0, 0, cb, (void*)"Edit", true},
    {"View", 0, 0, cb, (void*)"View", true},
    {"Help", 0, 0, cb, (void*)"Help", true},
};

int MyWindow::handle(int event)
{
    static Fl_5C_Tree tree(items);
    if (event == FL_PUSH && Fl::event_button() == 3){
        fl_popup_5c_window(&tree);
    }
}

int main(int argc, char* argv[])
{
    // test popping up a 5corners window
    MyWindow window(0, 0, 640, 480, "Popup Test");
    window.show(argc, argv);
    Fl::run();
}
