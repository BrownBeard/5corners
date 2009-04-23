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
#include <cstring>
#include <vector>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "Fl_5C_Popup_Window.h"
#include "Fl_5C_Tree.h"
using namespace std;

#define IS_EMPTY_ITEM(item) (strcmp((item).label, FL_5C_EMPTY_LABEL) == 0)
#define SELECT_ITEM(item) { impl->selection = (item); hide(); return 1; }

// struct Fl_5C_Popup_Window::Impl {{{
struct Fl_5C_Popup_Window::Impl
{
    Fl_5C_Tree* tree;
    Fl_5C_Item* selection;
    Fl_5C_Node* current_node;
    int highlighted;
};
// }}}
// Fl_5C_Popup_Window::Fl_5C_Popup_Window(x, y, w, h, l) {{{
//! @brief Constructor.
//!
//! See the FLTK documentation for a description of the parameters.
Fl_5C_Popup_Window::Fl_5C_Popup_Window(int x, int y, int w, int h,
                                       const char* l)
: Fl_5C_Trap_Window(x, y, w, h, l)
{
    impl = new Impl;
    impl->tree = 0;
    impl->selection = 0;
    impl->current_node = 0;
    impl->highlighted = 0;
}
// }}}
// Fl_5C_Popup_Window::~Fl_5C_Popup_Window() {{{
//! @brief Destructor.
Fl_5C_Popup_Window::~Fl_5C_Popup_Window()
{
    delete impl;
}
// }}}
// Fl_5C_Popup_Window::clearTree() {{{
//! @brief Clears the tree.
//!
//! Same as setTree(NULL).
void Fl_5C_Popup_Window::clearTree()
{
    setTree(0);
}
// }}}
// Fl_5C_Popup_Window::getTree() {{{
//! @brief Gets the tree.
//! @return The tree passed to setTree().
Fl_5C_Tree* Fl_5C_Popup_Window::getTree()
{
    return impl->tree;
}
// }}}
// Fl_5C_Popup_Window::draw() {{{
//! @brief Draws the contents of the window.
void Fl_5C_Popup_Window::draw()
{
    if (!impl->current_node) return;

    // draw the outline
    fl_color(FL_WHITE);
    fl_rectf(0, 0, w(), h());
    fl_color(FL_BLACK);
    fl_rect(0,       0,       w() / 2, h() / 2);
    fl_rect(w() / 2, 0,       w() / 2, h() / 2);
    fl_rect(0,       h() / 2, w() / 2, h() / 2);
    fl_rect(w() / 2, h() / 2, w() / 2, h() / 2);

    // draw the four subnodes
    fl_font(FL_TIMES, 20);
    for (size_t i = 0; i < 4; ++i){
        Fl_5C_Item& item = impl->current_node->children[i]->item;
        int x = (i == 0 || i == 3) ? 0 : w() / 2;
        int y = (i == 0 || i == 1) ? 0 : h() / 2;
        if (IS_EMPTY_ITEM(item)){
            // empty item, draw a gray box
            fl_color(FL_BLACK);
            fl_rectf(x + 1, y + 1, w() / 2 - 2, h() / 2 - 2);
        }
        else {
            // non-empty item, draw the text and possibly highlighting
            if (impl->highlighted == i){
                fl_color(0xff, 0xff, 0xaa);
                fl_rectf(x + 1, y + 1, w() / 2 - 2, h() / 2 - 2);
            }
            fl_color(FL_BLACK);
            fl_draw(item.label, x, y, w() / 2, h() / 2, FL_ALIGN_CENTER);
        }
    }
}
// }}}
// Fl_5C_Popup_Window::handle(event) {{{
//! @brief Handles events.
//! @param event FLTK event to handle.
//! @return 1 if handled, 0 otherwise.
//!
//! Handles events like mouse clicks and movements to navigate through the
//! tree.
int Fl_5C_Popup_Window::handle(int event)
{
    // don't do anything if we don't have a tree
    if (!impl->tree) SELECT_ITEM(0);

    // let Fl_5C_Trap_Window trap the pointer
    if (Fl_5C_Trap_Window::handle(event)) return 1;

    // FL_FOCUS {{{
    if (event == FL_FOCUS){
        // we need this to receive shortcut events
        return 1;
    }
    // }}}
    // FL_SHORTCUT {{{
    else if (event == FL_SHORTCUT){
        // see if a tree item uses this shortcut
        unsigned long shortcut = Fl::event_key();
        if (Fl::event_ctrl ()) shortcut |= FL_CTRL;
        if (Fl::event_alt  ()) shortcut |= FL_ALT;
        if (Fl::event_shift()) shortcut |= FL_SHIFT;
        Fl_5C_Node* node = impl->tree->getShortcutNode(shortcut);
        if (node) SELECT_ITEM(&(node->item));
    }
    // }}}
    // FL_MOVE {{{
    else if (event == FL_MOVE){
        // highlight the appropriate corner
        int i = (Fl::event_x() > w() / 2) ? 1 : 0;
        int j = (Fl::event_y() > h() / 2) ? 1 : 0;
        impl->highlighted = j * 2 + (j ? 1 - i : i);
        redraw();
        return 1;
    }
    // }}}
    // FL_PUSH {{{
    else if (event == FL_PUSH){
        // Left click {{{
        if (Fl::event_button() == 1){
            Fl_5C_Node* node = impl->current_node->children[impl->highlighted];
            if (!IS_EMPTY_ITEM(node->item)){
                if (node->item.leaf){
                    // leaf node, select this one
                    SELECT_ITEM(&(node->item));
                }
                else {
                    // non-leaf node, descend the tree
                    impl->current_node = node;
                    redraw();
                }
            }
        }
        // }}}
        // Right click {{{
        else if (Fl::event_button() == 3){
            if (impl->current_node == impl->tree->getRootNode()){
                // highest level, exit the popup window
                SELECT_ITEM(0);
            }
            else {
                // ascend to a higher level
                impl->current_node = impl->current_node->parent;
                redraw();
            }
        }
        // }}}
        return 1;
    }
    // }}}

    return 0;
}
// }}}
// Fl_5C_Popup_Window::popup() {{{
//! @brief Pops up the window.
//! @return The item that was selected, or NULL if nothing was selected.
//!
//! Displays a popup 5 Corners window with the selection tree.  Left click on
//! an item to select the item or to its subtree.  Right click to go back up
//! the tree.  If no tree has been set with setTree() or the user right-clicks
//! out of the tree, the function returns NULL.
Fl_5C_Item* Fl_5C_Popup_Window::popup()
{
    if (!impl->tree) return 0;
    border(0);
    hotspot(this);
    show();
    take_focus();
    set_modal();
    while (shown()){
        Fl::wait();
    }
    return impl->selection;
}
// }}}
// Fl_5C_Popup_Window::setTree(tree) {{{
//! @brief Sets the tree.
//! @param tree Pointer to the tree to use.
//!
//! Sets the tree used by the popup window.  NULL is valid.
void Fl_5C_Popup_Window::setTree(Fl_5C_Tree* tree)
{
    impl->tree = tree;
    impl->current_node = tree ? tree->getRootNode() : 0;
}
// }}}

// fl_popup_5c_window(tree) {{{
//! @brief Pops up a 5 Corners window.
//! @param tree Tree to use in the window.
//!
//! Displays an Fl_5C_Popup_Window with the given tree.  If an item is
//! selected, its callback is called.  Otherwise, nothing happens.
void fl_popup_5c_window(Fl_5C_Tree* tree)
{
    Fl_5C_Popup_Window window(0, 0, 320, 240, "5Corners");
    window.setTree(tree);
    Fl_5C_Item* item = window.popup();
    if (!item) return;
    if (item->callback) item->callback(&window, item->user_data);
}
// }}}
