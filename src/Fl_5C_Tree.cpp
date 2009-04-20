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
#include <cstring>
#include "Fl_5C_Tree.h"

using namespace std;
using namespace tr1;

//! Has a node pointer and items array.
/*!
 * \see buildNode()
 */
struct NodeItems {
    Fl_5C_Node *node;
    Fl_5C_Item *items;
};

//! Print a node.  Only really useful for debugging.
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

//! Print a tree.  Only really useful for debugging.
std::ostream& operator<<(std::ostream& os, const Fl_5C_Tree& t) {
    return os << *(t.getRootNode()->children[0]) << endl <<
                 *(t.getRootNode()->children[1]) << endl <<
                 *(t.getRootNode()->children[2]) << endl <<
                 *(t.getRootNode()->children[3]);
}

//! Parse items array, building a node, filling its children if necessary.
/*!
 * \param items The items array.
 * \param table The shortcuts table.
 * \return The node that was built, and the remaining items in the array.
 *
 * If the first of items is a leaf, then return that node, and the rest of the
 * items array.  Otherwise, the first item makes the item of the node that
 * will be returned, and its children will be built using buildNode 4 more
 * times.
 */
NodeItems buildNode(Fl_5C_Item *items,
                    unordered_map<unsigned long, Fl_5C_Node *>& table) {
    NodeItems ni;
    NodeItems res;

    if (items[0].shortcut != 0) {
        table[items[0].shortcut] = ni.node;
    }

    ni.items = items+1;
    ni.node = new Fl_5C_Node;
    ni.node->item = items[0];

    if (items[0].leaf) {
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

//! Constructor.
/*!
 * \see setItems()
 */
Fl_5C_Tree::Fl_5C_Tree(Fl_5C_Item *items) {
    root = NULL;
    setItems(items);
}

//! Clears the data, if there is any.
void Fl_5C_Tree::clear() {
    if (root) delete root;
}

//! Initialize a tree from an array of items.
/*!
 * \param items Array of items.
 *
 * Uses buildNode 4 times, for each of the four top-level nodes.  There should
 * not be a root node in the items array passed to this function.
 *
 * \see buildNode()
 * \see Fl_5C_Tree()
 */
void Fl_5C_Tree::setItems(Fl_5C_Item *items) {
    Fl_5C_Item *remaining = items;
    NodeItems res;
    clear();
    root = new Fl_5C_Node;
    root->item.label = "";
    root->item.shortcut_id = "";
    for (int i = 0; i < 4; i++) {
        res = buildNode(remaining, shortcut_table);
        res.node->parent = root;
        root->children.push_back(res.node);
        remaining = res.items;
    }
}

//! Return the items in the node, in a vector.
/*!
 * \param node The node of interest.
 * \return Items from this node down, in a vector.
 *
 * If the node has no children (item is a leaf), then merely return the node's
 * item in a vector of length one.  Otherwise, return a vector with the node's
 * item, and the concatenated results of getItems applied to each of the
 * node's children.
 */
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

//! Just calls the same function on the root node.  Visible from the outside.
vector<Fl_5C_Item> Fl_5C_Tree::getItems() {
    return getItems(root);
}

//! Accessor
Fl_5C_Node *Fl_5C_Tree::getRootNode() const {
    return root;
}

//! If key is a shortcut, return the corresponding node.
Fl_5C_Node *Fl_5C_Tree::getShortcutNode(unsigned long shortcut) {
    if (shortcut_table.find(shortcut) == shortcut_table.end()) {
        return NULL;
    } else {
        return shortcut_table[shortcut];
    }
}

//! Put the shortcut-node combo into the table if the right node is below this one.
/*!
 * \param shortcut The key combination.
 * \param lbl The string identifying which node.
 * \param node The current node.
 * \param table The shortcuts table.
 *
 * If the current node's item has the right label, then update the table with
 * the current node.  Otherwise, run insertShortcut on all of the children.
 */
void insertShortcut(unsigned long shortcut,
                    char *lbl,
                    Fl_5C_Node *node,
                    unordered_map<unsigned long, Fl_5C_Node *>& table) {
    if (strcmp(node->item.shortcut_id, lbl) == 0) {
        table[shortcut] = node;
    } else {
        for (vector<Fl_5C_Node *>::iterator i = node->children.begin();
                i != node->children.end();
                i++) {
            insertShortcut(shortcut, lbl, *i, table);
        }
    }
}

//! Read the config file, looking for shortcut instructions.
void Fl_5C_Tree::loadConfig(const char *name) {
    char filename_before[FL_PATH_MAX], filename_after[FL_PATH_MAX];
    char line[256];
    int pos, i;
    char cmd[256];
    char *args;
    char *tok;
    char space[] = " \t";
    char lbl[256];
    unsigned long shortcut;
    ifstream f;

    strcpy(filename_before, "~/.5corners/");
    strcat(filename_before, name);
    fl_filename_expand(filename_after, filename_before);

    f.open(filename_after);
    if (!f.is_open()) {
        return;
    }

    while (true) {
        f.getline(line, 256);
        if (f.eof()) break;
        pos = strcspn(line, space);
        strncpy(cmd, line, pos);
        cmd[pos] = '\0';
        if (strcmp(cmd, "shortcut") == 0) {
            args = strchr(line, '"') + 1;
            lbl[0] = '\0';
            for (i = 0; args[i] != 0; i++) {
                if (args[i] == '\\') {
                    strncat(lbl, args + ++i, 1);
                } else if (args[i] == '"') {
                    break;
                } else {
                    strncat(lbl, args + i, 1);
                }
            }

            shortcut = 0;
            tok = strtok(args+i+1, space);
            while (tok != NULL) {
                if (strcmp(tok, "CTRL") == 0) {
                    shortcut |= FL_CTRL;
                } else if (strcmp(tok, "ALT") == 0) {
                    shortcut |= FL_ALT;
                } else if (strcmp(tok, "SHIFT") == 0) {
                    shortcut |= FL_SHIFT;
                } else {
                    shortcut |= tok[0];
                }

                tok = strtok(NULL, space);
            }

            insertShortcut(shortcut, lbl, root, shortcut_table);
        }
    }

    f.close();
}
