// FCTree.h
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

#ifndef __FCTREE_H
#define __FCTREE_H

#include <string>
#include <iostream>
#include <ostream>
#include <vector>

enum {FC_NW, FC_NE, FC_SE, FC_SW};

using namespace std;

class FCTree {
    private:
        friend std::ostream& operator<<(std::ostream& os, const FCTree& t)
        {
            //return os << p.first << ' ' << p.last;
            if (t.leaf) {
                return os << "{" << t.value << "}";
            } else {
                return os << "{"  << t.titles[0] << " " << t.children[0]
                          << ", " << t.titles[1] << " " << t.children[1]
                          << ", " << t.titles[2] << " " << t.children[2]
                          << ", " << t.titles[3] << " " << t.children[3] << "}";
            }
        }

    public:
        // Valid for all nodes
        bool leaf;
        string title;  // Displayed while navigating menu
        string id;  // Used for keyboard shortcuts
        unsigned int shortcut;

        // Valid for interior nodes
        vector<FCTree> children;

        // Valid for leaf nodes
        void *data;
        (void *)callback(void *d);

        // Leaf constructor
        FCTree(string title="", string id="", unsigned int shortcut=0,
                void *data=NULL, (void *)callback(void *d)=NULL)
            : title(title), id(id), shortcut(shortcut), data(data),
            callback(callback), leaf(true) {}
        // Interior constructor
        FCTree(string title, string id, unsigned int shortcut,
                FCTree nw, FCTree ne, FCTree se, FCTree sw);
};

#endif
