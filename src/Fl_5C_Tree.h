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

//! Holds the root of the tree, handles shortcut information.
class Fl_5C_Tree {
private:
    Fl_5C_Node *root; //!< The root node of the tree.
    unordered_map<unsigned long, Fl_5C_Node *> shortcut_table; //!< Maps keys to nodes

    vector<Fl_5C_Item> getItems(Fl_5C_Node *node);

public:
    Fl_5C_Tree(Fl_5C_Item *items);
    void clear();
    void setItems(Fl_5C_Item *items);
    vector<Fl_5C_Item> getItems();
    Fl_5C_Node *getRootNode() const;
    Fl_5C_Node *getShortcutNode(unsigned long shortcut);
    void loadConfig(const char *name);
};

//! Holds the data for a node.
struct Fl_5C_Item {
    const char *label; //!< String displayed on screen during navigation.
    const char *shortcut_id; //!< String used for shortcut changing from config files.
    unsigned long shortcut; //!< Key combination that activates this item.  Put into table from buildNode().
                            //!
                            //! \see buildNode()
    Fl_Callback *callback; //!< Action that occurs when this is clicked, if leaf.
    void *user_data; //!< Passed into the callback.
    bool leaf; //!< True if this is a leaf node.
               //!
               //! \see buildNode()
};

#define FL_5C_EMPTY_LABEL "__empty__"
#define FL_5C_EMPTY_ITEM {FL_5C_EMPTY_LABEL, 0, 0, 0, 0, true}

//! Has an item, parent and children.  Upholds tree structure.
struct Fl_5C_Node {
    Fl_5C_Item item; //!< The data for this node.
    vector<Fl_5C_Node *> children; //!< Empty if leaf node.
    Fl_5C_Node *parent; //!< Node to whom this is a child.
};

std::ostream& operator<<(std::ostream& os, const Fl_5C_Node& n);
std::ostream& operator<<(std::ostream& os, const Fl_5C_Tree& t);

#endif
