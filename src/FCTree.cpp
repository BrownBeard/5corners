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

#include "FCTree.h"

using namespace std;

FCTree::FCTree(string nws, FCTree nwt, string nes, FCTree net,
               string ses, FCTree set, string sws, FCTree swt) {
    leaf = false;
    titles = vector<string>();
    titles.push_back(nws);
    titles.push_back(nes);
    titles.push_back(ses);
    titles.push_back(sws);
    children = vector<FCTree>();
    children.push_back(nwt);
    children.push_back(net);
    children.push_back(set);
    children.push_back(swt);
}
