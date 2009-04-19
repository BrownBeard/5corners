#include "../src/Fl_5C_Tree.h"
#include <iostream>

using namespace std;

int main() {
    Fl_5C_Item items[] = {
        { "File", "" },
          { "File1", "F1", 0, 0, 0, true },
          { "File2", "F2", 0, 0, 0, true },
          { "File3", "F3", 0, 0, 0, true },
          { "File4", "F4", 0, 0, 0, true },
        { "Edit", "" },
          { "Edit1", "E1", 0, 0, 0, true },
          { "Edit2", "E2", 0, 0, 0, true },
          { "Edit3", "E3", 0, 0, 0, true },
          { "Edit4", "E4", 0, 0, 0, true },
        { "Worthless", "W", 0, 0, 0, true },
        { "Stupid", "S", 0, 0, 0, true }
    };

    Fl_5C_Tree t(items);
    t.loadConfig("conftest");

    cout << t << endl;
    cout << 97 << "->" << t.getShortcutNode('a') << endl;
    cout << (FL_CTRL | 98) << "->" << t.getShortcutNode(FL_CTRL | 'b') << endl;
    cout << 108 << "->" << t.getShortcutNode('l') << endl;

    return 0;
}
