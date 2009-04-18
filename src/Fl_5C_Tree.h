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
#include <vector>
#include <tr1/unordered_map>

enum {FL_5C_NW, FL_5C_NE, FL_5C_SE, FL_5C_SW};

using namespace std;

class Fl_5C_Tree {
private:
    Fl_5C_Node *root;
    tr1::unordered_map<unsigned long, Fl_5C_Node *> shortcut_table;

    Fl_5C_Node *buildNode(Fl_5C_Item *items);
    vector<Fl_5C_Item> getItems(Fl_5C_Node *node);

public:
    Fl_5C_Tree(Fl_5C_Item *items);
    void clear();
    void setItems(Fl_5C_Item *items);
    vector<Fl_5C_Item> getItems();
    Fl_5C_Node *getRootNode();
    Fl_5C_Node *getShortcutNode(unsigned long shortcut);
    void loadConfig(string file);
};

struct Fl_5C_Node {
    Fl_5C_Item item;
    vector<Fl_5C_Node *> children;
};

struct Fl_5C_Item {
    const char *label;
    const char *shortcut_id = NULL;
    unsigned long shortcut = 0;
    Fl_Callback *callback = NULL;
    void *user_data = NULL;
    bool leaf = 0;
};

#endif
