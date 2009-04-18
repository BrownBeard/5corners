// FCTree.cpp
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

#include <cassert>
#include "Fl_5C_Tree.h"

using namespace std;
using namespace tr1;

struct NodeItems {
    Fl_5C_Node *node;
    Fl_5C_Item *items;
};


std::ostream& operator<<(std::ostream& os, const Fl_5C_Node& n) {
    if (n.item.leaf) {
        return os << n.item.label << " {}";
    } else {
        return os << n.item.label << " {" << *n.children[0]
            << ", " << *n.children[1]
            << ", " << *n.children[2]
            << ", " << *n.children[3] << "}";
    }
}

std::ostream& operator<<(std::ostream& os, const Fl_5C_Tree& t) {
    return os << *(t.getRootNode()->children[0]) << endl <<
                 *(t.getRootNode()->children[1]) << endl <<
                 *(t.getRootNode()->children[2]) << endl <<
                 *(t.getRootNode()->children[3]);
}

NodeItems buildNode(Fl_5C_Item *items,
                    unordered_map<unsigned long, Fl_5C_Node *>& table) {
    NodeItems ni;
    NodeItems res;

    cout << "buildNode .. " << items[0].label << endl;

    if (items[0].shortcut != 0) {
        table[items[0].shortcut] = ni.node;
    }

    ni.items = items+1;
    ni.node = new Fl_5C_Node;
    ni.node->item = items[0];

    if (items[0].leaf) {
        cout << "leaf" << endl;
        return ni;
    }

    for (int i = 0; i < 4; i++) {
        res = buildNode(ni.items, table);
        res.node->parent = ni.node;
        ni.node->children.push_back(res.node);
        ni.items = res.items;
    }

    return ni;
}

Fl_5C_Tree::Fl_5C_Tree(Fl_5C_Item *items) {
    root = NULL;
    setItems(items);
}

void Fl_5C_Tree::clear() {
    delete root;
}

void Fl_5C_Tree::setItems(Fl_5C_Item *items) {
    Fl_5C_Item *remaining = items;
    NodeItems res;
    clear();
    root = new Fl_5C_Node;
    root->item.label = "";
    for (int i = 0; i < 4; i++) {
        res = buildNode(remaining, shortcut_table);
        res.node->parent = root;
        root->children.push_back(res.node);
        remaining = res.items;
    }

}

vector<Fl_5C_Item> Fl_5C_Tree::getItems(Fl_5C_Node *node) {
    vector<Fl_5C_Item> retval, res;

    if (node->item.leaf) {
        retval.push_back(node->item);
        return retval;
    }

    retval.push_back(node->item);
    for (vector<Fl_5C_Node *>::iterator i = node->children.begin(); i != node->children.end(); i++) {
        res = getItems(*i);
        retval.insert(retval.end(), res.begin(), res.end());
    }

    return retval;
}

vector<Fl_5C_Item> Fl_5C_Tree::getItems() {
    return getItems(root);
}

Fl_5C_Node *Fl_5C_Tree::getRootNode() const {
    return root;
}

Fl_5C_Node *Fl_5C_Tree::getShortcutNode(unsigned long shortcut) {
    if (shortcut_table.find(shortcut) == shortcut_table.end()) {
        return NULL;
    } else {
        return shortcut_table[shortcut];
    }
}

void loadConfig(const string &name) {
    char filename[FL_PATH_MAX];
    char line[256];
    int tmp;

    fl_filename_expand(filename, ("~/.5corners/" + name).c_str());

    ifstream f(filename);

    while (true) {
        f.getline(line, 256);
        if (f.eof()) break;
        cout << line << endl;
    }
}
