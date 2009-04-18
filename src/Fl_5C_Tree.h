// Fl_5C_Tree.h
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

#ifndef __FL_5C_TREE_H
#define __FL_5C_TREE_H

#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <tr1/unordered_map>
#include <FL/Fl.H>
#include <FL/filename.H>
#include <FL/Fl_Widget.H>

using namespace std;
using namespace tr1;

enum {FL_5C_NW, FL_5C_NE, FL_5C_SE, FL_5C_SW};

struct Fl_5C_Node;
struct Fl_5C_Item;

class Fl_5C_Tree {
private:
    Fl_5C_Node *root;
    unordered_map<unsigned long, Fl_5C_Node *> shortcut_table;

    vector<Fl_5C_Item> getItems(Fl_5C_Node *node);

public:
    Fl_5C_Tree(Fl_5C_Item *items);
    void clear();
    void setItems(Fl_5C_Item *items);
    vector<Fl_5C_Item> getItems();
    Fl_5C_Node *getRootNode() const;
    Fl_5C_Node *getShortcutNode(unsigned long shortcut);
    void loadConfig(string name);
};

struct Fl_5C_Item {
    const char *label;
    const char *shortcut_id;
    unsigned long shortcut;
    Fl_Callback *callback;
    void *user_data;
    bool leaf;
};

#define FL_5C_EMPTY_ITEM {"__empty__", 0, 0, 0, 0, true}

struct Fl_5C_Node {
    Fl_5C_Item item;
    vector<Fl_5C_Node *> children;
    Fl_5C_Node *parent;
};

std::ostream& operator<<(std::ostream& os, const Fl_5C_Node& n);
std::ostream& operator<<(std::ostream& os, const Fl_5C_Tree& t);

#endif
